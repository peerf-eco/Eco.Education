/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoCalculatorB
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoCalculatorB
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_CALCULATOR_B_H__
#define __C_ECO_CALCULATOR_B_H__

#include "IEcoCalculatorX.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoCalculatorB {

    /* Таблица функций интерфейса IEcoCalculatorX */
    IEcoCalculatorXVTbl* m_pVTblIX;

    /* Неделигирующий интерфейс IEcoNondelegatingUnknown */
    IEcoUnknownVTbl* m_pVTblINondelegatingUnk;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Делегирующий IEcoUnknown, указывает на внешний или неделегирующий IEcoUnknown */
    IEcoUnknown* m_pIUnkOuter;

} CEcoCalculatorB, *CEcoCalculatorBPtr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoCalculatorB(/*in*/ IEcoCalculatorXPtr_t me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoCalculatorB(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoCalculatorXPtr_t* ppIX);
/* Удаление */
void ECOCALLMETHOD deleteCEcoCalculatorB(/* in */ IEcoCalculatorXPtr_t pIX);

#endif /* __C_ECO_CALCULATOR_B_H__ */
