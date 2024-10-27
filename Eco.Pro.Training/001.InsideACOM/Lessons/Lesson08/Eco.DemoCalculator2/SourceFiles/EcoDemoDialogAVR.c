/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoDemoDialogWin
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
#include "IEcoMemoryManager1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IdEcoHD44780LCDController1.h"
#include "IdEcoKeypad1.h"

#define ADDITION_OPERATOR       1
#define SUBTRACTION_OPERATOR    2
#define MULTIPLICATION_OPERATOR 3
#define DEVISION_OPERATOR       4
#define EQUAL_OPERATOR          10

extern IEcoInterfaceBus1* g_pIBus;
extern IEcoCalculatorX* g_pIX;
extern IEcoCalculatorY* g_pIY;
extern int8_t g_iInfo;

int16_t a = 0;
int16_t b = 0;
int32_t c = 0;
int8_t op = 0;

/*
 *
 * <сводка>
 *   Функция itoa
 * </сводка>
 *
 * <описание>
 *   Функция itoa
 * </описание>
 *
 */
//int16_t itoa(int16_t value, char_t *ptr) {
    //int16_t count=0,temp;
    //if(ptr==0)
        //return 0;
    //if(value==0) {
        //*ptr='0';
        //return 1;
    //}
//
    //if(value<0) {
        //value*=(-1);
        //*ptr++='-';
        //count++;
    //}
    //for(temp=value;temp>0;temp/=10,ptr++);
    //*ptr='\0';
    //for(temp=value;temp>0;temp/=10) {
        //*--ptr=temp%10+'0';
        //count++;
    //}
    //return count;
//}

/*
 *
 * <сводка>
 *   Функция DialogProcessing
 * </сводка>
 *
 * <описание>
 *   Функция DialogProcessing
 * </описание>
 *
 */
