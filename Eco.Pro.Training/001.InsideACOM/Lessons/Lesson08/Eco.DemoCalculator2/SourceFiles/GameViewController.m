//
//  GameViewController.m
//  Eco.DemoCalculator1
//
//  Created by Vladimir Bashev on 15.07.2021.
//

#include "IEcoSystem1.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"

extern IEcoCalculatorX* g_pIX;
extern IEcoCalculatorY* g_pIY;
extern IEcoSystem1* g_pISys;
extern int8_t g_iInfo;

#define ADDITION_OPERATOR       1
#define SUBTRACTION_OPERATOR    2
#define MULTIPLICATION_OPERATOR 3
#define DEVISION_OPERATOR       4

char_t g_strOut[10] = {0};
int16_t nCount = 0;
int16_t a = 0;
int16_t b = 0;
int32_t c = 0;
int8_t op = 0;
int8_t g_nSum = 0;

/* Разрешение конфликта */
#define int8_t  no_int8_t
#define wchar_t no_wchar_t
#define int64_t no_int64_t
#undef interface

#include <OpenGLES/ES1/gl.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>

static GLuint texture[1];
unsigned char dataFont[196610] = {0};
int g_iWidth = 0;
int g_iHeight = 0;


GLvoid drawText(unsigned char *text, int iMaxPrint, float xPos, float yPos) {
    float cx;
    float cy;
    float tx;
    float ty;
    int i, c;
    int iTextLen = 0;
    unsigned char textTmp[256] = {0};
    GLfloat *vertices;
    GLfloat *texture_coords;
    GLshort* indices;
    int texture_enabled;
    int blend_enabled;
    int gl_blend_src, gl_blend_dst;
    int vertex_array_enabled;
    int texture_array_enabled;
    float pen_x = 0.0f;

    if (!text) {
        return;
    }
    glLoadIdentity();
    glTranslatef(xPos, yPos, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    iTextLen = (int)strlen((const char *)text);
    memcpy(textTmp, text, iTextLen);

    if (iMaxPrint > 0 && iTextLen > iMaxPrint && iTextLen > 3) {
        iTextLen = iMaxPrint;
        textTmp[iMaxPrint] = 0;
        textTmp[iMaxPrint-1] = '.';
        textTmp[iMaxPrint-2] = '.';
    }

    glGetIntegerv(GL_TEXTURE_2D, &texture_enabled);
    if (!texture_enabled) {
        glEnable(GL_TEXTURE_2D);
    }

    glGetIntegerv(GL_BLEND, &blend_enabled);
    if (!blend_enabled) {
        glEnable(GL_BLEND);
    }

    glGetIntegerv(GL_BLEND_SRC, &gl_blend_src);
    glGetIntegerv(GL_BLEND_DST, &gl_blend_dst);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glGetIntegerv(GL_VERTEX_ARRAY, &vertex_array_enabled);
    if (!vertex_array_enabled) {
        glEnableClientState(GL_VERTEX_ARRAY);
    }

    glGetIntegerv(GL_TEXTURE_COORD_ARRAY, &texture_array_enabled);
    if (!texture_array_enabled) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    vertices = (GLfloat*) malloc(sizeof(GLfloat) * 8 * iTextLen);
    texture_coords = (GLfloat*) malloc(sizeof(GLfloat) * 8 * iTextLen);

    indices = (GLshort*) malloc(sizeof(GLfloat) * 5 * iTextLen);

    for(i = 0; i < iTextLen; ++i) {
        c = textTmp[i];
        cx= (float)(i%32)/20.0f;
        cy= (float)(i/32)/20.0f;
        tx= (float)(c%16)/16.0f;
        ty=(float)(c/16)/16.0f;
        vertices[8 * i + 0] =  cx + xPos;
        vertices[8 * i + 1] =  yPos -cy;
        vertices[8 * i + 2] = vertices[8 * i + 0] +0.0625f;
        vertices[8 * i + 3] = vertices[8 * i + 1];
        vertices[8 * i + 4] = vertices[8 * i + 0];
        vertices[8 * i + 5] = vertices[8 * i + 1] +0.0625f;
        vertices[8 * i + 6] = vertices[8 * i + 2];
        vertices[8 * i + 7] = vertices[8 * i + 5];

        texture_coords[8 * i + 0] = tx;
        texture_coords[8 * i + 1] = 1-ty-0.0625f;
        texture_coords[8 * i + 2] = tx+0.0625f;
        texture_coords[8 * i + 3] = 1-ty-0.0625f;
        texture_coords[8 * i + 4] = tx;
        texture_coords[8 * i + 5] = 1-ty;
        texture_coords[8 * i + 6] = tx+0.0625f;
        texture_coords[8 * i + 7] = 1-ty;

        indices[i * 6 + 0] = 4 * i + 0;
        indices[i * 6 + 1] = 4 * i + 1;
        indices[i * 6 + 2] = 4 * i + 3;
        indices[i * 6 + 3] = 4 * i + 3;
        indices[i * 6 + 4] = 4 * i + 2;
        indices[i * 6 + 5] = 4 * i + 0;
        pen_x += 1;
    }

    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texture_coords);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glDrawElements(GL_TRIANGLES, 6 * iTextLen, GL_UNSIGNED_SHORT, indices);

    if (!texture_array_enabled) {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    if (!vertex_array_enabled) {
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    if (!texture_enabled) {
        glDisable(GL_TEXTURE_2D);
    }

    glBlendFunc(gl_blend_src, gl_blend_dst);

    if (!blend_enabled) {
        glDisable(GL_BLEND);
    }

    free(vertices);
    free(texture_coords);
    free(indices);
}


void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a) {
    float vertices[4] = {0, 0, x2 - x1, y2 - y1};
    glLoadIdentity();
    glTranslatef(x1, y1, 0.0);
    glVertexPointer (2, GL_FLOAT , 0, vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor4f(r, g, b, a);
    glDrawArrays (GL_LINES, 0, 2);
}

void drawRectangle(float x, float y, float w, float h) {
    drawLine( x, y, x, y+h, x, 0.0f, 0.0f, 1.0f);
    drawLine( x, y+h, x+w, y+h, 0.0f, 0.0f, 0.0f, 1.0f);
    drawLine( x+w, y+h, x+w, y, 0.0f, 0.0f, 0.0f, 1.0f);
    drawLine( x+w, y, x, y, 0.0f, 0.0f, 0.0f, 1.0f);

}

void convertXY(int inX, int inY, float* outX, float* outY) {
    int w = g_iWidth/2;
    int h = g_iHeight/2;

        *outX = -1.0f + (float)inX/w;

        *outY = 1.0f - (float)inY/h;

}

#import "GameViewController.h"
#import <OpenGLES/ES2/glext.h>

GLvoid BuildFont(unsigned char *pFonts, int iSize) {
    glGenTextures(1, &texture[0]);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, pFonts);
}

@interface GameViewController () {}
@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;

@end

@implementation GameViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }

    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;

    [self setupGL];
}

