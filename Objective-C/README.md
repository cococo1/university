Objective-C
==========

Code written in Objective-C during University.

--

**SIPC** contains a lab in Objective-C for **Communication Protocols and Information Security**.

The protocol

This protocol was first derived together with Sveatoslav Persianov, but then modified according to needs of implementation.

What we need:

to send point coordinates (Action 1);

to distinguish somehow users (using colours);

to request others to clear the board (Action 2);

to have a proportional drawing on different screens (using ratio);

What we get:

A message consists of several headers. Each header is separated by /r/n. The end of message is marked by /r/n/r/n. Each header consists of the name of the header (let’s say “Color”, + “ :”+additional info (let’s say r;g;b).

Headers: 

Action – specifies if we send the point, or request to clean the board. Additional info is represented by an int, which can be either 1 or 2.

Color – specifies the id of the user, its colour (since all users have a different colour). Additional info is represented as 3 ints, separated by “;” which indicate the value of r,g,b (0255);

Point – specifies the coordinates of a point as the percent from total width and height of window. Additional info – two floats, with value from 0 to 1;

Ratio – specifies the ratio of the whiteboard screen. A float obtained by totalX/totalY.

Endpoint – (for iOS drawing) specifies if the point is the end point of the curve drawn by the user. Additional info – an int, 0 – false, 1 – true;

Timeout – Specifies the timeout for deciding if the board is cleared or not. An int, indicates the time in seconds;

According to all of the above, only two messages are acceptable :

“Action :%i/r/nColor :%i;%i;%i/r/nRatio :%f/r/nPoint :%f;%f/r/nEndpoint :%i/r/n/r/n” 

and

“Action :%i/r/nColor :%i;%i;%i/r/nTimeout :%i/r/n/r/n” 

--
