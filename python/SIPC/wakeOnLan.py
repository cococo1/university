# Send UDP broadcast packets WOL -wake on lan

MYPORT = 7
MACADDRESS='MY Mac address'

import sys, time #to use time
from socket import *

s = socket(AF_INET, SOCK_DGRAM)#uses IP version 4 and UDP
#s.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
s.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)
#s.bind(('', MYPORT))
#s.setblocking(0)#important!!


data='FFFFFFFFFFFF'+MACADDRESS*16

try:
    s.sendto(data, ('<broadcast>', MYPORT))
except:
    print "no receivers"

