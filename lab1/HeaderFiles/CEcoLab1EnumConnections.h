#ifndef __C_ECOLAB1_ENUM_CONNECTIONS_H__
#define __C_ECOLAB1_ENUM_CONNECTIONS_H__

#include "IEcoEnumConnections.h"
#include "IdEcoList1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1EnumConnections {

    IEcoEnumConnectionsVTbl* m_pVTblIEC;
    uint32_t m_cRef;
    IEcoList1* m_pSinkList;
    uint32_t m_cIndex;
    IEcoMemoryAllocator1* m_pIMem;
    IEcoSystem1* m_pISys;

} CEcoLab1EnumConnections;

int16_t ECOCALLMETHOD createCEcoLab1EnumConnections(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoList1* pIList, /* out */ IEcoEnumConnections** ppIEnum);
void ECOCALLMETHOD deleteCEcoLab1EnumConnections(/* in */ IEcoEnumConnections* pIEnum);

#endif /* __C_ECOLAB1_1_ENUM_CONNECTIONS_H__ */