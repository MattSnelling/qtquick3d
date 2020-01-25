/**
 *
 */

#pragma once

#include "include/Common.h"
#include "include/Singleton.h"
#include "RigModel.h"
#include "Path.h"

#include <QtCore/QObject>

namespace UI::ViewModels::Rig
{
	/**
	 * \author Matthew Snelling
	 * \date 04 Jan 2020
	 * \brief This class manages the rig scene in the virtual 3D world.
	 */
	class Scene : public QObject, public UI::Singleton<Scene>
	{
		Q_OBJECT
		UI_SINGLETON

	protected:
		QML_POINTER_PROPERTY(RigModel, currentRig) ///< The current rig in use.
		QML_POINTER_PROPERTY(Path, cameraPath) ///< The camera path.

	public:
		/**
		 * \details 3D rig scene class constructor.
		 * \param pParent The item parent.
		 */
		explicit Scene(QObject * pParent);
	};
} // namespace UI::ViewModels::Rig

