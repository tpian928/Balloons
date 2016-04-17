//
//  FishingLayer.cpp
//  FishJoyMini
//
//  Created by Ken on 14-3-11.
//
//

#include "FishingLayer.h"

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


bool FishingLayer::init(){
	
	Layer::init();
	_bullet=NULL;
	
	//Add background picture
	auto background = Sprite::create("CocoStudioRes/background.jpg");
	background->setAnchorPoint(Point(0,0));
	background->setPosition(Point(0,0));
	background->setTag(101);
	addChild(background,0);
	
	//Read the texture to sprite frame cache
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CocoStudioRes/cannon-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameScene/Item-chaojiwuqi-iphone-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CocoStudioRes/UI_GameMenuLayer-hd.plist");
	
    
    createBasicUI();
    
	//Get the instance of cannon
	cannon = Sprite::createWithSpriteFrameName("actor_cannon1_72.png");
    cannon->setPosition(480, 50);
    addChild(cannon,CANNON_LAYER_ORDER);
    
	//Add the touch event callback function
    EventListenerTouchOneByOne * listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(FishingLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(FishingLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(FishingLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
	
	//Activate update
	scheduleUpdate();
	
	//Init the fishes
	fishActorsInital();
	
	//Update the fishes one time
	updateFishMovement();
	
	//Preload background effect
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_COIN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_FIRE);
	
	return true;
}

void FishingLayer::createBasicUI()
{
    //create UI
    Sprite *boardBottom = Sprite::createWithSpriteFrameName("ui_box_02.png");
    boardBottom->setPosition(480, 41);
    addChild(boardBottom,UI_LAYER_ORDER);
    
    Sprite *boardTop = Sprite::createWithSpriteFrameName("ui_box_01.png");
    boardTop->setPosition(480, 578);
    addChild(boardTop,UI_LAYER_ORDER);
    
    //Get the instantce of ui_box_01_01 and make it rotate forever
    Sprite * wheelSpr = Sprite::createWithSpriteFrameName("ui_box_01_01.png");
    addChild(wheelSpr,UI_LAYER_ORDER);
    wheelSpr->setPosition(Point(480, 578));
    wheelSpr->runAction(RepeatForever::create((RotateBy::create(3, 360, 360))));
    
    //Get the instance of label of score
    scoreLabel = Label::createWithTTF("00000","fonts/Marker Felt.ttf", 24);
    scoreLabel->setPosition(242, 28);
    addChild(scoreLabel,UI_LAYER_ORDER);
    score = 0;
}


bool FishingLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    CCLOG("BEGAN:(%f,%f)",touch->getLocation().x,touch->getLocation().y);
    // can't touch the ui
    if(touch->getLocation().y < 80)
        return false;
    return true;
}
void FishingLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    setCannonRotation(touch->getLocation());
    CCLOG("MOVED:(%f,%f)",touch->getLocation().x,touch->getLocation().y);
}

void FishingLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    setCannonRotation(touch->getLocation());
    
    //Shoot the bullet
    bulletShoot(touch->getLocation());
    
    CCLOG("END:(%f,%f)",touch->getLocation().x,touch->getLocation().y);
    
}


void FishingLayer::bulletShoot(Point endPosition){
	
	if(_bullet==NULL){
		
		//Init the bullet
		auto bullet = Sprite::createWithSpriteFrameName("weapon_bullet_007.png");
		 
		//Set the offest of the raotation
        Vec2 cannonPos = cannon->getPosition();
        float angle = CC_DEGREES_TO_RADIANS(cannon->getRotation());
        Vec2 offset = 50 * Vec2(sinf(angle), cosf(angle));
        
        Vec2 bulletPos = cannonPos+ offset;
				
		//Set the anchorpoint, rotation, position of the bullet
		_bullet = bullet;
		_bullet->setAnchorPoint(Point(0.5, 0));
		_bullet->setRotation(cannon->getRotation());
		_bullet->setPosition(bulletPos);
		
		//Shoot the bullet and release after the action ended
		_bullet->runAction(Sequence::create(MoveTo::create(0.6, endPosition),
											CallFunc::create(CC_CALLBACK_0(FishingLayer::bulletRelease,this)),
											NULL));
		addChild(_bullet,BULLET_LAYRE_ORDER);
		
		//Play bullet shoot music effect
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_FIRE);
	}
}


void FishingLayer::bulletRelease(){

	//Release the bullet, and set the _bullet to NULL
	if(_bullet!=NULL){
		_bullet->removeFromParent();
		_bullet = NULL;
	}
}



void FishingLayer::setCannonRotation(Vec2 targetPos){
	
	//Calulatethe rotation of cannon
	auto radian = atan2(targetPos.y-cannon->getPosition().y ,targetPos.x-cannon->getPosition().x);
	auto angle= CC_RADIANS_TO_DEGREES(radian);
	auto rotation= -(angle)+90;
	
	//Set the rotation range
    cannon->setRotation(rotation);
	
}

