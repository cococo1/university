import socket
from string import*
import re
import time

def main():
    host="www.fucking-great-advice.ru";
    client=socket.socket(socket.AF_INET,socket.SOCK_STREAM);
    try:
        client.connect((host,80))
        print "Connection established."
    except:
        print "Connection failed"
        return

# This is the file which contains the current advice position (integer), normally the first
# position is 1, thus we will have the address: www.fucking-great-advice.ru/advice/1/
# If the download interrupts, it remembers the position at which it stopped, so it will resume
# from that position

    file2=open( "Current advice position.txt");
    s=file2.readline()
    file2.close()
    startAdvicePosition=int(s)
    if (startAdvicePosition==0): print "The program is going to download all advices from www.fucking-great-advice.ru"
    else: print "Resuming download of advices from www.fucking-great-advice.com. Starting with "+s+"th advice"
    #print s

# 20 007 is the biggest nr. associated with an advice which I saw

    for pathForAdvice in range(startAdvicePosition,20007): 
        #print "*****************"
        #print i
        #time.sleep(2)
        client.send("GET /advice/"+str(pathForAdvice)+" HTTP/1.1\r\n")
        client.send("Host:"+host+"\r\n")
        client.send("Connection: Keep-Alive\r\n");
        ##client.send("User-Agent: Bee\r\n")
        ##client.send("Accept: text\r\n")
        ##client.send("Accept-Language: ru\r\n")

        ##client.send("Accept-Enconding: gzip.deflate\r\n");
        ##client.send("Accept-Charset: ISO-88");

        ##client.send("Keep-Alive: 300\r\n")
        client.send("\r\n")
        
        ##response=client.recv(1024)
        ##print response

        ##client.send("Host: \r\n\r\n")


        ##client.send("User-Agent: \r\n\r\n")
        response=""
        response=client.recv(1024)
        
# It is mandatory in HTTP 1.1 for clients to handle situation when server response with 100 Continue;
# Basically we should ignore this and send another request.

        if (response=="HTTP/1.1 100 Continue\r\n\r\n"):
            print response
            
            response=client.recv(1024)
            
# We check what is the code sent back for our request - is it 200 Ok or 404 Not found?
            
        #print response
        time.sleep(0.5)
        result=response[9:12] #substring with code
        #print result
        

#Sometimes happens that no response arrives. A solution is to reconnect to server:

        if len(response)==0:
            print "Got no response.Server closed. Trying to reconnect:"
            client.close()
            #time.sleep(3)
            client=socket.socket(socket.AF_INET,socket.SOCK_STREAM);
            try:
                client.connect((host,80))
                print "Reconnected."
            except:
                print"Failed to reconnect."
                break;
            continue

# If code isn't 200 OK receive the rest of chunk and continue looping:

        if (not int(result)==200):
            response=response+client.recv(30000) #Probably 30000 is way too much for the remaining chunk :)
            #print response
            #print "continue"
            continue
# We receive chunks of data for our request, until the last 4 characters mark the end of response:
        while( not response[len(response)-4:]=="\r\n\r\n"):
            response=response+client.recv(1024)


# Paring HTML code:

        startIndex=find(response,"id=\"advice\">")+12
        endIndex=find(response,"</p",startIndex)
        unformattedAdvice=response[startIndex:endIndex]

# My "know-how" - editting the advice without regular expressions (anyway, I will consider them next time)
# Regular expressions are of course a better solution for this problem :)

        unformattedAdvice=unformattedAdvice.replace("&nbsp;"," ")
        unformattedAdvice=unformattedAdvice.replace("&#151;"," ")
        unformattedAdvice=unformattedAdvice.replace("&laquo;"," ")
        unformattedAdvice=unformattedAdvice.replace("&raquo;"," ")
        advice="";
        i=0;
        n=len(unformattedAdvice)
        while (i<n):
            while ( i<n  and unformattedAdvice[i]=='<'):
                while (i<n and (not unformattedAdvice[i]=='>')):
                    #print unformattedAdvice[i]
                    i=i+1;
                i=i+1;
            #print i
            
            if (i<n): advice=advice+unformattedAdvice[i];
            i=i+1;

# Finally we have the advice without other html characters

        ##print response[startIndex:endIndex]

# Write data into file:
        data=str(pathForAdvice)+". "+advice+"\r\n\r\n"
        file1=open("Fucking-great-advices.txt","a")
        file1.write(data)
        file1.close()
        
# Write the current position:

        file2=open("Current advice position.txt","w")
        file2.write(str(pathForAdvice+1))
        file2.close()
        print "Advice N# "+str(pathForAdvice)+" "+advice    
        #print advice


    client.close()
    
main()
    
