#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Box2D/Box2D/Box2D.h"

/*class revolute_joint
{
public:
	b2MouseJoint mousejoint;
	b2RevoluteJointDef rev_joint;
	b2Vec2 mouse_vec;
	PhysBody* pivot;
	PhysBody* box;
};*/

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	//revolute_joint lever;
};