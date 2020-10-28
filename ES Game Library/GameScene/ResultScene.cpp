#include "../StdAfx.h"
#include "ResultScene.hpp"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool ResultScene::Initialize()
{
	// TODO: Add your initialization logic here
	Result = GraphicsDevice.CreateSpriteFromFile(_T("ResultSprite/Result.png"));
	Font = GraphicsDevice.CreateSpriteFont(_T("ContinueAL"), 100);
	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void ResultScene::Finalize()
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
int ResultScene::Update()
{
    // TODO: Add your update logic here


	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void ResultScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();

	SpriteBatch.Draw(*Result, Vector3(0, 0, 0));
	/**
* @brief èüÇ¡ÇΩÉvÉåÉCÉÑÅ[ñº
*/
	SpriteBatch.DrawString(Font, Vector2(350, 0), Color(0, 0, 0), _T("%d"), Winplayer);
	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
