/**
 *
 */

#include "include/viewmodels/view3D/scene/Scene.h"

using UI::ViewModels::View3D::Scene::Scene;

Scene::Scene(QObject * pParent) :
	QObject(pParent),
	m_cameraPath(this),
	m_targetPath(this),
	m_upVectorPath(this)
{
	m_cameraPath.update_color(CAMERA_PATH_COLOR);
	m_targetPath.update_color(TARGET_PATH_COLOR);
	m_upVectorPath.update_color(UP_VECTOR_PATH_COLOR);
}
