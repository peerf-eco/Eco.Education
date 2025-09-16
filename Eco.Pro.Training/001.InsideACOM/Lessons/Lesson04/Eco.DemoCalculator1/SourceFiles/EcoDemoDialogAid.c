/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoDemoDialogAndroid
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

/* Eco OS */
#include "IEcoSystem1.h"
#include "IEcoCalculatorX.h"
#include "IEcoAndroidNativeApp1.h"

#include <jni.h>
#include <errno.h>

#include <android/asset_manager.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <unistd.h>
#include <stdio.h>
#include <android/sensor.h>
#include <android/log.h>
#include "android_native_app_glue.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))

/* For debug builds, always enable the debug traces in this library */
#ifndef NDEBUG
#  define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_VERBOSE, "native-activity", __VA_ARGS__))
#else
#  define LOGV(...)  ((void)0)
#endif

#define ADDITION_OPERATOR       1
#define SUBTRACTION_OPERATOR    2

extern IEcoCalculatorX* g_pIX;
extern IEcoSystem1* g_pISys;
extern int8_t g_iInfo;

char_t g_strOut[10] = {0};
int16_t nCount = 0;
int16_t a = 0;
int16_t b = 0;
int32_t c = 0;
int8_t op = 0;
int8_t g_nSum = 0;
int g_iWidth = 0;
int g_iHeight = 0;

/**
 * Our saved state data.
 */
struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};
AAssetManager* android_asset_manager;
static GLuint texture[1];
unsigned char dataFont[196610] = {0};

typedef unsigned long       DWORD;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef char                CHAR;
typedef short               SHORT;
typedef long                LONG;
typedef unsigned long       ULONG;

#pragma pack(push)
#pragma pack(1)

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;           //specifies the number of bytes required by the struct
    LONG biWidth;           //specifies width in pixels
    LONG biHeight;          //species height in pixels
    WORD biPlanes;          //specifies the number of color planes, must be 1
    WORD biBitCount;        //specifies the number of bit per pixel
    DWORD biCompression;    //spcifies the type of compression
    DWORD biSizeImage;      //size of image in bytes
    LONG biXPelsPerMeter;   //number of pixels per meter in x axis
    LONG biYPelsPerMeter;   //number of pixels per meter in y axis
    DWORD biClrUsed;        //number of colors used by th ebitmap
    DWORD biClrImportant;   //number of colors that are important
} BITMAPINFOHEADER;

typedef struct tagBITMAPFILEHEADER {
    WORD bfType;            //specifies the file type
    DWORD bfSize;           //specifies the size in bytes of the bitmap file
    WORD bfReserved1;       //reserved; must be 0
    WORD bfReserved2;       //reserved; must be 0
    DWORD bfOffBits;        //species the offset in bytes from the bitmapfileheader to the bitmap bits
} BITMAPFILEHEADER;

#pragma pack(pop)


/**
 * Shared state for our app.
 */
struct engine {
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    struct saved_state state;
};

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

GLvoid BuildFont(unsigned char *pFonts, int iSize) {
    glGenTextures(1, &texture[0]);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, pFonts);
}

static int android_read(void* cookie, char* buf, int size) {
    return AAsset_read((AAsset*)cookie, buf, size);
}

static int android_write(void* cookie, const char* buf, int size) {
    return EACCES; // can't provide write access to the apk
}

static fpos_t android_seek(void* cookie, fpos_t offset, int whence) {
    return AAsset_seek((AAsset*)cookie, offset, whence);
}

static int android_close(void* cookie) {
    AAsset_close((AAsset*)cookie);
    return 0;
}

void android_fopen_set_asset_manager(AAssetManager* manager) {
    android_asset_manager = manager;
}

FILE* android_fopen(const char* fname, const char* mode) {
    AAsset* asset = AAssetManager_open(android_asset_manager, fname, 0);
    if(!asset) return NULL;
    return funopen(asset, android_read, android_write, android_seek, android_close);
}

