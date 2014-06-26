//
//  ViewController.m
//  IppProblem1.0
//
//  Created by Maxim Chetrusca on 11/21/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "ViewController.h"
#import "ImageClient.h"

@interface ViewController ()


@property (weak, nonatomic) IBOutlet UIImageView *imageView1;


@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *spinner;
@property (strong, nonatomic) ImageClient* imageClient;


@end

@implementation ViewController

-(void) setup
{
    _imageClient = [[ImageClient alloc] init];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
    {
        [self setup];
    }
    return self;
}

-(void) awakeFromNib
{
    [super awakeFromNib];
    [self setup];
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.imageView1.contentMode = UIViewContentModeScaleAspectFit;
    
    self.spinner.center = self.view.center;
    [self.view addSubview:self.spinner];
    [self.spinner startAnimating];
    self.spinner.hidden = YES; // spinner is not visible until started
}

-(void) setBackgroundImageForNumber:(NSNumber*) number
{
    NSUInteger n = [number integerValue];
    
    self.imageView1.image = [self.imageClient gimmeYourImageForNumber:n];
    
    self.spinner.hidden = YES;
    
    
}

- (IBAction)buttonPressed:(UIButton *)sender
{
    //    NSLog(@"button pressed %@",sender.titleLabel.text);
    NSNumber* number = [NSNumber numberWithInt:[sender.titleLabel.text integerValue]];
    
    
    self.spinner.hidden = NO;
    [self performSelector:@selector(setBackgroundImageForNumber:) withObject:number afterDelay:0.1];
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}



@end
