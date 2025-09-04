#include "GamePlayScene.h"

GamePlayScene::~GamePlayScene() {}

void GamePlayScene::Initialize() {

	//プレイヤーの初期化
	player_ =std::make_unique<Player>();
	player_->Initialize();

	//シーソーの初期化
	seesaw_ = std::make_unique<Seesaw>();
	seesaw_->Initialize();
}

void GamePlayScene::Update() {
	player_->Update();
	seesaw_->Update();
}

void GamePlayScene::Draw() {
	player_->Draw();
	seesaw_->Draw();
}

void GamePlayScene::Debug() { seesaw_->Debug(); }