int16_t DialogProcessing() {
    int16_t result = -1;
    IEcoHD44780LCDController1* pILCD = 0;
    IEcoKeypad1* pIEcoKeypad1 = 0;
    uchar_t* strCalcU = "Calc v2 - Unk";
    uchar_t* strCalcA = "Calc v2 - A";
    uchar_t* strCalcB = "Calc v2 - B";
    uchar_t* strCalcC = "Calc v2 - C";
    uchar_t* strCalcD = "Calc v2 - D";
    uchar_t* strCalcE = "Calc v2 - E";
    uchar_t* str = 0;
    uint16_t* code = 0;
    uint16_t buf = 0;
    char_t res[10] = {0};
    uint8_t nCount = 0;

#ifdef ECO_LIB
    /* Регистрация статического компонента для работы с LCD */
    result = g_pIBus->pVTbl->RegisterComponent(g_pIBus, &CID_EcoHD44780LCDController1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_8A2D848DC91F4FD1893D4E0EA6D2DE0D);
    if (result != 0 ) {
        /* Возврат в случае ошибки */
        return result;
    }
    /* Регистрация статического компонента для работы с клавиатурой */
    result = g_pIBus->pVTbl->RegisterComponent(g_pIBus, &CID_EcoKeypad1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_28BA4535E46E4F3B9E73FD385DB56ED2);
    if (result != 0 ) {
        /* Возврат в случае ошибки */
        return result;
    }
#endif /* ECO_LIB */

    /* Получение интерфейса мембранной клавиатуры */
    result = g_pIBus->pVTbl->QueryComponent(g_pIBus, &CID_EcoKeypad1, 0, &IID_IEcoKeypad1, (void**) &pIEcoKeypad1);
    if (result != 0 || pIEcoKeypad1 == 0) {
       /* Возврат интерфейсов в случае ошибки */
       return result;
    }

   /* Инициализация мембранной клавиатуры */
    if (g_pIY == 0) {
       /* Если интерфейс калькулятора не доступен, то отключаем колонку операций сложения и вычитания */
        result = pIEcoKeypad1->pVTbl->Initialize(pIEcoKeypad1, 4, 3);
    }
    else {
        result = pIEcoKeypad1->pVTbl->Initialize(pIEcoKeypad1, 4, 4);
    }

   result = g_pIBus->pVTbl->QueryComponent(g_pIBus, &CID_EcoHD44780LCDController1, 0, &IID_IEcoHD44780LCDController1, (void**) &pILCD);
   if (result != 0 || pILCD == 0) {
       /* Возврат интерфейсов в случае ошибки */
        return result;
    }

   /* Инициализация контроллера LCD */
   result = pILCD->pVTbl->Init(pILCD, ECO_HD44780_DEFAULT_MODE);

   /* Установка адреса */
   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b10000000);

   /* Вывод 1 строки  */
    switch (g_iInfo) {
        case 0 :
            str = strCalcU;
        break;
        case 1 :
            str = strCalcA;
        break;
        case 2 :
            str = strCalcB;
        break;
        case 3 :
            str = strCalcC;
        break;
        case 4 :
            str = strCalcD;
        break;
        case 5 :
            str = strCalcE;
        break;
    }
   while(*str != '\0') {
       result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, *str);
       str++;
   }
    result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
    /* Цикл обработки сообщений */
    while (1) {

       code = pIEcoKeypad1->pVTbl->AwaitKeyStroke(pIEcoKeypad1);
       if (code != 0) {
           if (nCount > 0 && op == EQUAL_OPERATOR)
           {
               result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
               while(nCount != 0) {
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, ' ');
                   nCount--;
               }
               result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
               op = 0;
           }
           if (code == 0x4F) {
               result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '1');
               if (nCount == 0) {
                   buf = 1;
                   nCount++;
               }
               else if (nCount >= 1) {
                   buf = buf*10 + 1;
                   nCount++;
               }
           }
           else if (code == 0x50) {
               result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '2');
               if (nCount == 0) {
                   buf = 2;
                   nCount++;
               }
               else if (nCount >= 1) {
                   buf = buf*10 + 2;
                   nCount++;
               }
           }
           else if (code == 0x51) {
               result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '3');
               if (nCount == 0) {
                   buf = 3;
                   nCount++;
               }
               else if (nCount >= 1) {
                   buf = buf*10 + 3;
                   nCount++;
               }
           }
           else if (code == 0x1E) {
               if (nCount > 0) {
                   op = ADDITION_OPERATOR;
                   a = buf;
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   while(nCount != 0) {
                       result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, ' ');
                       nCount--;
                   }
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '+');
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   nCount = 0;
               }
           }
           else if (code == 0x4B) {
               result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '4');
               if (nCount == 0) {
                   buf = 4;
                   nCount++;
               }
               else if (nCount >= 1) {
                   buf = buf*10 + 4;
                   nCount++;
               }
           }
           else if (code == 0x4C) {
               result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '5');
               if (nCount == 0) {
                   buf = 5;
                   nCount++;
               }
               else if (nCount >= 1) {
                   buf = buf*10 + 5;
                   nCount++;
               }
           }
           else if (code == 0x4D) {
               result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '6');
               if (nCount == 0) {
                   buf = 6;
                   nCount++;
               }
               else if (nCount >= 1) {
                   buf = buf*10 + 6;
                   nCount++;
               }
           }
           else if (code == 0x30) {
               if (nCount > 0) {
                   op = SUBTRACTION_OPERATOR;
                   a = buf;
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   while(nCount != 0) {
                       result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, ' ');
                       nCount--;
                   }
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '-');
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   nCount = 0;
               }
           }
           else if (code == 0x47) {
               result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '7');
               if (nCount == 0) {
                   buf = 7;
                   nCount++;
               }
               else if (nCount >= 1) {
                   buf = buf*10 + 7;
                   nCount++;
               }
           }
           else if (code == 0x48) {
               result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '8');
               if (nCount == 0) {
                   buf = 8;
                   nCount++;
               }
               else if (nCount >= 1) {
                   buf = buf*10 + 8;
                   nCount++;
               }
           }
           else if (code == 0x49) {
               result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '9');
               if (nCount == 0) {
                   buf = 9;
                   nCount++;
               }
               else if (nCount >= 1) {
                   buf = buf*10 + 9;
                   nCount++;
               }
           }
           else if (code == 0x2E) {
               if (nCount > 0) {
                   op = DEVISION_OPERATOR;
                   a = buf;
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   while(nCount != 0) {
                       result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, ' ');
                       nCount--;
                   }
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '/');
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   nCount = 0;
               }
           }
           else if (code == 0x46) {
               if (nCount > 0) {
                   op = MULTIPLICATION_OPERATOR;
                   a = buf;
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   while(nCount != 0) {
                       result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, ' ');
                       nCount--;
                   }
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '*');
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   nCount = 0;
               }
           }
           else if (code == 0x52) {
               result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '0');
               if (nCount == 0) {
                   buf = 0;
                   nCount++;
               }
               else if (nCount >= 1) {
                   buf = buf*10 + 0;
                   nCount++;
               }
           }
           else if (code == 0x03) {
               result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '#');
           }
           else if (code == 0x20) {
               if (nCount > 0) {
                   b = buf;
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   while(nCount != 0) {
                       result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, ' ');
                       nCount--;
                   }
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, '=');
                   result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_IR, 0b11000000);
                    if (op == ADDITION_OPERATOR) {
                        c = g_pIX->pVTbl->Addition(g_pIX, a, b);
                    }
                    else if (op == SUBTRACTION_OPERATOR) {
                        c = g_pIX->pVTbl->Subtraction(g_pIX, a, b);
                    }
                    else if (op == MULTIPLICATION_OPERATOR) {
                        c = g_pIY->pVTbl->Multiplication(g_pIY, a, b);
                    }
                    else if (op == DEVISION_OPERATOR) {
                        c = g_pIY->pVTbl->Division(g_pIY, a, b);
                    }
                    itoa(c, res, 10);
                    str = res;
                    nCount = 0;
                    while(*str != '\0') {
                        result = pILCD->pVTbl->Write(pILCD, ECO_HD44780_RS_DR, *str);
                        str++;
                        nCount++;
                    }
                    op = EQUAL_OPERATOR;
               }
           }
       }
    }
    return result;
}
