from socket import*
import threading

class MyClient ( threading.Thread ):
    def __init__ ( self, channel):
        self.channel = channel
        #self.details = details
        threading.Thread.__init__ ( self )

    def run (self):
        try:
            self.channel.connect(("127.0.0.1",9999))
            print "Connection established."
        except:
            print "Connection failed."
            return
        response=self.channel.recv(100)
        print response
        while (1):
            message=raw_input("Give commands:")
            if (message==""):continue
            if (message=="%Hastalavista"):
                self.channel.send("1")
            elif (message=="%Time"):
                self.channel.send("2")
                response=self.channel.recv(100)
                print response
            elif (message=="%NumberOfConnectedClients"):
                self.channel.send("3")
                response=self.channel.recv(100)
                print int(response)
            elif (message=="%Fibonacci"):
                number=input("Give the number: ")
                if (number>30):
                    print "A lot"
                else:
                    self.channel.send("4")
                    self.channel.send(str(number))
                    response=self.channel.recv(100)
                    ans=int(response)
                    print ans
            elif (message=="%TellASecret"):
                self.channel.send("5")
                password=raw_input("Introduce password:")
                self.channel.send(password)
                response=self.channel.recv(100)
                print response
            elif (message[-1]=='?'):
                self.channel.send("6")
                response=client.recv(100)
                print response
            elif (message=='%Showtime'):
                self.channel.send("7")
                fileName=raw_input("What's the name of the file?")
                fileName=fileName+".jpg"
                f=open(fileName,"wb")
                data=self.channel.recv(32000)
                if data=="NoShowtime" :
                    print"Photo wasn't received."
                else:
                    f.write(data)
                    f.close()
                    print "The photo was saved."
            elif (message=="%Close"):
                self.channel.send("1")
                break
            else:
                self.channel.send("unknown command")
                response=self.channel.recv(100)
                print response
                    
        self.channel.close()
        print"Client closed."

client=socket()
MyClient(client).start()

