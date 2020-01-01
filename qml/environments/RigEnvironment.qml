/*
 *
 */

import QtQuick3D 1.14

SceneEnvironment {
    id: root
    backgroundMode: SceneEnvironment.SkyBox
    multisampleAAMode: SceneEnvironment.X8

    lightProbe: Texture {
        source: "qrc:/assets/skybox/HDR_029_Sky_Cloudy_Ref.hdr"
    }
}
