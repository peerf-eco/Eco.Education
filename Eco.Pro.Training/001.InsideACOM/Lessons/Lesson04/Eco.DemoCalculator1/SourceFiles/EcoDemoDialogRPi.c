/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoDemoDialogRPi
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
#include "IEcoMemoryManager1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoFileSystemManagement1.h"
#include "IEcoCalculatorX.h"
#include "IdEcoBIOSExtensions1.h"

#define ADDITION_OPERATOR       1
#define SUBTRACTION_OPERATOR    2
#define MULTIPLICATION_OPERATOR 3
#define DEVISION_OPERATOR       4

extern IEcoInterfaceBus1* g_pIBus;
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
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на интерфейс работы с видео сервисами */
    IEcoBIOSExtensions1VideoServices* pIVideoServices = 0;

    /* Получение интерфейса */
    g_pIBus->pVTbl->QueryComponent(g_pIBus, &CID_EcoBIOSExtensions1, 0, &IID_IEcoBIOSExtensions1VideoServices, (void**) &pIVideoServices);
    if (result != 0 && pIVideoServices == 0) {
        /* Возврат в случае ошибки */
        return result;
    }

    pIVideoServices->pVTbl->WriteString(pIVideoServices, 0, 0, 2, 0, CHARACTER_ATTRIBUTE_FORE_COLOR_YELLOW, "Demo Calculator 1.0", 19);

    switch (g_iInfo) {
        case 0 :
            pIVideoServices->pVTbl->WriteString(pIVideoServices, 0, 0, 2, 2, CHARACTER_ATTRIBUTE_FORE_COLOR_YELLOW, "Unknown", 8);
        break;
        case 1 :
            pIVideoServices->pVTbl->WriteString(pIVideoServices, 0, 0, 2, 2, CHARACTER_ATTRIBUTE_FORE_COLOR_YELLOW, "Eco.ComponentA 1.0.0.0", 22);
        break;
        case 2 :
            pIVideoServices->pVTbl->WriteString(pIVideoServices, 0, 0, 2, 2, CHARACTER_ATTRIBUTE_FORE_COLOR_YELLOW, "Eco.ComponentB 1.0.0.0", 22);
        break;
    }

    a = 5;
    b = 6;
    if (g_pIX != 0) {
        c = g_pIX->pVTbl->Addition(g_pIX, a, b);
    }

    if (c == 11) {
        pIVideoServices->pVTbl->WriteString(pIVideoServices, 0, 0, 2, 4, CHARACTER_ATTRIBUTE_FORE_COLOR_YELLOW, "5 + 6 = 11", 10);
    }
    else {
        pIVideoServices->pVTbl->WriteString(pIVideoServices, 0, 0, 12, 4, CHARACTER_ATTRIBUTE_FORE_COLOR_YELLOW, "5 + 6 = ?", 9);
    }
    /* Цикл обработки сообщений */
    while (1) {
        result = 0;
    }

    pIVideoServices->pVTbl->Release(pIVideoServices);

    return result;
}

