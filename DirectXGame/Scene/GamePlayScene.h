#pragma once  
#include<KamataEngine.h>
#include"../GameObject/Player/Player.h"
#include"../GameObject/Seesaw/Seesaw.h"
#include"../GameObject/Ground/MapChipField.h"

#include<vector>

class GamePlayScene {
public:
	~GamePlayScene();
	void Initialize();
	void Update();
	void Draw();

	void Debug();

private:
	std::unique_ptr<Player> player_ = nullptr;
	std::unique_ptr<Seesaw> seesaw_ = nullptr;
	MapChipField* mapChipField_;


	uint32_t texture_ = 0;
	std::vector<std::vector<KamataEngine::Sprite*>> blocks_;

	void GenerateBlocks();
};