

import QtQuick 2.14
import QtQuick3D 1.14

import Rig 1.0

Item {
    id: control
    property Camera camera: undefined
    property vector3d revolveAround: Qt.vector3d(0, 0, 0)

    property real rotateXSpeed: 0.1
    property real rotateYSpeed: 0.1
    property bool rotateXInvert: false
    property bool rotateYInvert: true

    property real panXSpeed: 0.01
    property real panYSpeed: 0.01
    property bool panXInvert: false
    property bool panYInvert: false

    property real revolveXSpeed: 0.1
    property real revolveYSpeed: 0.1
    property bool revolveXInvert: false
    property bool revolveYInvert: true

    property real zoomSpeed: 0.1
    property real zoomDivider: 120
    property bool zoomInvert: true

    readonly property bool inputsNeedProcessing: status.rotateView | status.panView | status.revolveView | status.zoomView

    implicitWidth: parent.width
    implicitHeight: parent.height

    DragHandler {
        id: mouseRotate
        target: null
        enabled: true
        acceptedButtons: Qt.LeftButton
        onCentroidChanged: {
            status.currentRotate = Qt.vector2d(centroid.position.x, centroid.position.y);
        }

        onActiveChanged: {
            if (active) {
                var position = Qt.vector2d(centroid.position.x, centroid.position.y);
                status.currentRotate = position;
                status.lastRotate = position;
                status.revolveView = true;
            }
            else {
                status.revolveView = false;
            }
        }
    }

    MouseArea {
        id: mousePan
        anchors.fill: parent
        propagateComposedEvents: true
        acceptedButtons: Qt.MiddleButton

        onPositionChanged: {
            if (pressedButtons & Qt.MiddleButton) {
                status.currentPan = Qt.vector2d(mouse.x, mouse.y);
            }
        }

        onPressed: {
            var position = Qt.vector2d(mouse.x, mouse.y);
            status.currentPan = position;
            status.lastPan = position;
            status.panView = true;
        }

        onReleased: {
            status.panView = false;
        }

        onWheel: {
            status.zoomView = true;
            var zoomDelta = wheel.angleDelta.y / zoomDivider;
            if ((zoomDelta < 0 && status.totalZoom > 0) || (zoomDelta > 0 && status.totalZoom > 0))
                status.totalZoom = zoomDelta;
            else
                status.totalZoom += zoomDelta;
        }
    }

    Timer {
        id: updateTimer
        interval: 16
        repeat: true
        running: control.inputsNeedProcessing
        onTriggered: {
            if (control.inputsNeedProcessing)
                status.processInput();
        }
    }

    QtObject {
        id: status

        property bool rotateView: false
        property vector2d lastRotate: Qt.vector2d(0, 0)
        property vector2d currentRotate: Qt.vector2d(0, 0)

        property bool panView: false
        property vector2d lastPan: Qt.vector2d(0, 0)
        property vector2d currentPan: Qt.vector2d(0, 0)

        property bool revolveView: false

        property bool zoomView: false
        property double totalZoom: 0.0

        function processInput() {
            if (camera == undefined)
                return;

            var rotationVector = camera.rotation;
            var positionVector = camera.position;
            var pivotPoint = camera.pivot;

            // Get the deltas
            var deltaRotate = Qt.vector2d(lastRotate.x - currentRotate.x, lastRotate.y - currentRotate.y);
            var deltaPan  = Qt.vector2d(lastPan.x - currentPan.x, lastPan.y - currentPan.y);
            lastRotate = currentRotate;
            lastPan = currentPan;

            if (rotateView && deltaRotate !== Qt.vector2d(0,0)) {
                // rotate x
                var rotateX = deltaRotate.x * -rotateXSpeed
                if (rotateXInvert)
                    rotateX = -rotateX;
                rotationVector.y += rotateX;

                // rotate y
                var rotateY = deltaRotate.y * rotateYSpeed
                if (rotateYInvert)
                    rotateY = -rotateY;
                rotationVector.x += rotateY;

                camera.setRotation(rotationVector);
            }
            else if(panView && deltaPan !== Qt.vector2d(0,0)) {
                // pan x
                var panX = deltaPan.x * -panXSpeed
                if (panXInvert)
                    panX = -panX;
                positionVector.x += panX;

                // pan y
                var panY = deltaPan.y * panYSpeed
                if (panYInvert)
                    panY = -panY;
                positionVector.y += panY;

                camera.setPosition(positionVector);
            }
            else if(revolveView && deltaRotate !== Qt.vector2d(0,0)) {
                // Revolve x
                var revolveX = deltaRotate.x * -revolveXSpeed
                if (revolveXInvert)
                    revolveX = -revolveX;

                // Revolve y
                var revolveY = deltaRotate.y * revolveYSpeed
                if (revolveYInvert)
                    revolveY = -revolveY;

                // To radians
                var thetaX = revolveX * Math.PI / 180;
                var thetaY = revolveY * Math.PI / 180;

                // Apply transforms
                var rotatedPosition = Utility.rotateAboutAxis(positionVector, Qt.vector3d(0, 1, 0), thetaX);
                rotatedPosition = Utility.rotateAboutAxis(rotatedPosition, Qt.vector3d(1, 0, 0), thetaY);
                camera.setPosition(rotatedPosition);

                //rotationVector = Utility.lookAt(rotatedPosition, rotationVector, revolveAround);
                camera.rotate(revolveX, Qt.vector3d(rotatedPosition.x, 1, rotatedPosition.z), Qt.LocalSpace);
                camera.rotate(revolveY, Qt.vector3d(1, rotatedPosition.y, rotatedPosition.z), Qt.LocalSpace);
                camera.setRotation(rotationVector);
            }
            else if (zoomView) {

                var multiplier = 0.0;
                if (totalZoom > 0.0) {
                    totalZoom -= zoomSpeed;
                    multiplier = -zoomSpeed;

                    if(totalZoom <= 0.0) {
                        totalZoom = 0.0;
                        zoomView = false;
                    }
                }
                else {
                    totalZoom += zoomSpeed;
                    multiplier = zoomSpeed;

                    if(totalZoom >= 0.0) {
                        totalZoom = 0.0;
                        zoomView = false;
                    }
                }

                if (zoomInvert)
                    multiplier = -multiplier;

                var forwardVector = camera.forward;
                var zoomTranslation = Qt.vector3d(forwardVector.x * multiplier, forwardVector.y * multiplier, forwardVector.z * multiplier);

                positionVector = Qt.vector3d(positionVector.x + zoomTranslation.x, positionVector.y + zoomTranslation.y, positionVector.z + zoomTranslation.z);
                camera.setPosition(positionVector);
            }
        }
    }
}
