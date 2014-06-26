from socket import*
import datetime
import threading



CONST_PASS=".FAF-4ever"
clientList=[]
nrOfClients=0
serverSocket=socket()

def fibonacci(n):
    if n==0 or n==1: return 1
    else: return fibonacci(n-1)+fibonacci(n-2)

    


class ServerThread(threading.Thread):
    def __init__ ( self,  clientSocket, clientAddress ):
      self.clientSocket = clientSocket
      self.clientAddress = clientAddress
      threading.Thread.__init__ ( self )



    def run(self):
        global nrOfClients
        global clientList
        global serverSocket
        print "Incoming connection:"
        print self.clientSocket, self.clientAddress
        clientList.append(self.clientSocket)
        nrOfClients+=1

        self.clientSocket.send("Server is waiting for commands:")

        while (1):
            command=self.clientSocket.recv(100)
            if (command=="1"):
                for client in clientList:
                    client.close()
                    print "A client disconnected"
                    nrOfClients-=1
                serverSocket.close()
                print "Server closed"
            elif(command=="2"):
                time=datetime.datetime.now()
                strTime=time.strftime("%Y-%m-%d %H:%M")
                self.clientSocket.send(strTime)
            elif(command=="3"):
                self.clientSocket.send(str(nrOfClients))
            elif (command=="4"):
                n=self.clientSocket.recv(100)
                self.clientSocket.send(str(fibonacci(int(n))));
            elif (command=="5"):
                password=self.clientSocket.recv(100)
                if (password==CONST_PASS):
                    self.clientSocket.send("Secret: The bomb is in the garage!")
                else:
                    self.clientSocket.send("Wrong password.")
            elif (command=="6"):
                self.clientSocket.send("42")
            elif (command=="7"):
                try:
                    f=open("Terminator2.jpg","rb")
                    data=f.read()
                    f.close()
                    self.clientSocket.send(data)
                except:
                    self.clientSocket.send("NoShowtime")
            else:
                self.clientSocket.send("Can you elaborate on that?")
        return 1


def main():
    try:
        global serverSocket
        serverSocket.bind(("127.0.0.1",9999))
        print "Server binded"
    except:
         print "Server did not bind"
         return
    global nrOfClients, clientList
    serverSocket.listen(5)
    while True:
        client,address=serverSocket.accept()
        ServerThread(client,address).start()


main()


