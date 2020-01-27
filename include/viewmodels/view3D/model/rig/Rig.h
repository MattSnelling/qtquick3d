/**
 *
 */

#pragma once

#include "include/Common.h"

#include <QtCore/QObject>

namespace UI::ViewModels::View3D::Model::Rig
{
	/**
	 * \author Matthew Snelling
	 * \date 04 Jan 2020
	 * \brief This base class defines a controllable 3D rig model.
	 */
	class Rig : public QObject
	{
		Q_OBJECT

	protected:

		QML_READONLY_PROPERTY_NODEF(QString, source) ///< The source QML for this rig.
		QML_READONLY_PROPERTY(bool, visible, true) ///< Is the model visible.
		QML_READONLY_PROPERTY(double, baseHeight, 0.0) ///< The origin height of the base node.

	public:

		/**
		 * \details Rig class constructor.
		 * \param pParent The item parent.
		 */
		explicit Rig(QObject * pParent);
	};
}
