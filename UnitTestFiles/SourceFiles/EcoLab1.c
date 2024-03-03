/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"

// Вспомогательная структура для передачи в функцию тестирования
typedef struct binSearch {
    char* typeUnderTest;
    int (_cdecl *compare)(const void *aPtr, const void *bPtr);
    void *(*createRandomSortedArray)(size_t count, IEcoMemoryAllocator1 *pIMem);
    void (*freeMem)(IEcoMemoryAllocator1 *pIMem, void *arr_ptr, size_t size);
    size_t elemSize;
} BinarySearch;

/* Компаратор int */
int __cdecl compareInt(const void *aPtr, const void *bPtr) {
    const int a = *((int *)aPtr);
	const int b = *((int *)bPtr);
    // printf("%p -- %p\n", aPtr, bPtr);
    // printf("%d -- %d\n", a, b);
    return (a > b) - (b > a);
}

/* Компаратор double */
int __cdecl compareDouble(const void *aPtr, const void *bPtr) {
    double a = *(double *)aPtr, b = *(double *)bPtr;
    return (a > b) - (b > a);
}

/* Компаратор float */
int __cdecl compareFloat(const void *aPtr, const void *bPtr) {
    float a = *(float *)aPtr, b = *(float *)bPtr;
    return (a > b) - (b > a);
}

/* Компаратор string */
int __cdecl compareString(const void *aPtr, const void *bPtr) {
    char *a = *(char **)aPtr, *b = *(char **)bPtr;
    return strcmp(a, b);
}

/* Компаратор Char */
int _cdecl compareChar(const void *aPtr, const void *bPtr) {
    int a = *(char *)aPtr, b = *(char *)bPtr;
    return (a > b) - (b > a);
}

/* Инициализация массива случайных int */
void* createAndSortRandomIntArray(size_t count, IEcoMemoryAllocator1 *pIMem) {
    int* array = (int *) pIMem->pVTbl->Alloc(pIMem, count * sizeof(int));
    if (array == NULL) {
        // Обработка ошибки
        return NULL;
    }

    // Заполнение массива случайными числами
    srand(time(NULL));
    for (int i = 0; i < count; ++i) {
        array[i] = rand() % 2000 - 1000; // Для примера случайные числа в диапазоне [0, 999]
    }

    // Сортировка массива по возрастанию
    qsort(array, count, sizeof(int), compareInt);

    return array;
}

/* Инициализация массива случайных char */
void* createAndSortRandomCharArray(size_t count, IEcoMemoryAllocator1 *pIMem) {
    char* array = (char *) pIMem->pVTbl->Alloc(pIMem, count * sizeof(char));
    if (array == NULL) {
        // Обработка ошибки
        return NULL;
    }

    // Заполнение массива случайными числами
    srand(time(NULL));
    for (int i = 0; i < count; ++i) {
        if (rand() % 2 == 0) {
            array[i*sizeof(char)] = rand() % ('z' - 'a' + 1) + 'a';
        }
        else {
            array[i*sizeof(char)] = rand() % ('Z' - 'A' + 1) + 'A';
        }
    }

    // Сортировка массива по возрастанию
    qsort(array, count, sizeof(char), compareChar);

    return array;
}

/* Инициализация массива случайных double */
void* createAndSortRandomDoubleArray(size_t count, IEcoMemoryAllocator1 *pIMem) {
    double* array = (double *) pIMem->pVTbl->Alloc(pIMem, count * sizeof(double));
    if (array == NULL) {
        // Обработка ошибки
        return NULL;
    }

    // Заполнение массива случайными числами
    srand(time(NULL));
    for (int i = 0; i < count; ++i) {
        array[i] = ((double)rand() / RAND_MAX);
    }

    // Сортировка массива по возрастанию
    qsort(array, count, sizeof(double), compareDouble);

    return array;
}

/* Инициализация массива случайных float */
void* createAndSortRandomFloatArray(size_t count, IEcoMemoryAllocator1 *pIMem) {
    float* array = (float *) pIMem->pVTbl->Alloc(pIMem, count * sizeof(float));
    if (array == NULL) {
        // Обработка ошибки
        return NULL;
    }

    // Заполнение массива случайными числами
    srand(time(NULL));
    for (int i = 0; i < count; ++i) {
        array[i] = ((float)rand() / RAND_MAX);
    }

    // Сортировка массива по возрастанию
    qsort(array, count, sizeof(float), compareFloat);

    return array;
}

/* Инициализация массива случайных string */
void *createAndSortRandomStringArray(size_t size, IEcoMemoryAllocator1 *pIMem) {
    size_t strSize;
    char **arr = (char **) pIMem->pVTbl->Alloc(pIMem, size * sizeof(char *));
    srand(time(NULL));
    for (size_t i = 0; i < size; i++) {
        arr[i] = (char *) pIMem->pVTbl->Alloc(pIMem, 30 * sizeof(char));
        strSize = rand() % 20 + 10;
        for (size_t j = 0; j < strSize; ++j) {
            if (rand() % 2 == 0) {
                arr[i][j] = (char) (rand() % ('z' - 'a' + 1) + 'a');
            }
            else {
                arr[i][j] = (char) (rand() % ('Z' - 'A' + 1) + 'A');
            }
        }
        arr[i][strSize] = 0;
    }
    qsort(arr, size, sizeof(char *), compareString);
    return arr;
}

