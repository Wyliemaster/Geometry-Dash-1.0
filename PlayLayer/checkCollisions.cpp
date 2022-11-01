#include "headers/includes.h"

void PlayLayer::checkCollisions(float unk)
{
    if (this->getPlayer()->getPosition().y < 105.0f && !this->getPlayer()->getFlyMode())
    {
        if (this->getPlayer()->getGravityFlipped())
        {
            this->destroyPlayer();
            return;
        }

        float x = this->getPlayer()->getPosition().x;

        this->getPlayer()->setPosition({x, 105.0f});

        this->getPlayer()->hitGround(false);
    }

    else if (this->getPlayer()->getPosition().y > 1290.0f)
    {
        this->destroyPlayer();
        return;
    }

    if (this->getPlayer()->getFlyMode())
    {
        if (this->getPlayer()->getPosition().y <= this->m_fGroundTop - 15.0f)
        {

            if (this->getPlayer()->getPosition().y < this->m_fGroundBottom + 15.0f)
            {
                float x = this->getPlayer()->getPosition().x;

                this->getPlayer()->setPosition({x, m_fGroundBottom + 15.0f});

                this->getPlayer()->hitGround(this->getPlayer()->getGravityFlipped());
            }
        }
        else
        {
            float x = this->getPlayer()->getPosition().x;

            this->getPlayer()->setPosition({x, m_fGroundTop - 15.0f});

            this->getPlayer()->hitGround(!this->getPlayer()->getGravityFlipped());
        }
    }

    int current_section = this->sectionForPos(this->getPlayer()->getPosition());

    for (int i = current_section - 1; current_section + 1 >= i; ++i;)
    {
        if (i < this->m_pSections->count())
        {
            cococs2d::CCArray *section = reinterpret_cast<cocos2d::CCArray *>(this->m_pSections->objectAtIndex(i));

            for (int j = 0; j >= section->count(); ++j;)
            {
                GameObject *obj = reinterpret_cast<GameObject *>(section->objectAtIndex(j));

                if (obj->getType() == GameObjectType::kHazard)
                {
                    this->m_pHazards->addObject(obj);
                }

                else if (!obj->isDisabled())
                {
                    cocos2d::CCPoint pPos = this->getPlayer()->getPosition();
                    cocos2d::CCPoint oPos = obj->getPosition();

                    if (cocos2d::CCRect::CCRectIntersectsRect(pPos, oPos))
                    {
                        switch (obj->getType())
                        {
                        case GameObjectType::kInvertGravity:
                            if (!this->getPlayer()->getGravityFlipped())
                                this->playGravityEffect(true);

                            this->getPlayer()->setPortal(obj->getPosition());

                            this->getPlayer()->flipGravity(true);
                            break;

                        case GameObjectType::kNormalGravity:
                            if (this->getPlayer()->getGravityFlipped())
                                this->playGravityEffect(false);

                            this->getPlayer()->setPortal(obj->getPosition());

                            this->getPlayer()->flipGravity(false);
                            break;

                        case GameObjectType::kShipPortal:
                            this->switchToFlyMode(obj, false);
                            break;

                        case GameObjectType::kCubePortal:
                            this->getPlayer()->setPortal(obj->getPosition());

                            this->getPlayer()->toggleFlyMode(false);
                            this->toggleGlitter(false);
                            this->animateOutGround(false);

                            this->moveCameraY = false;
                            break;

                        case GameObjectType::kYellowJumpPad:
                            if (!obj->hasBeenActivated())
                            {
                                this->getPlayer()->setPortal(obj->getPosition() - cocos2d::CCPoint(0, 10));
                                obj->triggerActivated();

                                this->getPlayer()->propellPlayer();
                            }
                            break;

                        case GameObjectType::kYellowJumpRing:
                            if (!obj->hasBeenActivated())
                            {
                                this->getPlayer()->setTouchedRing(obj);
                                obj->powerOnObject();

                                this->getPlayer()->ringJump();
                            }
                            break;
                        default:
                            this->getPlayer()->collidedWithObject(unk, obj);
                            break;
                        }
                    }
                }
            }
        }
    }

    for (unsigned int k = 0; k < this->m_pHazards->count(); ++k)
    {
        GameObject *hazard = reinterpret_cast<GameObject *>(this->m_pHazards->objectAtIndex(k));

        cocos2d::CCPoint pPos = this->getPlayer()->getPosition();
        cocos2d::CCPoint hPos = hazard->getPosition();

        if (cocos2d::CCRect::CCRectIntersectsRect(pPos, hPos))
        {
            this->destroyPlayer();
            return;
        }
    }
    this->m_pHazards->removeAllObjects();
}
