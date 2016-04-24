//
//  FishingLayer.cpp
//  FishJoyMini
//
//  Created by Ken on 14-3-11.
//
//

#include "ClickBalloonLayer.h"

// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define SOUND_COIN        "Audio/sound_coin.ogg"
#else
#define SOUND_COIN        "Audio/sound_coin.mp3"
#endif // CC_PLATFOR_ANDROID

// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define SOUND_FIRE        "Audio/sound_fire.ogg"
#else
#define SOUND_FIRE        "Audio/sound_fire.mp3"
#endif // CC_PLATFOR_ANDROID

#define FISH_LAYER_ORDER    1
#define BULLET_LAYRE_ORDER  2
#define UI_LAYER_ORDER      2
#define CANNON_LAYER_ORDER  3


bool ClickBalloonLayer::init(){

	Layer::init();
	//_bullet = NULL;

	//Add background picture
	auto background = Sprite::create("gamingbackground.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	background->setTag(101);
	addChild(background, 0);

	//Read the texture to sprite frame cache
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CocoStudioRes/cannon-hd.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameScene/Item-chaojiwuqi-iphone-hd.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CocoStudioRes/UI_GameMenuLayer-hd.plist");


	createBasicUI();

	//Get the instance of cannon
	//cannon = Sprite::createWithSpriteFrameName("actor_cannon1_72.png");
	//cannon->setPosition(480, 50);
	//addChild(cannon, CANNON_LAYER_ORDER);

	//Add the touch event callback function
	EventListenerTouchOneByOne * listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(ClickBalloonLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ClickBalloonLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ClickBalloonLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	schedule(schedule_selector(ClickBalloonLayer::updateBalloon), 1.0f);
	//三秒之后执行计数器
	schedule(schedule_selector(ClickBalloonLayer::updateTimeLabel), 1.0f);
	//Activate update
	//scheduleUpdate();

	//Init the fishes
	//fishActorsInital();

	//Update the fishes one time
	//updateFishMovement();

	//Preload background effect
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_COIN);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_FIRE);
	return true;
}

void ClickBalloonLayer::createBasicUI()
{
	////create UI
	//Sprite *boardBottom = Sprite::createWithSpriteFrameName("ui_box_02.png");
	//boardBottom->setPosition(480, 41);
	//addChild(boardBottom, UI_LAYER_ORDER);

	//Sprite *boardTop = Sprite::createWithSpriteFrameName("ui_box_01.png");
	//boardTop->setPosition(480, 578);
	//addChild(boardTop, UI_LAYER_ORDER);

	////Get the instantce of ui_box_01_01 and make it rotate forever
	//Sprite * wheelSpr = Sprite::createWithSpriteFrameName("ui_box_01_01.png");
	//addChild(wheelSpr, UI_LAYER_ORDER);
	//wheelSpr->setPosition(Point(480, 578));
	//wheelSpr->runAction(RepeatForever::create((RotateBy::create(3, 360, 360))));

	////Get the instance of label of score
	//scoreLabel = Label::createWithTTF("00000", "fonts/Marker Felt.ttf", 24);
	//scoreLabel->setPosition(242, 28);
	//addChild(scoreLabel, UI_LAYER_ORDER);
	score = 0;
	time = 100;
	round = 1;
	gamebar = Sprite::create("gamebar.png");
	gamebar->setPosition(320, 925);
	addChild(gamebar, UI_LAYER_ORDER);
	scoreLabel = Label::createWithTTF("score:0", "fonts/BuxtonSketch.ttf", 40);
	scoreLabel->setPosition(100, 930);
	addChild(scoreLabel, UI_LAYER_ORDER);
	timeLabel = Label::createWithTTF("time:100", "fonts/BuxtonSketch.ttf", 40);
	timeLabel->setPosition(320, 930);
	addChild(timeLabel, UI_LAYER_ORDER);
	roundLabel = Label::createWithTTF("round:1", "fonts/BuxtonSketch.ttf", 40);
	roundLabel->setPosition(540, 930);
	addChild(roundLabel, UI_LAYER_ORDER);
	
}


bool ClickBalloonLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("BEGAN:(%f,%f)", touch->getLocation().x, touch->getLocation().y);
	// can't touch the ui
	//if (touch->getLocation().y < 80)
		//return false;
	clickCheck(touch);
	return true;
}
void ClickBalloonLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	//setCannonRotation(touch->getLocation());
	CCLOG("MOVED:(%f,%f)", touch->getLocation().x, touch->getLocation().y);
}

void ClickBalloonLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	//setCannonRotation(touch->getLocation());

	//Shoot the bullet
	//bulletShoot(touch->getLocation());

	CCLOG("END:(%f,%f)", touch->getLocation().x, touch->getLocation().y);

}
void ClickBalloonLayer::update(float delta){

	//Update the movement of fishes by their speed, limit the move area of the fishes
	for (auto balloon : ballActors){

		if (balloon->getPositionX()<0){

			removeBallon(balloon);
		}
		else if (balloon->getPositionX()>640){

			removeBallon(balloon);
		}
		else if (balloon->getPositionY()>1000){

			removeBallon(balloon);
		}
		else if (balloon->getPositionY()<-100){

			removeBallon(balloon);
		}
		
	}

	////Check the collide
	//collideCheck();

}
void ClickBalloonLayer::updateBalloon(float dt){
	//每秒20%概率产生新的气球
	/*int rand = random() % 5;
	if (rand == 0){
		addNewBallon();
	}*/
	addNewBallon();
}

void ClickBalloonLayer::clickCheck(Touch *touch){
	for (auto balloon : ballActors){
		if ((balloon->getPositionX() - balloon->getContentSize().width / 2) < touch->getLocation().x&&touch->getLocation().x < (balloon->getPositionX() + balloon->getContentSize().width / 2))
		{
		
			if ((balloon->getPositionY() - balloon->getContentSize().height / 2)< touch->getLocation().y&&touch->getLocation().y < (balloon->getPositionY() + balloon->getContentSize().height / 2))
			{
				log("sccre:%d", balloon->getBallScore());
				score += balloon->getBallScore();
				char temp[64];		
				sprintf(temp, "%d", score);
				char tmp[64] = "score:";
				strcat(tmp, temp);
				scoreLabel->setString(tmp);
				removeBallon(balloon);
			}
		}
	}
}

void ClickBalloonLayer::removeBallon(Node* sender){
	//Get the collided fish
	BallActor *ballActor = (BallActor*)sender;

	//Remove the collided fish
	ballActor->setVisible(false);
	ballActor->removeAllChildrenWithCleanup(true);
	ballActor->removeFromParent();

	auto it_self = ballActors.begin();

	while (it_self != ballActors.end()) {

		BallActor* balloon = dynamic_cast<BallActor*>(*it_self);
		//If the bullet collide the fish
		if (balloon == ballActor) {
			it_self = ballActors.erase(it_self);
			break;
		}
		else{

			++it_self;
		}
	}
	//Play music effect when catch a fish
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_COIN);
}

void ClickBalloonLayer::addNewBallon(){
	int i = random() % 3;
	if (i == 0){
		auto ballon = BallActor::createWithType(BallActor::BallActorType::GoalBall);
		//设置ballon初始位置
		int tmp = 640 - ballon->getContentSize().width;
		ballon->setPosition(Point(rand() % tmp + ballon->getContentSize().width / 2, 0));
		ballon->setBallScore(1);
		((GoalBallActor*)ballon)->activateBallMovement();
		addChild(ballon, FISH_LAYER_ORDER);
		ballActors.pushBack(ballon);
	}
	else if (i == 1){
		auto ballon = BallActor::createWithType(BallActor::BallActorType::GoodBall);
		//设置ballon初始位置	
		int tmp = 640 - ballon->getContentSize().width;
		log("tmp:%d", tmp);
		ballon->setPosition(Point(rand() % tmp+ballon->getContentSize().width/2, 0));
		((GoalBallActor*)ballon)->activateBallMovement();
		addChild(ballon, FISH_LAYER_ORDER);
		ballActors.pushBack(ballon);
	}
	else {
		auto ballon = BallActor::createWithType(BallActor::BallActorType::BadBall);
		//设置ballon初始位置
		int tmp = 640 - ballon->getContentSize().width;
		ballon->setPosition(Point(rand() % tmp + ballon->getContentSize().width / 2, 0));
		((GoalBallActor*)ballon)->activateBallMovement();
		addChild(ballon, FISH_LAYER_ORDER);
		ballActors.pushBack(ballon);
	}

	
}

void ClickBalloonLayer::updateBalloonMovement(){
	for (auto balloon : ballActors) {
		balloon->setPosition(balloon->getPositionX(), balloon->getPositionY() + balloon->getSpeedY());
	}
}
void ClickBalloonLayer::updateTimeLabel(float dt)
{
	time--;
	char temp[64];
	sprintf(temp, "%d", time);
	char tmp[64] = "time:";
	strcat(tmp, temp);
	timeLabel->setString(tmp);
}