#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Box2D/Box2D/Box2D.h"



class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	//Lever Left
	PhysBody* pivot_left;
	PhysBody* lever_left;
	PhysBody* pivot_force_left;
	//lever Right
	PhysBody* pivot_Right;
	PhysBody* lever_Right;
	PhysBody* pivot_force_Right;

};