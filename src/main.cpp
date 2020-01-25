/**
 *
 */

#include "include/viewmodels/rig/Scene.h"
#include "include/viewmodels/rig/Utility.h"

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
	auto & scene = UI::ViewModels::Rig::Scene::instance(pContext);
	qmlRegisterSingletonInstance("Rig", 1, 0, "Scene", &scene);
    
	auto & utility = UI::ViewModels::Rig::Utility::instance(pContext);
	qmlRegisterSingletonInstance("Rig", 1, 0, "Utility", &utility);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
