#define NOMINMAX
#include "Player.h"
#include "../Ground/MapChipField.h"
#include <algorithm>

using namespace KamataEngine;

Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

Player::~Player() {
	delete sprite_;
	delete worldTransform_;
}

void Player::Initialize() {
	textureHandle_ = TextureManager::Load("player_walk.png");
	worldTransform_ = new WorldTransform();
	worldTransform_->Initialize();
	worldTransform_->translation_ = state_.pos;
	sprite_ = Sprite::Create(textureHandle_, {worldTransform_->translation_.x, worldTransform_->translation_.y});
	sprite_->SetAnchorPoint({0.5f, 0.5f});
	sprite_->SetTextureRect({0.0f, 0.0f}, {64.0f, 64.0f});
	sprite_->SetSize({64.0f, 64.0f});
}

void Player::Update() {
	Vector2 position = sprite_->GetPosition();

	if (onGround_) {
		// 移動
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			state_.velocity.x = 2.0f;
			sprite_->SetIsFlipX(false);
			UpdateAnimation();
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			state_.velocity.x = -2.0f;
			sprite_->SetIsFlipX(true);
			UpdateAnimation();
		} else {
			state_.velocity.x = 0.0f;
			sprite_->SetTextureRect({0.0f, 0.0f}, {64.0f, 64.0f});
		}
		// ジャンプ
		if (Input::GetInstance()->TriggerKey(DIK_UP)) {
			state_.velocity.y = kJumpAcceleration;
		}
	} else { // 空中
		state_.velocity.y -= kGravityAcceleration;
		state_.velocity.y = std::max(state_.velocity.y, -kLimitFallSpeed);
	}

	// 衝突情報を初期化
	CollisionMapInfo collisionMapInfo;
	collisionMapInfo.move = {state_.velocity.x, state_.velocity.y, 0};
	CheckMapCollision(collisionMapInfo);

	worldTransform_->translation_ = Add(worldTransform_->translation_, collisionMapInfo.move);

	if (collisionMapInfo.ceiling) {
		state_.velocity.y = 0;
	}

	bool landing = false;

	// 地面との当たり判定
	if (state_.velocity.y < 0) {
		if (worldTransform_->translation_.y <= 100.0f) {
			landing = true;
		}
	}

	if (onGround_) {
		if (worldTransform_->translation_.y > 100.0f) {
			onGround_ = false;
		}
	} else {
		// 着地
		if (landing) {
			worldTransform_->translation_.y = 100.0f;
			state_.velocity.y = 0.0f;
			onGround_ = true;
		}
	}
	worldTransform_->translation_.x += state_.velocity.x;
	worldTransform_->translation_.y += state_.velocity.y;

	float screenY = 720.0f - worldTransform_->translation_.y;
	sprite_->SetPosition({worldTransform_->translation_.x, screenY});
}

void Player::Draw() { sprite_->Draw(); }

void Player::CheckMapCollision(CollisionMapInfo& info) { CheckMapCollisionUp(info); };

void Player::CheckMapCollisionUp(CollisionMapInfo& info) {

	if (info.move.y <= 0) {
		return;
	}

	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(Add(worldTransform_->translation_, info.move), static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	// 真上の当たり判定を行う
	bool hit = false;

	// 左上点の判定
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition({positionsNew[kLeftTop].x, positionsNew[kLeftTop].y});
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}

	// 右上点の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition({positionsNew[kRightTop].x, positionsNew[kRightTop].y});
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}

	// ブロックにヒット？
	if (hit) {
		// 現在座標が壁の外か判定
		MapChipField::IndexSet indexSetNow;
		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition({worldTransform_->translation_.x + Vector2(0, +kHeight / 2.0f).x, worldTransform_->translation_.y + Vector2(0, +kHeight / 2.0f).y});
		if (hit) {
			// めり込みを排除する方向に移動量を設定する
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(
			    {worldTransform_->translation_.x + info.move.x + Vector2(0, +kHeight / 2.0f).x, worldTransform_->translation_.y + info.move.y + Vector2(0, +kHeight / 2.0f).y});
			MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
			float moveY = (worldTransform_->translation_.y) - (kHeight / 2.0f) - kBlank_;
			info.move.y = std::max(0.0f, moveY);
			info.ceiling = true;
		}
	}
}

void Player::UpdateAnimation() {
	// 経過時間を加算
	animationTimer_ += 0.01f;

	// 設定した時間（frame_duration）が経過したら、次のフレームへ
	if (animationTimer_ >= frameDuration_) {
		// 次のフレームにインデックスを移動
		currentFrame_++;

		// 最後のフレームに達したら最初に戻す（ループ）
		if (currentFrame_ >= frameCount_) {
			currentFrame_ = 0;
		}

		// スプライトシートの表示位置を更新
		// ここでは、1フレームのサイズが64x64pxで、横に4枚並んでいると仮定しています
		sprite_->SetTextureRect({64.0f * currentFrame_, 0.0f}, {64.0f, 64.0f});

		// タイマーをリセット
		animationTimer_ = 0.0f;
	}


}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {

	Vector3 offsetTable[] = {
	    {+kWidth / 2.0f, -kHeight / 2.0f, 0}, //  kRightBottom
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0}, //  kLeftBottom
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0}, //  kRightTop
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0}  //  kLeftTop
	};

	return Add(center, offsetTable[static_cast<uint32_t>(corner)]);
}