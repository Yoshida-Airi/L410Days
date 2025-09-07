#pragma once
#include<KamataEngine.h>


/// <summary>
/// プレイヤーの設定値
/// </summary>
struct Status 
{
	KamataEngine::Vector3 pos = {64, 100, 0};      // 初期化位置
	KamataEngine::Vector2 velocity = {}; // 移動速度
	int power = 1;           // 力と重さの値
};

class Player
{
public:
	~Player();
	void Initialize();
	void Update();
	void Draw();

private: 

	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::WorldTransform* worldTransform_;
	uint32_t textureHandle_ = 0;
	Status state_;

	bool onGround_ = true;

	static inline const float kJumpAcceleration = 20.0f;
	static inline const float kGravityAcceleration = 0.98f;
	static inline const float kLimitFallSpeed = 15.0f;
	
};
