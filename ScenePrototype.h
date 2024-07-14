#pragma once
#include "BaseScene.h"
#include "SoundWave.h"

class ScenePrototype:public BaseScene{
private:
	SoundWave* soundWave_;
public:
	ScenePrototype();//コンストラクタ
	//Function
	void Init()override;
	void Update()override;
	void Draw()override;
};

