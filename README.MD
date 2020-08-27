# Addressable Haptics

This project aims to make it easy to control long strings of haptic motors (or regular motors, or just about anything) from an Arduino or similar microcontroller. By decentralizing the motor control systems, daisy-chaining the motors and relying on one-wire communication, we drastically cut down on the number of PWM output pins needed.

This project and README are works-in-progress. Expect lots of changes.

## About the circuit

Each motor is accompanied by an ATtiny10 microcontroller that handles the reception, transmission, and decoding of commands. When a valid command is read, the ATtiny10 sets the motor intensity by PWMing an N-channel MOSFET. The ATtiny10 will continue to drive the motor while receiving and transmitting additional commands.

## About the communication protocol

Each chain of motors communicates using one wire, similar to the WS2812 LED system. Unlike the WS2812 LEDs, these motors are controlled individually, without a shift register. I felt that a shift register protocol would not be as useful for haptic motor applications, so I did not implement it.

The coding scheme is simple but I don't know the name for it. A one bit is encoded as LOW for 20 μs, then HIGH for 180 μs. A zero bit is encoded as LOW for 150 μs, then HIGH for 50 μs. When not transferring information, the line is usually HIGH. The actual timing of the bits may change as I continue development, so watch out!

Motors are given unary addresses. The first motor is address _0_, the second is address _10_, the third is _110_, the fourth is _1110_, the _n_th is (_n_-1) 1s followed by a 0. This allows the motor controllers to pass commands down the chain with less latency; however, it creates a strong disincentive for long chains of motors.

Each command is of the form `<address><value>`. The `value` is a 7-bit number that sets the PWM duty cycle for the motor at `address`. So, for example, the command `11101010101` would set motor #4 (that is, the motor with address `1110`) to an intensity of `1010101`, or 85/127.

## Some more detail about the communication protocol

If the first ATtiny10 receives a command that starts with `0`, it knows instantly that the message is intended for it. Similarly, if the first ATtiny10 receives a command that starts with `1`, it knows to pass the message down the line. However, it transmits the message _without the initial bit_. That is, if an ATtiny10 receives the command `101111111`, it would pass along the message `01111111`. This informs the next ATtiny10 in the chain that the command is intended for it.

## Why not just use WS2811 ICs?

1. I wanted to implement my own protocol and learn from the process.
1. I don't know the PWM frequency of the WS2811 and can't change it to suit inductive loads.
1. The shift-register approach doesn't make sense for the applications I envision.
1. I just enjoy using ATtiny10s!