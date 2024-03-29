#include "CEcoLab2.h"
#include "CEcoLab2Factory.h"

int16_t ECOCALLMETHOD CEcoLab2Factory_QueryInterface(IEcoComponentFactory* me, const UGUID* riid, void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoComponentFactory) ) {
        *ppv = me;
    }
    else {
        *ppv = 0;
        return -1;
    }
    ((IEcoUnknown*)(*ppv))->pVTbl->AddRef((IEcoUnknown*)*ppv);

    return 0;
}

uint32_t ECOCALLMETHOD CEcoLab2Factory_AddRef(/* in */ IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return -1;
    }

    (pCMe->m_cRef)++;
    return pCMe->m_cRef;
}

uint32_t ECOCALLMETHOD CEcoLab2Factory_Release(/* in */ IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return -1;
    }

    (pCMe->m_cRef)--;

    if ( pCMe->m_cRef == 0 ) {
        return 0;
    }
    return pCMe->m_cRef;
}

int16_t ECOCALLMETHOD CEcoLab2Factory_Init(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pIUnkSystem, /* in */ void* pv) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return -1;
    }

    int16_t result = pCMe->m_pInitInstance(pv, pIUnkSystem);
    return result;
}

int16_t ECOCALLMETHOD CEcoLab2Factory_Alloc(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pISystem, /* in */ struct IEcoUnknown *pIUnknownOuter, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;
    IEcoUnknown* pIUnk = 0;

    if (me == 0 ) {
        return -1;
    }

    if ( ( pIUnknownOuter != 0 ) && !IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        return -1;
    }

    int16_t result = pCMe->m_pInstance(pISystem, pIUnknownOuter, (void**)&pIUnk);
    if ( result != 0 || pIUnk == 0) {
        return -1;
    }

    result = me->pVTbl->Init(me, pISystem, pIUnk);
    if (result != 0) {
        return -1;
    }

    result = pIUnk->pVTbl->QueryInterface(pIUnk, riid, ppv);
    if (result != 0) {
        return -1;
    }
    pIUnk->pVTbl->Release(pIUnk);

    return result;
}

char_t* ECOCALLMETHOD CEcoLab2Factory_get_Name(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Name;
}

char_t* ECOCALLMETHOD CEcoLab2Factory_get_Version(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Version;
}

char_t* ECOCALLMETHOD CEcoLab2Factory_get_Manufacturer(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Manufacturer;
}

IEcoComponentFactoryVTbl g_x1F5DF16EE1BF43B999A434ED38FE8F3AFactoryVTbl = {
    CEcoLab2Factory_QueryInterface,
    CEcoLab2Factory_AddRef,
    CEcoLab2Factory_Release,
    CEcoLab2Factory_Alloc,
    CEcoLab2Factory_Init,
    CEcoLab2Factory_get_Name,
    CEcoLab2Factory_get_Version,
    CEcoLab2Factory_get_Manufacturer
};

CEcoLab2Factory g_x1F5DF16EE1BF43B999A434ED38FE8F3AFactory = {
    &g_x1F5DF16EE1BF43B999A434ED38FE8F3AFactoryVTbl,
    0,
    (CreateInstance)createCEcoLab2,
    (InitInstance)initCEcoLab2,
    "Lab2\0",
    "1.0.0\0",
    "Shadrin_Anton\0"
};

#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr() {
    return (IEcoComponentFactory*)&g_x1F5DF16EE1BF43B999A434ED38FE8F3AFactory;
};
#elif ECO_LIB
IEcoComponentFactory* GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A = (IEcoComponentFactory*)&g_x1F5DF16EE1BF43B999A434ED38FE8F3AFactory;
#endif