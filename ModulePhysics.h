#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -11.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

enum type {
	GREEN_LED, RED_LED_1, RED_LED_2, RED_LED_3, RED_LED_4, B_R_LED, B_C_LED, B_L_LED,
	L_TRIANGLE, R_TRIANGLE, ORANGE, DIANA, GAME_OVER, LEVER, TURBINE, RED_PANEL_1, RED_PANEL_2,
	RED_PANEL_3, RED_PANEL_4, BLUE_BUTTON, LEFT_PASS, LEFT_NOT_PASS, RIGHT_PASS, RIGHT_NOT_PASS,
	ENTRANCE, NOT_ENTRANCE, BLACK_BOX, NO_EFFECT };

enum _entityCategory{
	FLOOR_1 = 0x0001,
	FLOOR_2 = 0x0002,
	BALL_1	= 0x0004,
	BALL_2	= 0x0008	
};

// Small class to return to other modules to track position and rotation of physics bodies
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

	PhysBody* CreateCircle(int x, int y, int radius, bool isdyn, uint16 categoryBits, uint16 maskBits);
	PhysBody* CreateRectangle(int x, int y, int width, int height, bool isdyn, type type, uint16 categoryBits, uint16 maskBits);
	PhysBody* CreatePolygon(int x, int y, int* points, int size, float res, bool isdyn, type type, bool is_sensor, uint16 categoryBits, uint16 maskBits);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, type type);
	PhysBody* CreateChain(int x, int y, int* points, int size, float res, bool isdyn, uint16 categoryBits, uint16 maskBits);
	
	void CreateRevolutionJoint();
	b2RevoluteJoint* CreateRevolutionJoint_test(b2RevoluteJoint* joint, PhysBody* bodyA, PhysBody* bodyB, bool CollideCon, int posA_x, int posA_y, int posB_x, int posB_y, bool limit, int lowe_angle, int upper_angle);
	
	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

private:

	bool debug;
	b2World* world;
	b2MouseJoint* mouse_joint;
	b2Body* ground;
	b2Fixture* temp = NULL;

};