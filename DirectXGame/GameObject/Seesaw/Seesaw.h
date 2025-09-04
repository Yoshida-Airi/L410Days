#pragma once
#include<KamataEngine.h>

class Seesaw
{
public:
	~Seesaw();
	void Initialize();
	void Update();
	void Draw();

	void Debug();

private:
	std::unique_ptr<KamataEngine::Sprite> leftBlock_ = nullptr;
	std::unique_ptr<KamataEngine::Sprite> rightBlock_ = nullptr;
	uint32_t seesawTexture_ = 0;

	int32_t leftWeight_ = 1;
	int32_t rightWeight_ = 0;

	//初期位置の保存
	float leftInitialY_ = 0.0f;
	float rightInitialY_ = 0.0f;

	// シーソーの動きの最大振幅を定義
	const float kMaxAmplitude_ = 50.0f;
	float deltaY_ = 2.0f;	//変化量

};
