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
 *   Данный исходный код описывает реализацию интерфейсов CEcoList1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoList1.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoList1
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoList1_3A562281_QueryInterface(/* in */ IEcoList1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv) {
    CEcoList1_3A562281* pCMe = (CEcoList1_3A562281*)me;

    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoList1) ) {
        *ppv = &pCMe->m_pVTblIList;
        pCMe->m_pVTblIList->AddRef((IEcoList1Ptr_t)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIList;
        pCMe->m_pVTblIList->AddRef((IEcoList1Ptr_t)pCMe);
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
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoList1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoList1_3A562281_AddRef(/* in */ IEcoList1Ptr_t me) {
    CEcoList1_3A562281* pCMe = (CEcoList1_3A562281*)me;

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
 *   Функция Release для интерфейса IEcoList1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoList1_3A562281_Release(/* in */ IEcoList1Ptr_t me) {
    CEcoList1_3A562281* pCMe = (CEcoList1_3A562281*)me;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    atomicdecrement_int32_t(&pCMe->m_cRef);

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoList1_3A562281((IEcoList1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Count
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoList1_3A562281_Count(/* in */ IEcoList1Ptr_t me) {
    CEcoList1_3A562281* pCMe = (CEcoList1_3A562281*)me;

    if (pCMe != 0) {
        return pCMe->m_Count;
    }

    return 0; /* ERR_ECO_POINTER */
}

/*
 *
 * <сводка>
 *   Функция Item
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static void* ECOCALLMETHOD CEcoList1_3A562281_Item(/* in */ IEcoList1Ptr_t me, uint32_t index) {
    CEcoList1_3A562281* pCMe = (CEcoList1_3A562281*)me;
    CEcoList1Node_3A562281* pPrev = 0;
    void* pElement = 0;

    if (pCMe != 0) {
        if (pCMe->m_Count > 0 && index < pCMe->m_Count) {
            pPrev = pCMe->m_Elements;
            do {
                if (index == 0) {
                    pElement = pPrev->data;
                    break;
                }
                index--;
                pPrev = pPrev->next;

            } while (pPrev != 0);
        }
    }
    return pElement;
}

/*
 *
 * <сводка>
 *   Функция Add
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoList1_3A562281_Add(/* in */ IEcoList1Ptr_t me, voidptr_t value) {
    CEcoList1_3A562281* pCMe = (CEcoList1_3A562281*)me;
    CEcoList1Node_3A562281* pTemp = 0;
    uint32_t index = -1;

    if (pCMe != 0) {
        if (pCMe->m_Elements == 0) {
            pCMe->m_Elements = (CEcoList1Node_3A562281*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoList1Node_3A562281));
            if (pCMe->m_Elements == 0) {
                return index;
            }
            pCMe->m_Elements->data = value;
            pCMe->m_Elements->next = 0;
            index = 0;
            pCMe->m_Count = 1;
        }
        else {
            pTemp =  pCMe->m_Elements;
            while ( pTemp->next != 0) {
                pTemp = pTemp->next;
            }
            pTemp->next = (CEcoList1Node_3A562281*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoList1Node_3A562281));
            pTemp = pTemp->next;
            pTemp->data = value;
            pTemp->next = 0;
            index = pCMe->m_Count;
            pCMe->m_Count++;
        }
    }
    return index;
}

/*
 *
 * <сводка>
 *   Функция Remove
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static void ECOCALLMETHOD CEcoList1_3A562281_Remove(/* in */ IEcoList1Ptr_t me, voidptr_t value) {
    CEcoList1_3A562281* pCMe = (CEcoList1_3A562281*)me;
    CEcoList1Node_3A562281* pPrev = 0;
    CEcoList1Node_3A562281* pTemp = 0;

    if (pCMe != 0) {
        if (pCMe->m_Count > 0 ) {
            pPrev = pCMe->m_Elements;
            /* Проверка на начальный элемент списка */
            if (pPrev->data == value) {
                if (pCMe->m_Count == 1 ) {
                    pCMe->m_Elements = 0;
                    pCMe->m_Count = 0;
                }
                else {
                    pCMe->m_Elements = pPrev->next;
                    pCMe->m_Count = pCMe->m_Count -1;
                }
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pPrev);
                return;
            }
            while (pPrev->next != 0) {
                pTemp = pPrev->next;
                if (pTemp->data == value) {
                    /* Проверка на последний элемент списка */
                    if (pTemp->next == 0) {
                        pPrev->next = 0;
                    }
                    else {
                        pPrev->next = pTemp->next;
                    }
                    pCMe->m_Count = pCMe->m_Count - 1;
                    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pTemp);
                    break;
                }
                pPrev = pTemp;
            }
        }
    }
}

/*
 *
 * <сводка>
 *   Функция RemoveAt
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static void ECOCALLMETHOD CEcoList1_3A562281_RemoveAt(/* in */ IEcoList1Ptr_t me, uint32_t index) {
    CEcoList1_3A562281* pCMe = (CEcoList1_3A562281*)me;
    CEcoList1Node_3A562281* pPrev = 0;
    CEcoList1Node_3A562281* pTemp = 0;

    if (pCMe != 0) {
        if (pCMe->m_Count > 0 ) {
            pPrev = pCMe->m_Elements;
            /* Проверка на начальный элемент списка */
            if (index == 0) {
                if (pCMe->m_Count == 1 ) {
                    pCMe->m_Elements = 0;
                    pCMe->m_Count = 0;
                }
                else {
                    pCMe->m_Elements = pPrev->next;
                    pCMe->m_Count = pCMe->m_Count -1;
                }
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pPrev);
                return;
            }
            while (pPrev->next != 0) {
                index--;
                pTemp = pPrev->next;
                if (index == 0) {
                    /* Проверка на последний элемент списка */
                    if (pTemp->next == 0) {
                        pPrev->next = 0;
                    }
                    else {
                        pPrev->next = pTemp->next;
                    }
                    pCMe->m_Count = pCMe->m_Count - 1;
                    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pTemp);
                    break;
                }
                pPrev = pTemp;
            }
        }
    }
}

