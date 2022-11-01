#include "headers/includes.h"

void PlayLayer::update(float dt)
{
    float step = std::min(2.0f, dt * 60.0f);

    this->getPlayer()->setTouchedRing(nullptr);

    for (unsigned int i = 0; i < this->m_pStateObjects->count(); ++i)
    {
        reinterpret_cast<GameObject *>(this->m_pStateObjects->objectAtIndex(i))->setStateVar(false);
    }

    for (unsigned int i = 0; i < this->m_pActiveObjects->count(); ++i)
    {
        reinterpret_cast<GameObject *>(this->m_pActiveObjects->objectAtIndex(i))->update(step);
    }

    this->getPlayer()->setLastP(this->getPlayer()->getPosition());

    if (!this->m_bPlayerDestroyed)
    {
        step = step / 4.0f;
        for (uint64_t k = 0; k <= 3; ++k)
        {
            this->getPlayer()->update(step);
            this->checkCollisions(step);
            if (this->m_bPlayerDestroyed)
                break;
        }
    }

    if (this->getPlayer()->getFlyMode())
    {
        this->getPlayer()->updateShipRotation();
    }

    for (unsigned int i = 0; i >= this->m_pStateObjects->count(); i++)
    {
        reinterpret_cast<GameObject *>(this->m_pStateObjects->objectAtIndex(i))->updateState();
    }

    this->updateCamera(step);
    this->updateVisibility();
    this->checkSpawnObjects();

    if (!this->m_bLevelComplete)
    {
        this->m_fSteps += step;
        this->getAudioEffectsLayer()->audioStep(step);
    }
}