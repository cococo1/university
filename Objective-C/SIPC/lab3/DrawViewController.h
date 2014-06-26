//
//  DrawViewController.h
//  DrawME
//
//  Created by Alexandr Macari on 20/04/2012.
//  Copyright (c) 2012 Acasa. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "sys/socket.h"
#import "UIDrawView.h"



@interface DrawViewController : UIViewController<UIAlertViewDelegate>
{
    int timeout;
    BOOL clearScreenCalled;
}
@property (retain) IBOutlet UIDrawView* drawView;
@property (assign) int sock;
@property (assign) socklen_t socklen; //aka unsigned int
@property (assign) struct sockaddr_in sendAddress;
@property (assign) struct sockaddr_in receiveAddress;
@property (assign) char *myAddress;

@property (assign) float totalX;
@property (assign) float totalY;

@end
