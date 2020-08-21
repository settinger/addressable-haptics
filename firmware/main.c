#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Variables used below
volatile int timeSinceLastSignal = 0; // Approx. number of milliseconds without receiving a valid signal
int mode = 0;                // 0: idle mode; 1: pass-through mode; 2: receiver mode
char receivedBit = 0x00;         // What value to transmit when in pass-through mode
int bitsReceived = 0;        // How many bits received in receiver mode
int receivedData = 0;        // Data obtained in receiver mode
volatile int interrupted = 0; // If the interrupt flag is set

void Setup(void) {
	TCCR0A = (3<<COM0B0) | (2<<WGM00); // Datasheet p100; set PB1 (Pin 3) as PWM pin
	TCCR0B = (3<<WGM02) | (2<<CS00);   // Datasheet p103; set PWM behavior, set clock scaler to 125 kHz
	OCR0B = 0;                         // Counter for PWM on PB1 (pin 3)
	ICR0 = 127;                        // Counter resets approx. every millisecond, good for timing
	OCR0A = 63;                        // A nice middle-of-the-range value for timing during PWM
	DDRB = 3<<PORTB0;                  // Datasheet p76; Set PB1 (pin 3) and PB0 (pin 1) as output
	PUEB = 4<<PUEB0;                   // Datasheet p74; set PB2 (pin 4) to use internal pullup resistor
	sei();                             // Datasheet p25; enable interrupts
	EIMSK = 1;                         // Datasheet p57; enable external interrupts
	EICRA |= 2<<ISC00;                 // Datasheet p56; set external interrupt to detect falling edge
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
	timeSinceLastSignal = 0;
	bitsReceived = 0;
	receivedBit = 0;
	receivedData = 0;
}

void receiverMode(void) {
	mode = 2;
}

void sendSignal(char signal) {
	// If signal is a logical 1: clear PORTB0 for 20 μs, set PORTB0 for 180 μs, exit
	// If signal is a logical 0: clear PORTB0 for 150 μs, set PORTB0 for 50 μs, exit
	if (signal) {
		PORTB &= 0b1110;
		_delay_us(20);
		PORTB |= 0b0001;
		_delay_us(180);
	} else {
		PORTB &= 0b1110;
		_delay_us(180);
		PORTB |= 0b0001;
		_delay_us(20);
	}
}

// Check if a falling edge was detected on Pin 4
ISR(INT0_vect) {
	interrupted = 1;
}

int main(void) {
	
	Setup();
	
	while(1) {
		// Check if PB2 (pin 4) has triggered an interrupt
		if (interrupted) {
			interrupted = 0; // Clear interrupt flag
			timeSinceLastSignal = 0; // Clear idle timer
			// Wait .05 ms, take reading
			_delay_us(50);
			receivedBit = PINB & 0b00000100;
			
			// If we're in idle mode and reading is HIGH: enter pass-through mode
			if (mode == 0 && receivedBit) {
				passThroughMode();
			}
			// If we're in idle mode and reading is LOW: enter receiver mode
			else if (mode == 0 && !receivedBit) {
				receiverMode();
			}
			// If we're in pass-through mode: pass through
			else if (mode == 1) {
				sendSignal(receivedBit);
			}
			// If we're in receiver mode: add bit to received byte
			else if (mode == 2) {
				if (receivedBit) {
					receivedData |= 1<<bitsReceived;
				}
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
		if (timeSinceLastSignal >= 500) {
			idleMode();
		}
	}
}
