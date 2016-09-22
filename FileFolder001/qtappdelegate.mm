#import "QtAppDelegate.h"

@implementation QtAppDelegate

+(QtAppDelegate *)sharedQtAppDelegate{
    static dispatch_once_t pred;
    static QtAppDelegate *shared = nil;
    dispatch_once(&pred, ^{
        shared = [[super alloc] init];
    });
    return shared;
}

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
    NSLog(@"absoluteURL = %@", [url absoluteURL]);
    NSLog(@"scheme = %@", [url scheme]);
    if( [[url scheme] isEqual:@"file"] ){
        NSLog(@"path = %@", [url path]);
        NSLog(@"file = %@", [[url path] lastPathComponent] );
    }
    else{
        NSLog(@"Not a file.");
    }

    NSString *toDir = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/"];
    NSString *toFile = [toDir stringByAppendingPathComponent:[[url path] lastPathComponent]];
    NSLog(@"toFile = %@", toFile);

    NSFileManager* theFM = [[NSFileManager alloc] init];
    NSError* anError;

    NSURL *toUrl = [NSURL fileURLWithPath: toFile];
    if ([theFM removeItemAtURL:toUrl error:&anError]) {
        NSLog(@"Old file %@ removed.", toFile);
    }
    else{
        NSLog(@"Failed to remove old file." );
    }

    if ([theFM moveItemAtURL:url toURL:toUrl error:&anError]) {
        NSLog(@"New file %@ copied.", toFile);
    }
    else{
        NSLog(@"Failed to copy new file." );
    }
}

void QtAppDelegateInitialize ()
{
    QtAppDelegate *appDelegate = (QtAppDelegate *)[[UIApplication sharedApplication] delegate];
    [[UIApplication sharedApplication] setDelegate:[QtAppDelegate sharedQtAppDelegate]];

    NSLog(@"Created a new appdelegate");
}

@end
