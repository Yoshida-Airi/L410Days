#pragma once  
#include"../GameObject/Player/Player.h"
#include"../GameObject/Seesaw/Seesaw.h"

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
};