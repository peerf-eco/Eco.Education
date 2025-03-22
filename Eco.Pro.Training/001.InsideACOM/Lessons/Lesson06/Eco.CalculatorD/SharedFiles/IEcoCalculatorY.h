/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoCalculatorY
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoCalculatorY
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_CALCULATOR_Y_H__
#define __I_ECO_CALCULATOR_Y_H__

#include "IEcoBase1.h"

/* IEcoCalculatorY IID = {BD6414C2-9096-423E-A90C-04D77AFD1CAD} */
#ifndef __IID_IEcoCalculatorY
static const UGUID IID_IEcoCalculatorY = {0x01, 0x10, {0xBD, 0x64, 0x14, 0xC2, 0x90, 0x96, 0x42, 0x3E, 0xA9, 0x0C, 0x04, 0xD7, 0x7A, 0xFD, 0x1C, 0xAD}};
#endif /* __IID_IEcoCalculatorY */

typedef struct IEcoCalculatorY* IEcoCalculatorYPtr_t;

typedef struct IEcoCalculatorYVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoCalculatorYPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoCalculatorYPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoCalculatorYPtr_t me);

    /* IEcoCalculatorY */
    int32_t (ECOCALLMETHOD *Multiplication)(/* in */ IEcoCalculatorYPtr_t me, /* in */ int16_t a, /* in */ int16_t b);
    int16_t (ECOCALLMETHOD *Division)(/* in */ IEcoCalculatorYPtr_t me, /* in */ int16_t a, /* in */ int16_t b);

} IEcoCalculatorYVTbl, *IEcoCalculatorYVTblPtr;

interface IEcoCalculatorY {
    struct IEcoCalculatorYVTbl *pVTbl;
} IEcoCalculatorY;

#endif /* __I_ECO_CALCULATOR_Y_H__ */
