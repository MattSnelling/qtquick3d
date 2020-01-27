/**
 *
 */

#pragma once

#include "../Axis.h"
#include "Rig.h"

namespace UI::ViewModels::View3D::Model::Rig
{
	/**
	 * \author Matthew Snelling
	 * \date 04 Jan 2020
	 * \brief A controllable Staubli 3D rig model.
	 */
	class StaubliRig : public Rig
	{
		Q_OBJECT

	private:
		static constexpr const char SOURCE_RX160L[] = "qrc:/qml/models/rigs/staubli/RX160/RX160L.qml"; ///< RX160L model source.

	public:
		/**
		 * \brief Staubli rig type.
		 */
		enum class Type : int
		{
			RX160L
		};

	protected:
		QML_QOBJECT_PROPERTY(Axis, base) ///< Base axis (track or pedestal).
		QML_QOBJECT_PROPERTY(Axis, rotate) ///< Rotate axis.
		QML_QOBJECT_PROPERTY(Axis, lift) ///< Lift axis.
		QML_QOBJECT_PROPERTY(Axis, arm) ///< Arm axis.
		QML_QOBJECT_PROPERTY(Axis, pan) ///< Pan axis.
		QML_QOBJECT_PROPERTY(Axis, tilt) ///< Tilt axis.
		QML_QOBJECT_PROPERTY(Axis, roll) ///< Roll axis.

	public:

		/**
		 * \details Create a Staubli rig.
		 * \param pParent The item parent.
		 * \param type The type of Staubli rig.
		 */
		static QPointer<StaubliRig> createFromType(QObject * pParent, Type type);

	private:
		/**
		 * \details StaubliRig class constructor.
		 * \param pParent The item parent.
		 */
		StaubliRig(QObject * pParent);
	};
} // namespace UI::ViewModels::View3D::Model::Rig
