/*
 *
 */

import QtQuick 2.14
import QtQuick3D 1.14

import "../../.." as M

Node {
    id: rootNode

    property var rigModel: null

    rotationOrder: Node.XYZr
    orientation: Node.RightHanded

    M.Axis {
        id: track
        origin: Qt.vector3d(0, 0.98, 0)
        source: "meshes/track.mesh"
        axisModel: rigModel.track

        M.Model {
            id: base
            source: "meshes/base.mesh"

            M.Axis {
                id: rotate
                source: "meshes/rotate.mesh"
                axisModel: rigModel.rotate

                M.Axis {
                    id: lift
                    origin: Qt.vector3d(-0.15, 0.55, 0)
                    source: "meshes/lift.mesh"
                    axisModel: rigModel.lift

                    M.Axis {
                        id: arm
                        origin: Qt.vector3d(0, 0.825, 0)
                        source: "meshes/arm.mesh"
                        axisModel: rigModel.arm

                        M.Axis {
                            id: pan
                            source: "meshes/panL.mesh"
                            axisModel: rigModel.arm

                            M.Axis {
                                id: tilt
                                origin: Qt.vector3d(0, 0.925, 0)
                                source: "meshes/tilt.mesh"
                                axisModel: rigModel.tilt

                                M.Axis {
                                    id: roll
                                    origin: Qt.vector3d(0, 0.11, 0)
                                    source: "meshes/roll.mesh"
                                    axisModel: rigModel.roll
                                }
                            }
                        }
                    }
                }
            }
        } 
    }
}
