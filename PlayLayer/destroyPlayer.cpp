#include "headers/includes.h"

void PlayLayer::destroyPlayer()
{
    float percentage = 0.0f;

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

        if (!this->getPracticeMode())
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
        }

        GameSoundManager::sharedManager()->playEffect("explode_11.ogg", 1.0f, 0.0f, 0.65f);

        cocos2d::CCSequence::create(
            cocos2d::CCDelayTime::create(1.0f), 
            cocos2d::CCCallFunc::create(this, PlayLayer::resetLevel, 0), 
            0
            )->runAction();

        if (!this->getTestMode())
        {
            percentage = (this->getPlayer()->getPosition().x / this->m_fEndOfLevel) * 100.0f;
            this->getLevel()->savePercentage(percentage, this->getPracticeMode());
        }

        if (this->getLevel()->getLevelType() = LevelType::kLevelTypeMain)
        {
            GameManager::sharedState()->reportPercentageForLevel(this->getLevel()->getLevelID(), percentage, this->getPracticeMode());
        }

    }
}