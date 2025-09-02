#pragma once
#include<KamataEngine.h>
using namespace KamataEngine;

/// <summary>
/// プレイヤーの設定値
/// </summary>
struct Status 
{
	Vector2 pos = {64, 600}; // 初期化位置
	float speed = 2.0f;		 // 移動速度
	int power = 1;           // 力と重さの値
};

class Player
{
public:
	void Initialize();
	void Update();
	void Draw();

private: 

	Sprite* sprite_ = nullptr;
	uint32_t textureHandle_ = 0;
	Status* status;
	
};
