#ifndef __PLAYLAYER__
#define __PLAYLAYER__

#include "includes.h"

struct PlayLayer : cocos2d::CCLayer
{
public:
  float m_fCameraYCenter;
  float m_fGroundBottom;
  float m_fGroundTop;
  LevelSettingsObject *m_pLevelSettings;
  EndPortalObject *m_pEndPortal;
  cocos2d::CCArray *m_pCheckpoints;
  int m_eActiveEnterEffect;
  cocos2d::CCSprite *m_pBackground;
  cocos2d::CCSprite *m_pGround;
  cocos2d::CCSprite *m_pGroundBottomSquare;
  cocos2d::CCSprite *m_pGroundTopSquare;
  cocos2d::CCSprite *m_pGroundBottomLine;
  cocos2d::CCSprite *m_pGroundTopLine;
  cocos2d::CCLayer *m_pForeground;
  cocos2d::CCLayer *m_pGroundBottom;
  cocos2d::CCLayer *m_pGroundTop;
  float m_fGroundScale;
  float m_fBackgroundScale;
  bool m_bGroundAnimatedIn;
  cocos2d::CCArray *m_pSections;
  cocos2d::CCArray *m_pHazards;
  cocos2d::CCArray *m_pActiveObjects;
  cocos2d::CCArray *field_194;
  cocos2d::CCArray *m_pSpawnObjects;
  cocos2d::CCArray *field_19C;
  cocos2d::CCArray *m_pStateObjects;
  cocos2d::CCParticleSystemQuad *m_pGlitter;
  AudioEffectsLayer *m_pAudioEffectsLayer;
  float m_fGroundBottomStartPos;
  float m_fGroundTopStartPos;
  bool m_bPlayerDestroyed;
  bool m_bSomeBool;
  bool m_bMoveCameraX;
  bool m_bMoveCameraY;
  int field_1B8;
  int m_nPrevSection;
  int m_nNextSection;
  int m_nRodType;
  cocos2d::_ccColor3B m_cGroundCol;
  float m_fEndOfLevel;
  float m_fLastObjectXPos;
  cocos2d::CCLabelBMFont *m_pAttemptLabel;
  bool m_bShakingCamera;
  float m_fShakeIntensity;
  bool m_bLevelComplete;
  bool m_bShowedHint;
  char field_1E2;
  char field_1E3;
  int m_pEffectsManager;
  UILayer *m_pUILayer;
  PlayerObject *m_pPlayer;
  GJGameLevel *m_pLevel;
  cocos2d::CCPoint m_obCamera;
  int gap1FC;
  int field_200;
  int field_204;
  int field_208;
  cocos2d::CCPoint m_obCameraTo;
  bool m_bTestMode;
  bool m_bPracticeMode;
  char field_216;
  char field_217;
  cocos2d::CCSpriteBatchNode *m_pBatchNode;
  cocos2d::CCSpriteBatchNode *m_pBatchNodeAdd;
  cocos2d::CCLayer *m_pGameLayer;
  cocos2d::_ccColor3B m_cActiveBGColour;
  bool m_bCleanReset;
  cocos2d::CCPoint m_obStartPos;
  int field_230;
  int field_234;
  int field_238;
  int field_23C;
  int field_240;
  int field_244;
  int m_nAttempts;
  int m_nJumps;
  float m_fSteps;

public:

    void checkCollisions(float);
    void checkSpawnObjects();
    void destroyPlayer();
    void fullReset();
    void removeLastCheckpoint();
    void removeObjectFromSection(GameObject*);
    void resetLevel();
    void switchToFlyMode(GameObject*, bool);
    void toggleGlitter(bool);
    void togglePracticeMode(bool);
    void update(float);

    void playGravityEffect(bool);
    void animateOutGround(bool);
    void switchToFlyMode(GameObject*, bool);
    void stopCameraShake();
    void updateCamera(float);
    void updateVisibility();

    int sectionForPos(cocos2d::CCPoint);


    CREATE_GET_SET(Attempts, PlayLayer, int, n)
    CREATE_GET_SET(Jumps, PlayLayer, int, n)
    CREATE_GET_SET(ActiveEnterEffect, PlayLayer, int, e) // todo: handle enum

    CREATE_GET_SET(Steps, PlayLayer, float, f)
    CREATE_GET_SET(Camera, PlayLayer, cocos2d::CCPoint, ob)
    
    CREATE_GET_SET(CleanReset, PlayLayer, bool, b)
    CREATE_GET_SET(PracticeMode, PlayLayer, bool, b)
    CREATE_GET_SET(TestMode, PlayLayer, bool, b)

    CREATE_GET_SET(ActiveBGColour, PlayLayer, cocos2d::_ccColor3B, c)
    
    CREATE_GET_SET(Player, PlayLayer, PlayerObject*, p);
    CREATE_GET_SET(Level, PlayLayer, GJGameLevel*, p);
    CREATE_GET_SET(AudioEffectsLayer, PlayLayer, AudioEffectsLayer*, p)
    CREATE_GET_SET(UILayer, PlayLayer, UILayer*, p);
    CREATE_GET_SET(LevelSettings, PlayLayer, LevelSettingsObject*, p);
    CREATE_GET_SET(GEM, PlayLayer, GameEfectsManager*, p)
    CREATE_GET_SET(BatchNode, PlayLayer, cocos2d::CCSpriteBatchNode*, p)
    CREATE_GET_SET(BatchNodeAdd, PlayLayer, cocos2d::CCSpriteBatchNode*, p)
    CREATE_GET_SET(GameLayer, PlayLayer, cocos2d::CCLayer*, p)




};

#endif