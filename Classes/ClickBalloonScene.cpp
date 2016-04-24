//
//  FishingScene.cpp
//  FishJoyMini
//
//  Created by Ken on 14-3-11.
//
//

#include "ClickBalloonScene.h"


Scene* ClickBalloonScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ClickBalloonLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}