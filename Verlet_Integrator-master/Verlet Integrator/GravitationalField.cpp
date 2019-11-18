#include "IntegratorFunctions.h"
#include "ModuleVerlet.h"
#include "GravitationalField.h"
#include "Module.h"
#include "Application.h"

GravitationalField::GravitationalField(Application* app, bool start_enabled = true) : Module(app, start_enabled)
{
	bigPlanet = new Planet();
	smallPlanetObject = new PlanetObject();
}

//destructor
GravitationalField::~GravitationalField()
{}

bool GravitationalField::Init()
{
	//BIG PLANET SETTING VARS
	bigPlanet->atmosphere = 4.f;
	bigPlanet->gravity = 9.806f;
	bigPlanet->mass = 6.f;
	///speed and pos = 0

	//SMALL PLANET SETTING VARS
	smallPlanetObject->mass = 2.f;
	smallPlanetObject->position = { 1, 0 };
	smallPlanetObject->speed = 3.f;

	PrintPlanet(bigPlanet);

	return true;
}

//PreUpdate:
update_status GravitationalField::PreUpdate()
{

	return UPDATE_CONTINUE;
}

//Update: debug Camera
update_status GravitationalField::Update()
{

	return UPDATE_CONTINUE;
}

//PostUpdate
update_status GravitationalField::PostUpdate()
{
	return UPDATE_CONTINUE;
}

//CleanUp
bool GravitationalField::CleanUp()
{
	delete bigPlanet;
	delete smallPlanetObject;

	return true;
}


//----------------------------


void GravitationalField::PrintPlanet(Planet Earth)
{
	//MYTODO
}










Planet::Planet()
{
}

PlanetObject::PlanetObject()
{
}

void PlanetObject::PrintPlanetObject(PlanetObject Moon)
{
	//Create circle
}

vector2 PlanetObject::Move(Planet Earth, PlanetObject Moon)
{
	if (Earth.atmosphere > Moon.position.y)
	{
		
	}

	return position;
}