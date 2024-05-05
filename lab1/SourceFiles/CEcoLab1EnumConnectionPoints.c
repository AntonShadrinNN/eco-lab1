#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1EnumConnectionPoints.h"

int16_t ECOCALLMETHOD CEcoLab1EnumConnectionPoints_QueryInterface(/* in */ struct IEcoEnumConnectionPoints* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    if (IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoEnumConnectionPoints)) {
        *ppv = me;
    }
    else {
        *ppv = 0;
        return -1;
    }
    me->pVTbl->AddRef(me);
    return 0;
}

uint32_t ECOCALLMETHOD CEcoLab1EnumConnectionPoints_AddRef(/* in */ struct IEcoEnumConnectionPoints* me) {
    return 0;
}

uint32_t ECOCALLMETHOD CEcoLab1EnumConnectionPoints_Release(/* in */ struct IEcoEnumConnectionPoints* me) {
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1EnumConnectionPoints_Next(/* in */ struct IEcoEnumConnectionPoints* me, /* in */ uint32_t cConnections, /* out */ struct IEcoConnectionPoint **ppCP, /* out */ uint32_t *pcFetched) {
    return -1;
}

int16_t ECOCALLMETHOD CEcoLab1EnumConnectionPoints_Skip(/* in */ struct IEcoEnumConnectionPoints* me, /* in */ uint32_t cConnections) {
    return -1;
}

int16_t ECOCALLMETHOD CEcoLab1EnumConnectionPoints_Reset(/* in */ struct IEcoEnumConnectionPoints* me) {
    return 0 ;
}

int16_t ECOCALLMETHOD CEcoLab1EnumConnectionPoints_Clone(/* in */ struct IEcoEnumConnectionPoints* me, /* out */ struct IEcoEnumConnectionPoints **ppEnum) {
    return 0;
}

/* Create Virtual Table IEcoEnumConnectionPointsVTbl */
IEcoEnumConnectionPointsVTbl g_x0000000400000000C000000000000046VTblECP = {
	CEcoLab1EnumConnectionPoints_QueryInterface,
    CEcoLab1EnumConnectionPoints_AddRef,
    CEcoLab1EnumConnectionPoints_Release,
    CEcoLab1EnumConnectionPoints_Next,
    CEcoLab1EnumConnectionPoints_Skip,
    CEcoLab1EnumConnectionPoints_Reset,
    CEcoLab1EnumConnectionPoints_Clone	
};

int16_t ECOCALLMETHOD createCEcoLab1EnumConnectionPoints(/* in */ IEcoUnknown* pIUnkSystem, /* in */ struct IEcoConnectionPoint *pCP, /* out */ IEcoEnumConnectionPoints** ppIEnum) {
    CEcoLab1EnumConnectionPoints* pCMe = 0;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;	
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;		
    int16_t result = -1;

    if (ppIEnum == 0 || pIUnkSystem == 0 || pCP == 0) {
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

    pCMe = (CEcoLab1EnumConnectionPoints*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1EnumConnectionPoints));

    pCMe->m_pIMem = pIMem;

    pCMe->m_pVTblIECP = &g_x0000000400000000C000000000000046VTblECP;


    pCMe->m_List = 0;
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0,  &IID_IEcoList1, (void**)&pCMe->m_List);
    if (result != 0 || pCMe->m_List == 0) {
        deleteCEcoLab1EnumConnectionPoints((IEcoEnumConnectionPoints*)pCMe);
        return result;
    }

    pCMe->m_List->pVTbl->Add(pCMe->m_List, pCP);

    *ppIEnum = (IEcoEnumConnectionPoints*)pCMe;

    pISys->pVTbl->Release(pISys);

    return 0;
}

void ECOCALLMETHOD deleteCEcoLab1EnumConnectionPoints(/* in */ IEcoEnumConnectionPoints* pIEnum) {
    CEcoLab1EnumConnectionPoints* pCMe = (CEcoLab1EnumConnectionPoints*)pIEnum;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEnum != 0 ) {
        pIMem = pCMe->m_pIMem;
        if (pCMe->m_List != 0) {
            pCMe->m_List->pVTbl->Clear(pCMe->m_List);
            pCMe->m_List->pVTbl->Release(pCMe->m_List);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}