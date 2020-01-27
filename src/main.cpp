/**
 *
 */

#include "include/viewmodels/view3d/scene/PathScene.h"
#include "include/viewmodels/view3d/scene/RigScene.h"
#include "include/viewmodels/view3d/utility/Utility.h"

#include <QtCore/QResource>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuick3D/private/qquick3dviewport_p.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    if (!QResource::registerResource(QCoreApplication::applicationDirPath() + "/assets.rcc"))
    {
        qCritical() << "Failed to load assets";
        return -1;
    }

    QSurfaceFormat::setDefaultFormat(QQuick3DViewport::idealSurfaceFormat());

    // QML
    QQmlApplicationEngine engine;
    QQmlContext * pContext = engine.rootContext();

    // Singleton instances
	auto & rigScene = UI::ViewModels::View3D::Scene::RigScene::instance(pContext);
	qmlRegisterSingletonInstance("View3D", 1, 0, "RigScene", &rigScene);

    auto & pathScene = UI::ViewModels::View3D::Scene::PathScene::instance(pContext);
	qmlRegisterSingletonInstance("View3D", 1, 0, "PathScene", &pathScene);
    
	auto & utility = UI::ViewModels::View3D::Utility::Utility::instance(pContext);
	qmlRegisterSingletonInstance("View3D", 1, 0, "Utility", &utility);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
