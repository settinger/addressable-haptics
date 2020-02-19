#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Variables used below
int timeSinceLastSignal = 0; // Approx. number of milliseconds without receiving a valid signal
int mode = 0;                // 0: idle mode; 1: pass-through mode; 2: receiver mode
int receivedBit = 0;         // What value to transmit when in pass-through mode
int bitsReceived = 0;        // How many bits received in receiver mode
int receivedData = 0;        // Data obtained in receiver mode

void Setup(void) {
	TCCR0A = (3<<COM0B0) | (2<<WGM00) // Datasheet p100; set PB1 (Pin 3) as PWM pin
	TCCR0B = (3<<WGM02) | (2<<CS00)   // Datasheet p103; set PWM behavior, set clock scaler to 125 kHz
	OCR0B = 0;                        // Counter for PWM on PB1 (pin 3)
	ICR0 = 127;                       // Counter resets approx. every millisecond, good for timing
	OCR0A = 63;                       // A nice middle-of-the-range value for timing during PWM
	DDRB = 6<<PORTB0;                 // Datasheet p76; Set PB1 (pin 3) and PB2 (pin 4) as output
	PUEB = 3<<PUEB0;                  // Datasheet p74; set PB0 (pin 1) and PB1 (pin 3) to use internal pullup resistor
	sei();                            // Datasheet p25; enable interrupts
	EIMSK = 1;                        // Datasheet p57; enable external interrupts
	EICRA = 2<<ISC00;                 // Datasheet p56; set external interrupt to detect falling edge
	PCMSK = 1;                        // Datasheet p61; set PB0 (pin 1) as external interrupt pin
}

void idleMode(void) {
	mode = 0;
	timeSinceLastSignal = 0;
	bitsReceived = 0;
	receivedBit = 0;
	receivedData = 0;
}

void passThroughMode(void) {
	mode = 1;
}

void receiverMode(void) {
	mode = 2;
}

void sendSignal(int signal) {
	// If signal is a logical 1: clear PORTB2 for 20 μs, set PORTB2 for 180 μs, exit
	// If signal is a logical 0: clear portB2 for 150 μs, set PORTB2 for 50 μs, exit
	if (signal) {
		PORTB &= 0b1011;
		_delay_us(20);
		PORTB |= 0b0100;
		_delay_us(180);
		} else {
		PORTB &= 0b1011;
		_delay_us(150);
		PORTB |= 0b0100;
		_delay_us(50);
	}
}

int main(void) {
	
	Setup();
	
	while(1) {
		// Check if PB0 (pin 1) has triggered an interrupt
		if (EIFR & (1<<INTF0)) {
			EIFR |= 1<<INTF0; // Clear interrupt flag
			timeSinceLastSignal = 0; // Clear idle timer
			// Wait .1 ms, take reading
			_delay_us(100);
			receivedBit = PINB & 1;
			
			// If we're in idle mode and reading is HIGH: enter pass-through mode
			if (mode == 0 && receivedBit) {
				passThroughMode();
			}
			// If we're in idle mode and reading is LOW: enter receiver mode
			if (mode == 0 && !receivedBit) {
				receiverMode();
			}
			// If we're in pass-through mode: pass through
			if (mode == 1) {
				sendSignal(receivedBit);
			}
			// If we're in receiver mode: add bit to received byte
			if (mode == 2) {
				receivedData |= receivedBit<<bitsReceived;
				bitsReceived++;
				// If we've received seven bits: set OCR0B to the new motor intensity and enter idle mode
				if (bitsReceived >= 7) {
					OCR0B = receivedData;
					idleMode();
				}
			}
		}
		
		// Check if OC0A has ticked over
		if (TIFR0 & (1<<OCF0A)) {
			timeSinceLastSignal++;
			TIFR0 |= 1<<OCF0B; // Clear interrupt flag by writing a 1 to the register
		}
		
		// If we've been idle for approx. 5 milliseconds, enter idle mode
		if (timeSinceLastSignal >= 5) {
			idleMode();
		}
	}
}
