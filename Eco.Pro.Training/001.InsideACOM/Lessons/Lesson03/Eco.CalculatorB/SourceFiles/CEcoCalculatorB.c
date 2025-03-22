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
 *   Данный исходный код описывает реализацию интерфейсов CEcoCalculatorB
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoCalculatorB.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorB_QueryInterface(/* in */ IEcoCalculatorXPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorB_AddRef(/* in */ IEcoCalculatorXPtr_t me) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return pCMe->m_pIUnkOuter->pVTbl->AddRef(pCMe->m_pIUnkOuter);
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorB_Release(/* in */ IEcoCalculatorXPtr_t me) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return pCMe->m_pIUnkOuter->pVTbl->Release(pCMe->m_pIUnkOuter);
}

/*
 *
 * <сводка>
 *   Функция Addition
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int32_t ECOCALLMETHOD CEcoCalculatorB_Addition(/* in */ IEcoCalculatorXPtr_t me, /* in */ int16_t a, /* in */ int16_t b) {
    /*CEcoCalculatorB* pCMe = (CEcoCalculatorB*)me;*/
    int32_t result = 0;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    result = a + b;

    return result;
}

/*
 *
 * <сводка>
 *   Функция Subtraction
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorB_Subtraction(/* in */ IEcoCalculatorXPtr_t me, /* in */ int16_t a, /* in */ int16_t b) {
    /*CEcoCalculatorB* pCMe = (CEcoCalculatorB*)me;*/
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    result = a - b;

    return result;
}


/*
 *
 * <сводка>
 *   Функция NondelegatingQueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция NondelegatingQueryInterface для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorB_NondelegatingQueryInterface(/* in */IEcoUnknownPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoCalculatorX) ) {
        *ppv = &pCMe->m_pVTblIX;
        ((IEcoUnknown*)(*ppv))->pVTbl->AddRef((IEcoUnknown*)(*ppv));
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblINondelegatingUnk;
        ++pCMe->m_cRef;
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция NondelegatingAddRef
 * </сводка>
 *
 * <описание>
 *   Функция NondelegatingAddRef для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorB_NondelegatingAddRef(/* in */ IEcoUnknownPtr_t me) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция NondelegatingRelease
 * </сводка>
 *
 * <описание>
 *   Функция NondelegatingRelease для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorB_NondelegatingRelease(/* in */ IEcoUnknownPtr_t me) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoCalculatorB((IEcoCalculatorX*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoCalculatorB(/*in*/IEcoCalculatorXPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    /*CEcoCalculatorB* pCMe = (CEcoCalculatorB*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));*/

    /* Проверка указателей */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    /* Сохранение указателя на системный интерфейс */
    /*pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;*/

    /* Инициализация данных */

    return ERR_ECO_SUCCESES;
}

/* Create Virtual Table */
IEcoCalculatorXVTbl g_x9322111622484742AE0682819447843DVTblB = {
    CEcoCalculatorB_QueryInterface,
    CEcoCalculatorB_AddRef,
    CEcoCalculatorB_Release,
    CEcoCalculatorB_Addition,
    CEcoCalculatorB_Subtraction
};

/* Create Virtual Table */
IEcoUnknownVTbl g_x000000000000000000000000000000AAVTblB = {
    CEcoCalculatorB_NondelegatingQueryInterface,
    CEcoCalculatorB_NondelegatingAddRef,
    CEcoCalculatorB_NondelegatingRelease
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoCalculatorB(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoCalculatorXPtr_t* ppIX) {
    CEcoCalculatorB* pCMe = 0;
    int16_t result = ERR_ECO_POINTER;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIX == 0 || pIUnkSystem == 0) {
        return result; /* ERR_ECO_POINTER */
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (voidptr_t*)&pISys);
    /* Проверка */
    if (result != 0 || pISys == 0) {
        return ERR_ECO_NOSYSTEM;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (voidptr_t*)&pIBus);
    /* Проверка */
    if (result != 0 || pIBus == 0) {
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_NOBUS;
    }

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    result = pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (voidptr_t*) &pIMem);
    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение в случае ошибки */
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoCalculatorB*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoCalculatorB));
    if (pCMe == 0) {
        /* Освобождение в случае ошибки */
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_OUTOFMEMORY;
    }
    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoCalculatorX */
    pCMe->m_pVTblIX = &g_x9322111622484742AE0682819447843DVTblB;

    /* Неделигирующий интерфейс IEcoUnknown */
    pCMe->m_pVTblINondelegatingUnk = &g_x000000000000000000000000000000AAVTblB;

    pCMe->m_pIUnkOuter = 0;
    /* Если не агрегируется, использовать неделигирующий интерфейс IEcoUnknown */
    if (pIUnkOuter != 0) {
        pCMe->m_pIUnkOuter = pIUnkOuter;
    } else {
        pCMe->m_pIUnkOuter = (IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk;
    }

    /* Возврат указателя на интерфейс */
    *ppIX = (IEcoCalculatorX*)&pCMe->m_pVTblINondelegatingUnk;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoCalculatorB(/* in */ IEcoCalculatorXPtr_t pIX) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)pIX;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIX != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
