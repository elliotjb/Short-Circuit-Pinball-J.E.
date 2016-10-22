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

	circle = App->textures->Load("pinball/Ball.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/Map_Pinball.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	//sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);
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

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 8, true));
		circles.getLast()->data->listener = this;
	}

	/*if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}*/

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		if (circles.getFirst() != NULL)
		{
			circles.getFirst()->data->body->ApplyForceToCenter(b2Vec2(0.0f, -120.0f), true);
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
	p2List_item<PhysBody*>* c = ricks.getFirst();


	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x - 4.7f, y-3.0f, NULL, 1.0f);
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x - 10, y - 5, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
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
		215, 651,
		40, 551,
		93, 360,
		120, 258,
		122, 249,
		122, 237,
		124, 224,
		130, 212,
		143, 211,
		153, 235,
		164, 239,
		170, 238,
		144, 171,
		174, 63,
		183, 48,
		199, 35,
		217, 25,
		240, 18,
		260, 16,
		403, 16,
		419, 17,
		433, 20,
		446, 24,
		459, 30,
		469, 36,
		478, 44,
		486, 53,
		490, 62,
		650, 642,
		648, 651,
		638, 657,
		623, 656,
		615, 641,
		588, 559,
		582, 541,
		511, 244,
		510, 250,
		513, 259,
		534, 359,
		578, 553,
		400, 651,
		430, 723,
		180, 723,
		209, 658
	};

	int PartUP_right[40] = {
		455, 241,
		482, 181,
		459, 67,
		445, 48,
		426, 38,
		408, 34,
		378, 34,
		380, 46,
		429, 48,
		429, 62,
		399, 63,
		400, 108,
		437, 161,
		444, 158,
		437, 89,
		441, 80,
		455, 80,
		462, 92,
		480, 179,
		453, 240
	};

	int PartUP_center[22] = {
		348, 56,
		345, 56,
		343, 54,
		343, 47,
		343, 41,
		345, 38,
		348, 37,
		351, 38,
		352, 41,
		352, 51,
		351, 55
	};

	int PartUP_center_2[24] = {
		320, 42,
		319, 40,
		317, 39,
		315, 39,
		313, 40,
		312, 42,
		312, 50,
		313, 52,
		316, 53,
		318, 53,
		320, 52,
		320, 46
	};

	int PartUp_Left[56] = {
		228, 114,
		235, 64,
		210, 63,
		206, 122,
		200, 125,
		196, 134,
		190, 134,
		189, 128,
		198, 82,
		202, 66,
		205, 56,
		212, 48,
		226, 40,
		242, 35,
		256, 33,
		275, 32,
		287, 32,
		287, 46,
		284, 49,
		256, 56,
		249, 60,
		241, 118,
		239, 122,
		234, 121,
		232, 118,
		229, 122,
		226, 121,
		227, 118
	};

	int Part_Center_1[84] = {
		366, 207,
		365, 179,
		363, 172,
		359, 168,
		354, 163,
		348, 160,
		343, 158,
		337, 156,
		331, 154,
		323, 153,
		310, 152,
		302, 153,
		293, 155,
		287, 157,
		281, 160,
		276, 163,
		271, 168,
		268, 173,
		266, 200,
		264, 234,
		265, 241,
		268, 243,
		273, 242,
		275, 235,
		276, 192,
		280, 180,
		287, 172,
		298, 167,
		312, 165,
		328, 166,
		337, 169,
		345, 173,
		351, 178,
		354, 184,
		355, 192,
		355, 215,
		355, 236,
		356, 243,
		361, 245,
		366, 242,
		366, 232,
		366, 213
	};

	int Part_Center_2[22] = {
		309, 239,
		309, 229,
		309, 218,
		309, 209,
		310, 199,
		315, 198,
		320, 201,
		321, 211,
		321, 233,
		320, 243,
		312, 244
	};

	int Part_Left[20] = {
		127, 392,
		102, 502,
		102, 509,
		199, 558,
		200, 564,
		194, 565,
		95, 510,
		94, 499,
		120, 390,
		125, 387
	};

	int Part_Right[20] = {
		504, 393,
		525, 499,
		526, 508,
		525, 514,
		423, 563,
		418, 561,
		424, 556,
		521, 505,
		500, 394,
		501, 390
	};



	ricks.add(App->physics->CreateChain(0, 0, rick_head, 88, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, PartUP_right, 40, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, PartUP_center, 22, 0.5f, false));
	ricks.add(App->physics->CreateChain(0, 0, PartUP_center_2, 24, 0.5f, false));
	ricks.add(App->physics->CreateChain(0, 0, PartUp_Left, 56, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Center_1, 84, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Center_2, 22, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Left, 20, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Right, 20, 0, false));
	/*ricks.add(App->physics->CreateChain(0, 0, Part_Down_Left, 14, 1.85f, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Right_Left, 12, 1.85f, false));*/



	return true;
}