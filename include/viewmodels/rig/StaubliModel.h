/**
 *
 */

#pragma once

#include "Axis.h"
#include "RigModel.h"

namespace UI::ViewModels::Rig
{
	/**
	 * \author Matthew Snelling
	 * \date 04 Jan 2020
	 * \brief A controllable Staubli 3D rig model.
	 */
	class StaubliModel : public RigModel
	{
		Q_OBJECT

	private:

		static constexpr const char SOURCE[] = "qrc:/qml/models/rigs/staubli/RX160/RX160L.qml"; ///< Rig model source.

	protected:
		QML_QOBJECT_PROPERTY(Axis, track) ///< Track axis.
		QML_QOBJECT_PROPERTY(Axis, rotate) ///< Rotate axis.
		QML_QOBJECT_PROPERTY(Axis, lift) ///< Lift axis.
		QML_QOBJECT_PROPERTY(Axis, arm) ///< Arm axis.
		QML_QOBJECT_PROPERTY(Axis, pan) ///< Pan axis.
		QML_QOBJECT_PROPERTY(Axis, tilt) ///< Tilt axis.
		QML_QOBJECT_PROPERTY(Axis, roll) ///< Roll axis.

	public:
		/**
		 * \details StaubliModel class constructor.
		 * \param pParent The item parent.
		 */
		StaubliModel(QObject * pParent) :
			RigModel(pParent),
			m_track(this),
			m_rotate(this),
			m_lift(this),
			m_arm(this),
			m_pan(this),
			m_tilt(this),
			m_roll(this)
		{
			update_source(SOURCE);
		}
	};
} // namespace UI::ViewModels::Rig
