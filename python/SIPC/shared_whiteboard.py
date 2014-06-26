from Tkinter import *
from Tkinter import Tk
import time
import threading
import random
 
 
lastx, lasty = 0, 0
canvasWidth = 300
canvasHeight = 300
 
def doFoo(*args):
    print "Virtual event was generated"
 
def xy(event):
    global lastx, lasty
    lastx, lasty = event.x, event.y
 
def addLine(event):
    global lastx, lasty
    canvas.create_line((lastx, lasty, event.x, event.y))
    lastx, lasty = event.x, event.y
 
def dot(canvas, x, y):
	canvas.create_oval(x, y, x+1, y+1)
 
 
def worker(root, canvas):
	"""
	This function should read something from the socket and
	plot the dot on the canvas if a message is received.
	"""
	while True:
		time.sleep(2)
		#the coordinates of the dot to be drawn are randomized
		#but normally you should get them off the network
		x = random.randint(0, canvasWidth)
		y = random.randint(0, canvasHeight)
		dot(canvas, x, y)
 
		#in case you wish to do something else, you can
		#generate your custom event here
		#root.event_generate("<<Foo>>",when="tail")	
 
 
if __name__ == "__main__":
	root = Tk()
	root.columnconfigure(0, weight=1)
	root.rowconfigure(0, weight=1)
	root.bind("<<Foo>>",doFoo) #event, custom (not tied to the mouse/keyboard)
 
	canvas = Canvas(root, width=canvasWidth, height=canvasHeight)
	canvas.grid(column=0, row=0, sticky=(N, W, E, S))
	canvas.bind("<Button-1>", xy) #event, mouse-click
	canvas.bind("<B1-Motion>", addLine) #event, move mouse with a clicked button
 
	#start another thread, it will read stuff from the socket
	#and update the canvas if needed
	t = threading.Thread(target=worker, args=(root, canvas) )
	t.start()
 
	#drawing the canvas itself
	root.mainloop()
