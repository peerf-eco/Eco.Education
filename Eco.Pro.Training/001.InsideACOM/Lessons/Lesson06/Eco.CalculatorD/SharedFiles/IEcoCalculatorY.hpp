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

#ifndef __I_ECO_CALCULATOR_Y_HPP__
#define __I_ECO_CALCULATOR_Y_HPP__

#include "IEcoBase1.hpp"

/* IEcoCalculatorY IID = {BD6414C2-9096-423E-A90C-04D77AFD1CAD} */
#ifndef __IID_IEcoCalculatorY
static const UGUID IID_IEcoCalculatorY = {0x01, 0x10, {0xBD, 0x64, 0x14, 0xC2, 0x90, 0x96, 0x42, 0x3E, 0xA9, 0x0C, 0x04, 0xD7, 0x7A, 0xFD, 0x1C, 0xAD}};
#endif /* __IID_IEcoCalculatorY */

interface IEcoCalculatorY : public IEcoUnknown {
public:
    /* IEcoCalculatorY */
    virtual int32_t ECOCALLMETHOD Multiplication(/* in */ int16_t a, /* in */ int16_t b) = 0;
    virtual int16_t ECOCALLMETHOD Division(/* in */ int16_t a, /* in */ int16_t b) = 0;

};

#endif /* __I_ECO_CALCULATOR_Y_HPP__ */
