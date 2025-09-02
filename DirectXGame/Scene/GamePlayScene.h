#pragma once  
#include"../GameObject/Player/Player.h"

class GamePlayScene {
public:
	~GamePlayScene();
	void Initialize();
	void Update();
	void Draw();

private:
	Player* player_ = nullptr;
};