int LoadGLTextures(unsigned char* data, unsigned char* filename) {
    BITMAPFILEHEADER bmpheader = {0};
    BITMAPINFOHEADER bmpinfo = {0};
    unsigned char buff;
    int i=0;
    AAssetDir* assetDir = AAssetManager_openDir(android_asset_manager, "");
    AAsset* asset = AAssetManager_open(android_asset_manager, filename, AASSET_MODE_STREAMING);
    int nb_read = 0;

    nb_read = AAsset_read(asset, &bmpheader, sizeof(BITMAPFILEHEADER));
    nb_read = AAsset_read(asset, &bmpinfo, sizeof(BITMAPINFOHEADER));
    AAsset_seek(asset, bmpheader.bfOffBits, SEEK_SET);
    nb_read = AAsset_read(asset, data, bmpinfo.biSizeImage);
    for(i=0; i < bmpinfo.biSizeImage;i+=3)
    {
        buff = data[i];
        data[i] = data[i+2];
        data[i+2] = buff;
    }
    AAsset_close(asset);
    AAssetDir_close(assetDir);

    return 0;
}

/**
 * Initialize an EGL context for the current display.
 */
static int engine_init_display(struct engine* engine) {
    // initialize OpenGL ES and EGL

    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */
    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };
    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;
    const int size = 256*256*3;
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    char cwd[1024] = {0};
    eglInitialize(display, 0, 0);

    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria */
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);
    context = eglCreateContext(display, config, NULL, NULL);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGW("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    engine->display = display;
    engine->context = context;
    engine->surface = surface;
    engine->width = w;
    engine->height = h;
    g_iWidth = w;
    g_iHeight = h;
    engine->state.angle = 0;

    LoadGLTextures(dataFont, "peerFont_Windows_Codepage_1251.bmp");
    BuildFont(dataFont, size);

    // Initialize GL state.
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);

    return 0;
}

/**
 * Just the current frame in the display.
 */
static void engine_draw_frame(struct engine* engine) {
    if (engine->display == NULL) {
        // No display.
        return;
    }

    glClearColor (1.0,1.0,1.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT);
    drawText("Demo Calculator 1", 17, -0.45f, 0.425f);

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

    drawRectangle(-0.80f, 0.0f, 0.35f, 0.20f);  
    drawText("4", 1, -0.325f, 0.035f);
    drawRectangle(-0.35f, 0.0f, 0.35f, 0.20f);  
    drawText("5", 1, -0.110f, 0.035f);
    drawRectangle( 0.10f, 0.0f, 0.35f, 0.20f);  
    drawText("6", 1, 0.125f, 0.035f);

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

    eglSwapBuffers(engine->display, engine->surface);
}

/**
 * Tear down the EGL context currently associated with the display.
 */
static void engine_term_display(struct engine* engine) {
    if (engine->display != EGL_NO_DISPLAY) {
        eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (engine->context != EGL_NO_CONTEXT) {
            eglDestroyContext(engine->display, engine->context);
        }
        if (engine->surface != EGL_NO_SURFACE) {
            eglDestroySurface(engine->display, engine->surface);
        }
        eglTerminate(engine->display);
    }
    engine->animating = 0;
    engine->display = EGL_NO_DISPLAY;
    engine->context = EGL_NO_CONTEXT;
    engine->surface = EGL_NO_SURFACE;
}

/**
 * Process the next input event.
 */
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {
    int xPos = 0;
    int yPos = 0;
    struct engine* engine = (struct engine*)app->userData;
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        engine->animating = 1;
        engine->state.x = AMotionEvent_getX(event, 0);
        engine->state.y = AMotionEvent_getY(event, 0);
        xPos = engine->state.x;
        yPos = engine->state.y;
        float x = 0;
        float y = 0;
        convertXY(xPos, yPos, &x, &y);
        if ( AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_DOWN) {
            LOGI("touch click down: x=%d y=%d", engine->state.x, engine->state.y);
        }
        else if ( AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_UP) {
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

        return 1;
    }
    return 0;
}

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
    struct engine* engine = (struct engine*)app->userData;
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            // The system has asked us to save our current state.  Do so.
            engine->app->savedState = malloc(sizeof(struct saved_state));
            *((struct saved_state*)engine->app->savedState) = engine->state;
            engine->app->savedStateSize = sizeof(struct saved_state);
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if (engine->app->window != NULL) {
                engine_init_display(engine);
                engine_draw_frame(engine);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
            engine_term_display(engine);
            break;
        case APP_CMD_GAINED_FOCUS:
            // When our app gains focus, we start monitoring the accelerometer.
            if (engine->accelerometerSensor != NULL) {
                ASensorEventQueue_enableSensor(engine->sensorEventQueue,
                        engine->accelerometerSensor);
                // We'd like to get 60 events per second (in us).
                ASensorEventQueue_setEventRate(engine->sensorEventQueue,
                        engine->accelerometerSensor, (1000L/60)*1000);
            }
            break;
        case APP_CMD_LOST_FOCUS:
            // When our app loses focus, we stop monitoring the accelerometer.
            // This is to avoid consuming battery while not being used.
            if (engine->accelerometerSensor != NULL) {
                ASensorEventQueue_disableSensor(engine->sensorEventQueue,
                        engine->accelerometerSensor);
            }
            // Also stop animating.
            engine->animating = 0;
            engine_draw_frame(engine);
            break;
    }
}

