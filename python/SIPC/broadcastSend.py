# Send UDP broadcast packets

MYPORT = 50000

import sys, time #to use time
from socket import *

s = socket(AF_INET, SOCK_DGRAM)#uses IP version 4 and UDP
s.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
s.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)
s.bind(('', MYPORT))
s.setblocking(0)#important!!


while 1:
    data = repr(time.time()) + '\n'
    try:
        s.sendto(data, ('<broadcast>', MYPORT))
    except:
        print "no receivers"
    try:
        data=s.recv(1024)
        print data
    except:
        print "no messages"
    time.sleep(1)
