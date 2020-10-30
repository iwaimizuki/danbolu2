#pragma once


#include "../ESGLib.h"

class Item{
public:
	Item() {};
	~Item() {};

	bool Initialize();
	int  Update();
	void Draw();

	MODEL GatBlock() { return block; }

	void SetState(bool block_state, bool& metal_state);
	void gorira();
	OrientedBoundingBox GetOBB();

private:
	// •Ï”éŒ¾
	bool block_state_;
	bool metal_state_;

	MODEL block;
	MODEL metal;

	MODEL block_hitbox;
	MODEL metal_hitbox;



};
