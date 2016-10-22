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
	circle = box = PinballMap = PinballMap_2nd_Layer = NULL;
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
	PinballMap = App->textures->Load("pinball/Map_Pinball.png");
	PinballMap_2nd_Layer = App->textures->Load("pinball/Map_Pinball_2nd_Layer.png");

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	Lose_sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT + 10, SCREEN_WIDTH / 2, 10);

	CreateMap();
	CreateBouncers();

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

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 7, true));
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

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
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
	p2List_item<PhysBody*>* c;


	App->renderer->Blit(PinballMap, 0, 0, NULL);

	c = circles.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x - 4.7f, y - 3.0f, NULL, 1.0f);
		c = c->next;
	}

	c = boxes.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x - 10, y - 5, NULL, 1.0f, c->data->GetRotation());
		if (ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if (hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}


	App->renderer->Blit(PinballMap_2nd_Layer, 0, 0, NULL);


	// ray -----------------
	if (ray_on == true)
	{
		fVector destination(mouse.x - ray.x, mouse.y - ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if (normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}


	//Check GAME STATE
	if (Game_Over == true)
	{
		lose_ball->body->GetWorld()->DestroyBody(lose_ball->body);
		lose_ball = nullptr;
		circles.add(App->physics->CreateCircle(620, 600, 8, true));
		Game_Over = false;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	//App->audio->PlayFx(bonus_fx);

	if (bodyA != nullptr)
	{
		if (bodyB == Lose_sensor)
		{
			lose_ball = bodyA;
			Game_Over = true;
		}
	}

}


bool ModuleSceneIntro::CreateMap()
{
	int rick_head[100] = {
		215, 651,
		40, 551,
		93, 358,
		130, 358,
		156, 344,
		159, 337,
		132, 253,
		128, 245,
		123, 241,
		124, 224,
		130, 212,
		140, 206,
		153, 210,
		165, 240,
		168, 238,
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
		511, 246,
		504, 246,
		500, 249,
		467, 334,
		468, 341,
		496, 357,
		533, 357,
		578, 553,
		400, 651,
		430, 723,
		180, 723,
		210, 660
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

	int Left_Triangle[10] = {
		188, 501,
		157, 389,
		142, 467,
		143, 474,
		147, 480
	};

	int Right_Triangle[10] = {
		466, 390,
		431, 501,
		472, 481,
		476, 475,
		477, 467
	};

	ricks.add(App->physics->CreateChain(0, 0, rick_head, 100, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, PartUP_right, 40, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, PartUP_center, 22, 0.5f, false));
	ricks.add(App->physics->CreateChain(0, 0, PartUP_center_2, 24, 0.5f, false));
	ricks.add(App->physics->CreateChain(0, 0, PartUp_Left, 56, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Center_1, 84, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Center_2, 22, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Left, 20, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Right, 20, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Left_Triangle, 10, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Right_Triangle, 10, 0, false));
	/*ricks.add(App->physics->CreateChain(0, 0, Part_Down_Left, 14, 1.85f, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Right_Left, 12, 1.85f, false));*/

	circles.add(App->physics->CreateCircle(620, 600, 8, true));

	return true;
}


void ModuleSceneIntro::CreateBouncers()
{
	int Left_Bouncer[16] = {
		201, 501,
		196, 503,
		190, 501,
		157, 388,
		159, 384,
		167, 383,
		171, 388,
		202, 493
	};

	int Right_Bouncer[16] = {
		422, 503,
		416, 500,
		415, 494,
		452, 387,
		457, 383,
		463, 384,
		465, 389,
		429, 501
	};

	int Orange_Bouncer_1[16] = {
		312, 76,
		317, 79,
		327, 79,
		332, 76,
		332, 72,
		327, 69,
		317, 69,
		312, 71
	};

	int Orange_Bouncer_2[16] = {
		277, 100,
		282, 102,
		293, 102,
		298, 100,
		298, 96,
		293, 93,
		282, 93,
		277, 96
	};

	int Orange_Bouncer_3[16] = {
		347, 100,
		352, 102,
		363, 102,
		368, 100,
		368, 96,
		363, 93,
		352, 93,
		347, 96
	};

	bouncers.add(App->physics->CreatePolygon(0, 0, Left_Bouncer, 16, 1.5f, false));
	bouncers.add(App->physics->CreatePolygon(0, 0, Right_Bouncer, 16, 1.5f, false));
	bouncers.add(App->physics->CreatePolygon(0, 0, Orange_Bouncer_1, 16, 1.5f, false));
	bouncers.add(App->physics->CreatePolygon(0, 0, Orange_Bouncer_2, 16, 1.5f, false));
	bouncers.add(App->physics->CreatePolygon(0, 0, Orange_Bouncer_3, 16, 1.5f, false));
}