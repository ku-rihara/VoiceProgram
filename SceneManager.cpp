#include "SceneManager.h"
//Sceneclass
#include"ScenePrototype.h"

BaseScene* SceneManager::currentScene_ = NULL;

//グローバル変数----------------
bool BaseScene::isChange_;
bool BaseScene::isIncrement_;
bool BaseScene::isDecrement_;
//グローバル変数----------------

SceneManager::SceneManager() {
	BaseScene::SetIsChange(true);
	BaseScene::SetIsIncrement(true);
	scene_ = -1;//初期は-1から増やして0にする
}

void SceneManager::CangeScene(int& scene) {

	//シーン切り替え処理
	if (BaseScene::GetIsChange()) {

		if (BaseScene::GetIsIncrement()) {
			scene++;
		}
		else if (BaseScene::GetIsDecrement()) {
			scene--;
		}

		if (scene > CLEAR) {
			scene = PROTOTYPE;
		}
		if (currentScene_ != NULL) {
			delete currentScene_;
		}


		switch (scene) {

		case PROTOTYPE:

		/*	currentScene_ = new SceneTitle();*/
			currentScene_ = new ScenePrototype();
			Init();
			break;

		case PLAY:

			/*currentScene_ = new ScenePlay();*/

			break;

		case CLEAR:
			/*currentScene_ = new SceneClear();*/
			break;

		}
		BaseScene::SetIsChange(false);
		BaseScene::SetIsIncrement(false);
		BaseScene::SetIsDecrement(false);
	}
}

void SceneManager::Init() {
	//各シーンの初期化
	currentScene_->Init();
}

void SceneManager::Update() {
	//各シーンの更新
	currentScene_->Update();
}

void SceneManager::Draw() {
	//各シーンの描画
	currentScene_->Draw();

}