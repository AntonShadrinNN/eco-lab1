#ifndef __C_ECOLAB1_H__
#define __C_ECOLAB1_H__

#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoLab1.h"
#include "IEcoCalculatorY.h"
#include "IEcoCalculatorX.h"
#include "IEcoEnumConnections.h"
#include "IEcoConnectionPointContainer.h"
#include "CEcoLab1ConnectionPoint.h"

typedef struct CEcoLab1 {

    // Virtual tables
    IEcoLab1VTbl* m_pVTblIEcoLab1;
    IEcoCalculatorYVTbl* m_pVTblIY;
    IEcoCalculatorXVTbl* m_pVTblIX;
    IEcoUnknownVTbl* m_pVTblINondelegatingUnk;

    IEcoConnectionPointContainerVTbl* m_pVTblICPC;

    uint32_t m_cRef;

    IEcoMemoryAllocator1* m_pIMem;
    IEcoSystem1* m_pISys;

    /* Точка подключения */
    CEcoLab1ConnectionPoint* m_pISinkCP;

    char_t* m_Name;

    IEcoCalculatorX* m_pIX;
    IEcoCalculatorY* m_pIY;

    IEcoUnknown* m_pInnerUnknown;
    IEcoUnknown* m_pIUnkOuter;

} CEcoLab1, *CEcoLab1Ptr;


int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ struct IEcoLab1* me, /* in */ IEcoUnknown *pIUnkSystem);
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1);
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1);

#endif /* __C_ECOLAB1_H__ */