/*
 *
 * <сводка>
 *   Функция android_main
 * </сводка>
 *
 * <описание>
 *   Функция android_main
 * </описание>
 *
 */
void android_main(struct android_app* state) {
    struct engine engine;

    memset(&engine, 0, sizeof(engine));
    state->userData = &engine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
    ANativeActivity* nativeActivity = state->activity;
    const char* internalPath = nativeActivity->internalDataPath;
    android_asset_manager = nativeActivity->assetManager;

    engine.app = state;
    engine.sensorManager = ASensorManager_getInstance();
    engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
            ASENSOR_TYPE_ACCELEROMETER);
    engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
            state->looper, LOOPER_ID_USER, NULL, NULL);

    if (state->savedState != NULL) {
        engine.state = *(struct saved_state*)state->savedState;
    }


    while (1) {
        int ident;
        int events;
        struct android_poll_source* source;

        while ((ident=ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,
                (void**)&source)) >= 0) {

            if (source != NULL) {
                source->process(state, source);
            }

            if (ident == LOOPER_ID_USER) {
                if (engine.accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(engine.sensorEventQueue, &event, 1) > 0) {
                    }
                }
            }

            if (state->destroyRequested != 0) {
                engine_term_display(&engine);
                return;
            }
        }

        if (engine.animating) {
            engine.state.angle += .01f;
            if (engine.state.angle > 1) {
                engine.state.angle = 0;
            }

            engine_draw_frame(&engine);
        }
    }
}


static void free_saved_state(struct android_app* android_app) {
    pthread_mutex_lock(&android_app->mutex);
    if (android_app->savedState != NULL) {
        free(android_app->savedState);
        android_app->savedState = NULL;
        android_app->savedStateSize = 0;
    }
    pthread_mutex_unlock(&android_app->mutex);
}

int8_t android_app_read_cmd(struct android_app* android_app) {
    int8_t cmd;
    if (read(android_app->msgread, &cmd, sizeof(cmd)) == sizeof(cmd)) {
        switch (cmd) {
            case APP_CMD_SAVE_STATE:
                free_saved_state(android_app);
                break;
        }
        return cmd;
    } else {
        LOGE("No data on command pipe!");
    }
    return -1;
}

static void print_cur_config(struct android_app* android_app) {
    char lang[2], country[2];
    AConfiguration_getLanguage(android_app->config, lang);
    AConfiguration_getCountry(android_app->config, country);

    LOGV("Config: mcc=%d mnc=%d lang=%c%c cnt=%c%c orien=%d touch=%d dens=%d "
            "keys=%d nav=%d keysHid=%d navHid=%d sdk=%d size=%d long=%d "
            "modetype=%d modenight=%d",
            AConfiguration_getMcc(android_app->config),
            AConfiguration_getMnc(android_app->config),
            lang[0], lang[1], country[0], country[1],
            AConfiguration_getOrientation(android_app->config),
            AConfiguration_getTouchscreen(android_app->config),
            AConfiguration_getDensity(android_app->config),
            AConfiguration_getKeyboard(android_app->config),
            AConfiguration_getNavigation(android_app->config),
            AConfiguration_getKeysHidden(android_app->config),
            AConfiguration_getNavHidden(android_app->config),
            AConfiguration_getSdkVersion(android_app->config),
            AConfiguration_getScreenSize(android_app->config),
            AConfiguration_getScreenLong(android_app->config),
            AConfiguration_getUiModeType(android_app->config),
            AConfiguration_getUiModeNight(android_app->config));
}

