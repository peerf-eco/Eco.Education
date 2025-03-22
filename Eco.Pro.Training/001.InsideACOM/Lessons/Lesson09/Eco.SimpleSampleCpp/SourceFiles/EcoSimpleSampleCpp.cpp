// Eco.SimpleSampleCpp.cpp : Defines the entry point for the console application.
//

#include "IEcoBase1.hpp"
#include "IEcoSystem1.hpp"
#include "IdEcoInterfaceBus1.hpp"
#include "IdEcoMemoryManager1.hpp"
#include "IEcoCalculatorX.hpp"
#include "IdEcoCalculatorA.hpp"

extern "C" int16_t EcoMain(IEcoUnknown* pIUnk);

int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    char_t* name = 0;
    char_t* copyName = 0;
    int16_t c = 0;
    /* Указатели на интерфейсы калькулятора */
    IEcoCalculatorX* pIX = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->QueryInterface(&GID_IEcoSystem, (void **)&pISys);
        if (result != 0 || pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->QueryInterface(&IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса управления памятью */
    result = pIBus->QueryComponent(&CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**)&pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса для работы с калькулятором */
    result = pIBus->QueryComponent(&CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**)&pIX);

    /* Проверка */
    if (result != 0 || pIX == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Пример использования */
    name = (char_t*)pIMem->Alloc(10);
    pIMem->Fill(name, 'a', 9);
    pIMem->Free(name);

    c = pIX->Addition(10, 5);

    c = pIX->Subtraction(10, 5);

Release:

    /* Освобождение интерфейса */
    if (pIX != 0) {
        pIX->Release();
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->Release();
    }

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->Release();
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->Release();
    }

    return 0;
}
