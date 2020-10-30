#pragma once


#include "ESGLib.h"
#include "GameScene/GameScene.hpp"
#include "_MyClass/Item/Item.hpp"

class GameMain : public CGameScene {
public:
	GameMain() : DefaultFont(GraphicsDevice.CreateDefaultFont())
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~GameMain()
	{
#ifdef _INC_SQUIRREL
		Squirrel.ReleaseAllScripts();
#endif
#ifdef _INC_NUI
		NUI.ReleaseAllKinects();
#endif
#ifdef _INC_LIVE2D
		Live2D.ReleaseAllModels();
#endif
#ifdef _INC_EFFEKSEER
		Effekseer.ReleaseAllEffects();
#endif
#ifdef _INC_DIRECT2D
		Direct2D.ReleaseAllResources();
#endif
		MediaManager.ReleaseAllMedia();

		SoundDevice.ReleaseAllMusics();
		SoundDevice.ReleaseAllSounds();

		GraphicsDevice.ReleaseAllRenderTargets();
		GraphicsDevice.ReleaseAllStateBlocks();
		GraphicsDevice.ReleaseAllFonts();
		GraphicsDevice.ReleaseAllSprites();
		GraphicsDevice.ReleaseAllAnimationModels();
		GraphicsDevice.ReleaseAllModels();
		GraphicsDevice.ReleaseAllVertexBuffers();
		GraphicsDevice.ReleaseAllEffects();

		Finalize();
	}

public:
	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();


private:
	void Finalize();
	FONT DefaultFont;

private:
	// �ϐ��錾

	Item* item_class;

	// @brief�@���f��
	MODEL block;
	MODEL metal;
	MODEL player;

	// @brief�@�J����
	CAMERA camera;

	// @brief �����蔻��p�̃��f��
	MODEL player_hitbox;
	MODEL block_hitbox;
	MODEL metal_hitbox;
	
	// @brief �����蔻��p�̔�
	OrientedBoundingBox player_obb;
	OrientedBoundingBox block_obb;
	OrientedBoundingBox metal_obb;

	// @brief �����蔻��p�̃t���O
	bool hit_state;

	// @brief �u���b�N�ƃA�C�e���؂�ւ��p�̃t���O
	bool block_state;
	bool metal_state;

	// �֐��錾

};
