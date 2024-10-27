﻿/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEco.CalculatorDFactory
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию фабрики для компонента
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoCalculatorD.h"
#include "CEcoCalculatorDFactory.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция возвращает указатель на интерфейс
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorDFactory_QueryInterface(IEcoComponentFactoryPtr_t me, const UGUID* riid, voidptr_t* ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoComponentFactory) ) {
        *ppv = me;
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    ((IEcoUnknown*)(*ppv))->pVTbl->AddRef((IEcoUnknown*)*ppv);

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция увеличивает количество ссылок на интерфейс
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorDFactory_AddRef(/* in */ IEcoComponentFactoryPtr_t me) {
    CEcoCalculatorDFactory* pCMe = (CEcoCalculatorDFactory*)me;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция уменьшает количество ссылок на интерфейс
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorDFactory_Release(/* in */ IEcoComponentFactoryPtr_t me) {
    CEcoCalculatorDFactory* pCMe = (CEcoCalculatorDFactory*)me;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        //deleteCEcoCalculatorDFactory(&pCMe->m_VtblICF);
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
 *   Функция инициализирует компонент с параметрами
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorDFactory_Init(/* in */ IEcoComponentFactoryPtr_t me, /* in */ struct IEcoUnknown *pIUnkSystem, /* in */ void* pv) {
    CEcoCalculatorDFactory* pCMe = (CEcoCalculatorDFactory*)me;
    int16_t result = ERR_ECO_POINTER;

    if (me == 0 ) {
        return result;
    }

    /* Инициализация компонента */
    result = pCMe->m_pInitInstance(pv, pIUnkSystem);

    return result;
}

/*
 *
 * <сводка>
 *   Функция Alloc
 * </сводка>
 *
 * <описание>
 *   Функция создает компонент
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorDFactory_Alloc(/* in */ IEcoComponentFactoryPtr_t me, /* in */ struct IEcoUnknown *pISystem, /* in */ struct IEcoUnknown *pIUnknownOuter, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoCalculatorDFactory* pCMe = (CEcoCalculatorDFactory*)me;
    IEcoUnknown* pIUnk = 0;
    int16_t result = ERR_ECO_POINTER;

    if (me == 0 ) {
        return result;
    }

    /* Агрегирование при условии если IID это IID_IEcoUnknown */
    if ( ( pIUnknownOuter != 0 ) && !IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        /* не поддерживает агрегирование */
        return ERR_ECO_NOAGGREGATION;
    }

    /* Создание компонента */
    result = pCMe->m_pInstance(pISystem, pIUnknownOuter, (void**)&pIUnk);
    if ( result != 0 || pIUnk == 0) {
        return result;
    }

    /* Инициализация компонента */
    result = me->pVTbl->Init(me, pISystem, pIUnk);

    /* Получение указателя на интерфейс */
    result = pIUnk->pVTbl->QueryInterface(pIUnk, riid, ppv);

    /* Уменьшение ссылки запрошенной Фабрикой компонентов */
    pIUnk->pVTbl->Release(pIUnk);

    return result;
}

/*
 *
 * <сводка>
 *   Функция get_Name
 * </сводка>
 *
 * <описание>
 *   Функция возвращает наименование компонента
 * </описание>
 *
 */
static char_t* ECOCALLMETHOD CEcoCalculatorDFactory_get_Name(/* in */ IEcoComponentFactoryPtr_t me) {
    CEcoCalculatorDFactory* pCMe = (CEcoCalculatorDFactory*)me;

    if (me == 0 ) { /* ERR_ECO_POINTER */
        return 0;
    }

    return pCMe->m_Name;
}

/*
 *
 * <сводка>
 *   Функция get_Version
 * </сводка>
 *
 * <описание>
 *   Функция возвращает версию компонента
 * </описание>
 *
 */
static char_t* ECOCALLMETHOD CEcoCalculatorDFactory_get_Version(/* in */ IEcoComponentFactoryPtr_t me) {
    CEcoCalculatorDFactory* pCMe = (CEcoCalculatorDFactory*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
    }

    return pCMe->m_Version;
}

/*
 *
 * <сводка>
 *   Функция get_Manufacturer
 * </сводка>
 *
 * <описание>
 *   Функция возвращает наименование производителя компонента
 * </описание>
 *
 */
static char_t* ECOCALLMETHOD CEcoCalculatorDFactory_get_Manufacturer(/* in */ IEcoComponentFactoryPtr_t me) {
    CEcoCalculatorDFactory* pCMe = (CEcoCalculatorDFactory*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
    }

    return pCMe->m_Manufacturer;
}
/* Create Virtual Table */
IEcoComponentFactoryVTbl g_x3A8E44677E82475CB4A3719ED8397E61FactoryVTbl = {
    CEcoCalculatorDFactory_QueryInterface,
    CEcoCalculatorDFactory_AddRef,
    CEcoCalculatorDFactory_Release,
    CEcoCalculatorDFactory_Alloc,
    CEcoCalculatorDFactory_Init,
    CEcoCalculatorDFactory_get_Name,
    CEcoCalculatorDFactory_get_Version,
    CEcoCalculatorDFactory_get_Manufacturer
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
CEcoCalculatorDFactory g_x3A8E44677E82475CB4A3719ED8397E61Factory = {
    &g_x3A8E44677E82475CB4A3719ED8397E61FactoryVTbl,
    0,
    (CreateInstance)createCEcoCalculatorD,
    (InitInstance)initCEcoCalculatorD,
    "Eco.CalculatorD\0",
    "2.0.0.0\0",
    "PeerF\0"
};

#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr() {
    return (IEcoComponentFactory*)&g_x3A8E44677E82475CB4A3719ED8397E61Factory;
};
#elif ECO_LIB
IEcoComponentFactory* GetIEcoComponentFactoryPtr_3A8E44677E82475CB4A3719ED8397E61 = (IEcoComponentFactory*)&g_x3A8E44677E82475CB4A3719ED8397E61Factory;
#endif