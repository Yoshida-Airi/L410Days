#define NOMINMAX
#include "Player.h"
#include<algorithm>

using namespace KamataEngine;

Player::~Player() {
	delete sprite_;
	delete worldTransform_;
}

void Player::Initialize() {
	textureHandle_ = TextureManager::Load("white64x64.png");
	worldTransform_ = new WorldTransform();
	worldTransform_->Initialize();
	worldTransform_->translation_ = state_.pos;
	sprite_ = Sprite::Create(textureHandle_, {worldTransform_->translation_.x, worldTransform_->translation_.y});
}

void Player::Update() {
	Vector2 position = sprite_->GetPosition();

	if (onGround_) {
		// 移動
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			state_.velocity.x = 2.0f;
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			state_.velocity.x = -2.0f;
		}
		else
		{
			state_.velocity.x = 0.0f;
		}
		// ジャンプ
		if (Input::GetInstance()->TriggerKey(DIK_UP)) {
			state_.velocity.y = kJumpAcceleration;
		}
	} else { // 空中
		state_.velocity.y -= kGravityAcceleration;
		state_.velocity.y = std::max(state_.velocity.y, -kLimitFallSpeed);
	}

	bool landing = false;

	//地面との当たり判定
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
