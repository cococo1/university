//
//  DrawViewController.m
//  DrawME
//
//  Created by Alexandr Macari on 20/04/2012.
//  Copyright (c) 2012 Acasa. All rights reserved.
//

#define MYPORT 50001
#define TIMEOUT 10


 

#import "DrawViewController.h"
#import "netinet/in.h"
#import "arpa/inet.h"


@implementation DrawViewController

@synthesize sock,socklen,sendAddress,receiveAddress,myAddress;
@synthesize drawView;
@synthesize totalX,totalY;



- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) 
    {
        // Custom initialization
        timeout=0;
        clearScreenCalled=NO;
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    NSLog(@"Did reveiveMemory warning!!!");
    //[super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle


// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView
{
    CGRect aFrame=[[UIScreen mainScreen] bounds];
    self.view=[[UIView alloc]initWithFrame:aFrame];
    aFrame.size.width*=2;
    aFrame.size.height*=2;

    self.drawView=[[[UIDrawView alloc] initWithFrame:aFrame] autorelease];
    [self.view addSubview:self.drawView];
}



-(void) sendPacketWithValue:(NSValue*) value
{
    char message[100];
    BOOL panEndPoint=0;

    
        CGRect rect=[value CGRectValue];
        if (rect.size.height==0)//Action 1: Send a point
        {
            CGPoint point=rect.origin;
            panEndPoint=(int)rect.size.width; //used to transmit 0 or 1, if its the endpoint or not
            if (panEndPoint) 
                sprintf(message, 
                    "Action :%i\r\nColor :%i;%i;%i\r\nRatio :%f\r\nPoint :%f;%f\r\nEndpoint :%i\r\n\r\n",
                        1,self.drawView.users[0].r,self.drawView.users[0].g,self.drawView.users[0].b,self.drawView.users[0].ratio,point.x/totalX,point.y/totalY,1);
            else    sprintf(message, 
                            "Action :%i\r\nColor :%i;%i;%i\r\nRatio :%f\r\nPoint :%f;%f\r\nEndpoint :%i\r\n\r\n",
                            1,self.drawView.users[0].r,self.drawView.users[0].g,self.drawView.users[0].b,self.drawView.users[0].ratio,point.x/totalX,point.y/totalY,0);
        }
        else //Action 2: Clear screen 
        {
            self.drawView.users[0].clear=YES;
            sprintf(message, 
                    "Action :%i\r\nColor :%i;%i;%i\r\nTimeout :%i\r\n\r\n",
                    2,self.drawView.users[0].r,self.drawView.users[0].g,self.drawView.users[0].b,timeout);
        }
        

    sendto(sock, message,strlen(message) , 0, (struct sockaddr*)&sendAddress, sizeof(sendAddress));
// 0 - no additional flags about how the call is made

    //self.myAddress=inet_ntoa(receiveAddress.sin_addr);
    //NSLog(@"send:%s ",inet_ntoa(receiveAddress.sin_addr));
   // NSLog(@"send:%u rec:%u",sendAddress.sin_addr.s_addr,receiveAddress.sin_addr.s_addr);
   // NSLog(@"my %s",myAddress);



}


-(void) networkSetupToPort:(int) port
{

    int broadcast=1;//similar to boolean value, if 1 option will be enabled
    
    //create a socket  
    if ((sock=socket(AF_INET, SOCK_DGRAM, 0))<0) 
//AF_INET - use address family INET, with IPv4 for network layer
//SOCK_DGRAM - use UDP at transport layer
    {
        NSLog(@"Failed to connect.");
        return;
    }

    memset(&sendAddress, 0, sizeof(sendAddress)); //sets all bytes to zero
    sendAddress.sin_family=AF_INET;
    sendAddress.sin_addr.s_addr=htonl(INADDR_BROADCAST); //transforms the actual address in the right network-byte order
    sendAddress.sin_port=htons(port); //transform MYPORT into network-byte order
    
    
    memset(&receiveAddress, 0, sizeof(receiveAddress));
    receiveAddress.sin_family=AF_INET;
    receiveAddress.sin_port=htons(port); //transform MYPORT into network-byte order
    receiveAddress.sin_addr.s_addr=htonl(INADDR_ANY);//use any of the available network interfaces
    memset(&(receiveAddress.sin_zero), '\0', 8);
    
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))<0)
//SOL_SOCKET - manipulate the options at socket level
    {
        NSLog(@"Error while setting socket options");
        return;
    }
    if (bind(sock, (struct sockaddr*)&receiveAddress, sizeof(receiveAddress))==-1)
    {
        NSLog(@"Error: did not bind.");
        return;
    }
    
    socklen=sizeof(receiveAddress);
    
    
    
}

