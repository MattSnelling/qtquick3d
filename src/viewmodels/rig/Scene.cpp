/**
 *
 */

#include "include/viewmodels/rig/Scene.h"

#include "include/viewmodels/rig/StaubliModel.h"

using UI::ViewModels::Rig::Scene;

Scene::Scene(QObject * pParent) :
	QObject(pParent),
	p_currentRig(new StaubliModel(this))
{

}
