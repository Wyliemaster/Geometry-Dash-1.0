#include "headers/includes.h"

void PlayLayer::updateVisibility()
{
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();

    float unk = 70.0f;

    int prevSection = floorf(this->m_obCameraTo.x / 100) - 1.0f;
    int nextSection = ceilf((this->m_obCameraTo.x + winSize.width) / 100) + 1.0f;

    for (size_t i = prevSection; i < nextSection; i++)
    {
        if (i > 0)
        {
            if (i < this->m_pSections->count())
            {
                cocos2d::CCArray *section = dynamic_cast<cocos2d::CCArray *>(this->m_pSections->objectAtIndex(i));
                for (size_t j = 0;; j++)
                {

                    if (j < section->count())
                    {
                        GameObject *obj = section->objectAtIndex(j);

                        obj->activateObject();

                        if (obj->getType() == GameObjectType::kBallFrame || obj->getType() == GameObjectType::kYellowJumpRing)
                            obj->setScale(this->getAudioEffectsLayer()->getAudioScale())

                                cocos2d::CCPoint pos = obj->getRealPosition();

                        float unk2 = 0.0f;

                        if (obj->getType() == GameObjectType::kTransparent)
                        {
                            unk2 = obj->getTextureRect().origin.x * obj->getScaleX() * 0.4f;
                        }

                        unsigned char opacity = this->getRelativeMod(pos, unk, unk2) * 255.0f;

                        if (!obj->getDontTransform())
                        {
                            obj->setOpacity(opacity);
                            this->applyEnterEffect(obj);
                        }
                    }
                }
            }
        }
    }


    // deactivates the stuff already passed to optimise memory or something ig
    for (size_t i = this->m_nPrevSection; i < this->m_nNextSection; i++)
    {
        if (i > 0)
        {
            if (i < this->m_pSections->count())
            {
                cocos2d::CCArray *section = dynamic_cast<cocos2d::CCArray *>(this->m_pSections->objectAtIndex(i));
                for (size_t j = 0;; j++)
                {
                    if (j >= section->count())
                        break;

                    dynamic_cast<GameObject *>(section->objectAtIndex(j))->deactivateObject();
                }
            }
        }
    }
    this->m_nPrevSection = prevSection;
    this->m_nNextSection = nextSection;
}