#include "headers/includes.h"
void PlayLayer::resetLevel()
{
    GJGameLevel *level = this->getLevel();

    this->m_bLevelComplete = false;
    this->getUILayer()->enableMenu();
    this->stopCameraShake();

    this->setActiveEnterEffect(1);

    this->stopActionByTag(0);
    this->stopActionByTag(1);

    this->m_bMoveCameraX = false;
    this->m_bMoveCameraY = false;

    this->m_bSomeBool = this->getCleanReset();
    this->m_bPlayerDestroyed = false;

    for (size_t i = 0; i < m_pObjects->count(); i++)
    {
        GameObject *obj = dynamic_cast<GameObject *>(this->m_pObjects->objectAtIndex(i));
        obj->resetObject()
            obj->setEnterEffect(1);
    }

    this->getAudioEffectsLayer()->resetAudioVars();
    this->getPlayer()->resetObject();

    this->animateOutGround(true);

    if (this->m_pSpawnObjects)
    {
        this->m_pSpawnObjects->release();
        this->m_pSpawnObjects = nullptr;
    }

    this->m_pSpawnObjects = cocos2d::CCArray::create();

    for (size_t i = 0; i < this->m_pObjectsToSpawn->count(); i++)
    {
        GameObject *obj = dynamic_cast<GameObject *>(this->m_pObjectsToSpawn->objectAtIndex(i));
        this->m_pSpawnObjects->addObject(obj);
    }

    qsort(this->m_pSpawnObjects->data->arr, this->m_pSpawnObjects->data->num, 4, &xComp);

    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();

    this->m_obCameraTo.y = this->getPlayer()->getPosition().y - winSize.height + 90.0f;

    this->updateCamera(0.0f);
    this->updateVisibility();

    this->setCleanReset(false);

    this->tintBackground(this->getLevelSettings->getStartBGColor(), false);
    this->tintGround(this->getLevelSettings()->getStartGColor(), false);

    this->loadLastCheckpoint();
    this->updateCamera(0.0f);
    this->updateVisibility();
    this->updateAttempts();

    GameStatsManager::sharedState()->incrementStat("2");

    level->setAttempts(level->getAttempts() + 1);

    if (!this->getPracticeMode() || this->getTestMode())
    {
        CocosDenshion::SimpleAudioEngine *SAE = CocosDenshion::SimpleAudioEngine::sharedEngine();
        if (this->getPlayer()->getPosition().x > 0.0f)
        {
            if (!SAE->isBackgroundMusicPlaying())
            {
                const char *song = LevelTools::getAudioFileName(level->getAudioTrack());
                SAE->playBackgroundMusic(song, false);
            }

            float bgTime = this->getPlayer()->getPosition().x / 311.58;
            SAE->setBackgroundMusicTime(bgTime);
            SAE->resumeBackgroundMusic();
        }
        else
        {
            if (!SAE->isBackgroundMusicPlaying())
            {
                const char *song = LevelTools::getAudioFileName(level->getAudioTrack());
                SAE->playBackgroundMusic(song, false);
            }
            else
            {
                SAE->rewindBackgroundMusic();
            }
        }
    }
}