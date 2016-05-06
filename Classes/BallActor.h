//
//  BallActor.h
//
//  Created by wh 16-4-21.
//
//

#include "cocos2d.h"
#ifndef BallActor_h
#define BallActor_h

USING_NS_CC;

class BallActor : public cocos2d::Sprite
{
public:

	enum class BallActorType
	{
		GoalBall,
		BadBall,
		GoodBall,
	};

	/** Speed property of the balls */
	CC_SYNTHESIZE(float, speedX, SpeedX);
	CC_SYNTHESIZE(float, speedY, SpeedY);
	//CC_SYNTHESIZE(int, balloonScore);
	BallActorType ballType;

	/** Create the ball by their types */
	static BallActor* createWithType(BallActorType ballType);

	/** Play the death animation */
	virtual Animate* playDeathAnimation();

	/** Update the ball movement */
	void updateBallMovement(float dt);

	/** Activate the fish movement */
	void activateBallMovement();

protected:
	CC_SYNTHESIZE(int, ballScore, BallScore);
};

class GoalBallActor : public BallActor{

public:

	bool init();

	CREATE_FUNC(GoalBallActor);
	Animate* playDeathAnimation();
	void activateBallMovement();
};

class BadBallActor : public BallActor{

public:

	bool init();

	CREATE_FUNC(BadBallActor);
	Animate* playDeathAnimation();
	void activateBallMovement();
};

class GoodBallActor : public BallActor{

public:

	bool init();

	CREATE_FUNC(GoodBallActor);
	Animate* playDeathAnimation();
	void activateBallMovement();
};


#endif
