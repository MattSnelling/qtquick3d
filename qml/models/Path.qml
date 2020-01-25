/*
 *
 */

import QtQuick3D 1.14
import QtQuick3D.Helpers 1.14

import "../materials" as M

Repeater3D {
    id: path

    property var pathModel: null

    model: pathModel ? pathModel.count : 0
    visible: pathModel.visible

    Model {
        id: line

        property real length: pathModel.getSegmentLength(index)

        source: "meshes/cube.mesh"
        position: pathModel.getPoint(index)
        rotation: pathModel.getSegmentRotation(index)
        scale: Qt.vector3d(pathModel.thickness, length / 2, pathModel.thickness)

        receivesShadows: false
        materials: DefaultMaterial {
            diffuseColor: pathModel.color
            lighting: DefaultMaterial.NoLighting
        }
    }
}
