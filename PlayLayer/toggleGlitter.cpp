#include "headers/includes.h"

void PlayLayer::toggleGlitter(bool toggle)
{
    if (toggle)
        this->m_pGlitter->resumeSystem();
    else
        this->m_pGlitter->stopSystem();
}