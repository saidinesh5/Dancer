#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QtQml>

#ifdef MEASURE_BPM
#include "audiolistenerbpm.h"
#else
#include "audiolistener.h"
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

#ifdef MEASURE_BPM
    qmlRegisterType<AudioListenerBPM>("com.monkeybusiness.dancer",1,0,"AudioListener");
#else
    qmlRegisterType<AudioListener>("com.monkeybusiness.dancer",1,0,"AudioListener");
#endif

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
