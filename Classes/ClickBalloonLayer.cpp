//
//  ClickBalloonLayer.cpp
//

#include "ClickBalloonLayer.h"
bool ClickBalloonLayer::init(){

	Layer::init();
	//_bullet = NULL;

	//Add background picture
	auto background = Sprite::create("gamingbackground.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	background->setTag(101);
	addChild(background, 0);
	createBasicUI();

	return true;
}

void ClickBalloonLayer::createBasicUI()
{
	score = 0;
	time = 3;
	balloonClickSum = 0;
	speed = 0;
	miss = 0;
	gamebar = Sprite::create("gamebar.png");
	gamebar->setPosition(320, 925);
	addChild(gamebar);
	scoreLabel = Label::createWithTTF("score:0", "fonts/BuxtonSketch.ttf", 40);
	scoreLabel->setPosition(100, 930);
	addChild(scoreLabel);
	timeLabel = Label::createWithTTF("time:100", "fonts/BuxtonSketch.ttf", 40);
	timeLabel->setPosition(320, 930);
	addChild(timeLabel);
	balloonClickSumLabel = Label::createWithTTF("hits:0", "fonts/BuxtonSketch.ttf", 40);
	balloonClickSumLabel->setPosition(540, 930);
	addChild(balloonClickSumLabel);

	//Add the touch event callback function
	EventListenerTouchOneByOne * listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(ClickBalloonLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ClickBalloonLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ClickBalloonLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();
	schedule(schedule_selector(ClickBalloonLayer::updateBalloon), 0.2f);

	schedule(schedule_selector(ClickBalloonLayer::updateTimeLabel), 1.0f);
	
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
			miss++;
			removeBallon(balloon);
		}
		else if (balloon->getPositionX()>640){
			miss++;
			removeBallon(balloon);
		}
		else if (balloon->getPositionY()>900){
			log("remove overarea");
			miss++;
			removeBallon(balloon);
		}
		else if (balloon->getPositionY()<-100){
			miss++;
			removeBallon(balloon);
		}
		
	}
}
void ClickBalloonLayer::updateBalloon(float dt){
	//每0.2秒60%概率产生新的气球
	int rand = random() % 5;
	if (rand < 3){
		addNewBallon();
	}
}

