//
//  ClickBalloonLayer.h
//

#ifndef Ballon_ClickBalloonLayer_h
#define Ballon_ClickBalloonLayer_h
#include "cocos2d.h"
#include "BallActor.h"
#include <cstdlib>
#include "MainMenuLayer.h"
#include "GameOverLayer.h"

#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class ClickBalloonLayer : public Layer{

public:

	bool init();
	CREATE_FUNC(ClickBalloonLayer);

protected:

	void addNewBallon();
	Vector<BallActor*> ballActors;

	Sprite* gamebar;
	Label* timeLabel;
	Label* balloonClickSumLabel;
	Label* scoreLabel;

	int score;
	int time;
	int balloonClickSum;
	int miss;

	float speed;

	virtual void update(float delta);
	void updateBalloon(float dt);

	void createBasicUI();

	/** Callback func of shoot */
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	void clickCheck(Touch *touch);

	void removeBallon(Node* sender);

	void updateBalloonMovement();
	void updateTimeLabel(float dt);
	void increaseSpeed(BallActor* balloon);
};

#endif
