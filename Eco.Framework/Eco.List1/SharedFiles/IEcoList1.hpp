/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoList1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoList1
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

#ifndef __I_ECO_LIST_1_HPP__
#define __I_ECO_LIST_1_HPP__

#include "IEcoBase1.hpp"

/* IEcoList1 IID = {5AADBCB4-846C-4576-827B-287B5E67A152} */
#ifndef __IID_IEcoList1
static const UGUID IID_IEcoList1 = {0x01, 0x10, {0x5A, 0xAD, 0xBC, 0xB4, 0x84, 0x6C, 0x45, 0x76, 0x82, 0x7B, 0x28, 0x7B, 0x5E, 0x67, 0xA1, 0x52}};
#endif /* __IID_IEcoList1 */

interface IEcoList1 : public IEcoUnknown {
public:
    /* IEcoList1 */
    virtual uint32_t ECOCALLMETHOD Count(/* in*/ void) = 0;
    virtual void* ECOCALLMETHOD Item(/* in */ uint32_t index) = 0;
    virtual uint32_t ECOCALLMETHOD Add(/* in */ void* value) = 0;
    virtual uint32_t ECOCALLMETHOD IndexOf(/* in */ void* value) = 0;
    virtual void ECOCALLMETHOD InsertAt(/* in */ uint32_t index, /* in */ void* value) = 0;
    virtual void ECOCALLMETHOD Remove(/* in */ void* value) = 0;
    virtual void ECOCALLMETHOD RemoveAt(/* in */ uint32_t index) = 0;
    virtual void ECOCALLMETHOD Clear() = 0;
};

#endif /* __I_ECO_LIST_1_HPP__ */

