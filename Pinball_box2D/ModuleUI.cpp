#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleUI::~ModuleUI() {}

bool ModuleUI::Start()
{
	LOG("Loading UI");

	score_tx = App->textures->Load("pinball/Textures/high_score.png");

	font = App->fonts->Load("pinball/Textures/numbers.png", "0123456789", 1);

	score = 0;

	return true;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading user interface")

	App->textures->Unload(score_tx);
	App->fonts->UnLoad(font);

	return true;
}

update_status ModuleUI::Update() {

	if (score > high_score)
		high_score = score;

	SDL_Rect r = { 0,0,152,24 }; //High score text
	App->renderer->Blit(score_tx, SCREEN_WIDTH - 154, 2, &r);

	r = { 6,32,140,37 }; //score box
	App->renderer->Blit(score_tx, 0, 0, &r);

	sprintf_s(score_text, 10, "%7d", score);
	App->fonts->BlitText(15, 10, font, score_text);

	sprintf_s(high_score_text, 10, "%7d", high_score);
	App->fonts->BlitText(SCREEN_WIDTH - 130, 30, font, high_score_text);

	return UPDATE_CONTINUE;
}
