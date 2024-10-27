/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoDemoDialogWin
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

#include "windows.h"
#include <CommCtrl.h>
#include "resource.h"
#pragma comment(lib, "user32")
#pragma comment(lib, "comctl32.lib")

/* Eco OS */
#include "IEcoSystem1.h"
#include "IEcoMemoryManager1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoFileSystemManagement1.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"

#define ADDITION_OPERATOR       1
#define SUBTRACTION_OPERATOR    2
#define MULTIPLICATION_OPERATOR 3
#define DEVISION_OPERATOR       4

extern IEcoCalculatorX* g_pIX;
extern IEcoCalculatorY* g_pIY;
extern int8_t g_iInfo;

int16_t a = 0;
int16_t b = 0;
int32_t c = 0;
int8_t op = 0;


BOOL CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) { 
    HWND h;
    CHAR buf[10] = {0};
    int32_t nCount = 0;

    switch (message) { 
        case WM_CREATE:
           switch (g_iInfo) {
            case 0 :
                CreateWindow(TEXT("STATIC"), TEXT("Unknown"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP , 10, 10, 170, 26, hDlg, (HMENU)IDC_STATIC_INFO, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            break;
            case 1 :
                CreateWindow(TEXT("STATIC"), TEXT("Eco.ComponentA 1.0.0.0"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP , 10, 10, 170, 26, hDlg, (HMENU)IDC_STATIC_INFO, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            break;
            case 2 :
                CreateWindow(TEXT("STATIC"), TEXT("Eco.ComponentB 1.0.0.0"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP , 10, 10, 170, 26, hDlg, (HMENU)IDC_STATIC_INFO, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            break;
            case 3 :
                CreateWindow(TEXT("STATIC"), TEXT("Eco.ComponentC 2.0.0.0"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP , 10, 10, 170, 26, hDlg, (HMENU)IDC_STATIC_INFO, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            break;
            case 4 :
                CreateWindow(TEXT("STATIC"), TEXT("Eco.ComponentD 2.0.0.0"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP , 10, 10, 170, 26, hDlg, (HMENU)IDC_STATIC_INFO, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            break;
            case 5 :
                CreateWindow(TEXT("STATIC"), TEXT("Eco.ComponentE 2.0.0.0"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP , 10, 10, 170, 26, hDlg, (HMENU)IDC_STATIC_INFO, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
            break;
           }
           CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | ES_RIGHT | ES_NUMBER , 10, 30, 170, 26, hDlg, (HMENU)IDC_EDIT_RESULT, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("7"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 20, 70, 28, 28, hDlg, (HMENU)IDC_BUTTON_7, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("8"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 60, 70, 28, 28, hDlg, (HMENU)IDC_BUTTON_8, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("9"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 100, 70, 28, 28, hDlg, (HMENU)IDC_BUTTON_9, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("/"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 140, 70, 28, 28, hDlg, (HMENU)IDC_BUTTON_D, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("4"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 20, 110, 28, 28, hDlg, (HMENU)IDC_BUTTON_4, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("5"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 60, 110, 28, 28, hDlg, (HMENU)IDC_BUTTON_5, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("6"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 100, 110, 28, 28, hDlg, (HMENU)IDC_BUTTON_6, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("*"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 140, 110, 28, 28, hDlg, (HMENU)IDC_BUTTON_M, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("1"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 20, 150, 28, 28, hDlg, (HMENU)IDC_BUTTON_1, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("2"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 60, 150, 28, 28, hDlg, (HMENU)IDC_BUTTON_2, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("3"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 100, 150, 28, 28, hDlg, (HMENU)IDC_BUTTON_3, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("-"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 140, 150, 28, 28, hDlg, (HMENU)IDC_BUTTON_S, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("0"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 20, 190, 68, 28, hDlg, (HMENU)IDC_BUTTON_0, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("="), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 100, 190, 28, 28, hDlg, (HMENU)IDC_BUTTON_E, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);
           CreateWindow(TEXT("BUTTON"), TEXT("+"), WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 140, 190, 28, 28, hDlg, (HMENU)IDC_BUTTON_A, (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE), 0);

           if (g_pIX == 0) {
               EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_A), FALSE);
               EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_S), FALSE);
           }
           if (g_pIY == 0) {
               EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_D), FALSE);
               EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_M), FALSE);
           }

        return TRUE;

        case WM_COMMAND: 
            switch (LOWORD(wParam)) { 
                case IDOK:
                case IDCANCEL:
                    EndDialog(hDlg, wParam); 
                return TRUE; 
                case IDC_BUTTON_0:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    buf[nCount] = '0';
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
                case IDC_BUTTON_1:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    buf[nCount] = '1';
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
                case IDC_BUTTON_2:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    buf[nCount] = '2';
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
                case IDC_BUTTON_3:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    buf[nCount] = '3';
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
                case IDC_BUTTON_4:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    buf[nCount] = '4';
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
                case IDC_BUTTON_5:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    buf[nCount] = '5';
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
                case IDC_BUTTON_6:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    buf[nCount] = '6';
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
                case IDC_BUTTON_7:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    buf[nCount] = '7';
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
                case IDC_BUTTON_8:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    buf[nCount] = '8';
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
                case IDC_BUTTON_9:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    buf[nCount] = '9';
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
                case IDC_BUTTON_E:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    if (nCount > 0) {
                        b = atol(buf);
                    }
                    memset(buf, 0, 10);
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
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
                        MessageBox(hDlg, TEXT("Check operation"), TEXT("Error"), MB_ICONERROR | MB_OK);
                    }
                    _itoa(c, buf, 10);
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);

                return TRUE;
                case IDC_BUTTON_A:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    op = ADDITION_OPERATOR;
                    if (nCount > 0) {
                        a = atol(buf);
                    }
                    memset(buf, 0, 10);
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
                case IDC_BUTTON_S:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    op = SUBTRACTION_OPERATOR;
                    if (nCount > 0) {
                        a = atol(buf);
                    }
                    memset(buf, 0, 10);
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
                case IDC_BUTTON_M:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    op = MULTIPLICATION_OPERATOR;
                    if (nCount > 0) {
                        a = atol(buf);
                    }
                    memset(buf, 0, 10);
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
                case IDC_BUTTON_D:
                    nCount = GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf, 10);
                    op = DEVISION_OPERATOR;
                    if (nCount > 0) {
                        a = atol(buf);
                    }
                    memset(buf, 0, 10);
                    SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_RESULT), buf);
                return TRUE;
            }
        break;
        case WM_CLOSE:
            if (MessageBox(hDlg, TEXT("Close the program?"), TEXT("Close"), MB_ICONQUESTION | MB_YESNO) == IDYES) {
                DestroyWindow(hDlg);
            }
            return TRUE;

        case WM_DESTROY:
            PostQuitMessage(0);
            return TRUE;
        default:
            return DefWindowProc(hDlg, message, wParam, lParam);
    }
    return FALSE;
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
    int16_t result = -1;
    HWND hDlg;
    WNDCLASS wndClass = {0};
    MSG msg;
    BOOL ret;
    RECT rectScreen;
    int32_t x = 0;
    int32_t y = 0;
    int32_t nCmdShow = 0;

    /* вычисление координат центра экрана */
    GetWindowRect(GetDesktopWindow(), &rectScreen);
    x = rectScreen.right / 2 - 150;
    y = rectScreen.bottom / 2 - 75;

    /* Регистрация класса */
    wndClass.lpfnWndProc = (WNDPROC)DialogProc;
    wndClass.style = CS_HREDRAW|CS_VREDRAW;
    wndClass.hInstance =  GetModuleHandle(0);
    wndClass.lpszClassName = TEXT("Demo Calculator 2");
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

    RegisterClass(&wndClass);
    FreeConsole();
    /* Инициализация элементов управления и создание диалогового окна */
    InitCommonControls();
    hDlg = CreateWindow(TEXT("Demo Calculator 2"), TEXT("Demo Calculator 2"), WS_DLGFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU, x, y, 195, 260, NULL, NULL,  GetModuleHandle(0), NULL);
    ShowWindow(hDlg, SW_SHOWDEFAULT);

    /* Цикл обработки Windows сообщений */
    while   ((ret = GetMessage(&msg, 0, 0, 0)) != 0) {
        if(ret == -1)
            return -1;

        if  (!IsDialogMessage(hDlg, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return result;
}

