#include "GamePlayScene.h"

GamePlayScene::~GamePlayScene() {}

void GamePlayScene::Initialize() 
{
	
	player_ = new Player();
	player_->Initialize();

}

void GamePlayScene::Update() 
{ player_->Update(); }

void GamePlayScene::Draw() { player_->Draw(); }
