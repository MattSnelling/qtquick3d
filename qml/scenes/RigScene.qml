/*
 *
 */

import QtQuick 2.14
import QtQuick3D 1.14

import Rig 1.0

import "../models" as M

Node {
    id: sceneNode

    // Read-only properties
    readonly property int defaultBrightness: 20

    // Cameras
    property alias perspectiveCamera: perspective
    property alias topCamera: top

    PerspectiveCamera {
        id: perspective
        position: Qt.vector3d(0, 2, -3)
        //rotation: Qt.vector3d(30, 0, 0)
        clipNear: 0.01
    }

    PerspectiveCamera {
        id: top
        position: Qt.vector3d(0, 2, 0)
        rotation: Qt.vector3d(0, 0, 0)
        clipNear: 0.01
    }

    // Lights

    DirectionalLight {
        rotation: Qt.vector3d(45, 45, 0)
        brightness: defaultBrightness
    }
    DirectionalLight {
        rotation: Qt.vector3d(45, -45, 0)
        brightness: defaultBrightness
    }

    // Models

    Model {
        id: floor
        position: Qt.vector3d(0, 0, 0)
        scale: Qt.vector3d(0.1, 0, 0.1)
        source: "#Cube"
        materials: [ DefaultMaterial {
                diffuseMap: Texture {
                    source: "qrc:/assets/images/plane.png"
                }
            }
        ]
    }

    Loader3D {
        id: rigLoader

        property var rigModel: Scene.currentRig

        asynchronous: true
        visible: status == Loader3D.Ready
        source: rigModel ? rigModel.source : ""

        onLoaded: item.rigModel = rigModel
    }

    M.Path {
        id: cameraPath
        pathModel: Scene.cameraPath
    }
}
