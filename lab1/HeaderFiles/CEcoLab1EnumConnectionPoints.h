#ifndef __C_ECOLAB1_ENUM_CONNECTION_POINTS_H__
#define __C_ECOLAB1_ENUM_CONNECTION_POINTS_H__

#include "IEcoEnumConnectionPoints.h"
#include "IdEcoList1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1EnumConnectionPoints {
    IEcoEnumConnectionPointsVTbl* m_pVTblIECP;
    IEcoList1* m_List;
    IEcoMemoryAllocator1* m_pIMem;

} CEcoLab1EnumConnectionPoints;

int16_t ECOCALLMETHOD createCEcoLab1EnumConnectionPoints(/* in */ IEcoUnknown* pIUnkSystem, /* in */ struct IEcoConnectionPoint *pCP, /* out */ IEcoEnumConnectionPoints** ppIEnum);
void ECOCALLMETHOD deleteCEcoLab1EnumConnectionPoints(/* in */ IEcoEnumConnectionPoints* pIEnum);

#endif /* __C_ECOLAB1_ENUM_CONNECTION_POINTS_H__ */