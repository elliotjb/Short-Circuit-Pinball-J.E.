#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/Map_Pinball.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);
	CreateMap();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		/*ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();*/
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 8));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		if (circles.getFirst() != NULL)
		{
			circles.getFirst()->data->body->ApplyForceToCenter(b2Vec2(0.0f, -220.0f), true);
		}

	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}


bool ModuleSceneIntro::CreateMap()
{
	int rick_head[88] = {
		216, 660,
		41, 558,
		90, 369,
		136, 370,
		161, 357,
		130, 257,
		122, 248,
		125, 232,
		130, 221,
		144, 219,
		152, 223,
		164, 250,
		170, 249,
		147, 179,
		177, 65,
		187, 51,
		204, 41,
		222, 33,
		240, 29,
		256, 27,
		403, 26,
		419, 28,
		434, 32,
		445, 35,
		459, 40,
		470, 47,
		478, 54,
		486, 64,
		490, 73,
		650, 657,
		655, 672,
		650, 686,
		635, 686,
		628, 678,
		594, 565,
		582, 552,
		511, 255,
		502, 253,
		497, 264,
		464, 354,
		492, 370,
		530, 371,
		577, 554,
		394, 660
	};

	int PartUP_right[40] = {
		455, 252,
		482, 192,
		459, 78,
		443, 59,
		424, 50,
		408, 47,
		378, 46,
		377, 65,
		397, 69,
		398, 122,
		438, 181,
		447, 181,
		437, 113,
		435, 96,
		439, 85,
		449, 85,
		455, 89,
		462, 108,
		480, 190,
		453, 251
	};

	int PartUP_center[14] = {
		352, 49,
		352, 60,
		351, 67,
		344, 67,
		344, 56,
		345, 46,
		350, 46
	};

	int PartUP_center_2[16] = {
		319, 48,
		320, 54,
		319, 60,
		316, 64,
		312, 60,
		312, 50,
		313, 47,
		316, 45
	};
	int PartUp_Left[42] = {
		288, 46,
		287, 63,
		256, 72,
		246, 77,
		240, 136,
		230, 134,
		236, 69,
		209, 68,
		206, 133,
		200, 136,
		198, 147,
		193, 148,
		190, 141,
		203, 78,
		207, 62,
		215, 52,
		230, 45,
		242, 42,
		261, 41,
		276, 40,
		287, 41
	};

	int Part_Center_1[74] = {
		363, 195,
		366, 206,
		367, 251,
		356, 254,
		356, 208,
		351, 193,
		347, 186,
		338, 182,
		328, 179,
		317, 179,
		310, 179,
		302, 180,
		297, 182,
		290, 185,
		285, 191,
		282, 196,
		278, 203,
		277, 213,
		276, 224,
		276, 232,
		276, 242,
		274, 254,
		265, 254,
		268, 202,
		272, 190,
		277, 183,
		287, 177,
		296, 174,
		305, 172,
		314, 171,
		319, 171,
		328, 172,
		337, 174,
		342, 176,
		351, 180,
		356, 184,
		360, 189
	};

	int Part_Center_2[22] = {
		309, 250,
		309, 240,
		309, 229,
		309, 220,
		310, 210,
		315, 209,
		320, 212,
		321, 222,
		321, 244,
		320, 254,
		312, 255
	};

	int Part_Down_Left[14] = {
		169, 406,
		174, 413,
		203, 510,
		195, 513,
		184, 509,
		144, 490,
		160, 406
	};

	int Part_Right_Left[12] = {
		460, 402,
		473, 486,
		466, 492,
		424, 514,
		415, 509,
		455, 401
	};

	int Part_Left[20] = {
		127, 403,
		102, 513,
		102, 520,
		199, 569,
		200, 575,
		194, 576,
		95, 521,
		94, 510,
		120, 401,
		125, 398
	};

	int Part_Right[20] = {
		504, 404,
		525, 510,
		526, 519,
		525, 525,
		423, 574,
		418, 572,
		424, 567,
		521, 516,
		500, 405,
		501, 401
	};

	int Boton_Left[16] = {
		288, 106,
		281, 107,
		278, 112,
		281, 116,
		287, 116,
		294, 114,
		298, 111,
		294, 107
	};

	int Boton_Center[18] = {
		323, 83,
		316, 84,
		312, 90,
		316, 93,
		323, 94,
		329, 92,
		332, 89,
		331, 86,
		327, 84
	};

	int Boton_Right[18] = {
		356, 104,
		351, 105,
		346, 109,
		346, 114,
		350, 117,
		358, 117,
		364, 115,
		365, 109,
		361, 105
	};

	ricks.add(App->physics->CreateChain(0, 0, rick_head, 88, 0));
	ricks.add(App->physics->CreateChain(0, 0, PartUP_right, 40, 0));
	ricks.add(App->physics->CreateChain(0, 0, PartUP_center, 14, 0));
	ricks.add(App->physics->CreateChain(0, 0, PartUP_center_2, 16, 0));
	ricks.add(App->physics->CreateChain(0, 0, PartUp_Left, 42, 0));
	ricks.add(App->physics->CreateChain(0, 0, Part_Center_1, 74, 0));
	ricks.add(App->physics->CreateChain(0, 0, Part_Center_2, 22, 0));
	ricks.add(App->physics->CreateChain(0, 0, Part_Down_Left, 14, 3));
	ricks.add(App->physics->CreateChain(0, 0, Part_Right_Left, 12, 3));
	ricks.add(App->physics->CreateChain(0, 0, Part_Left, 20, 0));
	ricks.add(App->physics->CreateChain(0, 0, Part_Right, 20, 0));
	ricks.add(App->physics->CreateChain(0, 0, Boton_Left, 16, 2));
	ricks.add(App->physics->CreateChain(0, 0, Boton_Center, 18, 2));
	ricks.add(App->physics->CreateChain(0, 0, Boton_Right, 18, 2));

	return true;
}