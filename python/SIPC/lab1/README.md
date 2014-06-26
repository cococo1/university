SIPC lab 1
==========

--
To implement the following server and client:

Server requirements:

•	The server must print debug information about each incoming connection, indicating the remote address;

•	The server must implement 5 special commands that can be received from the client, to which the server will react in a special way:

o	%Hastalavista - if the server receives this command, it will terminate the connection and shut itself down;

o	%Time - the server will react by sending the client the current time of the system on which the server is running;

o	The other 3 commands have to be chosen by you;

•	If the server receives an unknown command - it must respond with "Can you elaborate on that? ";

•	If the server receives an unknown command that ends with a '?' - it must respond with "42";

Bonus features

•	The server must be able to handle multiple client connections at the same time;

•	The server supports an additional special command - %Showtime. Upon receiving it, the server will send an image to the client.

--
