#include "Player.h"

void Player::Initialize() {
	textureHandle_ = TextureManager::Load("white64x64.png");
	sprite_ = Sprite::Create(textureHandle_, {pos});
}

void Player::Update() {
	Vector2 position = sprite_->GetPosition();

	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		position.x += 1.0f;
	} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		position.x -= 1.0f;
	}

	sprite_->SetPosition(position);
}

void Player::Draw() { sprite_->Draw(); }
