/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoCalculatorE
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoCalculatorE
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_CALCULATOR_E_H__
#define __C_ECO_CALCULATOR_E_H__

#include "IdEcoCalculatorE.h"
#include "IdEcoCalculatorB.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoCalculatorE {

    /* Таблица функций интерфейса IEcoCalculatorY */
    IEcoCalculatorYVTbl* m_pVTblIY;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Указатель на IEcoUnknown внутреннего компонента */
    IEcoUnknown* m_pInnerUnknown;

} CEcoCalculatorE, *CEcoCalculatorEPtr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoCalculatorE(/*in*/ IEcoCalculatorYPtr_t me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoCalculatorE(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoCalculatorYPtr_t* ppIY);
/* Удаление */
void ECOCALLMETHOD deleteCEcoCalculatorE(/* in */ IEcoCalculatorY* pIY);

#endif /* __C_ECO_CALCULATOR_E_H__ */
