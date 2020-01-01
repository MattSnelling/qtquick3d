/*
 *
 */

import QtQuick 2.14
import QtQuick3D 1.14

import "../rigs/staubli" as RS

Node {
    id: sceneNode

    // Cameras
    property alias perspectiveCamera: perspective
    property alias topCamera: top

    PerspectiveCamera {
        id: perspective
        position: Qt.vector3d(0, 2, -3)
        rotation: Qt.vector3d(30, 0, 0)
    }

    PerspectiveCamera {
        id: top
        position: Qt.vector3d(0, 2, 0)
        rotation: Qt.vector3d(0, 0, 0)
    }

    // Lights

    DirectionalLight {
        rotation: Qt.vector3d(30, 70, 0)
    }

    // Models

    Model {
        id: floor
        position: Qt.vector3d(0, 0, 0)
        source: "#Cylinder"
        scale: Qt.vector3d(2, 0.2, 2)
        materials: [ PrincipledMaterial {
            }
        ]
    }

    Model {
        position: Qt.vector3d(0, 1.5, 0)
        source: "#Sphere"

        materials: [ DefaultMaterial {
                diffuseColor: "blue"
            }
        ]

        SequentialAnimation on y {
            loops: Animation.Infinite
            NumberAnimation {
                duration: 3000
                to: -1.5
                from: 1.5
                easing.type:Easing.InQuad
            }
            NumberAnimation {
                duration: 3000
                to: 1.5
                from: -1.5
                easing.type:Easing.OutQuad
            }
        }
    }

    RS.RX160L {}
}
