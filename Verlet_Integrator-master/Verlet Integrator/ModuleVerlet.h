#ifndef __ModuleVerlet_H__
#define __ModuleVerlet_H__

#include "Globals.h"
#include "Application.h"
#include"Module.h"
#include"Shape.h"
#include"p2List_Extended.h"

class VerletIntegrator;
class Shape;
struct Point;
class ModuleVerlet : public Module
{
public:

	ModuleVerlet(Application* app, bool start_enabled = true);
	~ModuleVerlet();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();


	p2List_Extended<Shape*> shapes;
	p2List_Extended<Point*> world_points;
	VerletIntegrator* integrator;

	Point* selected_point;

	Point* MouseHoverSelection();

};

#endif // __ModuleVerlet_H__