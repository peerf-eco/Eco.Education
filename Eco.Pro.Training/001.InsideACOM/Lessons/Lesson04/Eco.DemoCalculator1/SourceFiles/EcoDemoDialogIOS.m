/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoDemoDialogIOS
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

#include "IEcoSystem1.h"
#include "IEcoCommandArguments1.h"

extern IEcoSystem1* g_pISys;

/* Разрешение конфликта */
#define int8_t  no_int8_t
#define wchar_t no_wchar_t
#define int64_t no_int64_t
#undef interface

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

int16_t DialogProcessing() {
    NSString * appDelegateClassName;
    IEcoCommandArguments1* pIArgs = 0;
    int count = 0;
    char** argv = 0;

    /* Получение интерфейса для работы с интерфейсной шиной */
    g_pISys->pVTbl->QueryInterface(g_pISys, &IID_IEcoCommandArguments1, (void **)&pIArgs);
    
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
        appDelegateClassName = NSStringFromClass([AppDelegate class]);
    }
    count = pIArgs->pVTbl->get_Count(pIArgs);
    argv = pIArgs->pVTbl->get_Args(pIArgs);
    return UIApplicationMain(pIArgs->pVTbl->get_Count(pIArgs), pIArgs->pVTbl->get_Args(pIArgs), nil, appDelegateClassName);
}
