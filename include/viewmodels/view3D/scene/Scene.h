/**
 *
 */

#pragma once

#include "include/Common.h"
#include "include/viewmodels/view3D/model/Path.h"

#include <QtCore/QObject>
#include <QtGui/QColor>

namespace UI::ViewModels::View3D::Scene
{
	/**
	 * \author Matthew Snelling
	 * \date 26 Jan 2020
	 * \brief This class manages a scene in the virtual 3D world.
	 */
	class Scene : public QObject
	{
		Q_OBJECT

	protected:
		static constexpr QColor CAMERA_PATH_COLOR = QColorConstants::Blue; ///< The camera path colour.
		static constexpr QColor TARGET_PATH_COLOR = QColorConstants::Green; ///< The target path colour.
		static constexpr QColor UP_VECTOR_PATH_COLOR = QColorConstants::DarkRed; ///< The up vector path colour.

	protected:
		QML_QOBJECT_PROPERTY(Model::Path, cameraPath) ///< The camera path.
		QML_QOBJECT_PROPERTY(Model::Path, targetPath) ///< The target path.
		QML_QOBJECT_PROPERTY(Model::Path, upVectorPath) ///< The up vector path.

	public:
		/**
		 * \details 3D scene class constructor.
		 * \param pParent The item parent.
		 */
		explicit Scene(QObject * pParent);
	};
} // namespace UI::ViewModels::View3D::Scene
