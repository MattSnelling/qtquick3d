import QtQuick3D 1.14
import QtQuick 2.12

Node {
    id: rOOT
    rotationOrder: Node.XYZr
    orientation: Node.RightHanded

    Model {
        id: mount_top
        x: -0.15
        y: 3.39
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/mount_top.mesh"

        PrincipledMaterial {
            id: _material
            roughness: 1
            cullingMode: Material.DisableCulling
        }
        materials: [
            _material
        ]
    }

    Model {
        id: mount_left
        x: -0.15
        y: 3.39
        z: -0.5
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/mount_left.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: mount_right
        x: -0.15
        y: 3.39
        z: 0.5
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/mount_right.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: stand
        x: 4
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/stand.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: pedestal
        x: 2
        y: 0.98
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/pedestal.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: track
        y: 0.98
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/track.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: base
        y: 0.98
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/base.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: rotate
        y: 0.98
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/rotate.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: arm
        x: -0.15
        y: 2.355
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/arm.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: lift
        x: -0.15
        y: 1.53
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/lift.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: pan
        x: -0.15
        y: 2.355
        z: -1
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/pan.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: panL
        x: -0.15
        y: 2.355
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/panL.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: tilt
        x: -0.15
        y: 3.28
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/tilt.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: precision_rail
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/precision_rail.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: roll
        x: -0.15
        y: 3.39
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/roll.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: track_inverted
        y: 0.98
        z: -2
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/track_inverted.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: rotate_inverted
        y: 0.98
        z: -2
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/rotate_inverted.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: arm_inverted
        x: -0.15
        y: 2.355
        z: -2
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/arm_inverted.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: lift_inverted
        x: -0.15
        y: 1.53
        z: -2
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/lift_inverted.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: pan_inverted
        x: -0.15
        y: 2.355
        z: -3
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/pan_inverted.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: panL_inverted
        x: -0.15
        y: 2.355
        z: -2
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/panL_inverted.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: tilt_inverted
        x: -0.15
        y: 3.28
        z: -2
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/tilt_inverted.mesh"
        materials: [
            _material
        ]
    }

    Model {
        id: roll_inverted
        x: -0.15
        y: 3.39
        z: -2
        rotationOrder: Node.XYZr
        orientation: Node.RightHanded
        source: "meshes/roll_inverted.mesh"
        materials: [
            _material
        ]
    }
}
