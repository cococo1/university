//
//  DisplayViewController.m
//  BarCode Scanner
//
//  Created by Maxim Chetrusca on 2/21/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "DisplayViewController.h"
#import "ZBarReaderView.h"
#import "WebViewController.h"

@interface DisplayViewController () <ZBarReaderViewDelegate>

#define WEB_VIEW_SEGUE_IDENTIFIER @"toWebView"

@property (nonatomic, weak) IBOutlet ZBarReaderView *readerView;
@property (nonatomic,strong) NSString* code;

@end

@implementation DisplayViewController

//- (id)initWithNibName:(NSString *)nibNameOrNil
//               bundle:(NSBundle *)nibBundleOrNil
//{
//    self = [super initWithNibName:nibNameOrNil
//                           bundle:nibBundleOrNil];
//    if (self)
//    {
//        // Custom initialization
//    }
//    return self;
//}
//
//-(void) awakeFromNib{
//    [super awakeFromNib];
//   // NSLog(@"awakeFromNib");
//    
//}
//
//- (IBAction)startPressed:(id)sender {
//    self.readerView.hidden=NO;
//    [self.readerView start];
//
//}
//
//- (IBAction)stopPressed:(id)sender {
//    [self.readerView stop];
//}

-(void)setup
{
    self.readerView.readerDelegate = self;
    self.navigationController.navigationBar.barStyle = UIBarStyleBlackOpaque;
    self.imageView.image = [UIImage imageNamed:@"blonde.png"];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setup];
}

//DO we need to call super here? No.
-(void) viewDidLayoutSubviews
{
//    No need to call super here.
    self.readerView.hidden = NO;
    [self.readerView start];
}

-(void) prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString:WEB_VIEW_SEGUE_IDENTIFIER])
    {
        WebViewController *webvc = [segue destinationViewController];
        webvc.code = self.code;
    }
}

-(void) sendRequest
{
//    NSLog(@"request");
    [self performSegueWithIdentifier:WEB_VIEW_SEGUE_IDENTIFIER
                              sender:nil];

}

- (void) readerView: (ZBarReaderView*) view
     didReadSymbols: (ZBarSymbolSet*) syms
          fromImage: (UIImage*) img
{
    // do something useful with results
//    NSLog(@"did detect smth");
    for(ZBarSymbol *sym in syms)
    {
        self.code = sym.data;
        break;
    }

    [self.readerView stop];
//    NSLog(@"Detected: %@",self.code);
    [self sendRequest];
}

-(NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskAll;
}



-(void) willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    [self.readerView willRotateToInterfaceOrientation:toInterfaceOrientation duration:duration];

}

-(BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
    return  YES;
}

- (void)viewDidUnload {
    [self setImageView:nil];
    [super viewDidUnload];
}

@end
