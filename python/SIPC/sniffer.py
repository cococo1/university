from socket import*
import time

def sayVersion(byte):
    version=byte>>4
    if version==4:
            return "IPv4"
    elif version==5:
            return "ST Datagram Mode"
    elif version==6:
            return "IPv6"
    elif version==7:
            return "TP/IX"
    elif version==8:
            return "PIP"
    elif version==9:
            return "TUBA"
    else:
            return "Unknown"

def sayHeaderLength(byte):
    length=(byte&0b00001111)*4
    if length<5*4:
        return "Invalid length"
    else:
        return str(length)

def sayTypeOfService(byte):
#first two bits unused
    codepoint=byte>>2
    lowThreeBits=codepoint&0b000111
    highThreeBits=codepoint>>3
    if not lowThreeBits:
        return "CS"+str(highThreeBits)
    elif highThreeBits<5: #do not start with 101
        return "Assured Forwarding "+str(codepoint)
    elif not (codepoint^0b101100):
        return "Voice-Admit"
    elif not (codepoint^0b101110):
        return "Expedited Forwarding PHB"
    else:
        return "Unknown"

def sayTotalLength(twoBytes):
    result=ord(twoBytes[0])*pow(2,8)+ord(twoBytes[1])
    return str(result)

def sayFlags(byte):
    flags=byte>>5
    #1st bit is reserved
    flags=flags&0b011
    if flags==3:
        return "DF=1; MF=1" #don't fragment, more fragments follow this fragment
    elif flags==2:
        return "DF=1; MF=0"
    elif flags==1:
        return "DF=0; MF=1"
    else:
        return "DF=0; MF=0"

def sayProtocol(byte10):
    if byte10==0:
        return "HOPOPT"
    elif byte10==1:
        return "ICMP"
    elif byte10==2:
        return "IGAP"
    elif byte10==3:
        return "GGP"
    elif byte10==4:
        return "IP in IP encapsulation."
    elif byte10==5:
        return "ST"
    elif byte10==6:
        return "TCP"
    elif byte10==17:
        return "UDP"
    elif byte10==41:
        return "IPv6 over IPv4"
    elif byte10==7:
        return "UCL"
    elif byte10==16:
        return "Chaos"
    elif byte10==37:
        return "Datagram Delivery Protocol"
    elif byte10==34:
        return "Third Party Connect Protocol."
    elif byte10==61:
        return "Any host internal protocol."
    elif byte10==63:
        return "Any local network."
    else :
        return "Unknown"

def sayAddress(fourBytes):
    return str(ord(fourBytes[0]))+"."+str(ord(fourBytes[1]))+"."+str(ord(fourBytes[2]))+"."+str(ord(fourBytes[3]))

def parseIPPacket(data):
    print "\n**********Parsed data:*********"
    byte1=ord(data[0])
    print "Version: "+sayVersion(byte1)
    print "Header Length: "+sayHeaderLength(byte1)
    byte2=ord(data[1])
    print "Type of Service: "+sayTypeOfService(byte2)
    bytes3And4=data[2:4]
    print "Total Length: "+sayTotalLength(bytes3And4)
    bytes5And6=data[4:6]
    print "ID: "+sayTotalLength(bytes5And6)
    byte7=ord(data[6])
    print "Flags: "+sayFlags(byte7)
    bytes7And8=data[6:8]
    print "Fragment offset: "+sayTotalLength(bytes7And8)
    byte9=ord(data[8])
    print "TTL: "+str(byte9)#time to live
    byte10=ord(data[9])
    print "Protocol: "+sayProtocol(byte10)
    bytes11And12=data[10:12]
    print "Header checksum: "+sayTotalLength(bytes11And12)
    bytes13To16=data[12:16]
    print "Source: "+sayAddress(bytes13To16)
    bytes17To20=data[16:20]
    print "Destination: "+sayAddress(bytes17To20)
    print "Payload:"+data[23:] #Options + padding complete a raw of 32 bits
    
    
    
    
    


# the public network interface
HOST = gethostbyname(gethostname())

# create a raw socket and bind it to the public interface
s = socket(AF_INET, SOCK_RAW, IPPROTO_IP)
s.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)#reuse address if its in TIME_WAIT state
s.bind((HOST, 0))

# Include IP headers
s.setsockopt(IPPROTO_IP, IP_HDRINCL, 1)

# receive all packages
s.ioctl(SIO_RCVALL, RCVALL_ON)

# receive a package
while (1):
    [data,address]=s.recvfrom(65536)#2 to power 16 (total length field)
    print "{"
    print "An IP packet with the size "+str(len(data))+" was captured."
    print "Raw data: {"+data+"}"
    parseIPPacket(data)
    time.sleep(3)


s.close()
# disabled promiscuous mode
#s.ioctl(SIO_RCVALL, RCVALL_OFF)

