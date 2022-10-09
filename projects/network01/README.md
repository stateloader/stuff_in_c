ABOUT

		A simple Client/Server interpretation written in C to get a better understanding about the programming-langue, embedded
		programming, hardware and networking.

		The Server runs on a RaspberryPi over my local home-network (for now). It receives requests of type "pull" and "push"
		from connected clients. Pull-requests will fetch desired data from databases and send the entire content back to the
		client for processing while Push-requests do the opposite; writes/appends data created by clients to database(s).

		The Raspberry itself going to be connected to a device shining in red, green or blue in time. For now, however, this
		device isn't in place yet why push commands for swapping LED-colors just ends up as records in a database.

USAGE

		1) Download and unzip the Server and Client folder on different computers within the same LAN.
	
		2) Enter 'make' inside each folder.
	
		3) Enter './serverTCP <IP address> <port>' and the server should be up and running.
	
		4) Enter './clientTCP <IP address> <port>' and you should be able to communicate with the server

		To just test the functionality, do as above but use two terminal windows instead of two computers and run the executables
		over your loopback subnet.
	
		Example:
	
			./serverTCP 127.0.0.1 90190
			./clientTCP 127.0.0.1 90190
