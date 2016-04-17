//
//  MainMenuScene.cpp
//  FishJoyMini
//
//  Created by Ken on 14-3-6.
//
//

#include "MainMenuScene.h"
#include "MainMenuLayer.h"


Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
