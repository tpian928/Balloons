//
//  ClickBalloonScene.cpp
//

#include "ClickBalloonScene.h"


Scene* ClickBalloonScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ClickBalloonLayer::create();
	// add layer as a child to scene
	scene->addChild(layer,100);
	// return the scene
	return scene;
}