//
//  BallActor.cpp
//
//  Created by wh 16-4-21.
//
//

#include "BallActor.h"

BallActor* BallActor::createWithType(BallActorType ballType){

	BallActor* ball;

	//Create the fishes by the fish type
	switch (ballType) {
	case BallActorType::GoalBall:

		ball = GoalBallActor::create();
		break;
	case BallActorType::BadBall:

		ball = BadBallActor::create();
		break;
	case BallActorType::GoodBall:

		ball = GoodBallActor::create();
		break;

	default:
		break;
	}

	return ball;
}

Animate* BallActor::playDeathAnimation()
{
	return  NULL;
}

void BallActor::updateBallMovement(float delta){

	/*auto direction = rand() % 3 - 1.0f;
	auto shiftX = (rand() % 5 + 1)*direction;
	auto shiftY = (rand() % 5 + 1)*direction;

	setSpeedX(shiftX == 0 ? 1 : shiftX);
	setSpeedY(shiftY == 0 ? 1 : shiftY);
	auto rotation = -atan2(shiftY, shiftX);
	setRotation(rotation*180.0f / 3.14f + 180.0f);*/
	int x = getPositionX();
	int y = getPositionY();

	setPositionY(y + getSpeedY());
}

bool GoalBallActor::init(){

	BallActor::init();

	setSpeedX(1.0f);
	setSpeedY(2.0f);

	
	ballType = BallActorType::GoalBall;
	setBallScore(1);
	////Read the swimming animations textures
	//auto balls = Vector<SpriteFrame*>();
	//balls.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("balloon/balloon1.png"));
	//balls.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("balloon/balloon2.png"));
	//balls.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("balloon/balloon4.png"));
	//
	////Create swimming animation
	//auto ballAnimation = Animation::createWithSpriteFrames(balls, 0.1);
	//auto ballAnimate = Animate::create(ballAnimation);

	////Run the swiming action forever
	//runAction(RepeatForever::create(ballAnimate));
	setTexture("balloon/red.png");


	return true;
}

void GoalBallActor::activateBallMovement(){

	schedule(schedule_selector(BallActor::updateBallMovement), 0.02f);
}

Animate* GoalBallActor::playDeathAnimation(){

	////Read the death anmtions textures
	//auto deathFrames = Vector<SpriteFrame*>();
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_death_001.png"));
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_death_002.png"));
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_death_003.png"));
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_death_004.png"));
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_death_005.png"));

	////Create the death anmation
	//auto deathAnimation = Animation::createWithSpriteFrames(deathFrames, 0.1);
	//auto deathAnimate = Animate::create(deathAnimation);

	//return deathAnimate;
	return NULL;
}

bool BadBallActor::init(){

	BallActor::init();

	setSpeedX(1.5f);
	setSpeedY(3.0f);


	ballType = BallActorType::BadBall;
	setBallScore(2);
	////Read the swimming animations textures
	//auto balls = Vector<SpriteFrame*>();
	//balls.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("ballon2.png"));

	////Create swimming animation
	//auto ballAnimation = Animation::createWithSpriteFrames(balls, 0.1);
	//auto ballAnimate = Animate::create(ballAnimation);

	////Run the swiming action forever
	//runAction(RepeatForever::create(ballAnimate));
	setTexture("balloon/yellow.png");
	return true;
}

void BadBallActor::activateBallMovement(){

	schedule(schedule_selector(BallActor::updateBallMovement), 0.1f);
}


Animate* BadBallActor::playDeathAnimation(){

	auto deathFrames = Vector<SpriteFrame*>();

	////Read the death anmtions textures
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_death_001.png"));
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_death_002.png"));
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_death_003.png"));
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_death_004.png"));
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_death_005.png"));

	////Create the death anmation
	//auto deathAnimation = Animation::createWithSpriteFrames(deathFrames, 0.1);
	//auto deathAnimate = Animate::create(deathAnimation);

	//return deathAnimate;
	return NULL;
}

bool GoodBallActor::init(){

	BallActor::init();

	setSpeedX(2.0f);
	setSpeedY(5.0f);

	ballType = BallActorType::GoodBall;

	setBallScore(3);

	//Read the swimming animations textures
	//auto balls = Vector<SpriteFrame*>();
	//balls.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("ballon3.png"));

	////Create swimming animation
	//auto ballAnimation = Animation::createWithSpriteFrames(balls, 0.1);
	//auto ballAnimate = Animate::create(ballAnimation);

	////Run the swiming action forever
	//runAction(RepeatForever::create(ballAnimate));
	setTexture("balloon/blue.png");
	return true;
}

void GoodBallActor::activateBallMovement(){

	schedule(schedule_selector(BallActor::updateBallMovement), 0.1f);
}

Animate* GoodBallActor::playDeathAnimation(){

	////Read the death anmtions textures
	//auto deathFrames = Vector<SpriteFrame*>();
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_death_001.png"));
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_death_002.png"));
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_death_003.png"));
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_death_004.png"));
	//deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_death_005.png"));

	////Create the death anmation
	//auto deathAnimation = Animation::createWithSpriteFrames(deathFrames, 0.1);
	//auto deathAnimate = Animate::create(deathAnimation);

	//return deathAnimate;
	return NULL;
}
