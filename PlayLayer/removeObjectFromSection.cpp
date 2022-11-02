#include "headers/includes.h"

void PlayLayer::removeObjectFromSection(GameObject* obj)
{
    cocos2d::CCArray* section = dynamic_cast<cocos2d::CCArray*>(this->m_pSections->objectAtIndex(obj->getSectionIdx()));
    section->removeObject(obj, true);
}