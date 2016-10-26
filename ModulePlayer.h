#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2List.h"
#include "p2Point.h"
#include "Box2D/Box2D/Box2D.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	//Create the 3 Levers
	bool CreateLevers();
	void Restart_game();

public:

	//Lever Left
	PhysBody* pivot_left;
	PhysBody* lever_left;
	PhysBody* pivot_force_left;

	//lever Right
	PhysBody* pivot_Right;
	PhysBody* lever_Right;
	PhysBody* pivot_force_Right;

	//Lever UP Left
	PhysBody* lever_UP_left;
	PhysBody* pivot_UP_left;
	PhysBody* pivot_UP_force_left;

	//Textures
	SDL_Texture* lever_left_Tex;
	SDL_Texture* lever_right_Tex;
	SDL_Texture* lever_UP_Tex;

	uint Score;
	uint Lives;
	uint Last_score;
	uint Extra_Balls;
	bool ball_saved = false;

	uint lever_fx;

	bool active_left = false;
	bool active_right = false;

	//
	char title[50];

	//Joints of the Levers
	b2RevoluteJoint* Joint_lever_left = NULL;
	b2RevoluteJoint* Joint_force_left = NULL;
	b2RevoluteJoint* Joint_lever_right = NULL;
	b2RevoluteJoint* Joint_force_right = NULL;
	b2RevoluteJoint* Joint_lever_UP = NULL;
	b2RevoluteJoint* Joint_force_UP = NULL;
};