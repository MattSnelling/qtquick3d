import QtQuick3D 1.14
import QtQuick 2.12

Model {
    id: cube
    rotationOrder: Node.XYZr
    orientation: Node.RightHanded
    source: "meshes/cube.mesh"

    PrincipledMaterial {
        id: material_material
        baseColor: "#ffcccccc"
        metalness: 0
        roughness: 0.4
        cullingMode: Material.DisableCulling
    }
    materials: [
        material_material
    ]
}
