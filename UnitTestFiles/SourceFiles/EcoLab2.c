/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include "IEcoCalculatorY.h"
#include "IEcoCalculatorX.h"
#include "IdEcoLab2.h"

int __cdecl compareInt(const void *aPtr, const void *bPtr) {
    const int a = *(int *)aPtr;
	const int b = *(int *)bPtr;
    return (a > b) - (b > a);
}

void printArrayInt(const void *array, size_t size) {
    printf("[");
    for (size_t i = 0; i < size - 1; ++i) {
        printf("%d, ", ((int*)array)[i]);
    }
    printf("%d]\n", ((int*)array)[size - 1]);
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

    IEcoCalculatorY* pIY = NULL;
    IEcoCalculatorX* pIX = NULL;
    IEcoLab1* pIEcoLab1 = NULL;
    IEcoLab1* pIEcoLab2 = NULL;

    result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
    if (result != 0 && pISys == 0) {
        goto Release;
    }

    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        goto Release;
    }
#ifdef ECO_LIB
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        goto Release;
    }
#endif
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

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result != 0 || pIY == 0) {
        goto Release;
    }

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result != 0 || pIX == 0) {
        goto Release;
    }

    printf("Calculator:\n");
    printf("\t10 * 5 = %d\n", pIY->pVTbl->Multiplication(pIY, 10, 5));
    printf("\t10 / 5 = %d\n", pIY->pVTbl->Division(pIY, 10, 5));
    printf("\t5 + 5 = %d\n", pIX->pVTbl->Addition(pIX, 5, 5));
    printf("\t10 - 5 = %d\n\n", pIX->pVTbl->Subtraction(pIX, 10, 5));
    pIY->pVTbl->Release(pIY);
    pIX->pVTbl->Release(pIX);

    printf("Queries to different interfaces:\n");
    QueryInfo queries1[] = {
        { &IID_IEcoCalculatorX, "query interface X from interface EcoLab1", (void**)&pIX },
        { &IID_IEcoCalculatorY, "query interface Y from interface EcoLab1", (void**)&pIY },
        { &IID_IEcoLab1, "query inteface EcoLab1 from interface EcoLab1", (void**)&pIEcoLab1 }
    };
    for (int i = 0; i < 3; ++i) {
        result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, queries1[i].iid, queries1[i].ppInterface);
        if (result == 0) {
            printf("\t%s\n", queries1[i].message);
        }
    }
    pIX->pVTbl->Release(pIX);
    pIY->pVTbl->Release(pIY);
    pIEcoLab1->pVTbl->Release(pIEcoLab1);

    QueryInfo queries2[] = {
        { &IID_IEcoCalculatorX, "query interface X from interface X", (void**)&pIX },
        { &IID_IEcoCalculatorY, "query interface Y from interface X", (void**)&pIY },
        { &IID_IEcoLab1, "query interface EcoLab1 from interface X", (void**)&pIEcoLab1 }
    };

    for (int i = 0; i < 3; ++i) {
        result = pIX->pVTbl->QueryInterface(pIX, queries2[i].iid, queries2[i].ppInterface);
        if (result == 0) {
            printf("\t%s\n", queries2[i].message);
        }
    }
    pIX->pVTbl->Release(pIX);
    pIY->pVTbl->Release(pIY);
    pIEcoLab1->pVTbl->Release(pIEcoLab1);
    
    QueryInfo queries3[] = {
        { &IID_IEcoCalculatorX, "query interface X from interface Y", (void**)&pIX },
        { &IID_IEcoCalculatorY, "query interface Y from interface Y", (void**)&pIY },
        { &IID_IEcoLab1, "query IEcoLab1 from IY", (void**)&pIEcoLab1 }
    };

    for (int i = 0; i < 3; ++i) {
        result = pIY->pVTbl->QueryInterface(pIY, queries3[i].iid, queries3[i].ppInterface);
        if (result == 0) {
            printf("\t%s\n", queries3[i].message);
        }
    }

    pIX->pVTbl->Release(pIX);
    pIY->pVTbl->Release(pIY);
    pIEcoLab1->pVTbl->Release(pIEcoLab1);
    printf("\n");
    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorX, (void **) &pIX);

    pIMem->pVTbl->Free(pIMem, name);

    printf("Test aggregated binary search:\n");
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab2, 0, &IID_IEcoLab1, (void**) &pIEcoLab2);
    if (result == 0) {
        printf("Successfully called IEcoLab1 aggregated by CEcoLab2\n");
    }

    size_t testSize = 15;
    void *testArr = createSortedIntArray(pIMem, testSize);
    printf("array under test: ");
    printArrayInt(testArr, testSize);
    // Pick second element for test
    int elem_for_test = 2;
    void *targetElement =  (char *)testArr + sizeof(int) * elem_for_test;
    size_t res = pIEcoLab2->pVTbl->binarySearch(pIEcoLab2, testArr, testSize, sizeof(int), targetElement, compareInt);
    printf("%d expected to be returned, %d got\n", elem_for_test, res);

    pIMem->pVTbl->Free(pIMem, testArr);

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

    if (pIEcoLab2 != 0) {
        pIEcoLab2->pVTbl->Release(pIEcoLab2);
    }

    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

