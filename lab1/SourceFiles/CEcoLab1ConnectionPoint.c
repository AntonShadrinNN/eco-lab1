#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1ConnectionPoint.h"
#include "CEcoLab1EnumConnections.h"

int16_t ECOCALLMETHOD CEcoLab1ConnectionPoint_QueryInterface(/* in */ struct IEcoConnectionPoint* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1ConnectionPoint* pCMe = (CEcoLab1ConnectionPoint*)me;

    if (me == 0 || ppv == 0) {
        return -1;
    }

    if ( IsEqualUGUID(riid, &IID_IEcoConnectionPoint) ) {
        *ppv = &pCMe->m_pVTblICP;
        pCMe->m_pVTblICP->AddRef((IEcoConnectionPoint*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblICP;
        pCMe->m_pVTblICP->AddRef((IEcoConnectionPoint*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }

    return 0;
}

uint32_t ECOCALLMETHOD CEcoLab1ConnectionPoint_AddRef(/* in */ struct IEcoConnectionPoint* me) {
    CEcoLab1ConnectionPoint* pCMe = (CEcoLab1ConnectionPoint*)me;

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pICPC->pVTbl->AddRef(pCMe->m_pICPC);
}

uint32_t ECOCALLMETHOD CEcoLab1ConnectionPoint_Release(/* in */ struct IEcoConnectionPoint* me) {
    CEcoLab1ConnectionPoint* pCMe = (CEcoLab1ConnectionPoint*)me;

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pICPC->pVTbl->Release(pCMe->m_pICPC);
}

int16_t ECOCALLMETHOD CEcoLab1ConnectionPoint_GetConnectionInterface(/* in */ struct IEcoConnectionPoint* me, /* out */ UGUID *pIID) {
    CEcoLab1ConnectionPoint* pCMe = (CEcoLab1ConnectionPoint*)me;

    if (me == 0 || pIID == 0) {
        return -1;
    }

    pIID = (UGUID *)&pCMe->m_piid;
    return 0;
}

 int16_t ECOCALLMETHOD CEcoLab1ConnectionPoint_GetConnectionPointContainer(/* in */ struct IEcoConnectionPoint* me, /* out */ struct IEcoConnectionPointContainer **ppICPC) {
    CEcoLab1ConnectionPoint* pCMe = (CEcoLab1ConnectionPoint*)me;

    if (me == 0 || ppICPC == 0) {
        return -1;
    }

    *ppICPC = pCMe->m_pICPC;
    pCMe->m_pICPC->pVTbl->AddRef(pCMe->m_pICPC);

    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1ConnectionPoint_Advise(/* in */ struct IEcoConnectionPoint* me, /* in */ struct IEcoUnknown *pUnkSink, /* out */ uint32_t *pcCookie) {
    CEcoLab1ConnectionPoint* pCMe = (CEcoLab1ConnectionPoint*)me;
    int16_t result = 0;
    EcoConnectionData* pCD = 0;

    if (me == 0 || pUnkSink == 0 || pcCookie == 0) {
        return -1;
    }

    pCD = (EcoConnectionData*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(EcoConnectionData));

    result = pUnkSink->pVTbl->QueryInterface(pUnkSink, pCMe->m_piid, (void**)&pCD->pUnk);
    if (result == 0 && pCD->pUnk != 0) {
        pCD->cCookie = ++pCMe->m_cNextCookie;

        pCMe->m_pSinkList->pVTbl->Add(pCMe->m_pSinkList, pCD);

        *pcCookie = pCD->cCookie;
        return 0;
    }

    return -1;
}

int16_t ECOCALLMETHOD CEcoLab1ConnectionPoint_Unadvise(/* in */ struct IEcoConnectionPoint* me, /* in */ uint32_t cCookie) {
    CEcoLab1ConnectionPoint* pCMe = (CEcoLab1ConnectionPoint*)me;
    EcoConnectionData* pCD = 0;
    IEcoUnknown* pSink = 0;
    uint32_t indx = 0;
    uint32_t count = 0;

    if (me == 0 ) {
        return -1;
    }

    count = pCMe->m_pSinkList->pVTbl->Count(pCMe->m_pSinkList);
    for (indx = 0; indx < count; indx++) {
        pCD = (EcoConnectionData*)pCMe->m_pSinkList->pVTbl->Item(pCMe->m_pSinkList, indx);
        if (pCD->cCookie == cCookie) {
            pSink = pCD->pUnk;

            pCMe->m_pSinkList->pVTbl->RemoveAt(pCMe->m_pSinkList, indx);
            pSink->pVTbl->Release(pSink);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pCD);
            return 0;
        }
    }
    return -1;
}

int16_t ECOCALLMETHOD CEcoLab1ConnectionPoint_EnumConnections(/* in */ struct IEcoConnectionPoint* me, /* out */ struct IEcoEnumConnections **ppEnum) {
    CEcoLab1ConnectionPoint* pCMe = (CEcoLab1ConnectionPoint*)me;

    if (me == 0 || ppEnum == 0 ) {
        return -1;
    }

    return createCEcoLab1EnumConnections((IEcoUnknown*)pCMe->m_pISys, pCMe->m_pSinkList, ppEnum);
}

/* Create Virtual Table IEcoConnectionPointVTbl */
IEcoConnectionPointVTbl g_x0000000300000000C000000000000046VTblCP = {
    CEcoLab1ConnectionPoint_QueryInterface,
    CEcoLab1ConnectionPoint_AddRef,
    CEcoLab1ConnectionPoint_Release,
    CEcoLab1ConnectionPoint_GetConnectionInterface,
    CEcoLab1ConnectionPoint_GetConnectionPointContainer,
    CEcoLab1ConnectionPoint_Advise,
    CEcoLab1ConnectionPoint_Unadvise,
    CEcoLab1ConnectionPoint_EnumConnections
};

int16_t ECOCALLMETHOD createCEcoLab1ConnectionPoint(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoConnectionPointContainer* pICPC, /* in */ const UGUID* riid, /* out */ IEcoConnectionPoint** ppICP) {
    CEcoLab1ConnectionPoint* pCMe = 0;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;	
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;		
    int16_t result = -1;

    if (ppICP == 0 || pIUnkSystem == 0 || pICPC == 0) {
        return result;
    }

    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);

    if (result != 0 && pISys == 0) {
        return result;
    }

    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    if (result != 0 && pIMem == 0) {
        pISys->pVTbl->Release(pISys);
        return result;
    }

    pCMe = (CEcoLab1ConnectionPoint*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1ConnectionPoint));

    pCMe->m_pISys = pISys;

    pCMe->m_pIMem = pIMem;
    pCMe->m_cNextCookie = 0;

    pCMe->m_pICPC = pICPC;
    pCMe->m_piid = (UGUID*)riid;

    pCMe->m_pVTblICP = &g_x0000000300000000C000000000000046VTblCP;


    pCMe->m_pSinkList = 0;
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pCMe->m_pSinkList);
    if (result != 0 || pCMe->m_pSinkList == 0) {
        deleteCEcoLab1ConnectionPoint((IEcoConnectionPoint*)pCMe);
        return result;
    }

    *ppICP = (IEcoConnectionPoint*)pCMe;

    return 0;
}

void ECOCALLMETHOD deleteCEcoLab1ConnectionPoint(/* in */ IEcoConnectionPoint* pICP) {
    CEcoLab1ConnectionPoint* pCMe = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    EcoConnectionData* pCD = 0;
    uint32_t count = 0;
    uint32_t index = 0;

    if (pICP != 0 ) {
        pCMe = (CEcoLab1ConnectionPoint*)pICP;
        pIMem = pCMe->m_pIMem;
        if (pCMe->m_pSinkList != 0) {
            count = pCMe->m_pSinkList->pVTbl->Count(pCMe->m_pSinkList);
            for (index = 0; index < count; index++) {
                pCD = (EcoConnectionData*)pCMe->m_pSinkList->pVTbl->Item(pCMe->m_pSinkList, index);
                pIMem->pVTbl->Free(pIMem, pCD);
            }
            pCMe->m_pSinkList->pVTbl->Clear(pCMe->m_pSinkList);
            pCMe->m_pSinkList->pVTbl->Release(pCMe->m_pSinkList);
        }
        if (pCMe->m_pISys != 0) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
            pCMe->m_pISys = 0;
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}