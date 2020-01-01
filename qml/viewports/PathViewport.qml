/*
 *
 */

import QtQuick3D 1.14

import "../environments" as E
import "../scenes" as S

View3D {
    id: viewport
    importScene: S.PathScene { id: sceneNode }
    environment: E.PathEnvironment {}
    camera: sceneNode.perspectiveCamera
}
