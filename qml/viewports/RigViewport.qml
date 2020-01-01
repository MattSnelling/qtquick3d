/*
 *
 */

import QtQuick 2.14
import QtQuick3D 1.14
import QtQuick3D.Helpers 1.14

import "../environments" as E
import "../scenes" as S

View3D {
    id: viewport
    importScene: S.RigScene { id: sceneNode }
    environment: E.RigEnvironment {}
    camera: sceneNode.perspectiveCamera

    WasdController {
        id: viewController
        controlledObject: camera
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        speed: 0.1
        //keysEnabled: false

        MouseArea {
            id: mouseOverlay
            anchors.fill: parent
            propagateComposedEvents: true
            acceptedButtons: Qt.MiddleButton

            onPositionChanged: {
                if (pressedButtons & Qt.MiddleButton) {
                    viewController.mouseMoved(Qt.vector2d(mouse.x, mouse.y));
                }
            }

            onReleased: {
                viewController.mouseReleased(Qt.vector2d(mouse.x, mouse.y));
            }

            property bool goForward: false

            onWheel: {
                if (wheel.angleDelta.y > 0) {
                    goForward = true;
                    viewController.forwardPressed();
                    wheelChangeTimer.start();
                }
                else {
                    goForward = false;
                    viewController.backPressed();
                    wheelChangeTimer.start();
                }
            }

            Timer {
                id: wheelChangeTimer
                interval: 200
                onTriggered: {
                    if (mouseOverlay.goForward)
                        viewController.forwardReleased();
                    else
                        viewController.backReleased();
                }
            }
        }
    }
}
