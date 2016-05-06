//
//GameOverLayer.cpp
//
#include "GameOverLayer.h"
bool GameOverLayer::init(){
	Layer::init();
	//_bullet = NULL;

	//Add background picture
	auto background = Sprite::create("gameoverbackground.png");
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(20, 180));
	background->setTag(101);
	addChild(background, 0);
	initBestScore();
	
	return true;
}
void GameOverLayer::initBestScore(){
	FILE *fp = fopen("data.txt", "r+");
	if (!fp)
	{
		bestScore = 0;
		setBestScore(0);
	}
	fscanf(fp, "%d", &bestScore);
	fclose(fp);
}
void GameOverLayer::setBestScore(int score){
	FILE *fp = fopen("data.txt", "w");
	fprintf(fp, "%d", score);
	bestScore = score;
	fclose(fp);
}
int GameOverLayer::getBestScore(){
	return bestScore;
}