- (void)dealloc
{
    [self tearDownGL];

    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;

        [self tearDownGL];

        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)doubleClickTimer:(NSTimer *)theTimer {

}

- (void)setupGL
{

    [EAGLContext setCurrentContext:self.context];
    UIImage *tmpImageFont = [UIImage imageNamed:@"peerFont_Windows_Codepage_1251.bmp"];
    UIGraphicsBeginImageContext(tmpImageFont.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextTranslateCTM(context,  tmpImageFont.size.height, 0);
    CGContextScaleCTM(context, -1.0f,1.0f);
    CGContextTranslateCTM(context, tmpImageFont.size.width, 0);
    CGContextScaleCTM(context, -1.0f, 1.0f);
    CGContextDrawImage(context, CGRectMake(0.0, 0.0, tmpImageFont.size.width, tmpImageFont.size.height), [tmpImageFont CGImage]);
    UIImage *flipImageFont = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    CFDataRef imageRefFont = CGDataProviderCopyData(CGImageGetDataProvider(flipImageFont.CGImage));
    int iSizeFont = (int)CFDataGetLength(imageRefFont);
    unsigned char* bytesFont = (unsigned char* )CFDataGetBytePtr(imageRefFont);
    BuildFont(bytesFont, iSizeFont);


    int screenWidth = self.view.bounds.size.width;
    g_iWidth = screenWidth;
    int screenHeight = self.view.bounds.size.height;
    g_iHeight = screenHeight;
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    const char *documentsDirectory = [[paths objectAtIndex:0] UTF8String];
    
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];

   // Cube_tearDownGL();
}

