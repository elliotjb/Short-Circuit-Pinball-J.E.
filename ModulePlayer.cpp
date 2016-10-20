#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "p2Point.h"
#include "math.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}


// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	pivot_left = App->physics->CreateCircle(210, 580, 10, false);
	lever_left = App->physics->CreateRectangle(210, 580, 70, 10, true);
	pivot_force_left = App->physics->CreateCircle(280, 580, 5, true);

	pivot_Right = App->physics->CreateCircle(410, 580, 10, false);
	lever_Right = App->physics->CreateRectangle(410, 580, 70, 10, true);
	pivot_force_Right = App->physics->CreateCircle(340, 580, 5, true);

	App->physics->CreateRevolutionJoint();


	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		pivot_force_Right->body->ApplyForceToCenter(b2Vec2(0.0f, -300.0f), true);
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		pivot_force_left->body->ApplyForceToCenter(b2Vec2(0.0f, -300.0f), true);
	}

	return UPDATE_CONTINUE;
}

