#include "headers/includes.h"

void PlayLayer::destroyPlayer()
{
    float temp = 0.0f;

    if(!this->getPlayer()->getIsLocked() && !this->m_bPlayerDestroyed)
    {
        if (!this->m_bShowedHint && this->getLevel()->getLevelID() == 1 && !this->getPlayer()->hasJumped() && this->getAttempts() > 1)
        {
            this->showHint();
        }

        if (!this->m_bShowedHint && this->getLevel()->getLevelID() == 3 && !this->getPlayer()->hasRingJumped() && this->getAttempts() > 1)
        {
            this->showHint();
        }

        this->m_bPlayerDestroyed = true;

        this->getPlayer()->playerDestroyed();

        if (!this->m_bPracticeMode)
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
        }

        GameSoundManager::sharedManager()->playEffect("explode_11.ogg", 1.0f, 0.0f, 0.65f);

        cocos2d::CCSequence::create(
            cocos2d::CCDelayTime::create(1.0f), 
            cocos2d::CCCallFunc::create(this, PlayLayer::resetLevel, 0), 
            0
            )->runAction();

        if (!this->m_bTestMode)
        {
            temp = (this->getPlayer()->getPosition().x / this->field_1CC) * 100.0f;
            this->getLevel()->savePercentage(temp, this->m_bPracticeMode);
        }

        if (this->getLevel()->getLevelType() = LevelType::kLevelTypeMain)
        {
            GameManager::sharedState()->reportPercentageForLevel(this->getLevel()->getLevelID(), temp, this->m_bPracticeMode);
        }

    }
}