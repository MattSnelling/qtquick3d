/*
 *
 */

import QtQuick 2.14
import QtQuick3D 1.14
import QtQuick3D.Helpers 1.14

import "../environments" as E
import "../scenes" as S
import "../utilities" as U

View3D {
    id: viewport
    importScene: S.RigScene { id: sceneNode }
    environment: E.RigEnvironment {}
    camera: sceneNode.perspectiveCamera

    U.CameraController {
        id: cameraController
        camera: viewport.camera
    }

    Rectangle {
        color: "white"
        width: 200
        height: 300
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        Column {
            anchors.top: parent.top
            anchors.left: parent.left
            Text {
                text: "pos " + Math.round(camera.x) + "," + Math.round(camera.y) + "," + Math.round(camera.z)
            }
            Text {
                text: "rot " + Math.round(camera.rotation.x) + "," + Math.round(camera.rotation.y) + "," + Math.round(camera.rotation.z)
            }
        }
        }


}
