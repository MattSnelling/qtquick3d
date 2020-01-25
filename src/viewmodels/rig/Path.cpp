/**
 *
 */

#include "include/viewmodels/rig/Path.h"

#include <QtGui/QQuaternion>

using UI::ViewModels::Rig::Path;

Path::Path(QObject * pParent) :
	QObject(pParent)
{
}

QVector3D Path::getPoint(int index) const
{
	Q_ASSERT(index >= 0);

	if (index < m_points.count())
		return m_points.at(index);

	return m_points.last();
}

QVector3D Path::getSegmentRotation(int index) const
{
	Q_ASSERT(index >= 0);

	const QVector3D & thisPoint = getPoint(index);
	const QVector3D & nextPoint = getPoint(index + 1);

	QQuaternion rotation = QQuaternion::rotationTo(thisPoint, nextPoint);

	QVector3D rotationEuler = rotation.toEulerAngles();
	return rotationEuler;
}

float Path::getSegmentLength(int index) const
{
	Q_ASSERT(index >= 0);

	const QVector3D & thisPoint = getPoint(index);
	const QVector3D & nextPoint = getPoint(index + 1);

	float distance = thisPoint.distanceToPoint(nextPoint);
	return distance;
}

void Path::addPoint(const QVector3D & point)
{
	m_points.append(point);
}

void Path::clear()
{
	m_points.clear();
	emit countChanged(getCount());
}

void Path::set()
{
	emit countChanged(getCount());
}
