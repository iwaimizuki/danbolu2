#pragma once


#include "../../ESGLib.h"

class Item{
public:
	

	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

	bool SetState();

private:
	// 変数宣言

	// @brief　モデル
	MODEL block;
	MODEL metal;

	// @brief 当たり判定用の箱
	MODEL block_hitbox;
	MODEL metal_hitbox;

	// @brief ブロックとアイテム切り替え用のフラグ
	bool block_state;
	bool metal_state;

	// @brief 当たり判定用の箱
	OrientedBoundingBox block_obb;
	OrientedBoundingBox metal_obb;


	// 関数プロトタイプ

};
