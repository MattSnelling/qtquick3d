/*
 *
 */

import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12

import QtQuick3D.Helpers 1.14 // TEMP

import "./viewports" as V

Window {
    id: window
    width: 1280
    height: 720
    visible: true

    RowLayout {
        anchors.fill: parent

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true

            V.RigViewport {
                id: rigViewport
                anchors.fill: parent
            }

            DebugView {
                source: rigViewport
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true

            V.PathViewport {
                id: pathViewport
                anchors.fill: parent
            }

            DebugView {
                source: pathViewport
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
        }
    }
}
