# HAMOOPI INI Character Configuration System

## Overview

The HAMOOPI libretro core uses INI files to configure character properties, making the game data-driven and easily moddable without code changes.

## INI File Structure

### Location
All character INI files are located in: `chars/CharTemplate/`

### Three Configuration Files

#### 1. char.ini - Animation & Physics Configuration
Defines animation frame timing, sprite alignment, and physics properties for each animation state.

**Format:**
```ini
[StateID]
XAlign = <pixels>           # Sprite horizontal alignment point
YAlign = <pixels>           # Sprite vertical alignment point  
FrameTime_XX = <ticks>      # Duration of frame XX (in game ticks @ 60 FPS)
Hspeed = <float>            # Horizontal velocity
Vspeed = <float>            # Vertical velocity
Gravity = <float>           # Gravity applied per frame
```

**Example:**
```ini
[420]                      # Walk forward animation
XAlign = 31
YAlign = 92
Hspeed = 2                 # Moves 2 pixels/frame forward
FrameTime_00 = 3
FrameTime_01 = 6
FrameTime_02 = 4
```

#### 2. chbox.ini - Collision Box Configuration
Defines per-frame collision boxes (hurtboxes and hitboxes) for precise hit detection.

**Format:**
```ini
[StateID_FrameNum]
HurtBox01x1 = <x>          # Hurtbox 1 top-left X
HurtBox01y1 = <y>          # Hurtbox 1 top-left Y
HurtBox01x2 = <x>          # Hurtbox 1 bottom-right X
HurtBox01y2 = <y>          # Hurtbox 1 bottom-right Y
HitBox01x1 = <x>           # Hitbox 1 top-left X
HitBox01y1 = <y>           # Hitbox 1 top-left Y
HitBox01x2 = <x>           # Hitbox 1 bottom-right X
HitBox01y2 = <y>           # Hitbox 1 bottom-right Y
```

**Example:**
```ini
[151_01]                   # Close punch weak, frame 1
HurtBox01x1 = -14
HurtBox01y1 = -90
HurtBox01x2 = 29
HurtBox01y2 = -1
HitBox01x1 = 13            # Active hitbox during punch
HitBox01y1 = -96
HitBox01x2 = 45
HitBox01y2 = -78
```

#### 3. special.ini - Special Moves Configuration
Defines special move command sequences, damage values, and properties.

**Format:**
```ini
[SpecialID]
name = <string>            # Human-readable name
c1 = <direction>           # Command 1 (numpad notation: 2=down, 3=down-forward, 6=forward, etc.)
c2 = <direction>           # Command 2
c3 = <direction>           # Command 3
b1 = <button>              # Button (1-6=specific, 7=any punch, 8=any kick)
V1_Damage = <int>          # Light version damage
V2_Damage = <int>          # Medium version damage
V3_Damage = <int>          # Heavy version damage
HitType = Normal/Fall      # Hit reaction type
```

**Example:**
```ini
[700]                      # Special move 700 (Hadouken)
name=Hadouken
c1=2                       # Down
c2=3                       # Down-Forward
c3=6                       # Forward
b1=7                       # Any Punch
ThrowFireball = 4
V1_Damage = 100
```

## Implementation Architecture

### Data Structures