void ClickBalloonLayer::clickCheck(Touch *touch){
	for (auto balloon : ballActors){
		if ((balloon->getPositionX() - balloon->getContentSize().width / 2) < touch->getLocation().x&&touch->getLocation().x < (balloon->getPositionX() + balloon->getContentSize().width / 2))
		{
		
			if ((balloon->getPositionY() - balloon->getContentSize().height / 2)< touch->getLocation().y&&touch->getLocation().y < (balloon->getPositionY() + balloon->getContentSize().height / 2))
			{
				score += balloon->getBallScore();
				char temp[64];		
				sprintf(temp, "%d", score);
				char tmp[64] = "score:";
				strcat(tmp, temp);
				scoreLabel->setString(tmp);
				removeBallon(balloon);
				balloonClickSum++;
				char temp2[64];
				sprintf(temp2, "%d", balloonClickSum);
				char tmp2[64] = "hits:";
				strcat(tmp2, temp2);
				balloonClickSumLabel->setString(tmp2);
				break;
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
		auto balloon = BallActor::createWithType(BallActor::BallActorType::GoalBall);
		//设定气球初速度
		increaseSpeed(balloon);
		//设置ballon初始位置
		int tmp = 640 - balloon->getContentSize().width;
		balloon->setPosition(Point(rand() % tmp + balloon->getContentSize().width / 2, 0));
		balloon->setBallScore(1);
		((GoalBallActor*)balloon)->activateBallMovement();
		addChild(balloon);
		ballActors.pushBack(balloon);
	}
	else if (i == 1){
		auto balloon = BallActor::createWithType(BallActor::BallActorType::GoodBall);
		increaseSpeed(balloon);
		//设置ballon初始位置	
		int tmp = 640 - balloon->getContentSize().width;
		balloon->setPosition(Point(rand() % tmp + balloon->getContentSize().width / 2, 0));
		((GoalBallActor*)balloon)->activateBallMovement();
		addChild(balloon);
		ballActors.pushBack(balloon);
	}
	else {
		auto balloon = BallActor::createWithType(BallActor::BallActorType::BadBall);
		increaseSpeed(balloon);
		//设置ballon初始位置
		int tmp = 640 - balloon->getContentSize().width;
		balloon->setPosition(Point(rand() % tmp + balloon->getContentSize().width / 2, 0));
		((GoalBallActor*)balloon)->activateBallMovement();
		addChild(balloon);
		ballActors.pushBack(balloon);
	}

	
}

void ClickBalloonLayer::updateBalloonMovement(){
	for (auto balloon : ballActors) {
		balloon->setPosition(balloon->getPositionX(), balloon->getPositionY() + balloon->getSpeedY());
	}
}
void ClickBalloonLayer::updateTimeLabel(float dt)
{
	time++;
	speed = speed + 0.2;
	//五次机会
	if (miss <= 5){
		char temp[64];
		sprintf(temp, "%d", 5-miss);
		char tmp[64] = "chance:";
		strcat(tmp, temp);
		timeLabel->setString(tmp);
	}
	else{
		log("Game Over");
		this->unschedule(schedule_selector(ClickBalloonLayer::updateTimeLabel));
		_eventDispatcher->removeAllEventListeners();
		auto director = Director::getInstance();
		auto scene = director->getRunningScene();
		auto layer = GameOverLayer::create();
		//得分数
		Label* finalScoreLabel = Label::createWithTTF("100", "fonts/BuxtonSketch.ttf", 60);
		finalScoreLabel->setPosition(530, 560);
		char temp[64];
		sprintf(temp, "%d", score);
		finalScoreLabel->setString(temp);
		layer->addChild(finalScoreLabel);
		//击中气球数
		Label* balloonNumLabel = Label::createWithTTF("30", "fonts/BuxtonSketch.ttf", 60);
		balloonNumLabel->setPosition(530, 480);
		sprintf(temp, "%d", balloonClickSum);;
		balloonNumLabel->setString(temp);
		layer->addChild(balloonNumLabel);
		//最好战绩
		int bestScore = layer->getBestScore();
		if (score > bestScore){
			bestScore = score;
			layer->setBestScore(bestScore);
		}
		char tempScore[64];
		sprintf(tempScore, "%d", bestScore);
		Label* bestScoreLabel = Label::createWithTTF(tempScore, "fonts/BuxtonSketch.ttf", 60);
		bestScoreLabel->setPosition(530, 400);
		layer->addChild(bestScoreLabel);



		
		//Create the reStart button of the game
		auto reGameBtn = cocos2d::ui::Button::create("MainMenu/regame_btn.png");
		reGameBtn->setScale(0.5);
		reGameBtn->setPosition(Point(200, 300));
		reGameBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
			//Create the scene of MenuScene with a transtionFadeBL effect
			auto replaceScene = TransitionFade::create(2.0, ClickBalloonScene::createScene());

			//Replace the scene with the trasition effect scene
			Director::getInstance()->replaceScene(replaceScene);
			switch (type) {
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				//TODO:Start game hereg
				printf("click here");
				break;
			default:
				break;
			}
		});
		layer->addChild(reGameBtn);

		//Create the start button of the game
		auto exitGameBtn = cocos2d::ui::Button::create("MainMenu/exit_btn.png");
		exitGameBtn->setScale(0.5);
		exitGameBtn->setPosition(Point(400, 300));
		exitGameBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){

			//Create the scene of MenuScene with a transtionFadeBL effect
			auto replaceScene = TransitionFade::create(2.0, MainMenuScene::createScene());

			//Replace the scene with the trasition effect scene
			Director::getInstance()->replaceScene(replaceScene);
			switch (type) {
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
			//TODO:Start game hereg
			printf("click here");

				break;
			default:
				break;
			}
		});
		layer->addChild(exitGameBtn);
		scene->addChild(layer, 200);
		
	}
}
void ClickBalloonLayer::increaseSpeed(BallActor* balloon){
	balloon->setSpeedY(balloon->getSpeedY() + speed);
}