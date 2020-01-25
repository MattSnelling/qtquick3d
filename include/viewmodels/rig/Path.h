/**
 *
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
	 * \date 05 Jan 2020
	 * \brief A path that can be drawn within a 3D virtual scene.
	 */
	class Path : public QObject
	{
		Q_OBJECT

	private:

		static constexpr double DEFAULT_THICKNESS = 0.01; ///< The default path thickness (in metres).

	protected:
		Q_PROPERTY(int count READ getCount NOTIFY countChanged)
		QML_READONLY_PROPERTY(double, thickness, DEFAULT_THICKNESS) ///< The path thickness (in metres).
		QML_READONLY_PROPERTY(QColor, color, QColorConstants::Black) ///< The path colour.
		QML_READONLY_PROPERTY(bool, visible, true) ///< The path visibility.

	public:
		/**
		 * \details Path class constructor.
		 * \param pParent The item parent.
		 */
		explicit Path(QObject * pParent);

		/**
		 * \details Get a point along the path.
		 * \param index The point index.
		 */
		Q_INVOKABLE QVector3D getPoint(int index) const;

		/**
		 * \details Get the rotation of a point to the next one.
		 * \param index The point index.
		 * \return The segment rotation.
		 */
		Q_INVOKABLE QVector3D getSegmentRotation(int index) const;

		/**
		 * \details Get the length of a point to the next one (in metres).
		 * \param index The point index.
		 * \return The segment length.
		 */
		Q_INVOKABLE float getSegmentLength(int index) const;

		/**
		 * \details Get the number of points.
		 */
		inline int getCount() const
		{
			return m_points.count();
		}

		/**
		 * \details Append a point to the path. The count property will not be updated unti set() is called.
		 * \param point The point to add at the end.
		 */
		void addPoint(const QVector3D & point);

		/**
		 * \details Get the number of points.
		 */
		void clear();

		/**
		 * \details Update the count property (for QML).
		 */
		void set();
	
	Q_SIGNALS:
		/**
		 * \details Emitted when the point count has changed.
		 */
		void countChanged(int count);

	private:
		QVector<QVector3D> m_points; ///< The path points.
	};
} // namespace UI::ViewModels::Rig
