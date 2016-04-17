//
//  FishingLayer.h
//  FishJoyMini
//
//  Created by Ken on 14-3-11.
//
//

#ifndef FishJoyMini_FishingLayer_h
#define FishJoyMini_FishingLayer_h
#include "cocos2d.h"
#include "FishActor.h"
#include <cstdlib>
#include "MainMenuLayer.h"

#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class FishingLayer : public Layer{
	
public:
	
	bool init();
	CREATE_FUNC(FishingLayer);
	
protected:
	
	void fishActorsInital();
	Vector<FishActor*> fishActors;
	
	Sprite* cannon;
	
	Sprite* _bullet;
	
	Layout* widget;
	
	Label* scoreLabel;
	
	int score;

	void bulletRelease();
	
	virtual void update(float delta);
    
    void createBasicUI();
	
	/** Callback func of shoot */
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);

	void bulletShoot(Vec2 endPosition);
	
	void setCannonRotation(Vec2 targetPos);
	
	void collideCheck();
	
	void removeFishes(Node* sender);
	
	void updateFishMovement();
};

#endif
