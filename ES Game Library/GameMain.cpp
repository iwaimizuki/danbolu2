// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("ES Game Library"));


	// @brief ライトの初期化
	Light light;
	light.Type = Light_Directional;
	light.Direction = Vector3(0, 1, 1);
	light.Diffuse = Color(1.0f, 1.0f, 1.0f);
	light.Ambient = Color(1.0f, 1.0f, 1.0f);
	light.Specular = Color(1.0f, 1.0f, 1.0f);
	GraphicsDevice.SetLight(light);

	// @brief カメラの初期化
	camera->SetView(Vector3(0, 5, -20), Vector3(0, 0, 0));
	camera->SetPerspectiveFieldOfView(45.0f, 16.0f / 9.0f, 1.0f, 10000.0f);
	GraphicsDevice.SetCamera(camera);

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

	player = GraphicsDevice.CreateModelFromFile(_T("human_03.x"));
	player->SetMaterial(material);
	player->SetPosition(Vector3(8, 0, 0));
	player->SetScale(0.0254f);


	SimpleShape shape;

	// @brief プレイヤーの当たり判定用の箱
	player_obb   = player->GetOBB();
	player_obb.Radius.x *= 0.33333f;

	shape.Type   = Shape_Box;
	shape.Width  = player_obb.Radius.x * 2.0f;
	shape.Height = player_obb.Radius.y * 2.0f;
	shape.Depth  = player_obb.Radius.z * 2.0f;
	player_hitbox = GraphicsDevice.CreateModelFromSimpleShape(shape);
	player_hitbox->SetMaterial(material);

	block_obb = block->GetOBB();
	block_obb.Radius.x *= 0.33333f;

	shape.Type = Shape_Box;
	shape.Width = block_obb.Radius.x * 6.0f;
	shape.Height = block_obb.Radius.y * 2.0f;
	shape.Depth = block_obb.Radius.z * 2.0f;
	block_hitbox = GraphicsDevice.CreateModelFromSimpleShape(shape);
	block_hitbox->SetMaterial(material);

	metal_obb = metal->GetOBB();
	metal_obb.Radius.x *= 0.33333f;

	shape.Type = Shape_Box;
	shape.Width = block_obb.Radius.x * 6.0f;
	shape.Height = block_obb.Radius.y * 2.0f;
	shape.Depth = block_obb.Radius.z * 2.0f;
	metal_hitbox = GraphicsDevice.CreateModelFromSimpleShape(shape);
	metal_hitbox->SetMaterial(material);

	
	// @brief 当たり判定確認用のフラグ
	hit_state = false;

	// @brief ブロックとアイテム切り替え用のフラグの初期化
	block_state = true;
	metal_state = false;

	// @brief アイテムクラスの読み込み
	item_class = new Item;
	item_class->Initialize();

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void GameMain::Finalize()
{
	// TODO: Add your finalization logic here
}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int GameMain::Update()
{
	// TODO: Add your update logic here

	KeyboardState key = Keyboard->GetState();

	// @brief プレイヤーの移動
	if (key.IsKeyDown(Keys_Right))
	{
		player->Move(1, 0, 0);
	}
	if (key.IsKeyDown(Keys_Left))
	{
		player->Move(-1, 0, 0);
	}

	if (key.IsKeyDown(Keys_Up))
	{
		player->Move(0, 0, 1);
	}
	if (key.IsKeyDown(Keys_Down))
	{
		player->Move(0, 0, -1);
	}

	// @brief プレイヤー・ブロック・素材の当たり判定の座標補正
	player_obb.Center = player->GetPosition();
	player_obb.Center.y = player_obb.Radius.y;
	player_obb.SetAxis(player->GetDirectionQuaternion());

	block_obb.Center = block->GetPosition();
	block_obb.Center = block->GetPosition();
	block_obb.SetAxis(block->GetDirectionQuaternion());

	metal_obb.Center = metal->GetPosition();
	metal_obb.Center = metal->GetPosition();
	metal_obb.SetAxis(metal->GetDirectionQuaternion());

	// @brief プレイヤーとブロック・素材の当たり判定の処理
	if (player_obb.Intersects(block_obb))
	{
		hit_state = true;

		// @brief アイテムクラスの読み込み
		item_class->SetState();
	}
	else
	{
		hit_state = false;
	}


	// @brief アイテムクラスの読み込み
	item_class->Update();
	

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here

	// @brief 当たり判定確認背景
	if (hit_state == true)
	{
		GraphicsDevice.Clear(Color_Red);
	}
	else
	{
		GraphicsDevice.Clear(Color_CornflowerBlue);
	}

	GraphicsDevice.BeginScene();
	
	// @brief カメラのセット
	GraphicsDevice.SetCamera(camera);

	// @brief プレイヤーの描画
	player->Draw();

	// @brief アイテムクラスの読み込み
	item_class->Draw();

	GraphicsDevice.BeginAlphaBlend();

	// @brief プレイヤーの当たり判定の描画
	player_hitbox->SetPosition(player_obb.Center);
	player_hitbox->SetDirection(player->GetDirectionQuaternion());
	player_hitbox->DrawAlpha(0.5f);

	// @brief ブロックと素材の当たり判定の描画
	if (block_state == true)
	{
		block_hitbox->SetPosition(block_obb.Center);
		block_hitbox->SetDirection(block->GetDirectionQuaternion());
		block_hitbox->DrawAlpha(0.5f);
	}

	if (metal_state == true)
	{
		metal_hitbox->SetPosition(metal_obb.Center);
		metal_hitbox->SetDirection(metal->GetDirectionQuaternion());
		metal_hitbox->DrawAlpha(0.5f);
	}

	GraphicsDevice.EndAlphaBlend();

	SpriteBatch.Begin();

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
