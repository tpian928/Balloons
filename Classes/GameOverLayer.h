//
//  GameOverLayer.h
//

#ifndef Ballon_GameOverLayer_h
#define Ballon_GameOverLayer_h
#include "cocos2d.h"
#include "BallActor.h"
#include <cstdlib>
#include "MainMenuLayer.h"

#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class GameOverLayer : public Layer{

public:

	bool init();
	
	int getBestScore();
	
	void setBestScore(int score);
	CREATE_FUNC(GameOverLayer);
	
protected:
	int bestScore;
	void initBestScore();
};

#endif
