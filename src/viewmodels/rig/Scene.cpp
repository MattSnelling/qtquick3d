/**
 *
 */

#include "include/viewmodels/rig/Scene.h"

#include "include/viewmodels/rig/StaubliModel.h"

using UI::ViewModels::Rig::Scene;

Scene::Scene(QObject * pParent) :
	QObject(pParent),
	p_currentRig(new StaubliModel(this)),
	p_cameraPath(new Path(this))
{
	p_cameraPath->update_color(QColorConstants::Blue);

	p_cameraPath->addPoint({0, 0, 0});
	p_cameraPath->addPoint({0, 1, 0});
	p_cameraPath->addPoint({0, 1, 1});
	p_cameraPath->addPoint({1, 1.5, 1.5});
	p_cameraPath->addPoint({0.7, 1.25, 1.25});
	p_cameraPath->addPoint({0.3, 1.125, 1.125});
	p_cameraPath->set();
}
