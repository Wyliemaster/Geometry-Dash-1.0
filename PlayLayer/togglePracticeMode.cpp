#include "headers/includes.h"

void PlayLayer::togglePracticeMode(bool toggle)
{
    if (toggle != this->getPracticeMode())
    {
        CocosDenshion::SimpleAudioEngine *SAE CocosDenshion::SimpleAudioEngine::sharedEngine();

        this->setPracticeMode(toggle);

        this->getUILayer()->toggleCheckpointsMenu(toggle);

        if (!toggle)
        {
            while (true)
            {
                if (this->m_pCheckpoints->count() - 1 == 0)
                    break;

                this->removeLastCheckpoint();
            }

            const char *trackName = LevelTools::getAudioFileName(this->getLevel()->getAudioTrack());
            SAE->playBackgroundMusic(trackName, false);
            this->setCleanReset(true);
            this->resetLevel();
        }
        else if (!this->getTestMode())
        {
            SAE->pauseBackgroundMusic();
            SAE->playBackgroundMusic("StayInsideMe.mp3", true);
        }
    }
}