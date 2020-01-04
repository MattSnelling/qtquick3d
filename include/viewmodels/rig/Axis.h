/**
* Copyright (C) 2018 Mark Roberts Motion Control Limited
*/

#pragma once

#include "include/Common.h"

#include <QtCore/QObject>
#include <QtGui/QColor>
#include <QtGui/QVector3D>

namespace UI::ViewModels::Rig
{
	/**
	 * \author Matthew Snelling
	 * \date 04 Jan 2020
	 * \brief A controllable Staubli 3D rig model.
	 */
	class Axis : public QObject
	{
		Q_OBJECT

	protected:
		QML_READONLY_PROPERTY_NODEF(QVector3D, translation) ///< The axis translation, relative to previous axis.
		QML_READONLY_PROPERTY_NODEF(QVector3D, rotation) ///< The axis rotation, relative to previous axis.
		QML_READONLY_PROPERTY(QColor, color, QColorConstants::White) ///< The axis colour.

	public:
		/**
		 * \details Axis class constructor.
		 * \param pParent The item parent.
		 */
		explicit Axis(QObject * pParent) :
			QObject(pParent)
		{

		}
	};
} // namespace UI::ViewModels::Rig