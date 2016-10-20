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

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 8));
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
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
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
	int rick_head[94] = {
		215, 662,
		40, 562,
		93, 371,
		120, 269,
		128, 260,
		122, 248,
		124, 235,
		130, 224,
		143, 222,
		154, 229,
		164, 250,
		170, 249,
		144, 182,
		177, 65,
		187, 50,
		205, 37,
		224, 29,
		242, 26,
		260, 25,
		406, 25,
		422, 27,
		436, 30,
		449, 34,
		460, 40,
		470, 47,
		478, 54,
		486, 64,
		490, 73,
		650, 653,
		648, 662,
		638, 668,
		625, 662,
		621, 654,
		594, 565,
		582, 552,
		511, 255,
		504, 255,
		513, 270,
		534, 370,
		578, 564,
		400, 662,
		735, 705,
		722, -40,
		-37, -50,
		-25, 715,
		215, 720,
		214, 682
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

	int PartUP_center[22] = {
		348, 67,
		345, 67,
		343, 65,
		343, 58,
		343, 52,
		345, 49,
		348, 48,
		351, 49,
		352, 52,
		352, 62,
		351, 66
	};

	int PartUP_center_2[24] = {
		320, 53,
		319, 51,
		317, 50,
		315, 50,
		313, 51,
		312, 53,
		312, 61,
		313, 63,
		316, 64,
		318, 64,
		320, 63,
		320, 57
	};

	int PartUp_Left[56] = {
		228, 125,
		235, 75,
		210, 74,
		206, 133,
		200, 136,
		196, 145,
		190, 145,
		189, 139,
		198, 93,
		202, 77,
		205, 67,
		212, 59,
		226, 51,
		242, 46,
		256, 44,
		275, 43,
		287, 43,
		287, 57,
		284, 60,
		256, 67,
		249, 71,
		241, 129,
		239, 133,
		234, 132,
		232, 129,
		229, 133,
		226, 132,
		227, 129
	};

	int Part_Center_1[84] = {
		366, 218,
		365, 190,
		363, 183,
		359, 179,
		354, 174,
		348, 171,
		343, 169,
		337, 167,
		331, 165,
		323, 164,
		310, 163,
		302, 164,
		293, 166,
		287, 168,
		281, 171,
		276, 174,
		271, 179,
		268, 184,
		266, 211,
		264, 245,
		265, 252,
		268, 254,
		273, 253,
		275, 246,
		276, 203,
		280, 191,
		287, 183,
		298, 178,
		312, 176,
		328, 177,
		337, 180,
		345, 184,
		351, 189,
		354, 195,
		355, 203,
		355, 226,
		355, 247,
		356, 254,
		361, 256,
		366, 253,
		366, 243,
		366, 224
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

	int Boton_Left[30] = {
		286, 103,
		279, 104,
		275, 107,
		272, 112,
		272, 118,
		277, 121,
		283, 122,
		289, 122,
		295, 121,
		300, 119,
		304, 115,
		303, 110,
		300, 106,
		295, 104,
		290, 103
	};

	int Boton_Center[30] = {
		315, 82,
		310, 84,
		306, 88,
		306, 93,
		310, 96,
		315, 98,
		321, 99,
		326, 99,
		331, 97,
		335, 95,
		338, 91,
		335, 86,
		331, 83,
		325, 81,
		320, 81
	};


	int Boton_Right[32] = {
		353, 103,
		348, 104,
		342, 107,
		339, 111,
		340, 116,
		343, 120,
		348, 122,
		354, 123,
		360, 123,
		365, 122,
		370, 119,
		373, 115,
		372, 110,
		368, 106,
		363, 104,
		358, 103
	};

	int Part_center_Left_Withrest[18] = {
		130, 262,
		157, 347,
		157, 351,
		156, 354,
		136, 368,
		130, 370,
		97, 369,
		128, 332,
		128, 265
	};
	int Part_center_Right_Withrest[20] = {
		501, 258,
		467, 347,
		466, 352,
		469, 357,
		489, 368,
		495, 370,
		527, 369,
		508, 312,
		503, 284,
		503, 263
	};

	ricks.add(App->physics->CreateChain(0, 0, rick_head, 94, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, PartUP_right, 40, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, PartUP_center, 22, 0.5f, false));
	ricks.add(App->physics->CreateChain(0, 0, PartUP_center_2, 24, 0.5f, false));
	ricks.add(App->physics->CreateChain(0, 0, PartUp_Left, 56, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Center_1, 84, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Center_2, 22, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Left, 20, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_Right, 20, 0, false));
	ricks.add(App->physics->CreateChain(0, 0, Boton_Left, 30, 2, false));
	ricks.add(App->physics->CreateChain(0, 0, Boton_Center, 30, 2, false));
	ricks.add(App->physics->CreateChain(0, 0, Boton_Right, 32, 2, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_center_Left_Withrest, 18, 1, false));
	ricks.add(App->physics->CreateChain(0, 0, Part_center_Right_Withrest, 20, 1, false));


	return true;
}