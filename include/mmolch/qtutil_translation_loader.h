#pragma once

#include <QObject>
#include <QLocale>
#include <QLoggingCategory>
#include <QTranslator>
#include <QVector>
#include <QString>

class QCoreApplication;

namespace mmolch::qtutil {
Q_DECLARE_LOGGING_CATEGORY(lcTranslationLoader)

class TranslationLoader : public QObject
{
    Q_OBJECT
public:
    struct Module {
        QString libraryName;
        QString moduleName;
    };

    explicit TranslationLoader(QCoreApplication *app);

    TranslationLoader &addModules(const QVector<Module> &modules);
    TranslationLoader &addSearchDirs(const QVector<QString> &dirs);

    void loadAll(const QLocale &locale);

    QStringList genSearchDirs(const TranslationLoader::Module &module) const;

private:
    QVector<QString> m_searchDirs;
    QVector<Module> m_modules;
    QVector<QTranslator*> m_translators;
};

} // namespace mmolch::qtutil
