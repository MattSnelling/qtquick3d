/**
 *
 */

#include "include/viewmodels/view3D/scene/RigScene.h"

#include "include/viewmodels/view3D/model/Path.h"
#include "include/viewmodels/view3D/model/rig/StaubliRig.h"

using UI::ViewModels::View3D::Scene::RigScene;

RigScene::RigScene(QObject * pParent) :
	Scene(pParent),
	m_rigs(this)
{
	// TEMP
	m_rigs.append(Model::Rig::StaubliRig::createFromType(this, Model::Rig::StaubliRig::Type::RX160L));

	auto & cameraPath = get_cameraPath();

	cameraPath.addPoint({0, 0, 0});
	cameraPath.addPoint({0, 1, 0});
	cameraPath.addPoint({0, 1, 1});
	cameraPath.addPoint({1, 1.5, 1.5});
	cameraPath.addPoint({0.7, 1.25, 1.25});
	cameraPath.addPoint({0.3, 1.125, 1.125});
	cameraPath.set();
}
