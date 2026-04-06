#pragma once

#include <QObject>
#include <QLocale>
#include <QLoggingCategory>
#include <QStringList>
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
    TranslationLoader &addPaths(const QStringList &paths);

    void loadAll(const QLocale &locale);

private:
    QStringList genPaths(const TranslationLoader::Module &module, const QLocale &locale) const;

    QStringList m_paths;
    QVector<Module> m_modules;
    QVector<QTranslator*> m_translators;
};

} // namespace mmolch::qtutil
