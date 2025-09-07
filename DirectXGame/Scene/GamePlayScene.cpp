#include "GamePlayScene.h"

using namespace KamataEngine;

GamePlayScene::~GamePlayScene() {
	for (std::vector<Sprite*>& blockLine : blocks_) {
		for (Sprite* block : blockLine) {
			delete block;
		}
	}
}

void GamePlayScene::Initialize() {

	//プレイヤーの初期化
	player_ =std::make_unique<Player>();
	player_->Initialize();
	player_->SetMapChipField(mapChipField_);

	//シーソーの初期化
	seesaw_ = std::make_unique<Seesaw>();
	seesaw_->Initialize();

	mapChipField_ = new MapChipField();
	mapChipField_->LoadMapChipCsv("Resources/CSV/field.csv");
	GenerateBlocks();

	
}

void GamePlayScene::Update() {
	player_->Update();
	seesaw_->Update();

}

void GamePlayScene::Draw() {
	player_->Draw();
	seesaw_->Draw();

	for (std::vector<Sprite*>& blockLine : blocks_)
	{
		for (Sprite* block : blockLine)
		{
			if (block) {
				block->Draw();
			}
		}
	}



}

void GamePlayScene::Debug() { seesaw_->Debug(); }

void GamePlayScene::GenerateBlocks() {
	texture_ = KamataEngine::TextureManager::Load("white64x64.png");
	//要素数
	const uint32_t kNumBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	const uint32_t kNumBlockVirtical = mapChipField_->GetNumBlockVertical();

	//要素数の変更
	blocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		blocks_[i].resize(kNumBlockHorizontal);
	}

	//ブロックの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				blocks_[i][j] = Sprite::Create(texture_, {0, 0});
				blocks_[i][j]->Initialize();
				blocks_[i][j]->SetPosition(mapChipField_->GetMapChipPositionByIndex(j, i));
			}
		}
	}
}
