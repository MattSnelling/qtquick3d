/**
 *
 */

#pragma once

#include "include/Common.h"

#include <QtCore/QObject>

namespace UI::ViewModels::Rig
{
	/**
	 * \author Matthew Snelling
	 * \date 04 Jan 2020
	 * \brief This base class defines a controllable 3D rig model.
	 */
	class RigModel : public QObject
	{
		Q_OBJECT

	protected:

		QML_READONLY_PROPERTY_NODEF(QString, source) ///< The source QML for this rig.
		QML_READONLY_PROPERTY(bool, visible, true) ///< Is the model visible.

	public:

		/**
		 * \details RigModel class constructor.
		 * \param pParent The item parent.
		 */
		explicit RigModel(QObject * pParent) :
			QObject(pParent) 
		{

		}
	};
}
