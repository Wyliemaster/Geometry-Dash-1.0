#include "headers/includes.h"

void PlayLayer::checkSpawnObjects()
{
    while (true)
    {
        if (this->m_pSpawnObjects->count() - 1 != 0)
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