/* Очистка памяти */
void freeArrayMem(IEcoMemoryAllocator1 *pIMem, void *arr, size_t size) {
    pIMem->pVTbl->Free(pIMem, arr);
}

/* Очистка памяти из-под массива строк */
void freeStringArrayMem(IEcoMemoryAllocator1 *pIMem, void *arr, size_t size) {
    size_t i;
    char **arrCpy = (char **) arr;
    for (i = 0; i < size; ++i) {
        pIMem->pVTbl->Free(pIMem, arrCpy[i]);
    }
    pIMem->pVTbl->Free(pIMem, arr);
}

/* Бенчмарки */
void benchBS(IEcoLab1 *bs, IEcoMemoryAllocator1 *pIMem, FILE* resultsFile, BinarySearch *bsStruct, size_t size, void* target) {
    clock_t c1, c2;
    char* typeUnderTest = bsStruct->typeUnderTest;
    printf("Type under test: %s Array size: %d\n", typeUnderTest, size);
    void *arr = bsStruct->createRandomSortedArray(size, pIMem);
    size_t elemSize = bsStruct->elemSize;
    int (__cdecl *compare)(const void *, const void *) = bsStruct->compare;
    c1 = clock();
    bs->pVTbl->binarySearch(bs, arr, size, elemSize, &target, compare);
    c2 = clock();
    bsStruct->freeMem(pIMem, arr, size);


    fprintf(resultsFile, "%s,%d,%.100f\n", typeUnderTest, size, (double)(c2 - c1) * 100000000000.0);
}

/* Тесты */
int16_t testBS(IEcoLab1 *bs, IEcoMemoryAllocator1 *pIMem, BinarySearch *bsStruct) {
    char* typeUnderTest = bsStruct->typeUnderTest;
    size_t size = 1000;
    void *arr = bsStruct->createRandomSortedArray(size, pIMem);
    size_t elemSize = bsStruct->elemSize;
    srand(time(NULL));
    size_t targetIndex = rand() % 999;
    void *targetElement =  (char *)arr + elemSize * targetIndex;
    int (__cdecl *compare)(const void *, const void *) = bsStruct->compare;
    size_t resultingIndex = bs->pVTbl->binarySearch(bs, arr, size, elemSize, targetElement, compare);
    void *resultingElement = (char *)arr + elemSize * resultingIndex;
    if (memcmp(resultingElement, targetElement, elemSize)) {
        printf("Assertion failed: expected %d, but got %d while testing %s type\n", targetIndex, resultingIndex, typeUnderTest);
        printf("Values: %d %d\n", resultingElement, targetElement);
        return 1;
    }
    printf("Test for %s ran successfully\n", typeUnderTest);
    return 0;
}

int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    char_t* name = 0;
    char_t* copyName = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Выделение блока памяти */
    name = (char_t *)pIMem->pVTbl->Alloc(pIMem, 10);

    /* Заполнение блока памяти */
    pIMem->pVTbl->Fill(pIMem, name, 'a', 9);


    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    

    BinarySearch bsInstances[5] = {
        {"int", compareInt, createAndSortRandomIntArray, freeArrayMem, sizeof(int)},
        {"char", compareChar, createAndSortRandomCharArray, freeArrayMem, sizeof(char)},
        {"double", compareDouble, createAndSortRandomDoubleArray, freeArrayMem, sizeof(double)},
        {"float", compareFloat, createAndSortRandomFloatArray, freeArrayMem, sizeof(float)},
        {"string", compareString, createAndSortRandomStringArray, freeStringArrayMem, sizeof(char *)},
    };

    double target = 125;
    int sizes[3] = {
        100000,
        1000000,
        10000000,
    };

    FILE* file = fopen("results/results.csv", "w");
    if (file == NULL) {
        goto Release;
    }
    else {
        fprintf(file, "%s,%s,%s\n", "Array type", "Array size", "Resulting time in processor clocks * 100000000000");
        fclose(file);
    }

    FILE* results = fopen("results/results.csv", "a");
    if (results == NULL) {
        goto Release;
    }

    for (int i = 0; i < 5; i++) {
        result = testBS(pIEcoLab1, pIMem, &bsInstances[i]);
        if (result != 0) {
            printf("Abort. Assertion failed");
            goto Release;
        }
        result = testBS(pIEcoLab1, pIMem, &bsInstances[i]);
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            benchBS(pIEcoLab1, pIMem, results, &bsInstances[i], sizes[j], &target);
        }
    }

    fclose(results);
    /* Освлбождение блока памяти */
    pIMem->pVTbl->Free(pIMem, name);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

