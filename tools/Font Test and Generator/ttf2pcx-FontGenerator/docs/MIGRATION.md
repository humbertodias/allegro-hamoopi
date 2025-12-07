# Migration Guide: MFC to Qt

This document explains how the original MFC codebase was migrated to the new Qt implementation.

**Note:** The original MFC files have been removed from the repository. This tool is now Qt-only and cross-platform.

## File Mapping

### MFC (Windows-only) → Qt (Cross-platform)

| Original MFC Files | New Qt Files | Description |
|-------------------|--------------|-------------|
| `ttf2pcx.cpp/h` | `main.cpp` | Application entry point and initialization |
| `ttf2pcxdlg.cpp/h` | `mainwindow.cpp/h` | Main dialog/window with UI and logic |
| `character.cpp/h` | `character_qt.cpp/h` | Character rendering (Windows GDI → Qt) |
| `previewbutton.cpp/h` | `previewwidget.cpp/h` | Font preview control |
| `stdafx.cpp/h` | *removed* | MFC precompiled headers (not needed in Qt) |
| `resource.h` | *removed* | MFC resource definitions (not needed in Qt) |
| `ttf2pcx.rc` | *removed* | MFC resource file (Qt uses code-based UI) |
| `*.dsp, *.dsw` | `CMakeLists.txt` | Build system (Visual Studio → CMake) |
| `readme.txt` | `README.md` | Documentation |

## Key Changes

### 1. UI Framework
- **MFC**: Dialog-based application using resource files and ClassWizard
- **Qt**: QMainWindow with layouts and widgets created in code

### 2. Font Rendering
- **MFC**: Windows GDI (CDC, CBitmap, GetTextExtentPoint32W)
- **Qt**: QPainter, QImage, QFontMetrics (cross-platform)

### 3. Memory Management
- **MFC**: CString, CFont, manual new/delete
- **Qt**: QString, QFont, RAII with std::vector

### 4. File Dialogs
- **MFC**: CFileDialog
- **Qt**: QFileDialog

### 5. Message Boxes
- **MFC**: AfxMessageBox
- **Qt**: QMessageBox

### 6. Application Structure
- **MFC**: CWinApp + CDialog (modal)
- **Qt**: QApplication + QMainWindow

## Preserved Functionality

The following remain **identical** to ensure compatibility with Allegro:

- PCX file format and encoding
- Antialiasing algorithm (8x8 supersampling)
- Character range support (1-65535)
- Palette generation for antialiased output
- Character layout in output file (16x16 grid)

## Building

### Original (MFC) - No Longer Available
The original MFC version required Visual C++ 6 and was Windows-only. It has been replaced by the Qt version.

### Current (Qt)
```bash
# Works on Linux, Windows, macOS
mkdir build && cd build
cmake ..
make  # or: cmake --build .
```

## Testing

The Qt version includes automated tests:
- `test_core.cpp`: Tests character rendering and core functionality
- `test.sh`: Basic smoke test for application startup

Run tests:
```bash
cd build
./test_core
```