-(void) alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    NSLog(@"%i",buttonIndex);
    if (buttonIndex==1)
    {
        NSValue *value=[NSValue valueWithCGRect:CGRectMake(0, 0, 0, 1)];
        self.drawView.users[0].clear=YES;
        [self performSelectorInBackground:@selector(sendPacketWithValue:) withObject:value];
    }
}



-(void)alertBecause:(int)condition
{
    if (condition==0)
    {
        UIAlertView *alert=[[UIAlertView alloc] initWithTitle:
                            [NSString stringWithFormat:@"%s", inet_ntoa(receiveAddress.sin_addr)]
                                                      message:[NSString stringWithFormat:@"Let's clear the screen. Time to decide: %i seconds.",timeout]
                                                     delegate:self 
                                            cancelButtonTitle:@"Later" 
                                            otherButtonTitles:  @"Clear",nil];
    [alert show];
    [alert release];
    }
    else if (condition==2)
    {
        UIAlertView *alert=[[UIAlertView alloc] initWithTitle:@"Message:"
                                                      message:@"Request for clearing the whiteboard sent."
                                                     delegate:nil 
                                            cancelButtonTitle:@"Ok"
                            otherButtonTitles: nil];
        [alert show];
        [alert release];
    }
    else if (condition==3)
    {
        UIAlertView *alert=[[UIAlertView alloc] initWithTitle:@"Message:"
                                                      message:@"All online users agreed to clear the board. Board cleared."
                                                     delegate:nil 
                                            cancelButtonTitle:@"Ok" 
                            otherButtonTitles: nil];
        [alert show];
        [alert release];
    }
    else if (condition==4)
    {
        UIAlertView *alert=[[UIAlertView alloc] initWithTitle:@"Message:"
                                                      message:@"Not all online users agreed to clear the board."
                                                     delegate:nil 
                                            cancelButtonTitle:@"Ok" 
                            otherButtonTitles: nil];
        [alert show];
        [alert release];
    }

    
}
-(void) clearScreen
{
    clearScreenCalled=YES;
    BOOL allAgreeToClear=YES;
    NSLog(@"start counting...time:%i",timeout);
    while (timeout)
    {
        timeout--;
        sleep(1);
    }
    NSLog(@"time out!");
    for (int i=0; i<self.drawView.numberOfUsers; i++)
    {
        if (!self.drawView.users[i].clear)
        {
            allAgreeToClear=NO;
            break;
        }
    }
    
    if (allAgreeToClear)
    {
        for (int i=0; i<self.drawView.numberOfUsers; i++)
        {
            free(self.drawView.users[i].points);
            self.drawView.users[i].points=nil;
            self.drawView.users[i].numberOfPoints=0;
            self.drawView.users[i].clear=NO;
        }
        self.drawView.pathsToDraw=nil;
        self.drawView.colors=nil;
        [self.drawView setNeedsDisplay];
        [self alertBecause:3];
        
        
    }
    else
    {    
        for (int i=0; i<self.drawView.numberOfUsers; i++)
        {
            self.drawView.users[i].clear=NO;
        }
        [self alertBecause:4];

    }
    timeout=0;
    clearScreenCalled=NO;
}


