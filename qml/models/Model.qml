/*
 *
 */

import QtQuick3D 1.14

import "../materials" as M

Model {
    id: model

    property vector3d origin: Qt.vector3d(0, 0, 0)

    position: origin
    rotationOrder: Node.XYZr
    orientation: Node.RightHanded
    materials: M.AxisMaterial {}
}
