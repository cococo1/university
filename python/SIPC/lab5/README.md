SIPC lab 5
==========

--
To join the chat: “4”+”<Nickname>\0”+”#Main\0”+”00”;

To send a public message: “2”+”#Main\0”+”<Nickname>\0”+”<Message>\0”;

To send a private message: “6”+”<Nickname_sender>\0”+”<Nickname_receiver>\0” + “<Message>\0”;

To change the nickname: “3”+”<Old_nickname>\0”+”<New_nickname>\0”+”0”;

To change the topic: “B”+”<New_topic>\0”

To join a channel: “4”+”<Nickname>\0”+”<Channel_name>\0”+”00”;

To leave a channel: “5”+”<Nickname>\0 ”+”<Channel_name>\0”+”0”;

To leave the chat: “5”+”<Nickname>\0”+”#Main\0”+”0”;

Other messages are also possible but almost all the functionality of the chat can be implemented used the above messages.
--
