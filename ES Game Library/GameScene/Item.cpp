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
	
	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	material.Ambient = Color(0.5f, 0.5f, 0.5f);
	material.Specular = Color(1.0f, 1.0f, 1.0f);
	material.Power = 0.0f;

	block = GraphicsDevice.CreateModelFromFile(_T("block/block.x"));
	block->SetMaterial(material);
	block->SetPosition(Vector3(0, 0, 0));
	block->SetScale(0.0254f);

	metal = GraphicsDevice.CreateModelFromFile(_T("metal/metal.x"));
	metal->SetMaterial(material);
	metal->SetPosition(block->GetPosition());
	metal->SetScale(0.0254f);


	SimpleShape shape;

	// @brief ブロックの当たり判定用の箱
	block_obb = block->GetOBB();
	block_obb.Radius.x *= 0.33333f;

	shape.Type = Shape_Box;
	shape.Width = block_obb.Radius.z * 2.0f;
	shape.Height = block_obb.Radius.y * 2.0f;
	shape.Depth = block_obb.Radius.x * 6.0f;
	block_hitbox = GraphicsDevice.CreateModelFromSimpleShape(shape);
	block_hitbox->SetMaterial(material);

	// @brief 素材の当たり判定用の箱
	metal_obb = metal->GetOBB();
	metal_obb.Radius.x *= 0.33333f;

	shape.Type = Shape_Box;
	shape.Width = metal_obb.Radius.z * 2.0f;
	shape.Height = metal_obb.Radius.y * 2.0f;
	shape.Depth = metal_obb.Radius.x * 6.0f;
	metal_hitbox = GraphicsDevice.CreateModelFromSimpleShape(shape);
	metal_hitbox->SetMaterial(material);


	// @brief アイテム用の変数
	block_state_ = true;
	metal_state_ = false;

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
	if (block_state_ == true)
	{
		block->Draw();
	}
	if (metal_state_ == true)
	{
		metal->Draw();
	}


	if (block_state_ == true)
	{
		block_hitbox->SetPosition(block_obb.Center);
		block_hitbox->SetDirection(block->GetDirectionQuaternion());
		//block_hitbox->DrawAlpha(0.5f);
	}

	// @brief 素材の当たり判定の描画
	if (metal_state_ == true)
	{
		metal_hitbox->SetPosition(metal_obb.Center);
		metal_hitbox->SetDirection(metal->GetDirectionQuaternion());
		//metal_hitbox->DrawAlpha(0.5f);
	}

}
void Item::SetState(bool block_state, bool& metal_state)
{
	block_state_ = block_state;
	metal_state_ = metal_state;
}

void Item::gorira()
{
}

OrientedBoundingBox Item::GetOBB()
{
	if (block_state_)
		return block->GetOBB();

	return metal->GetOBB();
}