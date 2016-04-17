//
//  FishingScene.cpp
//  FishJoyMini
//
//  Created by Ken on 14-3-11.
//
//

#include "FishingScene.h"


Scene* FishingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = FishingLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}