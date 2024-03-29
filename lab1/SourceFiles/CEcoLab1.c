﻿#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorA.h"
#include "CEcoLab2.h"

int16_t ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ struct IEcoLab1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoUnknown * nonDelegating = (IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk;
    int16_t result;     
    if (me == 0 || ppv == 0) {
        return -1;
    }
    result = nonDelegating->pVTbl->QueryInterface(nonDelegating, riid, ppv);
    if (result != 0 && pCMe->m_pIUnkOuter != 0) {
        result = pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
    return result;
}

uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ struct IEcoLab1* me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ struct IEcoLab1* me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

size_t binarySearch(void *arrPrt, size_t size, size_t elemSize, void *target, int (__cdecl *compare)(const void *, const void *)) {
    int index = -1; 
    int left = 0;
    int right = (int)size - 1;
    int *arr = (int *)arrPrt;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        void *midElem = (char*)arrPrt + mid * elemSize;
        
        int comparisonResult = compare(midElem, target);

        if (comparisonResult == 0){
            return mid;
        }

        if (comparisonResult < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return index;
}

size_t CEcoLab1_binarySearch(struct IEcoLab1* me, void *arrPtr, size_t size, size_t elemSize, void *target, int (__cdecl *compare)(const void *, const void *)) {
    if (me == 0 || arrPtr == 0 || target == 0 || compare == 0) {
        return -2;
    }

    return binarySearch(arrPtr, size, elemSize, target, compare);

}

int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ struct IEcoLab1 * me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoUnknown *pOuterUnknown = (IEcoUnknown *)me;
    int16_t result = -1;

    if (me == 0 ) {
        return result;
    }

    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0) {
        return -1;
    }
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIY);
    if (result != 0 || pCMe->m_pIY == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIY);
    }
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, pOuterUnknown, &IID_IEcoUnknown, (void**) &pCMe->m_pInnerUnknown);
    if (result != 0 || pCMe->m_pInnerUnknown == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIX);
    }
    pIBus->pVTbl->Release(pIBus);

    return result;
}

int16_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorY_QueryInterface(/* in */ struct IEcoCalculatorY* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoLab1*));
    IEcoUnknown * nonDelegating = (IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk;
    int16_t result;
    if (me == 0 || ppv == 0) {
        return -1;
    }

    result = nonDelegating->pVTbl->QueryInterface(nonDelegating, riid, ppv);
    if (result != 0 && pCMe->m_pIUnkOuter != 0) {
        result = pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
    return result;
}

uint32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorY_AddRef(/* in */ struct IEcoCalculatorY* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*));

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

uint32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorY_Release(/* in */ struct IEcoCalculatorY* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*));

    if (me == 0 ) {
        return -1;
    }
    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

int32_t ECOCALLMETHOD CEcoLab1_Multiplication(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*));

    if (me == 0 ) {
        return -1;
    }

    int32_t result = 0;
    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Multiplication(pCMe->m_pIY, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab1_Division(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*));

    if (me == 0 ) {
        return -1;
    }

    int16_t result = 0;
    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Division(pCMe->m_pIY, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorX_QueryInterface(/* in */ struct IEcoCalculatorX* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*));
    IEcoUnknown * nonDelegating = (IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk;

    if (me == 0 || ppv == 0) {
        return -1;
    }

    int16_t result = nonDelegating->pVTbl->QueryInterface(nonDelegating, riid, ppv);
    if (result != 0 && pCMe->m_pIUnkOuter != 0) {
        result = pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
    return result;
}

uint32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorX_AddRef(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab1* pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*));

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

uint32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorX_Release(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab1* pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*));

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

int32_t ECOCALLMETHOD CEcoLab1_Addition(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*));

    if (me == 0 ) {
        return -1;
    }

    int32_t result = 0;
    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Addition(pCMe->m_pIX, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab1_Subtraction(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*));

    if (me == 0 ) {
        return -1;
    }

    int16_t result = 0;
    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Subtraction(pCMe->m_pIX, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab1_NondelegatingQueryInterface(/* in */ struct IEcoUnknown * me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*) - sizeof(struct IEcoCalculatorX*));
    int16_t result;
    if (me == 0 || ppv == 0) {
        return -1;
    }
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        (pCMe->m_cRef)++;
    }
    else if (IsEqualGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIY;
        (pCMe->m_cRef)++;
    }
    else if (IsEqualGUID(riid, &IID_IEcoCalculatorX)) {
        if (pCMe->m_pInnerUnknown != 0) {
            result = pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
            return result;
        }
        else {
            *ppv = &pCMe->m_pVTblIX;
            (pCMe->m_cRef)++;
        }
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblINondelegatingUnk;
        (pCMe->m_cRef)++;
    }
    else {
        *ppv = NULL;
        return -1;
    }
    return 0;
}

