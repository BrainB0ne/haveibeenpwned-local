# AGENTS.md - AI Agent Guidelines for haveibeenpwned-local

This document provides guidelines for AI agents working on the haveibeenpwned-local Qt/C++ codebase.

## Project Overview

A Qt GUI application to check passwords against a locally stored HaveIBeenPwned SQLite database. The project supports both CMake and qmake build systems.

- **Language**: C++17
- **Framework**: Qt6 (Widgets, Gui, Sql)
- **License**: GPL v3
- **Platforms**: Windows, Linux

## Build Commands

### CMake (Preferred)

```bash
# Configure (Windows with Ninja)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -G Ninja

# Configure (Linux with Ninja)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -G Ninja

# Build
cmake --build build --config Release

# Install (creates distribution package)
cmake --build build --config Release --target install
```

### qmake (Legacy)

```bash
# Generate Makefile
qmake haveibeenpwned-local.pro

# Build
make
```

### Testing

**No test framework is currently configured.** To run a single test (when tests are added):
```bash
# Example for Qt Test framework (not yet implemented)
# ./build/tests/test_name
```

## Code Style Guidelines

### General

- **Standard**: C++17
- **License**: GPL v3 header required on all source files
- **Indentation**: 4 spaces (no tabs)
- **Line endings**: Platform appropriate (CRLF on Windows, LF on Linux)
- **Maximum line length**: 120 characters

### File Organization

```
E:\Projects\Forgejo\haveibeenpwned-local/
├── CMakeLists.txt          # CMake build configuration
├── haveibeenpwned-local.pro # qmake build configuration
├── main.cpp                # Application entry point
├── mainwindow.cpp/h/ui     # Main window implementation
├── aboutdialog.cpp/h/ui    # About dialog
├── convertdialog.cpp/h/ui  # Database conversion dialog
├── preferencesdialog.cpp/h/ui # Settings dialog
├── resultdialog.cpp/h/ui   # Single result display
├── resulttabledialog.cpp/h/ui # Multiple results table
├── licensedialog.cpp/h/ui  # License display
├── pwnedresult.cpp/h       # Data model for results
└── haveibeenpwned-local.qrc # Qt resource file
```

### Naming Conventions

| Element | Convention | Example |
|---------|------------|---------|
| Classes | PascalCase | `MainWindow`, `PwnedResult` |
| Member variables | m + PascalCase | `mSQLiteDatabase`, `mSettings` |
| Functions | camelCase | `loadSettings()`, `calcHash()` |
| Constants | UPPER_SNAKE_CASE | `COLOR_RED`, `LINE_SEPARATOR` |
| UI files | lowercase.ui | `mainwindow.ui` |
| Include guards | FILENAME_H | `MAINWINDOW_H` |

### Includes

Order imports as follows:
```cpp
// 1. Own header (for .cpp files)
#include "mainwindow.h"
#include "ui_mainwindow.h"

// 2. Project headers (alphabetical)
#include "aboutdialog.h"
#include "convertdialog.h"
#include "pwnedresult.h"

// 3. Qt headers (alphabetical)
#include <QApplication>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QSqlDatabase>
```

### Qt-Specific Patterns

**Memory Management:**
```cpp
// Use parent-child hierarchy for automatic cleanup
QSettings *mSettings = new QSettings(..., this);
QProcess *mConversionProcess = new QProcess(this);

// Check for nullptr before use
if (mSettings)
{
    mSettings->setValue(...);
}

// Use deleteLater() for QObjects
resDialog->deleteLater();
```

**Signal/Slot Connections:**
```cpp
// Old-style (current codebase style)
connect(mConversionProcess, SIGNAL(readyReadStandardOutput()),
        this, SLOT(readConversionOutput()));

// Prefer new-style when writing new code
connect(mConversionProcess, &QProcess::readyReadStandardOutput,
        this, &MainWindow::readConversionOutput);
```

**QString Usage:**
```cpp
// Prefer QString for all string operations
QString fileName = QFileDialog::getOpenFileName(...);

// Use QString() for empty strings
mPassword = QString();

// String formatting with .arg()
ui->outputTextEdit->append(
    QString("Password: %1 | Hash: %2")
    .arg(password)
    .arg(hash));
```

### Error Handling

```cpp
// Check file existence before operations
if (!mSQLiteDatabase.isEmpty() && QFile::exists(mSQLiteDatabase))
{
    // ... perform database operations
}
else
{
    ui->outputTextEdit->append("<font color='red'>Error: No SQLite database found!</font>");
}

// Validate pointers before dereferencing
if (result)
{
    result->setPassword(line);
    mResults.append(result);
}
```

### Class Structure

```cpp
#ifndef CLASSNAME_H
#define CLASSNAME_H

#include <QMainWindow>  // Base class

// Forward declarations
class PwnedResult;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionExit_triggered();
    void on_checkButton_clicked();

private:
    Ui::MainWindow *ui;
    QString mSQLiteDatabase;
    QSettings *mSettings;
};

#endif // CLASSNAME_H
```

### GPL License Header Template

All source files must include:
```cpp
/*
 * HaveIBeenPwned Local
 * Copyleft 2025
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
```

## CI/CD

GitHub Actions workflows are located in `.github/workflows/`:
- `cmake-windows-latest.yml`: Windows build with Visual Studio 2022
- `cmake-ubuntu-latest.yml`: Ubuntu build with GCC

Both use Qt 6.9.3 and Ninja generator.

## Important Notes

- Application requires an external tool `hibp2sqlite` for database conversion
- Default database paths: `pwned_indexed.sqlite` (Windows), `~/pwned_indexed.sqlite` (Linux)
- Settings stored in INI format via QSettings
- This is a GUI application (`WIN32_EXECUTABLE TRUE` on Windows)