void android_app_pre_exec_cmd(struct android_app* android_app, int8_t cmd) {
    switch (cmd) {
        case APP_CMD_INPUT_CHANGED:
            LOGV("APP_CMD_INPUT_CHANGED\n");
            pthread_mutex_lock(&android_app->mutex);
            if (android_app->inputQueue != NULL) {
                AInputQueue_detachLooper(android_app->inputQueue);
            }
            android_app->inputQueue = android_app->pendingInputQueue;
            if (android_app->inputQueue != NULL) {
                LOGV("Attaching input queue to looper");
                AInputQueue_attachLooper(android_app->inputQueue,
                        android_app->looper, LOOPER_ID_INPUT, NULL,
                        &android_app->inputPollSource);
            }
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_INIT_WINDOW:
            LOGV("APP_CMD_INIT_WINDOW\n");
            pthread_mutex_lock(&android_app->mutex);
            android_app->window = android_app->pendingWindow;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_TERM_WINDOW:
            LOGV("APP_CMD_TERM_WINDOW\n");
            pthread_cond_broadcast(&android_app->cond);
            break;

        case APP_CMD_RESUME:
        case APP_CMD_START:
        case APP_CMD_PAUSE:
        case APP_CMD_STOP:
            LOGV("activityState=%d\n", cmd);
            pthread_mutex_lock(&android_app->mutex);
            android_app->activityState = cmd;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_CONFIG_CHANGED:
            LOGV("APP_CMD_CONFIG_CHANGED\n");
            AConfiguration_fromAssetManager(android_app->config,
                    android_app->activity->assetManager);
            print_cur_config(android_app);
            break;

        case APP_CMD_DESTROY:
            LOGV("APP_CMD_DESTROY\n");
            android_app->destroyRequested = 1;
            break;
    }
}

void android_app_post_exec_cmd(struct android_app* android_app, int8_t cmd) {
    switch (cmd) {
        case APP_CMD_TERM_WINDOW:
            LOGV("APP_CMD_TERM_WINDOW\n");
            pthread_mutex_lock(&android_app->mutex);
            android_app->window = NULL;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_SAVE_STATE:
            LOGV("APP_CMD_SAVE_STATE\n");
            pthread_mutex_lock(&android_app->mutex);
            android_app->stateSaved = 1;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_RESUME:
            free_saved_state(android_app);
            break;
    }
}

static void android_app_destroy(struct android_app* android_app) {
    LOGV("android_app_destroy!");
    free_saved_state(android_app);
    pthread_mutex_lock(&android_app->mutex);
    if (android_app->inputQueue != NULL) {
        AInputQueue_detachLooper(android_app->inputQueue);
    }
    AConfiguration_delete(android_app->config);
    android_app->destroyed = 1;
    pthread_cond_broadcast(&android_app->cond);
    pthread_mutex_unlock(&android_app->mutex);
    if (g_pIX != 0) {
        g_pIX->pVTbl->Release(g_pIX);
    }
    if (g_pISys != 0) {
        g_pISys->pVTbl->Release(g_pISys);
    }
    // Can't touch android_app object after this.
}

static void process_input(struct android_app* app, struct android_poll_source* source) {
    AInputEvent* event = NULL;
    while (AInputQueue_getEvent(app->inputQueue, &event) >= 0) {
        LOGV("New input event: type=%d\n", AInputEvent_getType(event));
        if (AInputQueue_preDispatchEvent(app->inputQueue, event)) {
            continue;
        }
        int32_t handled = 0;
        if (app->onInputEvent != NULL) handled = app->onInputEvent(app, event);
        AInputQueue_finishEvent(app->inputQueue, event, handled);
    }
}

static void process_cmd(struct android_app* app, struct android_poll_source* source) {
    int8_t cmd = android_app_read_cmd(app);
    android_app_pre_exec_cmd(app, cmd);
    if (app->onAppCmd != NULL) app->onAppCmd(app, cmd);
    android_app_post_exec_cmd(app, cmd);
}

