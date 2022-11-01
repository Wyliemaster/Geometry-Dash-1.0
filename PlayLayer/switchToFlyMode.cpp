#include "headers/includes.h"
void PlayLayer::switchToFlyMode(GameObject *pPortal, bool a3)
{
    this->getPlayer()->setPortalP(pPortal->getPosition());
    this->getPlayer()->setPortalObject(pPortal);
    this->getPlayer()->toggleFlyMode(true);
    this->getPlayer()->toggleGlitter(true);

    cocos2d::CCSize windowSize = cocos2d::CCDirector::sharedDirector()->getWinSize();

    this->m_fGroundBottom = pPortal->getPosition().y - 150.0f;
    this->m_fGroundTop = roundf(this->m_fGroundBottom / 30.0f) * 30.0f;

    this->m_fGroundBottom = std::min(90.0f, this->m_fGroundBottom);
    this->m_fGroundTop = this->m_fGroundTop + 300.0f;
    this->m_fCameraYCenter = this->m_fGroundBottom + 150.0f;

    this->animateOutGround(a3);

    float camY = this->m_fCameraYCenter + (windowSize.height / -2.0f);

    if (!a3)
    {
        this->moveCameraY(camY, 0.5f, 1.4f);
    }

    else
    {
        this->m_bMoveCameraY = true;
        this->m_obCameraTo.y = camY;
    }
}