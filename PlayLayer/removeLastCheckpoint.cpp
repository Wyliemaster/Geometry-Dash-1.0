#include "headers/includes.h"

void PlayLayer::removeLastCheckpoint()
{
    if (this->m_pCheckpoints->count() - 1 != 0)
    {
        GameObject* obj = dynamic_cast<CheckpointObject*>(this->m_pCheckpoints->lastObject())->getObject();

        this->removeObjectFromSection(obj);
        obj->removeGlow();
        obj->removeMeAndCleanup();

        this->m_pCheckpoints->removeLastObject(true);
    }
}