/*
 *
 * <сводка>
 *   Функция InsertAt
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static void ECOCALLMETHOD CEcoList1_3A562281_InsertAt(/* in */ IEcoList1Ptr_t me, uint32_t index, voidptr_t value) {
    CEcoList1_3A562281* pCMe = (CEcoList1_3A562281*)me;
    CEcoList1Node_3A562281* pPrev = 0;
    CEcoList1Node_3A562281* pTemp = 0;

    if (pCMe != 0) {
        if (pCMe->m_Count > 0 && index < pCMe->m_Count) {
            pPrev = pCMe->m_Elements;
            do {
                if (index == 0) {
                    pTemp = (CEcoList1Node_3A562281*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoList1Node_3A562281));
                    /* Недостаточно памяти для выделения */
                    if (pTemp == 0) {
                        return;
                    }
                    pTemp->data = value;
                    pTemp->next = pPrev;
                    pCMe->m_Count++;
                    /* Проверка на начало списка */
                    if (pPrev == pCMe->m_Elements) {
                        pCMe->m_Elements = pTemp;
                    }
                    break;
                }
                index--;
                pPrev = pPrev->next;

            } while (pPrev != 0);
        }
    }
}

/*
 *
 * <сводка>
 *   Функция IndexOf
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoList1_3A562281_IndexOf(/* in */ IEcoList1Ptr_t me, /* in */ voidptr_t value) {
    CEcoList1_3A562281* pCMe =  (CEcoList1_3A562281*)me;
    CEcoList1Node_3A562281* pPrev = 0;
    uint32_t index = 0;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    if (pCMe != 0) {
        if (pCMe->m_Count > 0 && index < pCMe->m_Count) {
            pPrev = pCMe->m_Elements;
            index = 0;
            while (pPrev != 0) {
                if (pPrev->data == value) {
                    break;
                }
                index++;
                pPrev = pPrev->next;
                if (pPrev == 0) {
                    index = -1;
                }
            };
        }
    }
    return index;
}

/*
 *
 * <сводка>
 *   Функция Clear
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static void ECOCALLMETHOD CEcoList1_3A562281_Clear(/* in */ IEcoList1Ptr_t me) {
    CEcoList1_3A562281* pCMe = (CEcoList1_3A562281*)me;
    CEcoList1Node_3A562281* pPrev = 0;
    CEcoList1Node_3A562281* pTemp = 0;

    if (pCMe != 0 ) {
        if (pCMe->m_Count > 0 ) {
            pPrev = pCMe->m_Elements;
            while (pPrev != 0) {
                pTemp = pPrev;
                pPrev = pPrev->next;
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pTemp);
            }
            pCMe->m_Count = 0;
            pCMe->m_Elements = 0;
        }
    }
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
int16_t ECOCALLMETHOD initCEcoList1_3A562281(/*in*/ IEcoList1Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    /*CEcoList1_3A562281* pCMe = (CEcoList1_3A562281*)me;*/

    /* Проверка указателей */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    /* Инициализация данных */

    return ERR_ECO_SUCCESES;
}

/* Create Virtual Table */
IEcoList1VTbl g_x5AADBCB4846C4576827B287B5E67A152VTbl_3A562281 = {
    CEcoList1_3A562281_QueryInterface,
    CEcoList1_3A562281_AddRef,
    CEcoList1_3A562281_Release,
    CEcoList1_3A562281_Count,
    CEcoList1_3A562281_Item,
    CEcoList1_3A562281_Add,
    CEcoList1_3A562281_IndexOf,
    CEcoList1_3A562281_InsertAt,
    CEcoList1_3A562281_Remove,
    CEcoList1_3A562281_RemoveAt,
    CEcoList1_3A562281_Clear
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
int16_t ECOCALLMETHOD createCEcoList1_3A562281(/* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* out */ IEcoList1Ptr_t* ppIList) {
    CEcoList1_3A562281* pCMe = 0;
    int16_t result = ERR_ECO_POINTER;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIList == 0 || pIUnkSystem == 0) {
        return result; /* ERR_ECO_POINTER */
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (voidptr_t*)&pISys);
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
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (voidptr_t*) &pIMem);
    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение в случае ошибки */
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoList1_3A562281*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoList1_3A562281));
    if (pCMe == 0) {
        /* Освобождение в случае ошибки */
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_OUTOFMEMORY;
    }
    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Инициализация данных экземпляра */
    pCMe->m_Elements = 0;
    pCMe->m_Count = 0;

    /* Создание таблицы функций интерфейса IEcoList1 */
    pCMe->m_pVTblIList = &g_x5AADBCB4846C4576827B287B5E67A152VTbl_3A562281;

    /* Возврат указателя на интерфейс */
    *ppIList = (IEcoList1*)pCMe;

    /* Освобождение интерфейсной шиной */
    pIBus->pVTbl->Release(pIBus);

    /* Освобождение системного интерфейса */
    pISys->pVTbl->Release(pISys);

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
void ECOCALLMETHOD deleteCEcoList1_3A562281(/* in */ IEcoList1Ptr_t pIList) {
    CEcoList1_3A562281* pCMe = (CEcoList1_3A562281*)pIList;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIList != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
