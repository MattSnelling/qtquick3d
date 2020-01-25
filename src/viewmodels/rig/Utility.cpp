/**
 *
 */

#include "include/viewmodels/rig/Utility.h"

#include <QtGui/QQuaternion>
#include <QtMath>

using UI::ViewModels::Rig::Utility;

Utility::Utility(QObject * pParent) :
	QObject(pParent)
{
}

QVector3D Utility::rotateAboutAxis(QVector3D point, QVector3D axis, double theta)
{
	QQuaternion q1(0, point);
	QQuaternion q2(qCos(theta / 2), axis.x() * qSin(theta / 2), axis.y() * qSin(theta / 2), axis.z() * qSin(theta / 2));
	QQuaternion q3 = q2 * q1 * q2.conjugated();

	return q3.vector();
}
