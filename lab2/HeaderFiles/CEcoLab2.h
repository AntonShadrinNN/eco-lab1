#ifndef __C_ECOLAB2_H__
#define __C_ECOLAB2_H__

#include "IEcoSystem1.h"
#include "IEcoLab1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoCalculatorY.h"
#include "IEcoCalculatorX.h"

typedef struct CEcoLab2 {

    // Virtual tables
    IEcoCalculatorYVTbl* m_pVTblIY;
    IEcoCalculatorXVTbl* m_pVTblIX;
    IEcoUnknownVTbl* m_pVTblINondelegatingUnk;

    // References count
    uint32_t m_cRef;

    IEcoMemoryAllocator1* m_pIMem;
    IEcoSystem1* m_pISys;

    char_t* m_Name;

    IEcoCalculatorY* m_pIY;
    IEcoUnknown* m_pInnerUnknownLab1;
    IEcoUnknown* m_pInnerUnknownB;
    IEcoCalculatorX* m_pIX;
    IEcoUnknown* m_pIUnkOuter;

} CEcoLab2, *CEcoLab2Ptr;

int16_t ECOCALLMETHOD initCEcoLab2(/*in*/ struct IEcoCalculatorY * me, /* in */ IEcoUnknown *pIUnkSystem);
int16_t ECOCALLMETHOD createCEcoLab2(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoCalculatorY** ppIEcoLab2);
void ECOCALLMETHOD deleteCEcoLab2(/* in */ IEcoCalculatorY* pIEcoLab2);

#endif /* __C_ECOLAB2_H__ */