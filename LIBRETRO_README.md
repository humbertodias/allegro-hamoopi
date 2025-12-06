# HAMOOPI Libretro Core

This directory contains the libretro port of HAMOOPI, allowing it to run on RetroArch and other libretro frontends.

## Features

The libretro core includes:
- ✅ **Character Selection Screen** - Choose from 4 unique fighters
- ✅ Full 2-player fighting game implementation
- ✅ Physics-based movement (walking, jumping)
- ✅ **Block/Defend Mechanic** - Defend against attacks with B button
- ✅ **Audio Effects** - Sound effects for attacks, jumps, hits, and blocks
- ✅ Combat system with health tracking
- ✅ Real-time gameplay at 60 FPS
- ✅ Title screen and winner announcement
- ✅ Controller/keyboard support for both players

## Building the Libretro Core

### Prerequisites

- GCC/G++ compiler
- Allegro 4 development libraries (`liballegro4-dev` on Debian/Ubuntu)
- Make

### Build Instructions

```bash
make -f Makefile.libretro
```

This will produce `hamoopi_libretro.so` (on Linux), `hamoopi_libretro.dylib` (on macOS), or `hamoopi_libretro.dll` (on Windows).

### Platform-Specific Builds

**Linux:**
```bash
make -f Makefile.libretro platform=unix
```

**macOS:**
```bash
make -f Makefile.libretro platform=osx
```

**Windows (MinGW):**
```bash
make -f Makefile.libretro platform=win
```

## Installing the Core

1. Build the core as described above
2. Copy `hamoopi_libretro.so` to your RetroArch cores directory:
   - Linux: `~/.config/retroarch/cores/`
   - Windows: `retroarch/cores/`
   - macOS: `~/Library/Application Support/RetroArch/cores/`
3. Copy `hamoopi_libretro.info` to your RetroArch info directory:
   - Linux: `~/.config/retroarch/info/`
   - Windows: `retroarch/info/`
   - macOS: `~/Library/Application Support/RetroArch/info/`

## Using the Core

1. Launch RetroArch
2. Go to "Load Core" and select "HAMOOPI"
3. Since HAMOOPI doesn't require content files, you can start it directly from "Start Core"
4. Press START to begin
5. Select your character!

## Game Flow

1. **Title Screen** → Press START to continue
2. **Character Selection** → Choose your fighter (4 characters available)
   - Use LEFT/RIGHT to browse characters
   - Press A button to confirm selection
   - Both players must select before continuing
3. **Fight!** → Battle begins when both players are ready
4. **Winner Screen** → Press START to return to character selection

## Characters

Choose from 4 unique fighters, each with distinct colors:
- **FIRE** (Red) - Aggressive fighter
- **WATER** (Blue) - Balanced fighter  
- **EARTH** (Green) - Defensive fighter
- **WIND** (Yellow) - Speed fighter

## Controls

The libretro core maps standard RetroArch controller buttons to HAMOOPI controls:

### Player 1
- **D-Pad**: 
  - Left/Right: Character selection navigation OR Movement in fight
  - Up: Jump (in fight)
- **A Button**: Confirm character selection OR Punch attack (in fight)
- **B Button**: Block/Defend (in fight) - Reduces damage by 80%
- **Start**: Begin game / Continue

### Player 2
- Same layout as Player 1

## Gameplay

- **Title Screen**: Press START to begin
- **Character Select**: Choose from 4 fighters, press A to confirm
- **Fight**: 
  - Move with D-pad
  - Jump with UP
  - Attack with A button
  - **Block with B button** - Hold to defend (reduces damage to 1 HP, but slows movement)
- **Objective**: Reduce opponent's health to zero
- **Winner Screen**: Press START to return to character selection

Each player starts with 100 HP. Land attacks to damage your opponent!

### Blocking Mechanics
- Hold B button to block incoming attacks
- Blocked attacks deal only 1 damage (vs 5 damage unblocked) - 80% damage reduction
- Movement speed reduced to 50% while blocking
- Cannot jump while blocking
- Cannot attack while blocking
- Visual shield indicator appears when blocking

## Files

- `libretro.cpp` - Main libretro API implementation
- `hamoopi_core.cpp` - Fighting game logic with character selection
- `hamoopi_core.h` - Header file for core functions
- `libretro.h` - Official libretro API header
- `Makefile.libretro` - Build system for the libretro core
- `link.T` - Version script for symbol visibility (Linux)
- `hamoopi_libretro.info` - Core metadata file

## Current Status

This is a fully functional libretro fighting game:
- ✅ Core builds successfully (32KB)
- ✅ Video output working (640x480 @ 60fps)
- ✅ **Audio output fully implemented** - Procedural sound effects at 44.1kHz
- ✅ Input handling implemented (2 players)
- ✅ Frame-based execution
- ✅ **Character selection screen fully integrated**
- ✅ **4 playable characters with unique colors**
- ✅ **Block/Defend mechanic fully implemented**
- ✅ **Audio effects for all actions** (jump, attack, hit, block)
- ✅ **Game logic fully integrated**
- ✅ **Physics engine (gravity, movement, collision)**
- ✅ **Combat system with health management and blocking**
- ✅ **Game states (title, character select, fight, winner)**
- ❌ Save states not implemented
- ⚠️ Full HAMOOPI character system pending (using simple sprites for now)

## Technical Details

The core implements a complete fighting game with:
- **Character Selection**: 4 fighters with distinct visual styles
- **Physics System**: Gravity-based movement, ground collision detection
- **Combat Mechanics**: Attack range detection, health tracking, blocking with damage reduction
- **Blocking System**: B button to defend, 80% damage reduction, visual shield indicator
- **Audio System**: Procedural sound generation at 44.1kHz stereo
  - **Jump Sound**: Rising pitch sweep (200Hz → 600Hz)
  - **Attack Sound**: Sharp percussive with falling pitch
  - **Hit Sound**: Impact noise burst
  - **Block Sound**: Metallic clang effect
- **Game Flow**: Title screen → Character selection → Fight → Winner → Repeat
- **Real-time Rendering**: Direct Allegro rendering at 60 FPS
- **Input Processing**: Frame-accurate controller input via libretro API

## Development Notes

The current implementation uses simplified sprite rendering (rectangles and circles) with color-coding per character to demonstrate the fighting game mechanics and character selection system. The architecture supports extending to full HAMOOPI character sprites and animations by integrating the original game's asset loading and rendering systems.

## License

The libretro core follows the same GPL v2 license as HAMOOPI.

## Contributing

Contributions are welcome! Please see the main HAMOOPI repository for contribution guidelines.
