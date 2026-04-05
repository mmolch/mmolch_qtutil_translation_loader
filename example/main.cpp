#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include "mmolch/qtutil_translation_loader.h"

using namespace mmolch::qtutil;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    auto *loader = new TranslationLoader(&app);

    loader->addModules({
                {"qt6", "qt"},
                {"qt6", "qtbase"},
                {"qt6", "qtdeclarative"},
                {"qt6keychain", "qtkeychain"}
            })
            .loadAll(QLocale("de_DE"));

    qInfo() << "QCoreApplication::translate(\"QShortcut\", \"Cancel\")           -> " << QCoreApplication::translate("QShortcut", "Cancel");
    qInfo() << "QCoreApplication::translate(\"QSpiAccessibleBridge\", \"note\")  -> " << QCoreApplication::translate("QSpiAccessibleBridge", "note");

    return 0;
}
