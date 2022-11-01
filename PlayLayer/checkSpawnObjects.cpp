#include "headers/includes.h"

void PlayLayer::checkSpawnObjects()
{
    while (true)
    {

        /*
        seems to converting count to a 64 bit number? i cant tell, the asm if anyone wants to look

        @0x198C9E
        R0 = count
        R2 = this


        MOVS    R3, R0
        SUBS    R2, R3, #1
        SBCS    R3, R2
        LSLS    R3, R3, #0x18
        LSRS    R3, R3, #0x18
        CMP     R3, #0
        */
        if (this->m_pSpawnObjects->count())
        {
            GameObject *obj = this->m_pSpawnObjects->objectAtIndex(0);
            if (obj->getSpawnXPos() < this->getPlayer()->getPosition().x)
            {
                obj->triggerObject();
                this->m_pSpawnObjects->removeObjectAtIndex(0, 1);
            }
            else
                break;
        }
        else
            break;
    }
}