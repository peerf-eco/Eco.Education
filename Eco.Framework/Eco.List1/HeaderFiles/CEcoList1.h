/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoList1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoList1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_LIST_1_H__
#define __C_ECO_LIST_1_H__

#include "IEcoList1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoList1Node_3A562281 {
    void* data;
    struct CEcoList1Node_3A562281* next;
} CEcoList1Node_3A562281;

typedef struct CEcoList1_3A562281 {

    /* Таблица функций интерфейса IEcoList1 */
    IEcoList1VTbl* m_pVTblIList;

    /* Счетчик ссылок */
    volatile uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Данные экземпляра */
    CEcoList1Node_3A562281* m_Elements;
    uint32_t m_Count;

} CEcoList1_3A562281, *CEcoList1_3A562281Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoList1_3A562281(/*in*/ IEcoList1Ptr_t me, /* in */IEcoUnknownPtr_t pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoList1_3A562281(/* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* out */ IEcoList1Ptr_t* ppIList);
/* Удаление */
void ECOCALLMETHOD deleteCEcoList1_3A562281(/* in */ IEcoList1Ptr_t pIList);

#endif /* __C_ECO_LIST_1_H__ */
