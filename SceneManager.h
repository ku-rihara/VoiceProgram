#pragma once
#include<Novice.h>
//class
#include"BaseScene.h"
//#include"SceneTitle.h"
//#include"ScenePlay.h"
//#include"SceneClear.h"

class SceneManager{
private:
	//包含
	static BaseScene* currentScene_;
public:
	enum  SCENE {
		PROTOTYPE,
		PLAY,
		CLEAR,
	};
	int scene_;
	//関数-----------------------------------------------
	SceneManager();
	static void CangeScene(int& scene);
	static void Init();
	static void Update();
	static void Draw();

};

