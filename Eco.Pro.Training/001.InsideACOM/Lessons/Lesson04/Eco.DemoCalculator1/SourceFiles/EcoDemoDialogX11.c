/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoDemoDialogX11
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
#include "IEcoCalculatorX.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

Display* dpy = 0;
int screen = 0;
Window win;
XEvent event;
GC gc;
XFontStruct* font;
XGCValues gcValues;
unsigned long mask;

#define ADDITION_OPERATOR       1
#define SUBTRACTION_OPERATOR    2

extern IEcoCalculatorX* g_pIX;
extern int8_t g_iInfo;

int16_t a = 0;
int16_t b = 0;
int32_t c = 0;
int8_t op = 0;

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
    int16_t result = -1;
    unsigned long black_pixel;
    unsigned long white_pixel;
    int x;
    int y;
    int direction;
    int ascent;
    int descent;
    char buf[10] = {0};
    int nCount = 0;
    int done = 0;
    Window textEditResult;
    Window button7, button8, button9, button4, button5, button6;
    Window button1, button2, button3, buttonS, button0, buttonE, buttonA;

    XSetWindowAttributes attrTextEdit;
    XCharStruct overall;
    XTextProperty     windowName;
    char* window_name = "Calculator 1";

    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
    screen = DefaultScreen(dpy);
    black_pixel = BlackPixel(dpy, screen);
    white_pixel = WhitePixel(dpy, screen);

    win = XCreateSimpleWindow(dpy, RootWindow(dpy, screen), 100, 100, 195, 260, 1, black_pixel, white_pixel);
    gcValues.background = WhitePixel(dpy, screen);
    gcValues.foreground = BlackPixel(dpy, screen);
    attrTextEdit.border_pixel = BlackPixel(dpy, screen);
    attrTextEdit.background_pixel = WhitePixel(dpy, screen);
    attrTextEdit.event_mask = ExposureMask;
    mask = GCForeground | GCBackground;
    gc = XCreateGC(dpy, win, mask, &gcValues);
    XSetBackground(dpy, gc, white_pixel);
    XSetForeground(dpy, gc, black_pixel);
    mask = CWBackPixel | CWBorderPixel | CWEventMask;
    const char* fontname = "-*-helvetica-*-r-*-*-14-*-*-*-*-*-*-*";
    font = XLoadQueryFont(dpy, fontname);
    if (!font) {
        fprintf(stderr, "unable to load font %s: using fixed\n", fontname);
        font = XLoadQueryFont(dpy, "fixed");
    }
    // XSetFont(dpy, gc, font->fid);
    XStringListToTextProperty(&window_name, 1, &windowName);
    XSetWMName(dpy, win, &windowName);
    XStringListToTextProperty(&window_name, 1, &windowName);
    XSetWMName(dpy, win, &windowName);
    switch (g_iInfo) {
        case 0 :
            XDrawImageString(dpy, win, gc, 10, 16, "Unknown", strlen("Unknown"));
        break;
        case 1 :
            XDrawImageString(dpy, win, gc, 10, 16, "Eco.ComponentA 1.0.0.0", strlen("Eco.ComponentA 1.0.0.0"));
        break;
        case 2 :
            XDrawImageString(dpy, win, gc, 10, 16, "Eco.ComponentB 1.0.0.0", strlen("Eco.ComponentB 1.0.0.0"));
        break;
    }

    attrTextEdit.event_mask = KeyPressMask | ButtonPressMask | ExposureMask;
    textEditResult = XCreateWindow(dpy, win, 10, 30, 170, 26, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);

    button7 = XCreateWindow(dpy, win, 20, 70, 28, 28, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);
    button8 = XCreateWindow(dpy, win, 60, 70, 28, 28, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);
    button9 = XCreateWindow(dpy, win, 100, 70, 28, 28, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);
    button4 = XCreateWindow(dpy, win, 20, 110, 28, 28, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);
    button5 = XCreateWindow(dpy, win, 60, 110, 28, 28, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);
    button6 = XCreateWindow(dpy, win, 100, 110, 28, 28, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);
    button1 = XCreateWindow(dpy, win, 20, 150, 28, 28, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);
    button2 = XCreateWindow(dpy, win, 60, 150, 28, 28, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);
    button3 = XCreateWindow(dpy, win, 100, 150, 28, 28, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);
    buttonS = XCreateWindow(dpy, win, 140, 150, 28, 28, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);
    button0 = XCreateWindow(dpy, win, 20, 190, 68, 28, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);
    buttonE = XCreateWindow(dpy, win, 100, 190, 28, 28, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);
    buttonA = XCreateWindow(dpy, win, 140, 190, 28, 28, 2, DefaultDepth(dpy, screen), InputOutput, DefaultVisual(dpy, screen), mask, &attrTextEdit);
    XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    XMapWindow(dpy, win);
    XMapWindow(dpy, textEditResult);
    XMapWindow(dpy, button7);
    XMapWindow(dpy, button8);
    XMapWindow(dpy, button9);
    XMapWindow(dpy, button4);
    XMapWindow(dpy, button5);
    XMapWindow(dpy, button6);
    XMapWindow(dpy, button1);
    XMapWindow(dpy, button2);
    XMapWindow(dpy, button3);
    XMapWindow(dpy, button0);
    XMapWindow(dpy, buttonE);

    if (g_pIX != 0) {
        XMapWindow(dpy, buttonA);
        XMapWindow(dpy, buttonS);
    }

    while (done == 0) {
        XNextEvent(dpy, &event);
        switch (event.type) {
            case Expose:
                switch (g_iInfo) {
                    case 0 :
                         XDrawImageString(dpy, win, gc, 10, 16, "Unknown", strlen("Unknown"));
                    break;
                    case 1 :
                        XDrawImageString(dpy, win, gc, 10, 16, "Eco.ComponentA 1.0.0.0", strlen("Eco.ComponentA 1.0.0.0"));
                    break;
                    case 2 :
                         XDrawImageString(dpy, win, gc, 10, 16, "Eco.ComponentB 1.0.0.0", strlen("Eco.ComponentB 1.0.0.0"));
                    break;
                }
                XDrawImageString(dpy, button7, gc, 12, 18, "7", strlen("7"));
                XDrawImageString(dpy, button8, gc, 12, 18, "8", strlen("8"));
                XDrawImageString(dpy, button9, gc, 12, 18, "9", strlen("9"));
                XDrawImageString(dpy, button4, gc, 12, 18, "4", strlen("4"));
                XDrawImageString(dpy, button5, gc, 12, 18, "5", strlen("5"));
                XDrawImageString(dpy, button6, gc, 12, 18, "6", strlen("6"));
                XDrawImageString(dpy, button1, gc, 12, 18, "1", strlen("1"));
                XDrawImageString(dpy, button2, gc, 12, 18, "2", strlen("2"));
                XDrawImageString(dpy, button3, gc, 12, 18, "3", strlen("3"));
                XDrawImageString(dpy, button0, gc, 16, 18, "0", strlen("0"));
                XDrawImageString(dpy, buttonE, gc, 12, 18, "=", strlen("="));
                if (g_pIX != 0) {
                    XDrawImageString(dpy, buttonA, gc, 12, 18, "+", strlen("+"));
                    XDrawImageString(dpy, buttonS, gc, 12, 18, "-", strlen("-"));
                }
           break;
           case ButtonPress:
                if (event.xbutton.window == button0) {
                    buf[nCount] = '0';
                    nCount++;
                    XDrawImageString(dpy, textEditResult, gc, 4, 16, buf, strlen(buf));
                }
                if (event.xbutton.window == button1) {
                    buf[nCount] = '1';
                    nCount++;
                    XDrawImageString(dpy, textEditResult, gc, 4, 16, buf, strlen(buf));
                }
                if (event.xbutton.window == button2) {
                    buf[nCount] = '2';
                    nCount++;
                    XDrawImageString(dpy, textEditResult, gc, 4, 16, buf, strlen(buf));
                }
                if (event.xbutton.window == button3) {
                    buf[nCount] = '3';
                    nCount++;
                    XDrawImageString(dpy, textEditResult, gc, 4, 16, buf, strlen(buf));
                }
                if (event.xbutton.window == button4) {
                    buf[nCount] = '4';
                    nCount++;
                    XDrawImageString(dpy, textEditResult, gc, 4, 16, buf, strlen(buf));
                }
                if (event.xbutton.window == button5) {
                    buf[nCount] = '5';
                    nCount++;
                    XDrawImageString(dpy, textEditResult, gc, 4, 16, buf, strlen(buf));
                }
                if (event.xbutton.window == button6) {
                    buf[nCount] = '6';
                    nCount++;
                    XDrawImageString(dpy, textEditResult, gc, 4, 16, buf, strlen(buf));
                }
                if (event.xbutton.window == button7) {
                    buf[nCount] = '7';
                    nCount++;
                    XDrawImageString(dpy, textEditResult, gc, 4, 16, buf, strlen(buf));
                }
                if (event.xbutton.window == button8) {
                    buf[nCount] = '8';
                    nCount++;
                    XDrawImageString(dpy, textEditResult, gc, 4, 16, buf, strlen(buf));
                }
                if (event.xbutton.window == button9) {
                    buf[nCount] = '9';
                    nCount++;
                    XDrawImageString(dpy, textEditResult, gc, 4, 16, buf, strlen(buf));
                }
                if (event.xbutton.window == buttonA) {
                    XClearWindow(dpy, textEditResult);
                    op = ADDITION_OPERATOR;
                    if (nCount > 0) {
                        a = atol(buf);
                    }
                    nCount = 0;
                    memset(buf, 0, 10);
                    XDrawImageString(dpy, textEditResult, gc, 4, 16, buf, strlen(buf));
                }
                if (event.xbutton.window == buttonS) {
                    XClearWindow(dpy, textEditResult);
                    op = SUBTRACTION_OPERATOR;
                    if (nCount > 0) {
                        a = atol(buf);
                    }
                    nCount = 0;
                    memset(buf, 0, 10);
                    XDrawImageString(dpy, textEditResult, gc, 4, 16, buf, strlen(buf));
                }
                if (event.xbutton.window == buttonE) {
                    XClearWindow(dpy, textEditResult);
                    if (nCount > 0) {
                        b = atol(buf);
                    }
                    nCount = 0;
                    memset(buf, 0, 10);
                    if (op == ADDITION_OPERATOR) {
                        c = g_pIX->pVTbl->Addition(g_pIX, a, b);
                    }
                    else if (op == SUBTRACTION_OPERATOR) {
                        c = g_pIX->pVTbl->Subtraction(g_pIX, a, b);
                    }
                    else {
                        c = 0;
                    }
                    sprintf(buf, "%d", c);
                    XDrawImageString(dpy, textEditResult, gc, 4, 16, buf, strlen(buf));
                }
            break;
        }
    }

    return result;
}


