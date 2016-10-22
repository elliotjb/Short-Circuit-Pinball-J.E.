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

public:

	//Lever Left
	PhysBody* pivot_left;
	PhysBody* lever_left;
	PhysBody* pivot_force_left;

	//lever Right
	PhysBody* pivot_Right;
	PhysBody* lever_Right;
	PhysBody* pivot_force_Right;

	SDL_Texture* lever_left_Tex;
	SDL_Texture* lever_right_Tex;

	uint lever_fx;
	bool active_left = false;
	bool active_right = false;


};