/**
 *
 */

#pragma once

#include "include/Singleton.h"

#include <QtCore/QObject>
#include <QtGui/QVector3D>

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

		/**
		 * \details Determine the required rotations to look at the given position.
		 * \param point The point to rotate.
		 * \param rotation The current rotation of the point.
		 * \param lookAt The position to look at.
		 * \return The required rotation.
		 */
		Q_INVOKABLE QVector3D lookAt(QVector3D point, QVector3D rotation, QVector3D lookAt);
	};
} // namespace UI::ViewModels::Rig
