//
//  WebViewController.m
//  BarCode Scanner
//
//  Created by Maxim Chetrusca on 3/13/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "WebViewController.h"

@interface WebViewController () <UIWebViewDelegate>

#define REQUEST_URL @"http://www.google.com"

@property (nonatomic, weak) IBOutlet UIWebView *webView;

@end

@implementation WebViewController

- (id)initWithNibName:(NSString *)nibNameOrNil
               bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil
                           bundle:nibBundleOrNil];
    if (self)
    {
        // Custom initialization
      //  [self setup];
    }
    return self;
}

-(void) awakeFromNib
{
    [super awakeFromNib];
    //[self setup];
}

#pragma mark UIWebViewDelegate
#pragma mark TO DO HERE
//did I implement it right? how to go to Settings?
-(void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    if (-1009 == error.code)
    {
//        NSLog(@"No internet connection");
        UIAlertView *connection=[[UIAlertView alloc]initWithTitle:@"Mobile Data is Turned Off"
                                                          message:@"Turn on mobile data or use Wi-Fi to access data."
                                                         delegate:nil
                                                cancelButtonTitle:@"OK"
                                                otherButtonTitles: nil];
        [connection show];
    }
    else
    {
        NSLog(@"Error: %@",error);
    }
}

-(void)webViewDidStartLoad:(UIWebView *)webView
{
//    NSLog(@"start loading");
    [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:YES];
}

-(void)webViewDidFinishLoad:(UIWebView *)webView
{
//    NSLog(@"finish loading");
    [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];

}

-(BOOL)webView:(UIWebView *)webView
shouldStartLoadWithRequest:(NSURLRequest *)request
navigationType:(UIWebViewNavigationType)navigationType
{
//    NSLog(@"going to load");
    return YES;
}

-(void) setup
{
//    NSLog(@"setup");
    self.webView.delegate = self;
}

#pragma mark TO_DO_HERE
//change url
- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setup];
    NSURL *url;
    if (!self.code)
    {
        url = [NSURL URLWithString:REQUEST_URL];
    }
    else if ([self.code characterAtIndex:0] == 'h')
    {
        self.title = @"Profile";
        url = [NSURL URLWithString:self.code];
    }
    else
    {
        self.title = @"Google";
        url = [NSURL URLWithString:[NSString stringWithFormat:@"http://www.google.com/search?q=%@",self.code]];
    }
    NSLog(@"url=%@",url);
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    [self.webView loadRequest:request];
}

- (void)didReceiveMemoryWarning
{
    //[super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


-(NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskAll;
}

@end
