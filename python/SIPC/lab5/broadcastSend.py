# Send UDP broadcast packets

MYPORT = 8167

import sys, time #to use time
from socket import *

s = socket(AF_INET, SOCK_DGRAM)#uses IP version 4 and UDP
s.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
s.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)
s.bind(('', MYPORT))
s.setblocking(0)#important!!


#data="2#Main\0"+"Hameak\0"+"dadada\0" #Send  a message to main
data="4"+"Hameak\0"+"#Main\0"+"00" #Hameak joins the net 
s.sendto(data, ('<broadcast>', MYPORT))

data="1"+"Hameak\0"+"Max\0"+"0"
s.sendto(data, ('<broadcast>', MYPORT))

data="2"+"#Main\0"+"Hameak\0"+"Hello, world!\0" #Hameak talks to main
s.sendto(data, ('<broadcast>', MYPORT))

data="3"+"Hameak\0"+"Hamidze\0"+"0" #Hameak renames as Hamidze
s.sendto(data, ('<broadcast>', MYPORT))

data="B"+"new topic"+"\0"#Hamidze changes the topic
s.sendto(data, ('<broadcast>', MYPORT))


try:
     (data,ad)=s.recvfrom(1024)
     print data
except:
     print "no messages"

data="5Hamidze\0"+"#Main\0"+"0" #Hameak leaves the net
s.sendto(data, ('<broadcast>', MYPORT))


s.close()