-(void) receivePackets
{
    char message[100];
    CGPoint point;
    int endPoint;
    int action;
    USER user;
    BOOL presentInList;
    int time;
    while(1)
    {
        recvfrom(sock, &message, sizeof(message), 0, (struct sockaddr*)&receiveAddress, &socklen);
        //NSLog(@"%s",message);
        if (receiveAddress.sin_port==htons(MYPORT-1))
        {
            if (!myAddress)
            {
                myAddress=malloc(17*sizeof(char));
                
            }
            strcpy(myAddress,inet_ntoa(receiveAddress.sin_addr));
            NSLog(@"%s",myAddress);
                
            close(sock);
            
            [self networkSetupToPort:MYPORT];
        }
      //  NSLog(@"myaddress:%s, recaddr: %s",myAddress,inet_ntoa(receiveAddress.sin_addr));
        if (!strcmp(myAddress,inet_ntoa(receiveAddress.sin_addr))) continue; //We are not interested in packets which come from ourselves
        
        
        

            sscanf(message, "Action :%i",&action);

            if (action==1)
            {
                sscanf(message, "Action :%i\r\nColor :%i;%i;%i\r\nRatio :%f\r\nPoint :%f;%f\r\nEndpoint :%i\r\n\r\n",
                       &action,&user.r,&user.g,&user.b,&user.ratio,&point.x,&point.y,&endPoint);
            
                if (self.drawView.users[0].r!=user.r || self.drawView.users[0].g!=user.g || self.drawView.users[0].b!=user.b)
                {
            
            
                    point.x*=totalX;
                    point.y*=totalY*(self.drawView.users[0].ratio/user.ratio);
        
                    presentInList=NO;
                    for (int i=1; i<self.drawView.numberOfUsers; i++)
                    {
                        if (self.drawView.users[i].r==user.r && self.drawView.users[i].g==user.g && self.drawView.users[i].b==user.b)
                        {
                            presentInList=YES;
                            
                            self.drawView.users[i].points=realloc(self.drawView.users[i].points, sizeof(CGPoint)*(self.drawView.users[i].numberOfPoints+1));
                            self.drawView.users[i].points[self.drawView.users[i].numberOfPoints]=point;
                            self.drawView.users[i].numberOfPoints++;

                            break;
                        }
                    }
        
                    if (!presentInList)
                    {
                        user.clear=NO;
                        user.numberOfPoints=1;
                        user.points=NULL;
                        user.points=realloc(user.points, sizeof(CGPoint));
                        user.points[0]=point;
                        self.drawView.users=(USER*)realloc(self.drawView.users, sizeof(USER)*(self.drawView.numberOfUsers+1));
                        self.drawView.users[self.drawView.numberOfUsers]=user;
                        self.drawView.numberOfUsers++;

                    }
                    if (endPoint)  { [self.drawView setBezier];  endPoint=0; }
                    [self.drawView performSelectorOnMainThread:@selector(setNeedsDisplay) withObject:nil waitUntilDone:NO];
                }//if (different color) 
                else //same color
                {
                    //int r=rand()%255,g=rand()%255,b=rand()%255;
                    int r=arc4random()%255,g=arc4random()%255,b=arc4random()%255;

                    self.drawView.users[0].r=r;
                    self.drawView.users[0].g=g;
                    self.drawView.users[0].b=b;
                }
            
            }//if (action==2)
        else if (action==2)
        {
            sscanf(message, "Action :%i\r\nColor :%i;%i;%i\r\nTimeout :%i\r\n\r\n",
                   &action,&user.r,&user.g,&user.b,&time);
            
            if (!timeout || timeout>time)timeout=time;
            
            if (!self.drawView.users[0].clear) [self performSelectorOnMainThread:@selector(alertBecause:) withObject:nil waitUntilDone:NO];
            
            if (!clearScreenCalled) [self performSelectorInBackground:@selector(clearScreen) withObject:nil];
            presentInList=NO;
            for (int i=1; i<self.drawView.numberOfUsers; i++)
            {
                if (self.drawView.users[i].r==user.r && self.drawView.users[i].g==user.g && self.drawView.users[i].b==user.b)
                {
                    presentInList=YES;
                    
                    self.drawView.users[i].clear=YES;
                    
                    break;
                }
            }
            
            if (!presentInList)
            {
                user.numberOfPoints=0;
                user.points=NULL;
                user.clear=YES;
                self.drawView.users=(USER*)realloc(self.drawView.users, sizeof(USER)*(self.drawView.numberOfUsers+1));
                self.drawView.users[self.drawView.numberOfUsers]=user;
                self.drawView.numberOfUsers++;
                
            }

            
        }
        
    }//while(1)
}

-(void) pan: (UIPanGestureRecognizer*) gesture
{
    CGPoint point=[gesture locationInView:self.drawView];
    CGRect rect=CGRectMake(point.x, point.y, 0, 0);////width indicates whether it's the end pan point or not
    NSValue *value=[NSValue valueWithCGRect:rect];

    self.drawView.users[0].points=realloc(self.drawView.users[0].points, sizeof(CGPoint)*(self.drawView.users[0].numberOfPoints+1));
    self.drawView.users[0].points[self.drawView.users[0].numberOfPoints]=point;
    self.drawView.users[0].numberOfPoints++;

    if (gesture.state==UIGestureRecognizerStateChanged ||
        gesture.state ==UIGestureRecognizerStateEnded)
    {
        [self.drawView setNeedsDisplay];
    }
    
    if (gesture.state==UIGestureRecognizerStateEnded) { 
        [self.drawView setBezier];
         rect=CGRectMake(point.x, point.y, 1, 0); //width indicates whether it's the end pan point or not
        value=[NSValue valueWithCGRect:rect];
        [self performSelectorInBackground:@selector(sendPacketWithValue:) withObject:value];
        [self performSelectorInBackground:@selector(sendPacketWithValue:) withObject:value];
        [self performSelectorInBackground:@selector(sendPacketWithValue:) withObject:value];

    }
    [self performSelectorInBackground:@selector(sendPacketWithValue:) withObject:value];
}

