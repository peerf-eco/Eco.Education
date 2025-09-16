
//
//  main.c
//  Eco.DemoCalculator1
//
//  Created by Vladimir Bashev on 13.02.2021.
//


#import "IEcoCalculatorX.h"
#import "IEcoCalculatorY.h"

extern IEcoCalculatorX* g_pIX;
extern IEcoCalculatorY* g_pIY;
extern int8_t g_iInfo;

#define ADDITION_OPERATOR       1
#define SUBTRACTION_OPERATOR    2
#define MULTIPLICATION_OPERATOR 3
#define DEVISION_OPERATOR       4

int8_t a = 0;
int8_t b = 0;
int8_t c = 0;
int16_t op = 0;

/* Разрешение конфликта */
#define int8_t  no_int8_t
#define wchar_t no_wchar_t
#define int64_t no_int64_t
#undef interface

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>


NSTextField *textFieldResult = 0;
NSString *bufInput = 0;


@interface ButtonHandler : NSObject
+ (void)buttonClick0:(id)sender;
+ (void)buttonClick1:(id)sender;
+ (void)buttonClick2:(id)sender;
+ (void)buttonClick3:(id)sender;
+ (void)buttonClick4:(id)sender;
+ (void)buttonClick5:(id)sender;
+ (void)buttonClick6:(id)sender;
+ (void)buttonClick7:(id)sender;
+ (void)buttonClick8:(id)sender;
+ (void)buttonClick9:(id)sender;
+ (void)buttonClickE:(id)sender;
+ (void)buttonClickA:(id)sender;
+ (void)buttonClickS:(id)sender;
@end


@implementation ButtonHandler
+ (void)buttonClick0:(id)sender{
    if ([bufInput length] != 0) {
        bufInput = [bufInput stringByAppendingString:@"0"];
        [textFieldResult setStringValue:bufInput];
    }
}
+ (void)buttonClick1:(id)sender{
    bufInput = [bufInput stringByAppendingString:@"1"];
    [textFieldResult setStringValue:bufInput];
}
+ (void)buttonClick2:(id)sender{
    bufInput = [bufInput stringByAppendingString:@"2"];
    [textFieldResult setStringValue:bufInput];
}
+ (void)buttonClick3:(id)sender{
    bufInput = [bufInput stringByAppendingString:@"3"];
    [textFieldResult setStringValue:bufInput];
}
+ (void)buttonClick4:(id)sender{
    bufInput = [bufInput stringByAppendingString:@"4"];
    [textFieldResult setStringValue:bufInput];
}
+ (void)buttonClick5:(id)sender{
    bufInput = [bufInput stringByAppendingString:@"5"];
    [textFieldResult setStringValue:bufInput];
}
+ (void)buttonClick6:(id)sender{
    bufInput = [bufInput stringByAppendingString:@"6"];
    [textFieldResult setStringValue:bufInput];
}
+ (void)buttonClick7:(id)sender{
    bufInput = [bufInput stringByAppendingString:@"7"];
    [textFieldResult setStringValue:bufInput];
}
+ (void)buttonClick8:(id)sender{
    bufInput = [bufInput stringByAppendingString:@"8"];
    [textFieldResult setStringValue:bufInput];
}
+ (void)buttonClick9:(id)sender{
    bufInput = [bufInput stringByAppendingString:@"9"];
    [textFieldResult setStringValue:bufInput];
}
+ (void)buttonClickE:(id)sender{
    if ([bufInput length] != 0) {
        b = atoi([bufInput UTF8String]);
    }
    if (op == ADDITION_OPERATOR) {
        c = g_pIX->pVTbl->Addition(g_pIX, a, b);
    }
    else if (op == SUBTRACTION_OPERATOR) {
        c = g_pIX->pVTbl->Subtraction(g_pIX, a, b);
    }
    else if (op == MULTIPLICATION_OPERATOR) {
         c = g_pIY->pVTbl->Multiplication(g_pIY, a, b);
    }
    else if (op == DEVISION_OPERATOR) {
        c = g_pIY->pVTbl->Division(g_pIY, a, b);
    }
    else {
        c = 0;
    }
    bufInput = [NSString stringWithFormat:@"%d", c];
    [textFieldResult setStringValue:bufInput];
    bufInput = [NSString stringWithFormat:@""];

}
+ (void)buttonClickA:(id)sender{
    op = ADDITION_OPERATOR;
    if ([bufInput length] != 0) {
        a = atol([bufInput UTF8String]);
    }
    bufInput = [NSString stringWithFormat:@""];
    [textFieldResult setStringValue:bufInput];
}
+ (void)buttonClickS:(id)sender{
    op = SUBTRACTION_OPERATOR;
    if ([bufInput length] != 0) {
        a = atol([bufInput UTF8String]);
    }
    bufInput = [NSString stringWithFormat:@""];
    [textFieldResult setStringValue:bufInput];
}
+ (void)buttonClickM:(id)sender{
    op = MULTIPLICATION_OPERATOR;
    if ([bufInput length] != 0) {
        a = atol([bufInput UTF8String]);
    }
    bufInput = [NSString stringWithFormat:@""];
    [textFieldResult setStringValue:bufInput];
}
+ (void)buttonClickD:(id)sender{
    op = DEVISION_OPERATOR;
    if ([bufInput length] != 0) {
        a = atol([bufInput UTF8String]);
    }
    bufInput = [NSString stringWithFormat:@""];
    [textFieldResult setStringValue:bufInput];
}
@end

