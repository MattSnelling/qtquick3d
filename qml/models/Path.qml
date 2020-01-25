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

        source: "#Cube"
        position: pathModel.getPoint(index)
        rotation: pathModel.getSegmentRotation(index)
        scale: Qt.vector3d(pathModel.getSegmentLength(index) / 100, pathModel.thickness / 100, pathModel.thickness / 100)

        materials: DefaultMaterial {
            diffuseColor: pathModel.color
        }
    }
}