uint32_t ECOCALLMETHOD CEcoLab1_NondelegatingAddRef(/* in */ struct IEcoUnknown* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*) - sizeof(struct IEcoCalculatorX*));

    if (me == 0 ) {
        return -1;
    }

    (pCMe->m_cRef)++;
    return pCMe->m_cRef;
}

uint32_t ECOCALLMETHOD CEcoLab1_NondelegatingRelease(/* in */ struct IEcoUnknown* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*) - sizeof(struct IEcoCalculatorX*));
    if (me == 0 ) {
        return -1;
    }
    (pCMe->m_cRef)--;

    if ( pCMe->m_cRef == 0 ) {
        if (pCMe->m_pInnerUnknown != 0) {
            if (pCMe->m_pInnerUnknown->pVTbl->Release(pCMe->m_pInnerUnknown) == 0) {
                pCMe->m_pInnerUnknown = 0;
            } else {
                pCMe->m_cRef = 1;
            }
        }
        if (pCMe->m_cRef == 0) {
            deleteCEcoLab1((IEcoLab1*)pCMe);
        }
        return 0;
    }
    return pCMe->m_cRef;
}

IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
        CEcoLab1_QueryInterface,
        CEcoLab1_AddRef,
        CEcoLab1_Release,
        CEcoLab1_binarySearch
};

IEcoCalculatorYVTbl g_xBD6414C29096423EA90C04D77AFD1CADVTblLab1 = {
    CEcoLab1_IEcoCalculatorY_QueryInterface,
    CEcoLab1_IEcoCalculatorY_AddRef,
    CEcoLab1_IEcoCalculatorY_Release,
    CEcoLab1_Multiplication,
    CEcoLab1_Division
};

IEcoCalculatorXVTbl g_x9322111622484742AE0682819447843DVTblLab1 = {
        CEcoLab1_IEcoCalculatorX_QueryInterface,
        CEcoLab1_IEcoCalculatorX_AddRef,
        CEcoLab1_IEcoCalculatorX_Release,
        CEcoLab1_Addition,
        CEcoLab1_Subtraction
};

IEcoUnknownVTbl g_x000000000000000000000000000000AAVTblLab1 = {
        CEcoLab1_NondelegatingQueryInterface,
        CEcoLab1_NondelegatingAddRef,
        CEcoLab1_NondelegatingRelease
};

int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1) {
    CEcoLab1* pCMe = 0;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
        return -1;
    }

    int16_t result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);
    if (result != 0 && pISys == 0) {
        return result;
    }

    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0) {
        return -1;
    }

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

    pCMe = (CEcoLab1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));
    pCMe->m_pISys = pISys;
    pCMe->m_pIMem = pIMem;

    pCMe->m_cRef = 1;

    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;
    pCMe->m_pVTblIY = &g_xBD6414C29096423EA90C04D77AFD1CADVTblLab1;
    pCMe->m_pVTblIX = &g_x9322111622484742AE0682819447843DVTblLab1;
    pCMe->m_pVTblINondelegatingUnk = &g_x000000000000000000000000000000AAVTblLab1;
    pCMe->m_pIUnkOuter = 0;
    if (pIUnkOuter != 0) {
        pCMe->m_pIUnkOuter = pIUnkOuter;
    } else {
        pCMe->m_pIUnkOuter = (IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk;
    }

    pCMe->m_Name = 0;
    pCMe->m_pIY = 0;
    pCMe->m_pIX = 0;
    pCMe->m_pInnerUnknown = 0;

    *ppIEcoLab1 = (IEcoLab1 *)pCMe;

    pIBus->pVTbl->Release(pIBus);

    return 0;
}

void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1) {
    CEcoLab1* pCMe = (CEcoLab1*)pIEcoLab1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1 != 0 ) {
        pIMem = pCMe->m_pIMem;
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pIY != 0) {
            pCMe->m_pIY->pVTbl->Release(pCMe->m_pIY);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
