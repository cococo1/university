# Send UDP broadcast packets

MYPORT = 8167

from socket import *

s = socket(AF_INET, SOCK_DGRAM)#uses IP version 4 and UDP
s.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
s.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)


#data="2#Main\0"+"Hameak\0"+"dadada\0" #Send  a message to main
raw_input('Join the net:')
data="4"+"Hameak\0"+"#Main\0"+"00" #Hameak joins the net 
s.sendto(data, ('<broadcast>', MYPORT))

raw_input('Say hello to main:')
data="2"+"#Main\0"+"Hameak\0"+"Hello, world!\0" #Hameak talks to main
s.sendto(data, ('<broadcast>', MYPORT))

raw_input('Rename himself:')
data="3"+"Hameak\0"+"Hamidze\0"+"0" #Hameak renames as Hamidze
s.sendto(data, ('<broadcast>', MYPORT))

raw_input('Change the topic:')
data="B"+"New Topic"+"\0"#Hamidze changes the topic
s.sendto(data, ('<broadcast>', MYPORT))

raw_input('Send a private message from Vlad')
data="6"+"Vlad\0"+"Maxim\0"+"Private message:)\0"#Hamidze sends a private message
s.sendto(data, ('<broadcast>', MYPORT))

raw_input('Change status:')
data="D"+"Hamidze\0"+"00" #Hameak enters in Normal mode
s.sendto(data, ('<broadcast>', MYPORT))
data="D"+"Hamidze\0"+"10" #Hameak enters in DND mode
s.sendto(data, ('<broadcast>', MYPORT))
data="D"+"Hamidze\0"+"20" #Hameak enters in Away mode
s.sendto(data, ('<broadcast>', MYPORT))
data="D"+"Hamidze\0"+"30" #Hameak enters in Offline mode
s.sendto(data, ('<broadcast>', MYPORT))


raw_input('Join a channel:')
data="4"+"Hamidze\0"+"#Wheel Channel\0"+"00" #Hameak creates and joins Wheel Channel
s.sendto(data, ('<broadcast>', MYPORT))

raw_input('leave the channel:')
data="5"+"Hamidze\0"+"#Wheel Channel\0"+"00" #Hameak leaves Wheel Channel
s.sendto(data, ('<broadcast>', MYPORT))

raw_input('leave the net:')
data="5Hamidze\0"+"#Main\0"+"0" #Hameak leaves the net
s.sendto(data, ('<broadcast>', MYPORT))


s.close()

