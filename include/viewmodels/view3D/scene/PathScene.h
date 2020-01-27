/**
 *
 */

#pragma once

#include "Scene.h"
#include "include/Common.h"
#include "include/Singleton.h"

#include <QtCore/QObject>

namespace UI::ViewModels::View3D::Scene
{
	/**
	 * \author Matthew Snelling
	 * \date 26 Jan 2020
	 * \brief This class manages the path scene in the virtual 3D world.
	 */
	class PathScene : public Scene, public UI::Singleton<PathScene>
	{
		Q_OBJECT
		UI_SINGLETON

	public:
		/**
		 * \details 3D path scene class constructor.
		 * \param pParent The item parent.
		 */
		explicit PathScene(QObject * pParent);
	};
} // namespace UI::ViewModels::View3D::Scene
