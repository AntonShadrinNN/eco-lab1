#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1EnumConnections.h"

int16_t ECOCALLMETHOD CEcoLab1EnumConnections_QueryInterface(/* in */ struct IEcoEnumConnections* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    if (IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoEnumConnections)) {
        *ppv = me;
    }
    else {
        *ppv = 0;
        return -1;
    }
    me->pVTbl->AddRef(me);
    return 0;
}

uint32_t ECOCALLMETHOD CEcoLab1EnumConnections_AddRef(/* in */ struct IEcoEnumConnections* me) {
    CEcoLab1EnumConnections* pCMe = (CEcoLab1EnumConnections*)me;

    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

uint32_t ECOCALLMETHOD CEcoLab1EnumConnections_Release(/* in */ struct IEcoEnumConnections* me) {
    CEcoLab1EnumConnections* pCMe = (CEcoLab1EnumConnections*)me;

    if (me == 0 ) {
        return -1;
    }

    --pCMe->m_cRef;

    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1EnumConnections((IEcoEnumConnections*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

int16_t ECOCALLMETHOD CEcoLab1EnumConnections_Next(/* in */ struct IEcoEnumConnections* me, /* in */ uint32_t cConnections, /* out */ struct EcoConnectionData *rgcd, /* out */ uint32_t *pcFetched) {
    CEcoLab1EnumConnections* pCMe = (CEcoLab1EnumConnections*)me;
    EcoConnectionData* pCD = 0;
    uint32_t count = 0;

    if (me == 0 || rgcd == 0 || (pcFetched == 0 && cConnections > 1) ) {
        return -1;
    }

    while ((pCMe->m_cIndex < pCMe->m_pSinkList->pVTbl->Count(pCMe->m_pSinkList)) && (count < cConnections)) {
        pCD = (EcoConnectionData*)pCMe->m_pSinkList->pVTbl->Item(pCMe->m_pSinkList, pCMe->m_cIndex);
        pCD->pUnk->pVTbl->AddRef(pCD->pUnk);
        rgcd->pUnk = pCD->pUnk;
        rgcd->cCookie = pCD->cCookie;
        count++;
        pCMe->m_cIndex++;
    };

    if (pcFetched != 0) {
        *pcFetched = count;
    }

    if (count < cConnections) {
        return -1;
    }
    else {
        return 0;
    }

    return -1;
}

int16_t ECOCALLMETHOD CEcoLab1EnumConnections_Skip(/* in */ struct IEcoEnumConnections* me, /* in */ uint32_t cConnections) {
    CEcoLab1EnumConnections* pCMe = (CEcoLab1EnumConnections*)me;
    uint32_t count = 0;

    if (me == 0 ) {
        return -1;
    }

    while ((pCMe->m_cIndex < pCMe->m_pSinkList->pVTbl->Count(pCMe->m_pSinkList)) && (count < cConnections)) {
        count++;
        pCMe->m_cIndex++;
    };

    if (count < cConnections) {
        return -1;
    }
    else {
        return 0;
    }

    return -1;
}

int16_t ECOCALLMETHOD CEcoLab1EnumConnections_Reset(/* in */ struct IEcoEnumConnections* me) {
    CEcoLab1EnumConnections* pCMe = (CEcoLab1EnumConnections*)me;

    if (me == 0 ) {
        return -1;
    }

    pCMe->m_cIndex = 0;

    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1EnumConnections_Clone(/* in */ struct IEcoEnumConnections* me, /* out */ struct IEcoEnumConnections **ppEnum) {
    CEcoLab1EnumConnections* pCMe = (CEcoLab1EnumConnections*)me;

    if (me == 0 || ppEnum ==0 ) {
        return -1;
    }

    return createCEcoLab1EnumConnections((IEcoUnknown*)pCMe->m_pISys, pCMe->m_pSinkList, ppEnum);
}

/* Create Virtual Table IEcoEnumConnectionsVTbl */
IEcoEnumConnectionsVTbl g_x0000000200000000C000000000000046VTblECP = {
	CEcoLab1EnumConnections_QueryInterface,
    CEcoLab1EnumConnections_AddRef,
    CEcoLab1EnumConnections_Release,
    CEcoLab1EnumConnections_Next,
    CEcoLab1EnumConnections_Skip,
    CEcoLab1EnumConnections_Reset,
    CEcoLab1EnumConnections_Clone	
};

int16_t ECOCALLMETHOD createCEcoLab1EnumConnections(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoList1* pIList, /* out */ IEcoEnumConnections** ppIEnum) {
    CEcoLab1EnumConnections* pCMe = 0;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;	
    EcoConnectionData* pCD = 0;
    EcoConnectionData* pNewCD = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;	
    int16_t result = -1;
    uint32_t indx = 0;

    if (ppIEnum == 0 || pIUnkSystem == 0 || pIList == 0) {
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

    pCMe = (CEcoLab1EnumConnections*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1EnumConnections));

    pCMe->m_pISys = pISys;

    pCMe->m_pIMem = pIMem;

    pCMe->m_cRef = 1;

    pCMe->m_pVTblIEC = &g_x0000000200000000C000000000000046VTblECP;

    pCMe->m_pSinkList = 0;
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0,  &IID_IEcoList1, (void**)&pCMe->m_pSinkList);
    if (result != 0 || pCMe->m_pSinkList == 0) {
        deleteCEcoLab1EnumConnections((IEcoEnumConnections*)pCMe);
        return result;
    }
    for (indx = 0; indx < pIList->pVTbl->Count(pIList); indx++) {
        pCD = (EcoConnectionData*)pIList->pVTbl->Item(pIList, indx);
        pNewCD = (EcoConnectionData*)pIMem->pVTbl->Alloc(pIMem, sizeof(EcoConnectionData));
        pNewCD->cCookie = pCD->cCookie;
        pNewCD->pUnk = pCD->pUnk;
        pNewCD->pUnk->pVTbl->AddRef(pNewCD->pUnk);
        pCMe->m_pSinkList->pVTbl->Add(pCMe->m_pSinkList, pNewCD);
    }
    pCMe->m_cIndex = 0;

    *ppIEnum = (IEcoEnumConnections*)pCMe;

    return 0;
}

void ECOCALLMETHOD deleteCEcoLab1EnumConnections(/* in */ IEcoEnumConnections* pIEnum) {
    CEcoLab1EnumConnections* pCMe = (CEcoLab1EnumConnections*)pIEnum;
    IEcoMemoryAllocator1* pIMem = 0;
    uint32_t indx = 0;
    EcoConnectionData* pCD = 0;

    if (pIEnum != 0 ) {
        pIMem = pCMe->m_pIMem;
        if (pCMe->m_pSinkList != 0) {
            for (indx = 0; indx < pCMe->m_pSinkList->pVTbl->Count(pCMe->m_pSinkList); indx++) {
                pCD = (EcoConnectionData*)pCMe->m_pSinkList->pVTbl->Item(pCMe->m_pSinkList, indx);
                pCD->pUnk->pVTbl->Release(pCD->pUnk);
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