#include "../../StdAfx.h"
#include "Item.hpp"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool Item::Initialize()
{
	// TODO: Add your initialization logic here

	// @brief マテリアルの設定
	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	material.Ambient = Color(0.5f, 0.5f, 0.5f);
	material.Specular = Color(1.0f, 1.0f, 1.0f);
	material.Power = 0.0f;

	// @brief モデルの読み込みと初期化
	block = GraphicsDevice.CreateModelFromFile(_T("block/block.x"));
	block->SetMaterial(material);
	block->SetPosition(Vector3(0, 0, 0));
	block->SetScale(0.0254f);

	metal = GraphicsDevice.CreateModelFromFile(_T("metal/metal.x"));
	metal->SetMaterial(material);
	metal->SetPosition(Vector3(0, 0, 0));
	metal->SetScale(0.0254f);

	SimpleShape shape;

	// @brief 当たり判定モデルの初期化
	block_obb = block->GetOBB();
	block_obb.Radius.x *= 0.33333f;

	shape.Type = Shape_Box;
	shape.Width = block_obb.Radius.x * 2.0f;
	shape.Height = block_obb.Radius.y * 2.0f;
	shape.Depth = block_obb.Radius.z * 4.0f;
	block_hitbox = GraphicsDevice.CreateModelFromSimpleShape(shape);
	block_hitbox->SetMaterial(material);

	metal_obb = metal->GetOBB();
	metal_obb.Radius.x *= 0.33333f;

	shape.Type = Shape_Box;
	shape.Width = block_obb.Radius.x * 2.0f;
	shape.Height = block_obb.Radius.y * 2.0f;
	shape.Depth = block_obb.Radius.z * 4.0f;
	metal_hitbox = GraphicsDevice.CreateModelFromSimpleShape(shape);
	metal_hitbox->SetMaterial(material);

	// @brief ブロックとアイテム切り替え用のフラグの初期化
	block_state = true;
	metal_state = false;

	return true;
}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int Item::Update()
{
    // TODO: Add your update logic here


	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void Item::Draw()
{
	// @brief ブロックと素材の描画
	if (block_state == true)
	{
		block->Draw();
	}
	if (metal_state == true)
	{
		metal->Draw();
	}
}
bool Item::SetState()
{
	
	block_state = false;
	metal_state = true;

	return block_state;
}
