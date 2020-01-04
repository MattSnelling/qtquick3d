/*
 *
 */

import QtQuick3D 1.14

import "../materials" as M
import "../models" as MS

// NOTE
// Blender -> z points up (away from the ground)
// QML -> y points up
// i.e. y and z are swapped

MS.Model {
    id: axis

    property var axisModel: null
    property alias outlineScale: outline.scale

    readonly property vector3d defaultOutlineScale: Qt.vector3d(1.01, 1.01, 1.01)

    rotation: axisModel.rotation
    position: origin.plus(axisModel.translation)

    MS.Model {
        id: outline
        source: parent.source.toString().replace(".mesh", "_inverted.mesh")
        castsShadows: false
        scale: defaultOutlineScale
        materials: M.AxisGlowMaterial {
            diffuseColor: axisModel.color
        }
    }
}
