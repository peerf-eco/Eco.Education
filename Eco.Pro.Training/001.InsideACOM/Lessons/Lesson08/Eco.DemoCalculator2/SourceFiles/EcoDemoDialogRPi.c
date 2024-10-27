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

    /* Цикл обработки сообщений */
    while (1) {
    }

    return result;
}

