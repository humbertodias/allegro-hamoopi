# HAMOOPI Code Organization

## Overview

The HAMOOPI codebase has been organized into a modular structure to improve maintainability and code clarity. While the main game logic remains in `HAMOOPI.c` (11,748 lines), the code is now structured with clear header files that define the logical modules.

## Module Structure

### Core Files

- **`HAMOOPI.c`** - Main game file containing the game loop, initialization, and all function implementations
- **`hamoopi_core.h`** - Central header that includes all modular components

### Modular Headers

#### 1. `hamoopi_types.h`
Defines all game structures and types:
- `struct HitSparkDEF` - Hit spark effect data
- `struct FireballsDEF` - Projectile data
- `struct PlayerDEF` - Complete player state and animation data

#### 2. `hamoopi_input.h`
Input handling function declarations:
- `check_keys_P1()` - Process Player 1 input
- `check_keys_P2()` - Process Player 2 input
- `MovSlots_P1()` - Manage Player 1 input buffer
- `MovSlots_P2()` - Manage Player 2 input buffer
- `zeraListaDeInputs()` - Clear input list

#### 3. `hamoopi_collision.h`
Collision detection and hit box management:
- `Checar_Colisao()` - Check for collisions between players
- `Aplicar_HIT()` - Apply hit effects and damage
- `Draw_CHBoxes_P1()` - Draw Player 1 collision boxes (debug)
- `Draw_CHBoxes_P2()` - Draw Player 2 collision boxes (debug)
- `Draw_CHBoxes_ED()` - Draw Editor collision boxes

#### 4. `hamoopi_player.h`
Player state and animation management:
- `LOAD_PLAYERS()` - Load player character data
- `PLAYER_STATE()` - Change player animation state
- `AddTableAtlas()` - Add animation frame to atlas
- `New_Fireball()` - Create a new projectile
- `New_HitBox()` - Create new hit boxes

#### 5. `hamoopi_editor.h`
Character editor functions:
- `ED_inicializar()` - Initialize the editor
- `ED_save_charini()` - Save character configuration
- `ED_load_charini()` - Load character configuration
- `ED_load_inputs()` - Load special move inputs

## File Organization in HAMOOPI.c

The main file is organized into these sections (marked with `[**NN]` tags):

1. **[**01]** Initial Declarations - Constants, globals, and structure definitions
2. **[**02]** Allegro Initialization - Graphics and sound system setup
3. **[**03]** Game Loop - Main game logic and state management
4. **[**04]** Collision System - (integrated into game loop)
5. **[**05]** FSM (Finite State Machine) - Character state management
6. **[**06]** Difs - Parameter changes and modifications
7. **[**07]** Drawing Functions - Rendering logic
8. **[**08]** Debug - Debug visualization
9. **[**09]** Edit Mode - Character editor
10. **[**10]** Finalization - Cleanup and resource deallocation
11. **[**11]** Check Keys - Input processing functions (lines 7359-7943)
12. **[**12]** States (Chg) - State change functions (lines 7945+)

## Benefits of This Organization

1. **Improved Navigation** - Developers can quickly find function declarations by module
2. **Clear Responsibilities** - Each header file represents a logical subsystem
3. **Better Documentation** - Headers serve as API documentation
4. **Future Refactoring** - Provides a foundation for further code splitting if needed
5. **Minimal Changes** - All existing code continues to work without modification

## Usage

To include the modular structure in new files:

```c
#include "hamoopi_core.h"  // Includes all modules
```

Or include specific modules:

```c
#include "hamoopi_types.h"
#include "hamoopi_input.h"
// etc.
```

## Future Improvements

While the current organization improves code clarity through headers, future refactoring could:

1. Extract functions into separate `.c` files with proper extern declarations
2. Reduce global state by passing structures as parameters
3. Create a proper game engine API with initialization/update/render functions
4. Split the 11,748-line file into multiple implementation files

## Compilation

The modular structure doesn't affect compilation. The project continues to use:

- **CMake** for build configuration (see `CMakeLists.txt`)
- **Make** for simplified building (see `Makefile`)
- Supports both SDL2 and Allegro 4 backends

Build with:
```bash
make build
```

Or using CMake directly:
```bash
cmake -B build
cmake --build build
```
