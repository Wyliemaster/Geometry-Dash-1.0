#include "headers/includes.h"

void PlayLayer::updateCamera(float dt)
{
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    cocos2d::CCPoint cam = m_obCamera;

    PlayerObject *player = this->getPlayer();

    float shakeOffset = (winSize.width / -2) + 75.0f;
    float unk4 = 0.0f;
    float unk5 = 10.0f;

    cocos2d::CCPoint shake = {0.0f, 0.0f};

    cocos2d::CCPoint pPos = player->getPosition();

    if (!player->getFlyMode())
    {
        float unk2 = 90.0f;
        float unk3 = 120.0f;

        if (player->getGravityFlipped())
        {
            std::swap(unk2, unk3);
        }

        if (player->getPosition().y <= this->cam.y + winSize.height - unk2)
        {
            if (player->getPosition().y < cam.y + unk3)
                unk4 = player->getPosition().y - unk3;
        }
        else
        {
            unk4 = player->getPosition().y - winSize.height + unk2;
        }

        if (!player->getGravityFlipped())
        {
            cocos2d::CCPoint lastGPos = player->getLastGroundPos();

            if (lastGPos.y == 105.0f && player->getPosition().y <= this->cam.y + winSize.height - unk2)
                unk4 = 0.0f;
        }
    }
    else
    {
        unk4 = 0.0f;
        if (this->m_fCameraYCenter + (winSize.height / -2.0f > 0.0f))
            unk4 = this->m_fCameraYCenter + (winSize.height / -2.0f);
        unk5 = 30.0f;
    }

    this->cam.y += (unk4 - this->cam.y) / unk5;

    if (this->cam.y <= 0.0f)
        this->cam.y = 0.0f;

    if (this->cam.y - winSize.height)
        this->cam.y -= winSize.height;

    if (this->m_bFirstAttempt)
    {
        if (this->cam.x <= 15.0f)
            this->cam.x = 15.0f;
    }

    if (!this->m_bMoveCameraX || !this->m_bMoveCameraY)
    {
        float temp = this->m_fEndOfLevel - winSize.width + cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getScreenLet();

        if (this->m_fEndOfLevel > 0.0f)
        {
            if (this->cam.x >= temp)
                this->cam.x = temp;

            if (temp - this->cam.x < 50.0f)
                this->moveCameraToPos({temp, this->m_pEndPortal->getPosition().y + (winSize.height / -2.0f)});
        }
    }

    if (!this->m_bMoveCameraX)
        m_obCamera.x = cam.x;

    if (!this->m_bMoveCameraY)
        m_obCamera.y = cam.y;

    if (this->m_bShakingCamera)
    {
        float r1 = rand() / 2147500000.0;
        float r2 = rand() / 2147500000.0;

        shake.x = ((2 * r1) - 1.0f) * this->m_fShakeIntensity;
        shake.y = ((2 * r2) - 1.0f) * this->m_fShakeIntensity;
    }

    cocos2d::CCCamera *ccCamera = this->getGameLayer()->getCamera();
    ccCamera->setCenterXYZ(shake.x, shake.y, 0.0f);
    ccCamera->setEyeXYZ(shake.x, shake.y, 1.0f);

    float bgScale = 0.0f;

    while (bgScale < this->m_fBackgroundScale)
        bgScale += this->m_fBackgroundScale;

    this->m_pBackground->setPosition({(shakeOffset - shake.x) * 0.1. shake.y * 1.0f});

    float gScale = 0.0f;

    while (gScale < this->m_fGroundScale)
        gScale += m_fGroundScale;

    this->m_pGround->setPosition({shakeOffset - shake.x, 90.0f});

    this->m_pForeground->setPosition({0.0f, shake.y});

    this->m_pGlitter->setPosition({shake.x + (winSize.width / 2), shake.y + (winSize.height / 2)});
}
