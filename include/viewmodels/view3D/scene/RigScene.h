/**
 *
 */

#pragma once

#include "include/Common.h"
#include "include/Singleton.h"
#include "Scene.h"
#include "../model/rig/Rig.h"

#include <QtCore/QObject>

namespace UI::ViewModels::View3D::Scene
{
	/**
	 * \author Matthew Snelling
	 * \date 26 Jan 2020
	 * \brief This class manages the rig scene in the virtual 3D world.
	 */
	class RigScene : public Scene, public UI::Singleton<RigScene>
	{
		Q_OBJECT
		UI_SINGLETON

	protected:
		QML_OBJMODEL_PROPERTY(Model::Rig::Rig, rigs) ///< The rigs in the scene.

	public:
		/**
		 * \details 3D rig scene class constructor.
		 * \param pParent The item parent.
		 */
		explicit RigScene(QObject * pParent);
	};
} // namespace UI::ViewModels::Rig