static void* android_app_entry(void* param) {
    struct android_app* android_app = (struct android_app*)param;

    android_app->config = AConfiguration_new();
    AConfiguration_fromAssetManager(android_app->config, android_app->activity->assetManager);

    print_cur_config(android_app);

    android_app->cmdPollSource.id = LOOPER_ID_MAIN;
    android_app->cmdPollSource.app = android_app;
    android_app->cmdPollSource.process = process_cmd;
    android_app->inputPollSource.id = LOOPER_ID_INPUT;
    android_app->inputPollSource.app = android_app;
    android_app->inputPollSource.process = process_input;

    ALooper* looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    ALooper_addFd(looper, android_app->msgread, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, NULL,
            &android_app->cmdPollSource);
    android_app->looper = looper;

    pthread_mutex_lock(&android_app->mutex);
    android_app->running = 1;
    pthread_cond_broadcast(&android_app->cond);
    pthread_mutex_unlock(&android_app->mutex);

    android_main(android_app);

    android_app_destroy(android_app);
    return NULL;
}

// --------------------------------------------------------------------
// Native activity interaction (called from main thread)
// --------------------------------------------------------------------

static struct android_app* android_app_create(ANativeActivity* activity,
        void* savedState, size_t savedStateSize) {
    LOGI("android_app_create\n");
    struct android_app* android_app = (struct android_app*)malloc(sizeof(struct android_app));
    memset(android_app, 0, sizeof(struct android_app));
    android_app->activity = activity;

    pthread_mutex_init(&android_app->mutex, NULL);
    pthread_cond_init(&android_app->cond, NULL);

    if (savedState != NULL) {
        android_app->savedState = malloc(savedStateSize);
        android_app->savedStateSize = savedStateSize;
        memcpy(android_app->savedState, savedState, savedStateSize);
    }

    int msgpipe[2];
    if (pipe(msgpipe)) {
        LOGI("could not create pipe: %s", strerror(errno));
        return NULL;
    }
    android_app->msgread = msgpipe[0];
    android_app->msgwrite = msgpipe[1];

    pthread_attr_t attr; 
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&android_app->thread, &attr, android_app_entry, android_app);

    // Wait for thread to start.
    pthread_mutex_lock(&android_app->mutex);
    while (!android_app->running) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }
    pthread_mutex_unlock(&android_app->mutex);

    return android_app;
}

static void android_app_write_cmd(struct android_app* android_app, int8_t cmd) {
    if (write(android_app->msgwrite, &cmd, sizeof(cmd)) != sizeof(cmd)) {
        LOGI("Failure writing android_app cmd: %s\n", strerror(errno));
    }
}

static void android_app_set_input(struct android_app* android_app, AInputQueue* inputQueue) {
    pthread_mutex_lock(&android_app->mutex);
    android_app->pendingInputQueue = inputQueue;
    android_app_write_cmd(android_app, APP_CMD_INPUT_CHANGED);
    while (android_app->inputQueue != android_app->pendingInputQueue) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }
    pthread_mutex_unlock(&android_app->mutex);
}

static void android_app_set_window(struct android_app* android_app, ANativeWindow* window) {
    pthread_mutex_lock(&android_app->mutex);
    if (android_app->pendingWindow != NULL) {
        android_app_write_cmd(android_app, APP_CMD_TERM_WINDOW);
    }
    android_app->pendingWindow = window;
    if (window != NULL) {
        android_app_write_cmd(android_app, APP_CMD_INIT_WINDOW);
    }
    while (android_app->window != android_app->pendingWindow) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }
    pthread_mutex_unlock(&android_app->mutex);
}

static void android_app_set_activity_state(struct android_app* android_app, int8_t cmd) {
    pthread_mutex_lock(&android_app->mutex);
    android_app_write_cmd(android_app, cmd);
    while (android_app->activityState != cmd) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }
    pthread_mutex_unlock(&android_app->mutex);
}

static void android_app_free(struct android_app* android_app) {
    pthread_mutex_lock(&android_app->mutex);
    android_app_write_cmd(android_app, APP_CMD_DESTROY);
    while (!android_app->destroyed) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }
    pthread_mutex_unlock(&android_app->mutex);

    close(android_app->msgread);
    close(android_app->msgwrite);
    pthread_cond_destroy(&android_app->cond);
    pthread_mutex_destroy(&android_app->mutex);
    free(android_app);
}

static void onDestroy(ANativeActivity* activity) {
    LOGI("Destroy: %p\n", activity);
    android_app_free((struct android_app*)activity->instance);
}

static void onStart(ANativeActivity* activity) {
    LOGI("Start: %p\n", activity);
    android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_START);
}

