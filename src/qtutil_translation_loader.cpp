#include "mmolch/qtutil_translation_loader.h"

#include <optional>
#include <QCoreApplication>
#include <QDir>

namespace mmolch::qtutil {
Q_LOGGING_CATEGORY(lcTranslationLoader, "mmolch.qtutil.translationloader")

TranslationLoader::TranslationLoader(QCoreApplication *app)
    : QObject(app)
{
}

TranslationLoader &TranslationLoader::addModules(const QVector<Module> &modules)
{
    m_modules += modules;
    return *this;
}

TranslationLoader &TranslationLoader::addSearchDirs(const QVector<QString> &dirs)
{
    m_searchDirs += dirs;
    return *this;
}

QStringList TranslationLoader::genSearchDirs(const TranslationLoader::Module &module) const
{
    static const QString appDir = QCoreApplication::applicationDirPath();
    static const std::optional<QString> env_path = qEnvironmentVariable("QT_TRANSLATION_PATH");

    QStringList searchDirs;
    searchDirs.append(appDir + "/../share/" + module.libraryName + "/translations");
    searchDirs.append(QString("/usr/share/") + module.libraryName + "/translations");
    searchDirs.append(QString("/usr/local/share/") + module.libraryName + "/translations");
    searchDirs.append(appDir + "/../translations");
    searchDirs.append(appDir + "/translations");
    searchDirs << m_searchDirs;
    if (env_path)
        searchDirs.append(env_path.value());

    return searchDirs;
}

void TranslationLoader::loadAll(const QLocale &locale)
{
    for (const auto &module : std::as_const(m_modules)) {
        bool module_loaded = false;
        for (const QString &dir : genSearchDirs(module)) {
            auto *translator = new QTranslator(this);

            if (translator->load(locale, module.moduleName, "_", dir)) {
                module_loaded = true;
                qCDebug(lcTranslationLoader) << "Loaded translation:" << translator->filePath();

                QCoreApplication::installTranslator(translator);
                m_translators.append(translator);
                break;
            }

            delete translator;
        }
        if (!module_loaded)
            qCWarning(lcTranslationLoader) << "Failed to load translation for" << module.libraryName << ":" << module.moduleName;
    }
}

} // namespace mmolch::qtutil
