#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "imagereader.h"
#include "filedialoghelper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    FileDialogHelper fileDialogHelper;
    engine.rootContext()->setContextProperty("FileDialogHelper", &fileDialogHelper);

    ImageReader reader;
    engine.rootContext()->setContextProperty("imageReader", &reader);

    engine.loadFromModule("HUB75_Generator", "Main");

    return QCoreApplication::exec();
}