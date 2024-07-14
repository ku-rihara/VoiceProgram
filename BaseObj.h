//#pragma once
//#include<Novice.h>
//#include"Vector2C.h"
////class
//#include"Camera.h"
//#include"MiniCamera.h"
//#include"mapchip.h"
//
//class BaseObj{
//protected:
//	////包含
//	MiniCamera* miniCamera_;
//	Camera* camera_;
//	Mapchip* mapchip_;
//
//	//座標
//	Vector2 worldPos_;
//	Vector2 oldWorldPos_;
//	Vector2i fitMapsizePos_;
//
//	//Mapnum
//	Vector2 centerMapNum_;
//	Vertex mapNum_;
//	Vertex oldMapNum_;
//	bool isFlight_;
//
//	//Parameter
//	Vector2 velocity_;
//	Vector2 acceleration_;
//	Vector2 scale_;
//	Vector2 size_;
//	Vector2 radius_;
//	float theta_;
//
//	//頂点とマトリックス
//	Vertex screenVertex_;
//	Vertex localVertex_;
//	Matrix3x3 matrix_;
//	Matrix3x3 wvpVpMatrix_;
//
//	Vertex MiniScreenVertex_;
//	Vertex miniLocalVertex_;
//	Matrix3x3 MiniMatrix_;
//	Matrix3x3 MiniwvpVpMatrix_;
//	Vector2 drawStart_;
//	Vector2 drawEnd_;
//public:
//	BaseObj();//コンストラクタ
//	~BaseObj();//デストラクタ
//
//	virtual void Init();
//	virtual void RenderingPipeline();
//	virtual void MiniRenderingPipeline();
//	virtual void MapChipColligion();
//	virtual void DrawRangeCut(Vector2 scrollpos, float viewportWidth, float viewportHeight);
//	virtual void BackGroundDrawRangeCut(Vector2 centerPos,float viewportWidth, float viewportHeight);
//	
//	Vector2 GetWorldPos()const { return worldPos_; }
//	Vertex GetScreenVertex()const { return screenVertex_; }
//	Vector2 GetSize()const { return size_; }
//	Vector2 GetRadius()const { return radius_; }
//	//スクリーンの中心座標
//	Vector2 GetScreenCenter()const { return Vector2(screenVertex_.LeftTop.x + size_.x / 2, screenVertex_.LeftTop.y + size_.y / 2); }
//	Vector2 GetMiniScreenCenter()const { return Vector2(MiniScreenVertex_.LeftTop.x + size_.x / 2, MiniScreenVertex_.LeftTop.y + size_.y / 2); }
//
//	void SetCamera(Camera* camera) { camera_ = camera; }
//	void SetMiniCamera(MiniCamera* mcamera) { miniCamera_ = mcamera; }
//	void SetMapChip(Mapchip* mapchip) { mapchip_ = mapchip; }
//	void SetWorldPos(Vector2 pos) { this->worldPos_ = pos; }
//	void SetWorldPosX(float pos) { this->worldPos_.x = pos; }
//	void SetWorldPosY(float pos) { this->worldPos_.y = pos; }
//	void SetScaleX(float pos) { this->scale_.x = pos; }
//	void SetScaleY(float pos) { this->scale_.y = pos; }
//};
//
