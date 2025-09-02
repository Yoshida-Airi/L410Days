#include "Player.h"

Player::~Player() { delete sprite_; }

void Player::Initialize() {
	textureHandle_ = TextureManager::Load("white64x64.png");
	sprite_ = Sprite::Create(textureHandle_, {status.pos});
}

void Player::Update() {
	Vector2 position = sprite_->GetPosition();

	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		position.x += status.speed;
	} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		position.x -= status.speed;
	}

	sprite_->SetPosition(position);
}

void Player::Draw() { sprite_->Draw(); }
