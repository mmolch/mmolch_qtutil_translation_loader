# mmolch_qtutil_translation_loader

A small Qt6 utility library that simplifies loading translation files (`.qm`) for multiple Qt or third‑party modules.
It automatically searches common translation directories, respects `QT_TRANSLATION_PATH`, and installs all successfully loaded translators into the running `QCoreApplication`.

---

## Features

- Load translations for multiple modules with one call
- Automatic search path generation:
  - App-relative paths
  - `/usr/share/<module>/translations`
  - `/usr/local/share/<module>/translations`
  - Custom search directories
  - `QT_TRANSLATION_PATH` environment variable
- Simple, chainable API
- Works with Qt6 (Core)

---

## Example Usage

```cpp
#include <QCoreApplication>
#include "mmolch/qtutil_translation_loader.h"

using namespace mmolch::qtutil;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    TranslationLoader loader(&app);

    loader.addModules({
            {"qt6", "qt"},
            {"qt6", "qtbase"},
            {"qt6", "qtdeclarative"},
            {"qt6keychain", "qtkeychain"}
        })
        .loadAll(QLocale::system());

    return app.exec();
}
```

---

## Build Instructions

### Requirements
- CMake ≥ 3.16
- Qt6 (Core)

### Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

The repository includes a small example application (`example/`) demonstrating typical usage.

---

## API Overview

### `TranslationLoader`

| Method | Description |
|--------|-------------|
| `addModules(QVector<Module>)` | Registers modules to load translations for |
| `addSearchDirs(QVector<QString>)` | Adds custom search directories |
| `loadAll(QLocale)` | Loads translations for all modules |
| `genSearchDirs(Module)` | Returns all search paths for a module |

### Module Structure

```cpp
struct Module {
    QString libraryName;  // e.g. "qt6"
    QString moduleName;   // e.g. "qtbase"
};
```

---

## License

MIT — feel free to use it in your own projects.