void FishingLayer::update(float delta){
	
	//Update the movement of fishes by their speed, limit the move area of the fishes
	for(auto fish:fishActors){
				
		if(fish->getPositionX()>1000){
			
			fish->setPosition(Point(-40,rand()% 480));
		}
        else if (fish->getPositionX()<-100){
			
			fish->setPosition(1000,rand()%480);
		}
        else if (fish->getPositionY()>700){
            
			fish->setPosition(rand()%960,700);
		}
        else if (fish->getPositionY()<-100){
	
			fish->setPosition(rand()%960,-40);
		}
        else{

			fish->setPosition(fish->getPositionX()+fish->getSpeedX(), fish->getPositionY()+fish->getSpeedY());
		}
	}
	
	//Check the collide
	collideCheck();
}

void FishingLayer::collideCheck(){
	
	//Check the collide when the bullet is exist
	if(_bullet!=NULL){

		auto it_self = fishActors.begin();
		
		while (it_self!= fishActors.end()) {

            FishActor * fish = dynamic_cast<FishActor*>(*it_self);
			//If the bullet collide the fish
			if (_bullet->getBoundingBox().intersectsRect(fish->getBoundingBox())) {
				
				//Release the bullet
				_bullet->removeFromParent();
				_bullet=NULL;
				
				//Set the score
				score+=fish->getFishScore();
				char temp[64];
				sprintf(temp, "%d",score);
				scoreLabel->setString(temp);
				
				//Tag the collided fish
				fish->setTag(200);
				
				//Play the fish death's animations and release them
                fish->runAction(Sequence::create(fish->playDeathAnimation(),
                                                 CallFunc::create(std::bind(&FishingLayer::removeFishes,this,fish)),
                                                 NULL));
                
				
				
				//Move the fish from the fishes vector
				it_self=fishActors.erase(it_self);
				
				break;
			}else{
				
				++it_self;
			}
		}
	}
}

void FishingLayer::removeFishes(Node* sender){
	
	//Get the collided fish
    FishActor *fishActor = (FishActor*)sender;
		
	//Remove the collided fish
	fishActor->setVisible(false);
	fishActor->removeAllChildrenWithCleanup(true);
	fishActor->removeFromParent();
	
	//Play music effect when catch a fish
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_COIN);
}

void FishingLayer::fishActorsInital(){
	
	//Get the windows size
	auto winSize = Director::getInstance()->getWinSize();
	
	//Init fishes
	for (int fishIndex=0; fishIndex<8; fishIndex++) {
		
		//Create fishes
		auto smallFishActor = FishActor::createWithType(FishActor::FishActorType::SmallFish);
		auto angelFishActor = FishActor::createWithType(FishActor::FishActorType::AngelFish);
		auto croakerFishActor = FishActor::createWithType(FishActor::FishActorType::Croaker);
		auto amphiprionFishActor = FishActor::createWithType(FishActor::FishActorType::Bream);
		auto breamFishActor = FishActor::createWithType(FishActor::FishActorType::SmallFish);
		
		//Set ths fishes position
		smallFishActor->setPosition(Point(rand()%910,rand()%590));
		angelFishActor->setPosition(Point(rand()%910,rand()%590));
		croakerFishActor->setPosition(Point(rand()%910,rand()%590));
		amphiprionFishActor->setPosition(Point(rand()%910,rand()%590));
		breamFishActor->setPosition(Point(rand()%910,rand()%430));
		
		((SmallFishActor*)smallFishActor)->activateFishMovement();
		((AngelFishActor*)angelFishActor)->activateFishMovement();
		((CroakerActor*)croakerFishActor)->activateFishMovement();
		((AmphiprionActor*)amphiprionFishActor)->activateFishMovement();
		((BreamActor*)breamFishActor)->activateFishMovement();
		
		//Add the fishes into the layer
		addChild(smallFishActor,FISH_LAYER_ORDER);
		addChild(angelFishActor,FISH_LAYER_ORDER);
		addChild(croakerFishActor,FISH_LAYER_ORDER);
		addChild(amphiprionFishActor,FISH_LAYER_ORDER);
		addChild(breamFishActor,FISH_LAYER_ORDER);
		
		//Add the fishes into the fish vector
		fishActors.pushBack(smallFishActor);
		fishActors.pushBack(angelFishActor);
		fishActors.pushBack(croakerFishActor);
		fishActors.pushBack(amphiprionFishActor);
		fishActors.pushBack(breamFishActor);
	}
}

void FishingLayer::updateFishMovement(){
	
	//Change the direction and speed of the fishes
	for (auto fish:fishActors) {
		
		auto direction = rand()%3-1.0f;
		auto shiftX = (rand()%3+1)*direction;
		auto shiftY = (rand()%3+1)*direction;
				
		fish->setSpeedX(shiftX==0?1:shiftX);
		fish->setSpeedY(shiftY==0?1:shiftY);
		auto rotation = -atan2(shiftY, shiftX);
		fish->setRotation(rotation*180.0f/3.14f+180.0f);
	}
}