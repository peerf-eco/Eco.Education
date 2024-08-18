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

#ifndef __I_ECO_LIST_1_H__
#define __I_ECO_LIST_1_H__

#include "IEcoBase1.h"

/* IEcoList1 IID = {5AADBCB4-846C-4576-827B-287B5E67A152} */
#ifndef __IID_IEcoList1
static const UGUID IID_IEcoList1 = {0x01, 0x10, {0x5A, 0xAD, 0xBC, 0xB4, 0x84, 0x6C, 0x45, 0x76, 0x82, 0x7B, 0x28, 0x7B, 0x5E, 0x67, 0xA1, 0x52}};
#endif /* __IID_IEcoList1 */

typedef struct IEcoList1* IEcoList1Ptr_t;

typedef struct IEcoList1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface )(/* in */ IEcoList1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef )(/* in */ IEcoList1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release )(/* in */ IEcoList1Ptr_t me);

    /* IEcoList1 */
    uint32_t (ECOCALLMETHOD *Count)(/* in */ IEcoList1Ptr_t me);
    voidptr_t (ECOCALLMETHOD *Item)(/* in */ IEcoList1Ptr_t me, /* in */ uint32_t index);
    uint32_t (ECOCALLMETHOD *Add)(/* in */ IEcoList1Ptr_t me, /* in */ voidptr_t value);
    uint32_t (ECOCALLMETHOD *IndexOf)(/* in */ IEcoList1Ptr_t me, /* in */ voidptr_t value);
    void (ECOCALLMETHOD *InsertAt)(/* in */ IEcoList1Ptr_t me, /* in */ uint32_t index, /* in */ voidptr_t value);
    void (ECOCALLMETHOD *Remove)(/* in */ IEcoList1Ptr_t me, /* in */ voidptr_t value);
    void (ECOCALLMETHOD *RemoveAt)(/* in */ IEcoList1Ptr_t me, /* in */ uint32_t index);
    void (ECOCALLMETHOD *Clear)(/* in */ IEcoList1Ptr_t me);

} IEcoList1VTbl, *IEcoList1VTblPtr;

interface IEcoList1 {
    struct IEcoList1VTbl *pVTbl;
} IEcoList1;

#endif /* __I_ECO_LIST_1_H__ */

