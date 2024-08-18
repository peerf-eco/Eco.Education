/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoList1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoList1
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

#ifndef __ID_ECO_LIST_1_H__
#define __ID_ECO_LIST_1_H__

#include "IEcoBase1.h"
#include "IEcoList1.h"

/* EcoList1 CID = {53884AFC-93C4-48EC-AA92-9C8D3A562281} */
#ifndef __CID_EcoList1
static const UGUID CID_EcoList1 = {0x01, 0x10, {0x53, 0x88, 0x4A, 0xFC, 0x93, 0xC4, 0x48, 0xEC, 0xAA, 0x92, 0x9C, 0x8D, 0x3A, 0x56, 0x22, 0x81}};
#endif /* __CID_EcoList1 */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_53884AFC93C448ECAA929C8D3A562281;
#endif

#endif /* __ID_ECO_LIST_1_H__ */
