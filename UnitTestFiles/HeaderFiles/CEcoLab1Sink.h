#ifndef __C_ECOLAB1_SINK_H__
#define __C_ECOLAB1_SINK_H__

#include "IEcoLab1.h"
#include "IEcoLab1Events.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1Sink {

    IEcoLab1VTblEvents* m_pVTblIEcoLab1Events;

    int16_t (ECOCALLMETHOD *Advise)(/* in */ struct CEcoLab1Sink* me, /* in */IEcoLab1 *pIEcoLab1);
    int16_t (ECOCALLMETHOD *Unadvise)(/* in */ struct CEcoLab1Sink* me, /* in */IEcoLab1 *pIEcoLab1);

    uint32_t m_cRef;
    uint32_t m_cCookie;

    IEcoMemoryAllocator1* m_pIMem;


} CEcoLab1Sink, *CEcoLab1SinkPtr;

int16_t ECOCALLMETHOD createCEcoLab1Sink(/* in */ IEcoMemoryAllocator1* pIMem, /* out */ IEcoLab1Events** ppIEcoLab1Events);
void ECOCALLMETHOD deleteCEcoLab1Sink(/* in */ IEcoLab1Events* pIEcoLab1Events);

#endif /* __C_ECOLAB1_SINK_H__ */