```cpp
// Animation frame configuration
typedef struct {
    int state_id;              // Animation state (e.g., 420 for walk forward)
    int xalign, yalign;        // Sprite alignment point
    int frame_times[30];       // Frame durations in ticks
    int frame_count;           // Number of frames
    float hspeed;              // Horizontal velocity
    float vspeed;              // Vertical velocity
    float gravity;             // Gravity per frame
} AnimationConfig;

// Per-frame collision box configuration
typedef struct {
    int state_id;              // Animation state
    int frame_num;             // Frame number
    CollisionBox hurtboxes[5]; // Up to 5 hurtboxes
    CollisionBox hitboxes[3];  // Up to 3 hitboxes
    int hurtbox_count;
    int hitbox_count;
} FrameCollisionConfig;

// Special move configuration
typedef struct {
    int special_id;            // Special move ID (700-790)
    char name[64];             // Human-readable name
    int commands[10];          // Command sequence (numpad notation)
    int command_count;
    int button;                // Required button
    int v1_damage, v2_damage, v3_damage; // Damage values
    int throw_fireball;        // Projectile spawn frame
    float hspeed, vspeed;      // Physics properties
} SpecialMoveConfig;

// Complete character configuration
typedef struct {
    char name[64];
    AnimationConfig animations[50];      // All animation states
    int animation_count;
    FrameCollisionConfig frame_boxes[500]; // All frame boxes
    int frame_box_count;
    SpecialMoveConfig specials[10];      // Up to 10 special moves
    int special_count;
} CharacterConfig;
```

### Loading System

```cpp
// Load character configuration from INI files
CharacterConfig* load_character_config(const char* char_folder) {
    CharacterConfig* config = (CharacterConfig*)malloc(sizeof(CharacterConfig));
    
    char path[256];
    
    // Load char.ini (animation timing and physics)
    snprintf(path, sizeof(path), "%s/char.ini", char_folder);
    load_char_ini(config, path);
    
    // Load chbox.ini (collision boxes)
    snprintf(path, sizeof(path), "%s/chbox.ini", char_folder);
    load_chbox_ini(config, path);
    
    // Load special.ini (special moves)
    snprintf(path, sizeof(path), "%s/special.ini", char_folder);
    load_special_ini(config, path);
    
    return config;
}

// Parse char.ini using Allegro's config functions
void load_char_ini(CharacterConfig* config, const char* path) {
    DATAFILE *dat = load_datafile(path);
    if (!dat) return;
    
    // Iterate through all sections [StateID]
    // Parse XAlign, YAlign, FrameTime_XX, Hspeed, Vspeed, Gravity
    // Store in config->animations[]
    
    unload_datafile(dat);
}
```

### Runtime Usage

```cpp
// During gameplay, query configuration data
AnimationConfig* get_animation_config(CharacterConfig* config, int state_id) {
    for (int i = 0; i < config->animation_count; i++) {
        if (config->animations[i].state_id == state_id) {
            return &config->animations[i];
        }
    }
    return NULL;
}

// Get collision boxes for current animation frame
FrameCollisionConfig* get_frame_boxes(CharacterConfig* config, int state_id, int frame) {
    for (int i = 0; i < config->frame_box_count; i++) {
        if (config->frame_boxes[i].state_id == state_id &&
            config->frame_boxes[i].frame_num == frame) {
            return &config->frame_boxes[i];
        }
    }
    return NULL;
}
```

## Benefits

### Modding Support
- Players can create custom characters without code changes
- Easy to tweak balance (damage, speed, frame timing)
- Artists can iterate on animations independently

### Professional Fighting Game Features
- Per-frame collision box precision
- Command-based special moves
- Configurable physics per animation state
- Multiple collision boxes per frame (HAMOOPI spec supports up to 5 hurtboxes, 3 hitboxes)

### Maintenance
- Game balance changes via INI edits
- No recompilation needed for character tweaks
- Clear separation of data and code

## Animation State IDs (HAMOOPI Specification)

### Close Range (151-156)
- 151: Weak punch
- 152: Medium punch
- 153: Strong punch
- 154: Weak kick
- 155: Medium kick
- 156: Strong kick

### Crouching (200-210)
- 200: Crouch stance
- 201-203: Crouch punches (weak/medium/strong)
- 204-206: Crouch kicks
- 207-210: Crouch blocking

### Air Attacks (300-326)
- 300-306: Neutral jump attacks
- 310-316: Backward jump attacks
- 320-326: Forward jump attacks

### Movement (410-482)
- 410: Walk backward
- 420: Walk forward
- 470-472: Dodge/roll
- 480-482: Running

### Hit Reactions (501-606)
- 501-503: Light/medium/strong hit
- 550-552: Falling/bouncing/getting up
- 601-608: Transition states

