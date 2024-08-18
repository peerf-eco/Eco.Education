/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoList1
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
#include "IEcoInterfaceBus1.h"
#include "IdEcoList1.h"
#include "IEcoError1.h"

/* Глобальный указатель на системный интерфейс */
IEcoSystem1* g_pISys = 0;

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
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    IEcoError1* pIErr = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    char_t ptrErrMessage[100] = {0};
    uint16_t iErrSize = 100;
    char_t* ptrStr = 0;
    char_t* pszStr1 = "Test String 1";
    char_t* pszStr2 = "Test String 2";
    /* Указатель на тестируемый интерфейс */
    IEcoList1* pIList = 0;
    uint32_t iCount = 0;
    uint32_t iIndex = 0;

    /* Проверка и создание системного интрефейса */
    if (g_pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&g_pISys);
        if (result != 0 && g_pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = g_pISys->pVTbl->QueryInterface(g_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса обработки ошибок */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoError1, (void **)&pIErr);
    if (result != 0 || pIErr == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    pIErr->pVTbl->get_Description(pIErr, result, (void*)ptrErrMessage, &iErrSize);

#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoList1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_53884AFC93C448ECAA929C8D3A562281);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif

    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**) &pIList);
    if (result != 0 || pIList == 0) {
        iErrSize = 100;
        pIErr->pVTbl->get_Description(pIErr, result, (void*)ptrErrMessage, &iErrSize);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Формирование саиска */
    iIndex = pIList->pVTbl->Add(pIList, pszStr1);
    iIndex = pIList->pVTbl->Add(pIList, pszStr2);
    iCount = pIList->pVTbl->Count(pIList);
    /* Проверка количества элементов списка */
    if (iCount == 2) {
        for (iIndex = 0; iIndex < iCount; iIndex++) {
            ptrStr = (char_t*)pIList->pVTbl->Item(pIList, iIndex);
        }
        /* Удаление элемента по индексу */
        pIList->pVTbl->RemoveAt(pIList, 0);
        /* Удаление элемента по указателю */
        pIList->pVTbl->Remove(pIList, pszStr2);
    }
    iCount = pIList->pVTbl->Count(pIList);
    /* Формирование списка */
    //iIndex = pIList->pVTbl->Add(pIList, pszStr1);
    pIList->pVTbl->InsertAt(pIList, 0, pszStr1);
    pIList->pVTbl->InsertAt(pIList, 0, pszStr2);
    iIndex = pIList->pVTbl->IndexOf(pIList, pszStr1);
    /* удаление всех элементов из списка */
    pIList->pVTbl->Clear(pIList);
    iCount = pIList->pVTbl->Count(pIList);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIList != 0) {
        pIList->pVTbl->Release(pIList);
    }

    /* Освобождение системного интерфейса */
    if (g_pISys != 0) {
        g_pISys->pVTbl->Release(g_pISys);
    }

    return result;
}

