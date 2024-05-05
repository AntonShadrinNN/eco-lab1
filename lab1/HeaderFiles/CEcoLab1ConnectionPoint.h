#ifndef __C_ECOLAB1_CONNECTION_POINT_H__
#define __C_ECOLAB1_CONNECTION_POINT_H__

#include "IEcoConnectionPoint.h"
#include "IEcoConnectionPointContainer.h"
#include "IdEcoList1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1ConnectionPoint {

    IEcoConnectionPointVTbl* m_pVTblICP;
    IEcoConnectionPointContainer* m_pICPC;
    UGUID* m_piid;
    uint32_t m_cNextCookie;
    IEcoList1* m_pSinkList;
    IEcoMemoryAllocator1* m_pIMem;
    IEcoSystem1* m_pISys;

} CEcoLab1ConnectionPoint;

int16_t ECOCALLMETHOD createCEcoLab1ConnectionPoint(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoConnectionPointContainer* pICPC, /* in */ const UGUID* riid, /* out */ IEcoConnectionPoint** ppICP);
void ECOCALLMETHOD deleteCEcoLab1ConnectionPoint(/* in */ IEcoConnectionPoint* pICP);

#endif /* __C_ECOLAB1_CONNECTION_POINT_H__ */