#pragma mark - GLKView and GLKViewController delegate methods

extern float _rotation;

- (void)update
{
    int screenWidth = self.view.bounds.size.width;
    int screenHeight = self.view.bounds.size.height;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor (1.0,1.0,1.0,1.0);
     glClear (GL_COLOR_BUFFER_BIT);
     drawText("Demo Calculator 2", 17, -0.45f, 0.425f);

     switch (g_iInfo) {
         case 0 :
             drawText("Unknown", 7, -0.45f, 0.395f);
         break;
         case 1 :
             drawText("Eco.ComponentA 1.0.0.0", 22, -0.45f, 0.395f);
         break;
         case 2 :
             drawText("Eco.ComponentB 1.0.0.0", 22, -0.45f, 0.395f);
         break;
         case 3 :
             drawText("Eco.ComponentC 2.0.0.0", 22, -0.45f, 0.395f);
         break;
         case 4 :
             drawText("Eco.ComponentD 2.0.0.0", 22, -0.45f, 0.395f);
         break;
         case 5 :
             drawText("Eco.ComponentE 2.0.0.0", 22, -0.45f, 0.395f);
         break;
             
     }

     drawRectangle(-0.80f, 0.50f, 1.6f, 0.20f);

     if (g_nSum > 0 && nCount != 0) {
         drawText("          ", 10, -0.375f, 0.285f);
         memset(g_strOut+nCount, 0, 10 - nCount);
         g_nSum = 0;
         drawText((char*)g_strOut, nCount, -0.375f, 0.285f);
     }
     else if (g_nSum > 0 && nCount == 0) {
         drawText((char*)g_strOut, g_nSum, -0.375f, 0.285f);
     }
     else {
         drawText((char*)g_strOut, nCount, -0.375f, 0.285f);
     }
     drawRectangle(-0.80f, 0.25f, 0.35f, 0.20f);
     drawText("7", 1, -0.325f, 0.158f);
     drawRectangle(-0.35f, 0.25f, 0.35f, 0.20f);
     drawText("8", 1, -0.110f, 0.158f);
     drawRectangle( 0.10f, 0.25f, 0.35f, 0.20f);
     drawText("9", 1, 0.125f, 0.158f);
     drawRectangle( 0.55f, 0.25f, 0.35f, 0.20f);
     drawText("/", 1, 0.345f, 0.158f);

     drawRectangle(-0.80f, 0.0f, 0.35f, 0.20f);
     drawText("4", 1, -0.325f, 0.035f);
     drawRectangle(-0.35f, 0.0f, 0.35f, 0.20f);
     drawText("5", 1, -0.110f, 0.035f);
     drawRectangle( 0.10f, 0.0f, 0.35f, 0.20f);
     drawText("6", 1, 0.125f, 0.035f);
     drawRectangle( 0.55f, 0.0f, 0.35f, 0.20f);
     drawText("*", 1, 0.345f, 0.035f);

     drawRectangle(-0.80f, -0.25f, 0.35f, 0.20f);
     drawText("1", 1, -0.325f, -0.095f);
     drawRectangle(-0.35f, -0.25f, 0.35f, 0.20f);
     drawText("2", 1, -0.110f, -0.095f);
     drawRectangle( 0.10f, -0.25f, 0.35f, 0.20f);
     drawText("3", 1, 0.125f, -0.095f);
     drawRectangle( 0.55f, -0.25f, 0.35f, 0.20f);
     drawText("-", 1, 0.345f, -0.095f);

     drawRectangle(-0.80f, -0.50f, 0.80f, 0.20f);
     drawText("0", 1, -0.205f, -0.215f);
     drawRectangle( 0.10f, -0.50f, 0.35f, 0.20f);
     drawText("=", 1, 0.125f, -0.215f);
     drawRectangle( 0.55f, -0.50f, 0.35f, 0.20f);
     drawText("+", 1, 0.345f, -0.215f);

 }

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint touchLocation = [touch locationInView:touch.view];
    int xPos = touchLocation.x;
    int yPos = touchLocation.y;
    NSLog(@"Mouse position xPos:%d - yPos:%d", xPos, yPos);
}

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint touchLocation = [touch locationInView:touch.view];
    int xPos = touchLocation.x;
    int yPos = touchLocation.y;
}
-(void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint touchLocation = [touch locationInView:touch.view];
    int xPos = touchLocation.x;
    int yPos = touchLocation.y;
    float x = 0;
    float y = 0;
    convertXY(xPos, yPos, &x, &y);
    NSLog(@"Mouse position xPos:%d=%f - yPos:%d=%f", xPos, x, yPos, y);
    if ( x >= -0.8f && x <= -0.45f && y <= 0.45f && y >= 0.25f)
     {
         g_strOut[nCount] = '7';
         nCount++;
     }
     if ( x >= -0.35f && x <= 0 && y <= 0.45f && y >= 0.25f)
     {
         g_strOut[nCount] = '8';
         nCount++;
     }
     if ( x >= 0.1f && x <= 0.45f && y <= 0.45f && y >= 0.25f)
     {
         g_strOut[nCount] = '9';
         nCount++;
     }
     if ( x >= 0.55f && x <= 0.9f && y <= 0.45f && y >= 0.25f)
     {
         op = DEVISION_OPERATOR;
         if (nCount > 0) {
             a = atol(g_strOut);
         }
         memset(g_strOut, 0, 10);
         nCount = 0;
     }
     if ( x >= -0.8f && x <= -0.45f && y <= 0.2f && y >= 0.0f)
     {
         g_strOut[nCount] = '4';
         nCount++;
     }
     if ( x >= -0.35f && x <= 0 && y <= 0.2f && y >= 0.0f)
     {
         g_strOut[nCount] = '5';
         nCount++;
     }
     if ( x >= 0.1f && x <= 0.45f && y <= 0.2f && y >= 0.0f)
     {
         g_strOut[nCount] = '6';
         nCount++;
     }
     if ( x >= 0.55f && x <= 0.9f && y <= 0.2f && y >= 0.0f)
     {
         op = MULTIPLICATION_OPERATOR;
         if (nCount > 0) {
             a = atol(g_strOut);
         }
         memset(g_strOut, 0, 10);
         nCount = 0;
     }
     if ( x >= -0.8f && x <= -0.45f && y <= -0.05f && y >= -0.25f)
     {
         g_strOut[nCount] = '1';
         nCount++;
     }
     if ( x >= -0.35f && x <= 0 && y <= -0.05f && y >= -0.25f)
     {
         g_strOut[nCount] = '2';
         nCount++;
     }
     if ( x >= 0.1f && x <= 0.45f && y <= -0.05f && y >= -0.25f)
     {
         g_strOut[nCount] = '3';
         nCount++;
     }
     if ( x >= 0.55f && x <= 0.9f && y <= -0.05f && y >= -0.25f)
     {
         op = SUBTRACTION_OPERATOR;
         if (nCount > 0) {
             a = atol(g_strOut);
         }
         memset(g_strOut, 0, 10);
         nCount = 0;
     }
     if ( x >= -0.8f && x <= 0.0f && y <= -0.3f && y >= -0.5f)
     {
         g_strOut[nCount] = '0';
         nCount++;
     }
     if ( x >= 0.1f && x <= 0.45f && y <= -0.3f && y >= -0.5f)
     {
         if (nCount > 0) {
             b = atol(g_strOut);
         }
         memset(g_strOut, 0, 10);
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
         g_nSum = sprintf(g_strOut, "%d", c);
         nCount = 0;
     }
     if ( x >= 0.55f && x <= 0.9f && y <= -0.3f && y >= -0.5f)
     {
         op = ADDITION_OPERATOR;
         if (nCount > 0) {
             a = atol(g_strOut);
         }
         memset(g_strOut, 0, 10);
         nCount = 0;
     }

}

@end
