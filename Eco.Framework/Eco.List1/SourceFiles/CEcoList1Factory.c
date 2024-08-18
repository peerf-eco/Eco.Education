/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoList1Factory
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

#include "CEcoList1.h"
#include "CEcoList1Factory.h"

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
static int16_t ECOCALLMETHOD CEcoList1Factory_3A562281_QueryInterface(IEcoComponentFactoryPtr_t me, const UGUID* riid, voidptr_t* ppv) {
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
static uint32_t ECOCALLMETHOD CEcoList1Factory_3A562281_AddRef(/* in */ IEcoComponentFactoryPtr_t me) {
     CEcoList1Factory_3A562281* pCMe = (CEcoList1Factory_3A562281*)me;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return atomicincrement_int32_t(&pCMe->m_cRef);
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
static uint32_t ECOCALLMETHOD CEcoList1Factory_3A562281_Release(/* in */ IEcoComponentFactoryPtr_t me) {
    CEcoList1Factory_3A562281* pCMe = (CEcoList1Factory_3A562281*)me;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    atomicdecrement_int32_t(&pCMe->m_cRef);

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        //deleteCEcoList1Factory(&pCMe->m_VtblICF);
        return ERR_ECO_SUCCESES;
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
static int16_t ECOCALLMETHOD CEcoList1Factory_3A562281_Init(/* in */ IEcoComponentFactoryPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ voidptr_t pv) {
    CEcoList1Factory_3A562281* pCMe = (CEcoList1Factory_3A562281*)me;
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
static int16_t ECOCALLMETHOD CEcoList1Factory_3A562281_Alloc(/* in */IEcoComponentFactoryPtr_t me, /* in */ IEcoUnknownPtr_t pISystem, /* in */ IEcoUnknownPtr_t pIUnknownOuter, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv) {
    CEcoList1Factory_3A562281* pCMe = (CEcoList1Factory_3A562281*)me;
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
    result = pCMe->m_pInstance(pISystem, pIUnknownOuter, (voidptr_t*)&pIUnk);
    if ( result != 0 || pIUnk == 0) {
        return result;
    }

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
static char_t* ECOCALLMETHOD CEcoList1Factory_3A562281_get_Name(/* in */ IEcoComponentFactoryPtr_t me) {
    CEcoList1Factory_3A562281* pCMe = (CEcoList1Factory_3A562281*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
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
static char_t* ECOCALLMETHOD CEcoList1Factory_3A562281_get_Version(/* in */ IEcoComponentFactoryPtr_t me) {
    CEcoList1Factory_3A562281* pCMe = (CEcoList1Factory_3A562281*)me;

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
static char_t* ECOCALLMETHOD CEcoList1Factory_3A562281_get_Manufacturer(/* in */ IEcoComponentFactoryPtr_t me) {
    CEcoList1Factory_3A562281* pCMe = (CEcoList1Factory_3A562281*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
    }

    return pCMe->m_Manufacturer;
}

/* Create Virtual Table */
IEcoComponentFactoryVTbl g_x53884AFC93C448ECAA929C8D3A562281FactoryVTbl = {
    CEcoList1Factory_3A562281_QueryInterface,
    CEcoList1Factory_3A562281_AddRef,
    CEcoList1Factory_3A562281_Release,
    CEcoList1Factory_3A562281_Alloc,
    CEcoList1Factory_3A562281_Init,
    CEcoList1Factory_3A562281_get_Name,
    CEcoList1Factory_3A562281_get_Version,
    CEcoList1Factory_3A562281_get_Manufacturer
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
CEcoList1Factory_3A562281 g_x53884AFC93C448ECAA929C8D3A562281Factory = {
    &g_x53884AFC93C448ECAA929C8D3A562281FactoryVTbl,
    0,
    (CreateInstance)createCEcoList1_3A562281,
    (InitInstance)initCEcoList1_3A562281,
    "Eco.List\0",
    "1.0.0.0\0",
    "PeerF\0"
};

#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr() {
    return (IEcoComponentFactory*)&g_x53884AFC93C448ECAA929C8D3A562281Factory;
};
#elif ECO_LIB
IEcoComponentFactory* GetIEcoComponentFactoryPtr_53884AFC93C448ECAA929C8D3A562281 = (IEcoComponentFactory*)&g_x53884AFC93C448ECAA929C8D3A562281Factory;
#endif
