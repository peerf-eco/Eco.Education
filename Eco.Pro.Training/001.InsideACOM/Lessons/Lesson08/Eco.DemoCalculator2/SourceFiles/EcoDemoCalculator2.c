/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoDemoCalculator2
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
#include "IdEcoMemoryManager1.h"
#include "EcoDemoDialog.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorC.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"

/* Указатель на интерфейс работы с системной интерфейсной шиной */
IEcoInterfaceBus1* g_pIBus = 0;
/* Указатель на системный интерфейс */
IEcoSystem1* g_pISys = 0;
/* Указатели на интерфейсы калькулятора */
IEcoCalculatorX* g_pIX = 0;
IEcoCalculatorY* g_pIY = 0;
int8_t g_iInfo = 0;

#ifdef ECO_AVR8
extern __heap_start;
#endif /* ECO_AVR8 */


/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    IEcoMemoryManager1* pIMemMgr = 0;
#ifdef ECO_AVR8
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
#endif /* ECO_AVR8 */

    /* Проверка и создание системного интрефейса */
    if (g_pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&g_pISys);
        if (result != 0 && g_pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = g_pISys->pVTbl->QueryInterface(g_pISys, &IID_IEcoInterfaceBus1, (void **)&g_pIBus);
    if (result != 0 || g_pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Для решений со статической компановкой */
#ifdef ECO_LIB
    /* Для AVR8 системный компонент не включает менеджер памяти и расширение пула интерфейсной шины */
#ifdef ECO_AVR8
    /* Регистрация статического компонента для работы с менеджером памяти */
    result = g_pIBus->pVTbl->RegisterComponent(g_pIBus, &CID_EcoMemoryManager1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_0000000000000000000000004D656D31);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Запрос расширения интерфейсной шины */
    result = g_pIBus->pVTbl->QueryInterface(g_pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        /* Установка расширения менаджера памяти */
        pIMemExt->pVTbl->set_Manager(pIMemExt, &CID_EcoMemoryManager1);
        /* Установка разрешения расширения пула */
        pIMemExt->pVTbl->set_ExpandPool(pIMemExt, 1);
    }
    pIMemExt->pVTbl->Release(pIMemExt);
    /* Получение интерфейса управления памятью */
    g_pIBus->pVTbl->QueryComponent(g_pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryManager1, (void**) &pIMemMgr);
    if (result != 0 || pIMemMgr == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Инициализация кучи */
    pIMemMgr->pVTbl->Init(pIMemMgr, &__heap_start, 0x000200);
#endif /* ECO_AVR8 */

    /* Регистрация статического компонента для работы с компонентом "A" */
    //result = g_pIBus->pVTbl->RegisterComponent(g_pIBus, &CID_EcoCalculatorA, (IEcoUnknown*)GetIEcoComponentFactoryPtr_4828F6552E4540E78121EBD220DC360E);
    //if (result != 0 ) {
        /* Освобождение в случае ошибки */
    //    goto Release;
    //}
    /* Регистрация статического компонента для работы с компонентом "B" */
    result = g_pIBus->pVTbl->RegisterComponent(g_pIBus, &CID_EcoCalculatorB, (IEcoUnknown*)GetIEcoComponentFactoryPtr_AE202E543CE54550899603BD70C62565);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с компонентом "C" */
    //result = g_pIBus->pVTbl->RegisterComponent(g_pIBus, &CID_EcoCalculatorC, (IEcoUnknown*)GetIEcoComponentFactoryPtr_4828F6552E4540E78121EBD220DC360E);
    //if (result != 0 ) {
    //    /* Освобождение в случае ошибки */
    //    goto Release;
    //}
    /* Регистрация статического компонента для работы с компонентом "D" */
    //result = g_pIBus->pVTbl->RegisterComponent(g_pIBus, &CID_EcoCalculatorD, (IEcoUnknown*)GetIEcoComponentFactoryPtr_3A8E44677E82475CB4A3719ED8397E61);
    //if (result != 0 ) {
        /* Освобождение в случае ошибки */
    //    goto Release;
    //}
    /* Регистрация статического компонента для работы с компонентом "E" */
    result = g_pIBus->pVTbl->RegisterComponent(g_pIBus, &CID_EcoCalculatorE, (IEcoUnknown*)GetIEcoComponentFactoryPtr_872FEF1DE3314B87AD44D1E7C232C2F0);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif /* ECO_LIB */

    /* Начало блока кода реализующий выбор компонентов исходя из условий */

    /* Получение интерфейса по работе с умножением и делением у компонента "E" агрегирующего компонент "B" */
    result = g_pIBus->pVTbl->QueryComponent(g_pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**) &g_pIY);
    /* Проверка */
    if (result == 0 && g_pIY != 0) {
        /* Получение интерфейса по работе со сложением и вычитанием у компонента "B" */
        result = g_pIY->pVTbl->QueryInterface(g_pIY, &IID_IEcoCalculatorX, (void**) &g_pIX);
        g_iInfo = 5;
    }
    else {

        /* Получение интерфейса по работе с умножением и делением у компонента "D" включающего компонент "A" */
        result = g_pIBus->pVTbl->QueryComponent(g_pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**) &g_pIY);
        /* Проверка */
        if (result == 0 && g_pIY != 0) {
            /* Получение интерфейса по работе со сложением и вычитанием у компонента "A" */
            result = g_pIY->pVTbl->QueryInterface(g_pIY, &IID_IEcoCalculatorX, (void**) &g_pIX);
            g_iInfo = 4;
        }
        else {

            /* Получение интерфейса по работе с умножением и делением у компонента "C" */
            result = g_pIBus->pVTbl->QueryComponent(g_pIBus, &CID_EcoCalculatorC, 0, &IID_IEcoCalculatorY, (void**) &g_pIY);
            /* Проверка */
            if (result == 0 && g_pIY != 0) {
                /* Получение интерфейса по работе со сложением и вычитанием у компонента "C" */
                result = g_pIY->pVTbl->QueryInterface(g_pIY, &IID_IEcoCalculatorX, (void**) &g_pIX);
                g_iInfo = 3;
            }
            else {
                /* Получение интерфейса по работе со сложением и вычитанием у компонента "B" c поддержкой агрегирования */
                result = g_pIBus->pVTbl->QueryComponent(g_pIBus, &CID_EcoCalculatorB, 0, &IID_IEcoCalculatorX, (void**) &g_pIX);
                /* Проверка */
                if (result != 0 || g_pIX == 0) {
                    /* Получение интерфейса по работе со сложением и вычитанием у компонента "A" */
                    result = g_pIBus->pVTbl->QueryComponent(g_pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &g_pIX);
                    if (result == 0 && g_pIX != 0) {
                        g_iInfo = 1;
                    }
                }
                else {
                    g_iInfo = 2;
                }
            }
        }
    }
    /* Завершение блока кода выбора компонентов */

    DialogProcessing();

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (g_pIBus != 0) {
        g_pIBus->pVTbl->Release(g_pIBus);
    }

    /* Освобождение интерфейса менеджера памяти */
    if (pIMemMgr != 0) {
        pIMemMgr->pVTbl->Release(pIMemMgr);
    }

    /* Освобождение интерфейса калькулятора */


    if (g_pIY != 0) {
        g_pIY->pVTbl->Release(g_pIY);
    }

    if (g_pIX != 0) {
        g_pIX->pVTbl->Release(g_pIX);
    }

    /* Освобождение системного интерфейса */
    if (g_pISys != 0) {
        g_pISys->pVTbl->Release(g_pISys);
    }

    return result;
}

