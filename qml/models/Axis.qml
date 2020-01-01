/*
 *
 */

import QtQuick3D 1.14

import "../materials" as M

// NOTE
// Blender -> z points up (away from the ground)
// QML -> y points up
// i.e. y and z are swapped

Model {
    id: axis

    property var axisModel: null
    property alias axisColor: axisMaterial.diffuseColor
    property alias outlineScale: outline.scale

    readonly property Vector3D defaultOutlineScale: Qt.vector3d(1.01, 1.01, 1.01)

    rotationOrder: Node.XYZr
    orientation: Node.RightHanded
    materials: M.AxisMaterial {}

    rotation: axisModel.rotation
    position: axisModel.position

    Model {
        id: outline
        source: parent.source.replace(".mesh", "_inverted.mesh")
        castsShadows: false
        scale: defaultOutlineScale
        materials: M.AxisGlowMaterial {
            color: axisModel.color
        }
    }
}
