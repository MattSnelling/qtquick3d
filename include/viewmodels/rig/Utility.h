/**
 *
 */

#pragma once

#include "include/Singleton.h"

#include <QtCore/QObject>
#include <QtGui/QVector3D>
#include <QtGui/QMatrix4x4>

namespace UI::ViewModels::Rig
{
	/**
	 * \author Matthew Snelling
	 * \date 19 Jan 2020
	 * \brief A utility singleton class to calculate various 3D transforms. 
	 */
	class Utility : public QObject, public UI::Singleton<Utility>
	{
		Q_OBJECT
		UI_SINGLETON

	public:
		/**
		 * \details Utility class constructor.
		 * \param pParent The item parent.
		 */
		explicit Utility(QObject * pParent);

		/**
		 * \details Rotate a point about an axis.
		 * \param point The point to rotate.
		 * \param axis The axis to rotate about (unit vector).
		 * \param theta The angle in degrees to rotate.
		 * \return The rotated point.
		 */
		Q_INVOKABLE QVector3D rotateAboutAxis(QVector3D point, QVector3D axis, double theta);
	};
} // namespace UI::ViewModels::Rig
