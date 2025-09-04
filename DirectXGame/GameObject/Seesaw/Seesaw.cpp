#include "Seesaw.h"
#include<algorithm>

using namespace KamataEngine;

Seesaw::~Seesaw() {}

void Seesaw::Initialize() {
	seesawTexture_ = TextureManager::Load("white64x64.png");
	leftBlock_ = std::unique_ptr<Sprite>(Sprite::Create(seesawTexture_, {10, 10}));
	rightBlock_ = std::unique_ptr<Sprite>(Sprite::Create(seesawTexture_, {120, 10}));

	//ブロックの初期位置の保存
	leftInitialY_ = leftBlock_->GetPosition().y;
	rightInitialY_ = rightBlock_->GetPosition().y;
}

void Seesaw::Update() {

	//現在位置の取得
	Vector2 leftPosition = leftBlock_->GetPosition();
	Vector2 rightPosition = rightBlock_->GetPosition();

	if (leftWeight_ > rightWeight_) {
		// 左が重いとき
		leftPosition.y += deltaY_;
		rightPosition.y -= deltaY_;
	} else if (rightWeight_ > leftWeight_) {
		// 右が重いとき
		leftPosition.y -= deltaY_;
		rightPosition.y += deltaY_;
	} else {
		// 釣り合っているとき
		if (leftPosition.y > leftInitialY_) {
			leftPosition.y -= deltaY_;
		} else if (leftPosition.y < leftInitialY_) {
			leftPosition.y += deltaY_;
		}
		if (rightPosition.y > rightInitialY_) {
			rightPosition.y -= deltaY_;
		} else if (rightPosition.y < rightInitialY_) {
			rightPosition.y += deltaY_;
		}
	}

	// 初期位置を基準として、Y座標に限度を適用
	leftPosition.y = std::clamp(leftPosition.y, leftInitialY_ - kMaxAmplitude_, leftInitialY_ + kMaxAmplitude_);
	rightPosition.y = std::clamp(rightPosition.y, rightInitialY_ - kMaxAmplitude_, rightInitialY_ + kMaxAmplitude_);

	// 更新された座標をセット
	leftBlock_->SetPosition(leftPosition);
	rightBlock_->SetPosition(rightPosition);
}

void Seesaw::Draw() {
	leftBlock_->Draw();
	rightBlock_->Draw();
}

void Seesaw::Debug() 
{
#ifdef _DEBUG
	ImGui::Begin("Seesaw Controls");
	ImGui::InputInt("Left Weight", &leftWeight_);
	ImGui::InputInt("Right Weight", &rightWeight_);
	ImGui::End();
#endif
}
