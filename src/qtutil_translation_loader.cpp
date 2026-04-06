#include "mmolch/qtutil_translation_loader.h"

#include <optional>
#include <QCoreApplication>
#include <QDir>
#include <QLibraryInfo>
#include <QtCore/qglobal.h>

namespace mmolch::qtutil {
Q_LOGGING_CATEGORY(lcTranslationLoader, "mmolch.qtutil.translationloader")

TranslationLoader::TranslationLoader(QCoreApplication *app)
    : QObject(app)
{
#ifdef NDEBUG
    QLoggingCategory::setFilterRules("mmolch.qtutil.translationloader.debug=false\n");
#endif // NDEBUG
}

TranslationLoader &TranslationLoader::addModules(const QVector<Module> &modules)
{
    m_modules += modules;
    return *this;
}

TranslationLoader &TranslationLoader::addPaths(const QStringList &paths)
{
    m_paths += paths;
    return *this;
}

QStringList TranslationLoader::genPaths(const TranslationLoader::Module &module, const QLocale &locale) const
{
    static const QString appDir = QCoreApplication::applicationDirPath();
    const QString posix = locale.name(); // e.g. "de_DE"
    const QString langOnly = QLocale(locale.language()).name(); // e.g. "de"

    QStringList paths;

    paths.append(appDir + "/../share/" + module.libraryName + "/translations/" + module.moduleName + "_" + posix);
    paths.append(appDir + "/../share/" + module.libraryName + "/translations/" + module.moduleName + "_" + langOnly);

    paths.append(appDir + "/../translations/" + module.moduleName + "_" + posix);
    paths.append(appDir + "/../translations/" + module.moduleName + "_" + langOnly);

    paths.append(appDir + "/translations/" + module.moduleName + "_" + posix);
    paths.append(appDir + "/translations/" + module.moduleName + "_" + langOnly);

    paths.append("/usr/local/share/" + module.libraryName + "/translations/" + module.moduleName + "_" + posix);
    paths.append("/usr/local/share/" + module.libraryName + "/translations/" + module.moduleName + "_" + langOnly);

    paths.append("/usr/share/" + module.libraryName + "/translations/" + module.moduleName + "_" + posix);
    paths.append("/usr/share/" + module.libraryName + "/translations/" + module.moduleName + "_" + langOnly);

    paths.append("/usr/local/share/locale/" + posix + "/LC_MESSAGES/" + module.moduleName);
    paths.append("/usr/local/share/locale/" + langOnly + "/LC_MESSAGES/" + module.moduleName);

    paths.append("/usr/share/locale/" + posix + "/LC_MESSAGES/" + module.moduleName);
    paths.append("/usr/share/locale/" + langOnly + "/LC_MESSAGES/" + module.moduleName);

    return paths;
}

void TranslationLoader::loadAll(const QLocale &locale)
{
    for (const QString &path : std::as_const(m_paths)) {
        auto *translator = new QTranslator(this);

        if (translator->load(path)) {
            qCDebug(lcTranslationLoader) << "Loaded translation file:"
                                         << translator->filePath();

            QCoreApplication::installTranslator(translator);
            m_translators.append(translator);
        } else {
            qCWarning(lcTranslationLoader) << "Failed to load translation file:" << path;
            delete translator;
        }
    }

    for (const auto &module : std::as_const(m_modules)) {
        bool module_loaded = false;
        for (const QString &path : genPaths(module, locale)) {
            auto *translator = new QTranslator(this);

            if (translator->load(path)) {
                module_loaded = true;
                qCDebug(lcTranslationLoader) << "Loaded translation file:"
                                             << translator->filePath();

                QCoreApplication::installTranslator(translator);
                m_translators.append(translator);
                break;
            }

            delete translator;
        }
        if (!module_loaded)
            qCWarning(lcTranslationLoader) << "Failed to load translation for"
                                           << module.libraryName << ":" << module.moduleName;
    }
}

} // namespace mmolch::qtutil
