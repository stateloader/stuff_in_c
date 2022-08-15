ABOUT

	A simple Client/Server-interpretation written in C to get a better understanding about the programming-langue,
	embedded programming, hardware and networking.

GENERAL

	The Server runs on a RaspberryPi over my local home-network (for now). It receives requests of type "pull" and "push"
	(anyone's guess what inspired me on this one) from connected clients. Pull-requests will fetch desired data from databases
	and send the entire content back to the client for processing while Push-requests do the opposite; writes/appends data
	created by clients to database(s). The Raspberry itself communicates with a simple Device shining in red, green and blue.

	I've tried to make the source-code somewhat "modular" based on the various states taking place on both client- and server
	-side. At the moment, the client's only able to send/read messages and change which colour (and read "LED-history")
	currently being shone on the device. However, I've tried to make the code scalable why there's quite some (messy) code in
	place for just these few operations =)

	Originally, I wanted to use ATMega328P and write the entire thing in C. In my current IoT-studies we played around with a
	shield earlier this year, solded and plugged it onto an Arduino, while using avr-dude for some sweet embedded programming.
	Hence, In this project I wanted to take it a step further and don't have ANYTHING to with Arduino at all but I just couldn't
	get my hands on the damn chip. Instead it all boiled down to an ESP8266EX (development card "Wemos D1 Mini").

	I've Flashed the "Wemos" using MicroPython. Nothing fancy. It just reads the latest entry in device.dat within a loop while
	current LED-colour is govern based on latest entry stored in this file.
