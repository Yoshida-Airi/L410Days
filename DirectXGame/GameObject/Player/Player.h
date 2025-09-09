#pragma once
#include<KamataEngine.h>

class MapChipField;

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

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	enum Corner { kRightBottom, kLeftBottom, kRightTop, kLeftTop, kNumCorner };

private: 

	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::WorldTransform* worldTransform_;
	MapChipField* mapChipField_ = nullptr;
	
	uint32_t textureHandle_ = 0;
	Status state_;

	//マップとの当たり判定情報
	struct CollisionMapInfo {
		bool ceiling = false;
		bool landing = false;
		bool hitWall = false;
		KamataEngine::Vector3 move;
	};

	bool onGround_ = true;

	static inline const float kJumpAcceleration = 20.0f;
	static inline const float kGravityAcceleration = 0.98f;
	static inline const float kLimitFallSpeed = 15.0f;
	
	//キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	float kBlank_ = 0.5f;

	// アニメーションを管理する変数
	float animationTimer_ = 0.0f;
	int currentFrame_= 0;
	const int frameCount_ = 4;         // アニメーションの総フレーム数
	const float frameDuration_ = 0.1f; // 1フレームあたりの表示時間（秒）

private:

	//マップ衝突判定
	void CheckMapCollision(CollisionMapInfo& info);

	void CheckMapCollisionUp(CollisionMapInfo& info);
	/*void CheckMapCollisionDown(CollisionMapInfo& info);
	void CheckMapCollisionRight(CollisionMapInfo& info);
	void CheckMapCollisionLeft(CollisionMapInfo& info);*/

	void UpdateAnimation();

	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);
};