### Celebrations (610-618)
- 610: Intro
- 611-614: Victory poses
- 615: Time over loss

### Special Moves (700+)
- 700-790: Up to 10 special moves per character
- Each special can have sub-states (e.g., 701=fireball, 702=fireball hit spark)

## Numpad Notation for Commands

```
7   8   9        Up-Back    Up    Up-Forward
 \  |  /              \     |     /
  \ | /                \    |    /
4 -   - 6    =    Back - Neutral - Forward
  / | \                /    |    \
 /  |  \              /     |     \
1   2   3        Down-Back Down Down-Forward
```

**Common Special Move Patterns:**
- Quarter Circle Forward: 2,3,6 + Button (Hadouken)
- Quarter Circle Back: 2,1,4 + Button
- Dragon Punch: 6,2,3,6 + Button (Shoryuken)
- Half Circle: 4,1,2,3,6 + Button

## File Format Details

### char.ini Timing System
- All frame times are in game ticks @ 60 FPS
- FrameTime value of 99 = hold indefinitely (used for air states)
- Hspeed/Vspeed in pixels per frame
- Gravity typically 0.6 (standard fighting game feel)

### chbox.ini Coordinate System
- Origin point is character's XAlign/YAlign position
- Negative Y = upward from origin
- Multiple boxes per frame allowed (HurtBox01, HurtBox02, etc.)
- Coordinates are relative to sprite alignment point

### special.ini Damage System
- Base damage values: DMG1=50, DMG2=100, DMG3=150
- Custom damage overrides per special move
- V1/V2/V3 correspond to light/medium/heavy button strength

## Current Implementation Status

✅ **Implemented:**
- Sprite loading system from PCX files
- Animation state machine with HAMOOPI state IDs
- Basic collision detection
- Character selection (4 characters)

🔨 **In Progress:**
- INI parsing infrastructure
- Dynamic collision box loading from chbox.ini
- Configurable animation timing from char.ini
- Special move command detection from special.ini

📋 **Planned:**
- Full per-frame collision box system
- Command buffer for special move input detection
- Multiple special moves per character
- Hit type system (Normal/Fall)
- Combo system

## Extension Guide

### Adding New Animation States

1. Create PCX sprite files: `{state_id}_{frame}.pcx`
2. Add entry to char.ini with timing
3. Add per-frame collision boxes to chbox.ini
4. Map game state to animation in code

### Creating Custom Special Moves

1. Choose special ID (700-790)
2. Define command sequence in special.ini
3. Set damage values (V1/V2/V3_Damage)
4. Create animation frames (700_00.pcx, 700_01.pcx, etc.)
5. Add collision boxes for each frame in chbox.ini
6. Optional: Add projectile state (701, 702, etc.) for fireball-style specials

### Character Balancing

Common balance adjustments via INI:
- **Speed**: Adjust Hspeed in movement animations (410, 420)
- **Jump height**: Modify Vspeed in jump animations (300, 310, 320)
- **Attack damage**: Change V1/V2/V3_Damage in special.ini
- **Frame advantage**: Adjust FrameTime values for faster/slower attacks
- **Hitbox size**: Modify collision box coordinates in chbox.ini

## References

- HAMOOPI Specification: Original 2D fighting game engine specification
- Animation State IDs: See section above for complete list
- Numpad Notation: Standard fighting game community notation
- Collision System: See HITBOX_SYSTEM_SUMMARY.md

## Future Enhancements

- **Chain cancels**: Define cancel windows in char.ini
- **Juggle system**: Add juggle point tracking
- **Guard damage**: Configurable chip damage per move
- **Priority system**: Define move priorities for clash resolution
- **Sound effects**: Link sound IDs to animation frames
- **Visual effects**: Spawn effect sprites at specific frames
- **Camera shake**: Define shake intensity per hit
- **Hitstun/Blockstun**: Configurable frame advantage data

This INI-based system provides the foundation for a fully moddable, professional-quality 2D fighting game within the libretro ecosystem.
