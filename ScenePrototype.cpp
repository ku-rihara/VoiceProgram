#include "ScenePrototype.h"


ScenePrototype::ScenePrototype() {
	
	soundWave_ = new SoundWave();
}

void ScenePrototype::Init() {
	soundWave_->Init();
}

void ScenePrototype::Update() {
	soundWave_->Update();
	
}

void ScenePrototype::Draw() {
	soundWave_->Draw();
	

}