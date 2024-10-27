/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoCalculatorX
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoCalculatorX
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

#ifndef __I_ECO_CALCULATOR_X_HPP__
#define __I_ECO_CALCULATOR_X_HPP__

#include "IEcoBase1.hpp"

/* IEcoCalculatorX IID = {93221116-2248-4742-AE06-82819447843D} */
#ifndef __IID_IEcoCalculatorX
static const UGUID IID_IEcoCalculatorX = {0x01, 0x10, {0x93, 0x22, 0x11, 0x16, 0x22, 0x48, 0x47, 0x42, 0xAE, 0x06, 0x82, 0x81, 0x94, 0x47, 0x84, 0x3D}};
#endif /* __IID_IEcoCalculatorX */

interface IEcoCalculatorX : public IEcoUnknown {
public:
    /* IEcoCalculatorX */
    virtual int32_t ECOCALLMETHOD Addition(/* in */ int16_t a, /* in */ int16_t b) = 0;
    virtual int16_t ECOCALLMETHOD Subtraction(/* in */ int16_t a, /* in */ int16_t b) = 0;
};

#endif /* __I_ECO_CALCULATOR_X_HPP__ */
