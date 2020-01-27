/**
 *
 */

#include "include/viewmodels/view3d/model/rig/StaubliRig.h"

using UI::ViewModels::View3D::Model::Rig::StaubliRig;

QPointer<StaubliRig> StaubliRig::createFromType(QObject * pParent, Type type)
{
	QPointer<StaubliRig> pRig = new StaubliRig(pParent);

	switch (type)
	{
	case Type::RX160L:
		pRig->update_source(SOURCE_RX160L);
		break;
	}

	return pRig;
}

StaubliRig::StaubliRig(QObject * pParent) :
	Rig(pParent),
	m_base(this),
	m_rotate(this),
	m_lift(this),
	m_arm(this),
	m_pan(this),
	m_tilt(this),
	m_roll(this)
{

}