int16_t DialogProcessing() {
    NSApp = [NSApplication sharedApplication];
    NSRect frame = NSMakeRect(100, 100, 195, 260);
    NSUInteger styleMask = NSWindowStyleMaskTitled
    | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;;
    NSRect rect = [NSWindow contentRectForFrameRect:frame styleMask:styleMask];
    NSWindow * window =  [[NSWindow alloc] initWithContentRect:rect styleMask:styleMask backing: NSBackingStoreBuffered    defer:false];
    [window setBackgroundColor:[NSColor lightGrayColor]];
    [window setTitle:@"Demo Calculator 2"];
    [window makeKeyAndOrderFront:  window];


    bufInput = [[NSString alloc] init];
    NSTextField *textFieldInfo = [[NSTextField alloc] initWithFrame:NSMakeRect(10, 210, 150, 17)];
    switch (g_iInfo) {
     case 0 :
            [textFieldInfo setStringValue:@"Unknown"];
     break;
     case 1 :
            [textFieldInfo setStringValue:@"Eco.ComponentA 1.0.0.0"];
    
    break;
    case 2 :
            [textFieldInfo setStringValue:@"Eco.ComponentB 1.0.0.0"];
    break;
    case 3 :
            [textFieldInfo setStringValue:@"Eco.ComponentC 2.0.0.0"];
    break;
    case 4 :
            [textFieldInfo setStringValue:@"Eco.ComponentD 2.0.0.0"];
    break;
    case 5 :
            [textFieldInfo setStringValue:@"Eco.ComponentE 2.0.0.0"];
    break;
            
    }
    [textFieldInfo setBezeled:NO];
    [textFieldInfo setDrawsBackground:NO];
    [textFieldInfo setEditable:NO];
    [textFieldInfo setSelectable:NO];
    [[window contentView] addSubview:textFieldInfo];

    textFieldResult = [[NSTextField alloc] initWithFrame:NSMakeRect(10, 190, 180, 20)];
    [[window contentView] addSubview:textFieldResult];
    
    NSButton *button7 = [[NSButton alloc] initWithFrame:NSMakeRect(10, 140, 50, 50)];
       [[window contentView] addSubview: button7];
       [button7 setTitle: @"7"];
       [button7 setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [button7 setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [button7 setTarget:[ButtonHandler class]];
    [button7 setAction:@selector(buttonClick7:)];

    NSButton *button8 = [[NSButton alloc] initWithFrame:NSMakeRect(50, 140, 50, 50)];
       [[window contentView] addSubview: button8];
       [button8 setTitle: @"8"];
       [button8 setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [button8 setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [button8 setTarget:[ButtonHandler class]];
    [button8 setAction:@selector(buttonClick8:)];

    NSButton *button9 = [[NSButton alloc] initWithFrame:NSMakeRect(90, 140, 50, 50)];
       [[window contentView] addSubview: button9];
       [button9 setTitle: @"9"];
       [button9 setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [button9 setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [button9 setTarget:[ButtonHandler class]];
    [button9 setAction:@selector(buttonClick9:)];

    NSButton *buttonM = [[NSButton alloc] initWithFrame:NSMakeRect(130, 140, 50, 50)];
       [[window contentView] addSubview: buttonM];
       [buttonM setTitle: @"*"];
       [buttonM setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [buttonM setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [buttonM setTarget:[ButtonHandler class]];
    [buttonM setAction:@selector(buttonClickM:)];
    
    NSButton *button4 = [[NSButton alloc] initWithFrame:NSMakeRect(10, 110, 50, 50)];
       [[window contentView] addSubview: button4];
       [button4 setTitle: @"4"];
       [button4 setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [button4 setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [button4 setTarget:[ButtonHandler class]];
    [button4 setAction:@selector(buttonClick4:)];

    NSButton *button5 = [[NSButton alloc] initWithFrame:NSMakeRect(50, 110, 50, 50)];
       [[window contentView] addSubview: button5];
       [button5 setTitle: @"5"];
       [button5 setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [button5 setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [button5 setTarget:[ButtonHandler class]];
    [button5 setAction:@selector(buttonClick5:)];

    NSButton *button6 = [[NSButton alloc] initWithFrame:NSMakeRect(90, 110, 50, 50)];
       [[window contentView] addSubview: button6];
       [button6 setTitle: @"6"];
       [button6 setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [button6 setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [button6 setTarget:[ButtonHandler class]];
    [button6 setAction:@selector(buttonClick6:)];

    NSButton *buttonD = [[NSButton alloc] initWithFrame:NSMakeRect(130, 110, 50, 50)];
       [[window contentView] addSubview: buttonD];
       [buttonD setTitle: @"/"];
       [buttonD setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [buttonD setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [buttonD setTarget:[ButtonHandler class]];
    [buttonD setAction:@selector(buttonClickD:)];

    
    NSButton *button1 = [[NSButton alloc] initWithFrame:NSMakeRect(10, 80, 50, 50)];
       [[window contentView] addSubview: button1];
       [button1 setTitle: @"1"];
       [button1 setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [button1 setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [button1 setTarget:[ButtonHandler class]];
    [button1 setAction:@selector(buttonClick1:)];

    NSButton *button2 = [[NSButton alloc] initWithFrame:NSMakeRect(50, 80, 50, 50)];
       [[window contentView] addSubview: button2];
       [button2 setTitle: @"2"];
       [button2 setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [button2 setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [button2 setTarget:[ButtonHandler class]];
    [button2 setAction:@selector(buttonClick2:)];

    NSButton *button3 = [[NSButton alloc] initWithFrame:NSMakeRect(90, 80, 50, 50)];
       [[window contentView] addSubview: button3];
       [button3 setTitle: @"3"];
       [button3 setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [button3 setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [button3 setTarget:[ButtonHandler class]];
    [button3 setAction:@selector(buttonClick3:)];

    NSButton *buttonS = [[NSButton alloc] initWithFrame:NSMakeRect(130, 80, 50, 50)];
       [[window contentView] addSubview: buttonS];
       [buttonS setTitle: @"-"];
       [buttonS setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [buttonS setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [buttonS setTarget:[ButtonHandler class]];
    [buttonS setAction:@selector(buttonClickS:)];

    NSButton *button0 = [[NSButton alloc] initWithFrame:NSMakeRect(10, 50, 90, 50)];
       [[window contentView] addSubview: button0];
       [button0 setTitle: @"0"];
       [button0 setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [button0 setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [button0 setTarget:[ButtonHandler class]];
    [button0 setAction:@selector(buttonClick0:)];

    NSButton *buttonE = [[NSButton alloc] initWithFrame:NSMakeRect(90, 50, 50, 50)];
       [[window contentView] addSubview: buttonE];
       [buttonE setTitle: @"="];
       [buttonE setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [buttonE setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [buttonE setTarget:[ButtonHandler class]];
    [buttonE setAction:@selector(buttonClickE:)];

    NSButton *buttonA = [[NSButton alloc] initWithFrame:NSMakeRect(130, 50, 50, 50)];
       [[window contentView] addSubview: buttonA];
       [buttonA setTitle: @"+"];
       [buttonA setButtonType:NSMomentaryLightButton]; //Set what type button You want
       [buttonA setBezelStyle:NSRoundedBezelStyle]; //Set what style You want
    [buttonA setTarget:[ButtonHandler class]];
    [buttonA setAction:@selector(buttonClickA:)];

    if (g_pIX == 0) {
        [buttonA setEnabled: NO];
        [buttonS setEnabled: NO];
    }
    if (g_pIY == 0) {
        [buttonM setEnabled: NO];
        [buttonD setEnabled: NO];
    }
    
    [NSApp run];

    return 0;
}
