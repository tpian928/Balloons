//
//  MainMenuLayer.cpp
//  
#include "MainMenuLayer.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define BG_MUSIC        "Audio/music_1.ogg"
#else
#define BG_MUSIC        "Audio/music_1.mp3"
#endif // CC_PLATFOR_ANDROID

bool MainMenuLayer::init(){
	

	//Get the windows size
	auto winSize = Director::getInstance()->getWinSize();
	
	//Set the background picture
	auto ui_background = Sprite::create("MainMenu/ui_background_normal-hd.png");
	ui_background->setAnchorPoint(Point(0.0f,0.0f));
	ui_background->setPosition(Point(0.0f,0.0f));
	addChild(ui_background,0.0f);
    
	//Create the start button of the game
    auto startGameBtn = cocos2d::ui::Button::create("MainMenu/play_btn.png");
    startGameBtn->setScale(0.5);
	startGameBtn->setPosition(Point(winSize.width/2,100));
    startGameBtn->addTouchEventListener([&](Ref* sender,cocos2d::ui::Widget::TouchEventType type){

		//Create the scene of BalloonScene with a transtionFadeBL effect
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
	addChild(startGameBtn,1.0f);

	return true;

}
