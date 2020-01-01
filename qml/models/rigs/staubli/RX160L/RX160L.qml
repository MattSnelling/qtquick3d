/*
 *
 */

import QtQuick 2.14
import QtQuick3D 1.14

import "../../.." as M

Node {
    id: rootNode

    property var rigViewModel: null

    rotationOrder: Node.XYZr
    orientation: Node.RightHanded

    M.Axis {
        id: base
        source: "meshes/base.mesh"
        axisModel: rigViewModel.base

        M.Axis {
            id: rotate
            y: 0.5
            source: "meshes/rotate.mesh"
            axisModel: rigViewModel.rotate

            M.Axis {
                id: lift
                y: 0.5
                z: -0.4
                source: "meshes/lift.mesh"
                axisModel: rigViewModel.lift

                M.Axis {
                    id: arm
                    y: 1
                    z: 0.4
                    source: "meshes/arm.mesh"
                    axisModel: rigViewModel.arm
                }
            }
        } 
    }
}
