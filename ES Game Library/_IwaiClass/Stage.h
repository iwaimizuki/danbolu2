#pragma once

#include "../ESGLib.h"

class Stage {
public:
    void Initialize();
    void Draw();
	Vector3 map_position;
private:
	Material material;
	MODEL block;//壊れない
	MODEL pillar;//壊れる
	MODEL map;//床
	const float scale = 0.0254f;
	int xz[15][19];//ファイルの読み込み
	char comma;//カンマ読み込み
};