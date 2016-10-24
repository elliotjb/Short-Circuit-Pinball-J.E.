#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

// Small class to return to other modules to track position and rotation of physics bodies
enum type { GREEN_LED, RED_LED, B_R_LED, B_C_LED, B_L_LED, L_TRIANGLE, R_TRIANGLE, ORANGE, DIANA, GAME_OVER, LEVER, TURBINE, RED_PANEL, BLUE_BUTTON };

class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
	type type;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius, bool isdyn);
	PhysBody* CreateRectangle(int x, int y, int width, int height, bool isdyn, type type);
	PhysBody* CreatePolygon(int x, int y, int* points, int size, float res, bool isdyn, type type, bool is_sensor);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, type type);
	PhysBody* CreateChain(int x, int y, int* points, int size, float res, bool isdyn);
	
	void CreateRevolutionJoint();
	
	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

private:

	bool debug;
	b2World* world;
	b2MouseJoint* mouse_joint;
	b2Body* ground;
	b2Fixture* temp = NULL;

};