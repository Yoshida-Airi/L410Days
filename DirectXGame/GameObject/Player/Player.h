#pragma once
#include<KamataEngine.h>
using namespace KamataEngine;

class Player
{
public:
	void Initialize();
	void Update();
	void Draw();

private: 

	int power = 1;	//力と重さの値
	Vector2 pos = {64, 600};	//初期化位置
	Sprite* sprite_ = nullptr;
	uint32_t textureHandle_ = 0;

	
};
