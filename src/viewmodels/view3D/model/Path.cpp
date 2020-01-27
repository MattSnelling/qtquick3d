/**
 *
 */

#include "include/viewmodels/view3D/model/Path.h"

#include <QtGui/QQuaternion>

using UI::ViewModels::View3D::Model::Path;

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

	QVector3D line(nextPoint.x() - thisPoint.x(), nextPoint.y() - thisPoint.y(), nextPoint.z() - thisPoint.z());

	QQuaternion rotation = QQuaternion::rotationTo(QVector3D(0.0f, 1.0f, 0.0f), line);

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
