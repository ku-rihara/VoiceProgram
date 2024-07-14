//#define _USE_MATH_DEFINES
//#include"math.h"
//
////Function
//#include"Matrix3x3.h"
////#include"Map.h"
////class
//#include "BaseObj.h"
//
//
//BaseObj::BaseObj() {
//	Init();
//};
//
//BaseObj::~BaseObj() {
//
//}
//
//void BaseObj::Init() {
//	//頂点とマトリックス
//	screenVertex_ = {};
//	matrix_ = {};
//	wvpVpMatrix_ = {};
//	acceleration_ = {};
//	theta_ = 0;
//}
//
////レンダリングパイプライン
//void BaseObj::RenderingPipeline() {
//
//	//camera_->MakeCamelaMatrix();
//	matrix_ = MakeAffineMatrix(scale_, theta_, worldPos_);
//	wvpVpMatrix_ = wvpVpMatrix(matrix_, camera_->GetViewMatrix(), camera_->GetOrthoMatrix(), camera_->GetViewportMatrix());
//	screenVertex_ = Transform(localVertex_, wvpVpMatrix_);
//}
//
////ミニカメラのレンダリングパイプライン
//void BaseObj::MiniRenderingPipeline() {
//	//miniCamera_->MakeCamelaMatrix();
//	MiniMatrix_ = MakeAffineMatrix(scale_, theta_, worldPos_);
//	MiniwvpVpMatrix_ = wvpVpMatrix(MiniMatrix_, miniCamera_->GetViewMatrix(), miniCamera_->GetOrthoMatrix(), miniCamera_->GetViewportMatrix());
//	MiniScreenVertex_ = Transform(miniLocalVertex_, MiniwvpVpMatrix_);
//}
//
//void BaseObj::DrawRangeCut(Vector2 scrollpos, float viewportWidth, float viewportHeight) {
//	Vector2 scrollPos = scrollpos;
//
//	// ビューポート内にあるかどうかの判定
//	bool withinX = (worldPos_.x + size_.x / 2 >= scrollPos.x) && (worldPos_.x - size_.x / 2 <= scrollPos.x + viewportWidth);
//	bool withinY = (worldPos_.y + size_.y / 2 >= scrollPos.y) && (worldPos_.y - size_.y / 2 <= scrollPos.y + viewportHeight);
//
//	if (withinX && withinY) {
//		// 左端がはみ出ている場合の調整
//		drawStart_ = {};
//		drawEnd_ = size_ - drawStart_;
//
//		float localLeft = size_.x;
//		if (worldPos_.x - size_.x / 2 < scrollPos.x) {
//			localLeft = (size_.x / 2 + (-scrollPos.x + (worldPos_.x - size_.x / 2))) * 2;
//			drawStart_.x = (size_.x) - (size_.x - (scrollPos.x - (worldPos_.x - size_.x / 2)));
//			drawEnd_.x = size_.x - drawStart_.x;
//		}
//
//		// 右端がはみ出ている場合の調整
//		float localRight = size_.x;
//		if (worldPos_.x + size_.x / 2 > scrollPos.x + viewportWidth) {
//			localRight = (size_.x / 2 - ((worldPos_.x + size_.x / 2) - (scrollPos.x + viewportWidth))) * 2;
//			drawStart_.x = 0;
//			drawEnd_.x = (size_.x - ((worldPos_.x + size_.x / 2) - (scrollPos.x + viewportWidth)));
//		}
//
//		// 上端がはみ出ている場合の調整
//		float localTop = size_.y;
//		if (worldPos_.y - size_.y / 2 < scrollPos.y) {
//			localTop = (size_.y / 2 + (-scrollPos.y + (worldPos_.y - size_.y / 2))) * 2;
//			drawStart_.y = (size_.y) - (size_.y - (scrollPos.y - (worldPos_.y - size_.y / 2)));
//			drawEnd_.y = size_.y - drawStart_.y;
//		}
//
//		// 下端がはみ出ている場合の調整
//		float localBottom = size_.y;
//		if (worldPos_.y + size_.y / 2 > scrollPos.y + viewportHeight) {
//			localBottom = (size_.y / 2 - ((worldPos_.y + size_.y / 2) - (scrollPos.y + viewportHeight))) * 2;
//			drawStart_.y = 0;
//			drawEnd_.y = (size_.y - ((worldPos_.y + size_.y / 2) - (scrollPos.y + viewportHeight)));
//		}
//		miniLocalVertex_ = { Vector2(localLeft, localTop),	Vector2(localRight, localTop),
//						     Vector2(localLeft, localBottom),Vector2(localRight, localBottom),
//		};
//	}
//}
//
//void BaseObj::BackGroundDrawRangeCut(Vector2 centerPos, float viewportWidth, float viewportHeight) {
//	drawStart_.x = 0;
//	drawStart_.y = 0;
//	drawEnd_.x = size_.x - drawStart_.x;
//	drawEnd_.y = size_.y - drawStart_.y;
//
//	float localLeft = size_.x;
//
//	if (miniCamera_->GetZoomLevel().x < 1.0f) {
//		localLeft = (size_.x / 2 + ((centerPos.x - size_.x / 2))) * 2;
//		drawStart_.x = (size_.x) - (size_.x - (-(centerPos.x - size_.x / 2)));
//		drawEnd_.x = size_.x - drawStart_.x * 2;
//	}
//
//	// 右端がはみ出ている場合の調整
//	float localRight = size_.x;
//	if (centerPos.x + size_.x / 2 > viewportWidth) {
//		localRight = (size_.x / 2 - ((centerPos.x + size_.x / 2) - (viewportWidth))) * 2;
//	}
//
//	// 上端がはみ出ている場合の調整
//	float localTop = size_.y;
//	if (miniCamera_->GetZoomLevel().y < 1.0f) {
//		localTop = (size_.y / 2 + ((centerPos.y - size_.y / 2))) * 2;
//		drawStart_.y = (size_.y) - (size_.y - (-(centerPos.y - size_.y / 2)));
//		drawEnd_.y = size_.y - drawStart_.y * 2;
//	}
//
//	// 下端がはみ出ている場合の調整
//	float localBottom = size_.y;
//	if (centerPos.y + size_.y / 2 > viewportHeight) {
//		localBottom = (size_.y / 2 - ((centerPos.y + size_.y / 2) - viewportHeight)) * 2;
//	}
//	miniLocalVertex_ = { Vector2(localLeft, localTop),
//							Vector2(localRight, localTop),
//							 Vector2(localLeft, localBottom),
//							 Vector2(localRight, localBottom),
//	};
//}
//
//void BaseObj::MapChipColligion() {
//	/*maxPos_.x = MAX(worldPos_.x, oldWorldPos_.x);
//	maxPos_.y = MAX(worldPos_.y, oldWorldPos_.y);
//
//	fitMapsizePos_.intx = int(maxPos_.x / (mapchip_->GetMapchipSize() / 2));
//	fitMapsizePos_.intx = int(fitMapsizePos_.intx * (mapchip_->GetMapchipSize() / 2));
//
//	fitMapsizePos_.inty = int(maxPos_.y / (mapchip_->GetMapchipSize() / 2));
//	fitMapsizePos_.inty = int(fitMapsizePos_.inty * (mapchip_->GetMapchipSize() / 2));*/
//
//	//マップ間の隙間を埋める
//	fitMapsizePos_ = fitMapSize(worldPos_, oldWorldPos_, mapchip_->GetMapchipSize());
//
//	//マップ番号の計算
//	mapNum_.LeftTop = LeftTopMapNum(worldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
//	mapNum_.RightTop = RightTopMapNum(worldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
//	mapNum_.LeftBottom = LeftBottomMapNum(worldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
//	mapNum_.RightBottom = RightBottomMapNum(worldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
//	centerMapNum_.x = worldPos_.x / mapchip_->GetMapchipSize();
//	centerMapNum_.y = worldPos_.y / mapchip_->GetMapchipSize();
//
//	//オールド座標のマップ番号
//	oldMapNum_.LeftTop = LeftTopMapNum(oldWorldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
//	oldMapNum_.RightTop = RightTopMapNum(oldWorldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
//	oldMapNum_.LeftBottom = LeftBottomMapNum(oldWorldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
//	oldMapNum_.RightBottom = RightBottomMapNum(oldWorldPos_, 1, size_.y, size_.x, mapchip_->GetMapchipSize());
//
//	//自機の４頂点のどれかが当たっている時
//	if (mapchip_->map[int(mapNum_.RightTop.y)][int(mapNum_.RightTop.x)] == BLOCK || mapchip_->map[int(mapNum_.RightBottom.y)][int(mapNum_.RightBottom.x)] == BLOCK ||
//		mapchip_->map[int(mapNum_.LeftTop.y)][int(mapNum_.LeftTop.x)] == BLOCK || mapchip_->map[int(mapNum_.LeftBottom.y)][int(mapNum_.LeftBottom.x)] == BLOCK) {
//
//		//Y方向
//		if (mapchip_->map[int(oldMapNum_.RightTop.y)][int(mapNum_.RightTop.x)] != BLOCK && mapchip_->map[int(oldMapNum_.RightBottom.y)][int(mapNum_.RightBottom.x)] != BLOCK &&
//			mapchip_->map[int(oldMapNum_.LeftTop.y)][int(mapNum_.LeftTop.x)] != BLOCK && mapchip_->map[int(oldMapNum_.LeftBottom.y)][int(mapNum_.LeftBottom.x)] != BLOCK) {
//
//			//縦の斜め移動時にマップとの隙間を埋める
//			worldPos_.y = float(fitMapsizePos_.inty);
//
//			//仮に埋まってしまったらプレイヤーの半径分戻す
//			if (mapchip_->map[int(centerMapNum_.y)][int(centerMapNum_.x)] == BLOCK) {
//				worldPos_.y -= size_.y / 2;
//			}
//
//
//			//地面についていたら浮いている状態のフラグを降ろす
//			if (mapchip_->map[int(mapNum_.LeftBottom.y)][int(mapNum_.LeftBottom.x)] == BLOCK || mapchip_->map[int(mapNum_.RightBottom.y)][int(mapNum_.RightBottom.x)] == BLOCK) {
//
//				isFlight_ = false;
//
//			}
//			else {
//				isFlight_ = true;
//				/*landing_.easingRock = false;*/
//			}
//
//			//上にぶつかったら加速度と速度を0にする
//			if (mapchip_->map[int(mapNum_.LeftTop.y)][int(mapNum_.LeftTop.x)] == BLOCK || mapchip_->map[int(mapNum_.RightTop.y)][int(mapNum_.RightTop.x)] == BLOCK) {
//				velocity_.y = 0;
//			}
//		}
//
//		//X方向
//		else if (mapchip_->map[int(mapNum_.RightTop.y)][int(oldMapNum_.RightTop.x)] != BLOCK && mapchip_->map[int(mapNum_.RightBottom.y)][int(oldMapNum_.RightBottom.x)] != BLOCK &&
//			mapchip_->map[int(mapNum_.LeftTop.y)][int(oldMapNum_.LeftTop.x)] != BLOCK && mapchip_->map[int(mapNum_.LeftBottom.y)][int(oldMapNum_.LeftBottom.x)] != BLOCK) {
//
//			//横の斜め移動時にマップとの隙間を埋める
//			worldPos_.x = float(fitMapsizePos_.intx);
//		}
//
//		else {
//			worldPos_.x = float(fitMapsizePos_.intx);
//			worldPos_.y = float(fitMapsizePos_.inty);
//
//			//仮に埋まってしまったらプレイヤーの半径分戻す
//			if (mapchip_->map[int(centerMapNum_.y)][int(centerMapNum_.x)] == BLOCK) {
//				worldPos_.y -= size_.y / 2;
//			}
//
//			//地面についていたら浮いている状態のフラグを降ろす
//			if (mapchip_->map[int(mapNum_.LeftBottom.y)][int(mapNum_.LeftBottom.x)] == BLOCK || mapchip_->map[int(mapNum_.RightBottom.y)][int(mapNum_.RightBottom.x)] == BLOCK) {
//
//				isFlight_ = false;
//				/*if (landing_.isEasing == false && landing_.easingRock == false) {
//					landing_.isEasing = true;
//					landing_.easingPlus = 1;
//				}*/
//			}
//
//			else {
//				isFlight_ = true;
//				/*landing_.easingRock = false;*/
//			}
//
//			//上にぶつかったら加速度と速度を0にする
//			if (mapchip_->map[int(mapNum_.LeftTop.y)][int(mapNum_.LeftTop.x)] == BLOCK || mapchip_->map[int(mapNum_.RightTop.y)][int(mapNum_.RightTop.x)] == BLOCK) {
//				velocity_.y = 0;
//			}
//		}
//	}
//	else {
//		isFlight_ = true;
//		/*landing_.easingRock = false;*/
//	}
//}
