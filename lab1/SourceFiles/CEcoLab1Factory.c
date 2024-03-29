#include "CEcoLab1.h"
#include "CEcoLab1Factory.h"

int16_t ECOCALLMETHOD CEcoLab1Factory_QueryInterface(IEcoComponentFactory* me, const UGUID* riid, void** ppv) {
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

uint32_t ECOCALLMETHOD CEcoLab1Factory_AddRef(/* in */ IEcoComponentFactory* me) {
    CEcoLab1Factory* pCMe = (CEcoLab1Factory*)me;

    if (me == 0 ) {
        return -1;
    }

    (pCMe->m_cRef)++;
    return pCMe->m_cRef;
}

uint32_t ECOCALLMETHOD CEcoLab1Factory_Release(/* in */ IEcoComponentFactory* me) {
    CEcoLab1Factory* pCMe = (CEcoLab1Factory*)me;

    if (me == 0 ) {
        return -1;
    }

    (pCMe->m_cRef)--;

    if ( pCMe->m_cRef == 0 ) {
        return 0;
    }
    return pCMe->m_cRef;
}

int16_t ECOCALLMETHOD CEcoLab1Factory_Init(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pIUnkSystem, /* in */ void* pv) {
    CEcoLab1Factory* pCMe = (CEcoLab1Factory*)me;

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pInitInstance(pv, pIUnkSystem);


}

int16_t ECOCALLMETHOD CEcoLab1Factory_Alloc(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pISystem, /* in */ struct IEcoUnknown *pIUnknownOuter, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1Factory* pCMe = (CEcoLab1Factory*)me;
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

char_t* ECOCALLMETHOD CEcoLab1Factory_get_Name(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab1Factory* pCMe = (CEcoLab1Factory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Name;
}

char_t* ECOCALLMETHOD CEcoLab1Factory_get_Version(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab1Factory* pCMe = (CEcoLab1Factory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Version;
}


char_t* ECOCALLMETHOD CEcoLab1Factory_get_Manufacturer(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab1Factory* pCMe = (CEcoLab1Factory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Manufacturer;
}

IEcoComponentFactoryVTbl g_x1F5DF16EE1BF43B999A434ED38FE8F3AFactoryVTbl = {
    CEcoLab1Factory_QueryInterface,
    CEcoLab1Factory_AddRef,
    CEcoLab1Factory_Release,
    CEcoLab1Factory_Alloc,
    CEcoLab1Factory_Init,
    CEcoLab1Factory_get_Name,
    CEcoLab1Factory_get_Version,
    CEcoLab1Factory_get_Manufacturer
};

CEcoLab1Factory g_x1F5DF16EE1BF43B999A434ED38FE8F3AFactory = {
    &g_x1F5DF16EE1BF43B999A434ED38FE8F3AFactoryVTbl,
    0,
    (CreateInstance)createCEcoLab1,
    (InitInstance)initCEcoLab1,
    "Lab1\0",
    "1.0.0\0",
    "Anton_Shadrin\0"
};

#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr() {
    return (IEcoComponentFactory*)&g_x1F5DF16EE1BF43B999A434ED38FE8F3AFactory;
};
#elif ECO_LIB
IEcoComponentFactory* GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A = (IEcoComponentFactory*)&g_x1F5DF16EE1BF43B999A434ED38FE8F3AFactory;
#endif