/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include "IEcoCalculatorY.h"
#include "IEcoCalculatorX.h"

#include "IEcoConnectionPointContainer.h"
#include "IEcoConnectionPoint.h"
#include "IEcoLab1Events.h"
#include "CEcoLab1Sink.h"

int __cdecl compareInt(const void *aPtr, const void *bPtr) {
    const int a = *(int *)aPtr;
	const int b = *(int *)bPtr;
    return (a > b) - (b > a);
}

void *createSortedIntArray(IEcoMemoryAllocator1 *pIMem, size_t size) {
    srand(time(0) % 100000);
    int *arr = (int *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(int));
    for (size_t i = 0; i < size; i++) {
        arr[i] = rand() %2000 - 1000;
    }
    qsort(arr, size, sizeof(int), compareInt);
    return arr;
}

typedef struct {
    const UGUID *iid;
    char* message;
    void** ppInterface;
} QueryInfo;

int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* System interface pointer */
    IEcoSystem1* pISys = 0;
    /* System interface bus pointer */
    IEcoInterfaceBus1* pIBus = 0;
    /* Memory interface pointer */
    IEcoMemoryAllocator1* pIMem = 0;
    char_t* name = 0;
    char_t* copyName = 0;

    IEcoLab1* pIEcoLab1 = 0;
    /* Pointer to pointer connection interface */
    IEcoConnectionPointContainer* pICPC = 0;
    /* Point connection interface pointer */
    IEcoConnectionPoint* pICP = 0;
    /* Callback interface pointer */
    IEcoLab1Events* pIEcoLab1Sink = 0;
    IEcoUnknown* pISinkUnk = 0;
    uint32_t cAdvise = 0;
    
    result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
    if (result != 0 && pISys == 0) {
        goto Release;
    }

    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        goto Release;
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    if (result != 0 || pIMem == 0) {
        goto Release;
    }

    name = (char_t *)pIMem->pVTbl->Alloc(pIMem, 10);

    pIMem->pVTbl->Fill(pIMem, name, 'a', 9);


    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        goto Release;
    }

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void **)&pICPC);
    if (result != 0 || pICPC == 0) {
        goto Release;
    }
    printf("queried CPContainer\n");

    result = pICPC->pVTbl->FindConnectionPoint(pICPC, &IID_IEcoLab1Events, &pICP);
    if (result != 0 || pICP == 0) {
        goto Release;
    }

    pICPC->pVTbl->Release(pICPC);
    printf("found connection point\n");

    result = createCEcoLab1Sink(pIMem, (IEcoLab1Events**)&pIEcoLab1Sink);

    if (pIEcoLab1Sink != 0) {
        result = pIEcoLab1Sink->pVTbl->QueryInterface(pIEcoLab1Sink, &IID_IEcoUnknown,(void **)&pISinkUnk);
        if (result != 0 || pISinkUnk == 0) {
            goto Release;
        }
        result = pICP->pVTbl->Advise(pICP, pISinkUnk, &cAdvise);
        if (result == 0 && cAdvise == 1) {
            // do smth
        }
        pISinkUnk->pVTbl->Release(pISinkUnk);
    }

    size_t testSize = 15;
    void *testArr = createSortedIntArray(pIMem, testSize);
    // Pick second element for test
    int elem_for_test = 2;
    void *targetElement =  (char *)testArr + sizeof(int) * elem_for_test;
    size_t res = pIEcoLab1->pVTbl->binarySearch(pIEcoLab1, testArr, testSize, sizeof(int), targetElement, compareInt);
    printf("%d expected to be returned, %d got\n", elem_for_test, res);

    pIMem->pVTbl->Free(pIMem, testArr);
    
    if (pIEcoLab1Sink != 0) {
        result = pICP->pVTbl->Unadvise(pICP, cAdvise);
        pIEcoLab1Sink->pVTbl->Release(pIEcoLab1Sink);
        pICP->pVTbl->Release(pICP);
    }


Release:
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }

    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