static void onResume(ANativeActivity* activity) {
    LOGI("Resume: %p\n", activity);
    android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_RESUME);
}

static void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen) {
    struct android_app* android_app = (struct android_app*)activity->instance;
    void* savedState = NULL;

    LOGI("SaveInstanceState: %p\n", activity);
    pthread_mutex_lock(&android_app->mutex);
    android_app->stateSaved = 0;
    android_app_write_cmd(android_app, APP_CMD_SAVE_STATE);
    while (!android_app->stateSaved) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }

    if (android_app->savedState != NULL) {
        savedState = android_app->savedState;
        *outLen = android_app->savedStateSize;
        android_app->savedState = NULL;
        android_app->savedStateSize = 0;
    }

    pthread_mutex_unlock(&android_app->mutex);

    return savedState;
}

static void onPause(ANativeActivity* activity) {
    LOGI("Pause: %p\n", activity);
    android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_PAUSE);
}

static void onStop(ANativeActivity* activity) {
    LOGI("Stop: %p\n", activity);
    android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_STOP);
}

static void onConfigurationChanged(ANativeActivity* activity) {
    struct android_app* android_app = (struct android_app*)activity->instance;
    LOGI("ConfigurationChanged: %p\n", activity);
    android_app_write_cmd(android_app, APP_CMD_CONFIG_CHANGED);
}

static void onLowMemory(ANativeActivity* activity) {
    struct android_app* android_app = (struct android_app*)activity->instance;
    LOGI("LowMemory: %p\n", activity);
    android_app_write_cmd(android_app, APP_CMD_LOW_MEMORY);
}

static void onWindowFocusChanged(ANativeActivity* activity, int focused) {
    LOGI("WindowFocusChanged: %p -- %d\n", activity, focused);
    android_app_write_cmd((struct android_app*)activity->instance,
            focused ? APP_CMD_GAINED_FOCUS : APP_CMD_LOST_FOCUS);
}

static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {
    LOGI("NativeWindowCreated: %p -- %p\n", activity, window);
    android_app_set_window((struct android_app*)activity->instance, window);
}

static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {
    LOGI("NativeWindowDestroyed: %p -- %p\n", activity, window);
    android_app_set_window((struct android_app*)activity->instance, NULL);
}

static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {
    LOGI("InputQueueCreated: %p -- %p\n", activity, queue);
    android_app_set_input((struct android_app*)activity->instance, queue);
}

static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {
    LOGI("InputQueueDestroyed: %p -- %p\n", activity, queue);
    android_app_set_input((struct android_app*)activity->instance, NULL);
}



/*
 *
 * <сводка>
 *   Функция DialogProcessing
 * </сводка>
 *
 * <описание>
 *   Функция DialogProcessing
 * </описание>
 *
 */
int16_t DialogProcessing() {
    IEcoAndroidNativeApp1* pINativeApp = 0;
    ANativeActivity* activity;
    void* savedState;
    size_t savedStateSize;

    /* Получение интерфейса для работы с Native App */
    g_pISys->pVTbl->QueryInterface(g_pISys, &IID_IEcoAndroidNativeApp1, (void **)&pINativeApp);

    pINativeApp->pVTbl->get_Activity(pINativeApp, &activity, &savedState, &savedStateSize);


    activity->callbacks->onDestroy = onDestroy;
    activity->callbacks->onStart = onStart;
    activity->callbacks->onResume = onResume;
    activity->callbacks->onSaveInstanceState = onSaveInstanceState;
    activity->callbacks->onPause = onPause;
    activity->callbacks->onStop = onStop;
    activity->callbacks->onConfigurationChanged = onConfigurationChanged;
    activity->callbacks->onLowMemory = onLowMemory;
    activity->callbacks->onWindowFocusChanged = onWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
    activity->callbacks->onInputQueueCreated = onInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;

    activity->instance = android_app_create(activity, savedState, savedStateSize);
	
    /* Увеличим счетчики на 1 глобальных указателей на интерфейс, так как будем работать в потоке и выйдем из основной функции вернув управление Android */
    if (g_pIX != 0) {
        g_pIX->pVTbl->AddRef(g_pIX);
    }
    if (g_pISys != 0) {
        g_pISys->pVTbl->AddRef(g_pISys);
    }
    return 0;
}
