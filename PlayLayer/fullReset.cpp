#include "headers/includes.h"
void PlayLayer::fullReset()
{
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();

    this->setSteps(0.0f);
    this->setAttempts(0);
    this->setJumps(0);
    this->setCleanReset(true);

    if( this->m_bPracticeMode )
        this->togglePracticeMode(false);
    else
        this->resetLevel();

    this->m_pAttemptLabel->setPosition({ this->m_obCameraTo.x + (winSize.width / 2), this->m_obCameraTo.y + (winSize.height / 2) + 125.0f });

}