-(IBAction)clearPressed:(id)sender
{
    if (!timeout) 
    {
        [self alertBecause:2];
         timeout=TIMEOUT;
    }
    if (!clearScreenCalled) [self performSelectorInBackground:@selector(clearScreen) withObject:nil];

    NSValue *value=[NSValue valueWithCGRect:CGRectMake(0, 0, 0, 1)];
    self.drawView.users[0].clear=YES;
    NSLog(@"time clearPressed:%i",timeout);
    [self performSelectorInBackground:@selector(sendPacketWithValue:) withObject:value];


}

-(void) pan2: (UIPanGestureRecognizer*) gesture
{
    if (gesture.state==UIGestureRecognizerStateChanged ||
        gesture.state ==UIGestureRecognizerStateEnded)
    {
     //   NSLog(@"panning");
        CGPoint translation=[gesture translationInView:self.drawView];
        [gesture setTranslation:CGPointZero inView:self.drawView];

       // NSLog(@"transition:%f,%f center:%f,%f",translation.x,translation.y,self.drawView.center.x,self.drawView.center.y);
        translation.x+=self.drawView.center.x;
        translation.y+=self.drawView.center.y;
        self.drawView.center=translation;

        
        //[self.drawView setNeedsDisplay];


    }
    
}

-(void) setup
{
    

    //int r=rand()%255,g=rand()%255,b=rand()%255;
    int r=arc4random()%255,g=arc4random()%255,b=arc4random()%255;
    self.drawView.users=(USER*)realloc(self.drawView.users, sizeof(USER)*(self.drawView.numberOfUsers+1));
    self.drawView.users[0].r=r;
    self.drawView.users[0].g=g;
    self.drawView.users[0].b=b;
    CGRect rect=[[UIScreen mainScreen]bounds];
    totalX=rect.size.width;
    totalY=rect.size.height;
    self.drawView.users[0].ratio=totalX/totalY;
    self.drawView.users[0].points=NULL;
    self.drawView.users[0].numberOfPoints=0;
    self.drawView.users[0].clear=NO;
    
    
    self.drawView.numberOfUsers=1;
    

    
    
    [self networkSetupToPort:MYPORT-1];
    
    
    UIPanGestureRecognizer *pangr=[[UIPanGestureRecognizer alloc]
                                   initWithTarget:self action:@selector(pan:)];
    [self.drawView addGestureRecognizer:pangr];
    [pangr release];

    
    UIPanGestureRecognizer *pangr2=[[UIPanGestureRecognizer alloc]
                                   initWithTarget:self action:@selector(pan2:)];
    [pangr2 setMinimumNumberOfTouches:2];
    [self.drawView addGestureRecognizer:pangr2];
    [pangr2 release];
    
    UIButton *clearButton=[UIButton buttonWithType:UIButtonTypeRoundedRect];
    clearButton.frame=CGRectMake(20, 30, 80, 40);
    [clearButton setTitle:@"ClearMe!" forState:UIControlStateNormal];
    [clearButton addTarget:self action:@selector(clearPressed:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:clearButton];
    

    
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setup];
    [self performSelectorInBackground:@selector(receivePackets) withObject:nil];
    [self sendPacketWithValue:nil];
}


- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
   // self.drawView.points=nil;
    self.drawView.pathsToDraw=nil;
    self.drawView.colors=nil;
    free(self.drawView.users);
    self.drawView.users=NULL;
    self.drawView.numberOfUsers=0;
    
    self.drawView=nil;
    
}

-(void) dealloc
{
    close(sock);
    free(myAddress);
    myAddress=NULL;
    [self.drawView.pathsToDraw release];
    [self.drawView.colors release];
    free(self.drawView.users);
    self.drawView.users=NULL;
    self.drawView.numberOfUsers=0;
    
    [drawView release];

    [super dealloc];
}

-(void) didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    if (self.interfaceOrientation==UIInterfaceOrientationPortrait || self.interfaceOrientation==UIInterfaceOrientationPortraitUpsideDown)
    {
        totalX=self.view.bounds.size.width;
        totalY=self.view.bounds.size.height;
    }
    else
    {
        totalX=self.view.bounds.size.height;
        totalY=self.view.bounds.size.width;
    }
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return YES;//(interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation==UIInterfaceOrientationLandscapeRight);
}

@end
