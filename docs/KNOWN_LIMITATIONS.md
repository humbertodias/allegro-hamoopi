# Known Limitations and Future Improvements

This document describes the current limitations of the backend abstraction layer and suggests improvements for future iterations.

## Current Limitations

### 1. KeyCode Mapping Dependency

**Issue**: The `AllegroInputBackend` currently maps abstract `KeyCode` enums directly to Allegro's `KEY_*` constants. This creates a circular dependency where the abstraction layer depends on Allegro-specific values.

**Impact**: 
- The input abstraction is not fully library-agnostic
- Makes porting to other libraries more complex

**Current Workaround**: 
- The mapping works correctly for Allegro
- Maintains backward compatibility with existing code

**Future Improvement**:
```cpp
// Instead of mapping KeyCode::KEY_A to Allegro's KEY_A,
// use backend-agnostic integer codes:
enum KeyCode {
    KEY_A = 1,
    KEY_B = 2,
    // etc.
};

// Then each backend does its own translation:
class AllegroInputBackend {
    int allegroKeyMap[KEY_MAX] = {
        [KEY_A] = KEY_A,  // Allegro constant
        [KEY_B] = KEY_B,
        // etc.
    };
};
```

### 2. Background Color in Text Rendering

**Issue**: The compatibility wrapper functions `wrapper_textout_ex` and `wrapper_textout_centre_ex` accept a background color parameter for compatibility with Allegro's API, but this parameter is silently ignored.

**Impact**:
- Code that relies on non-transparent text backgrounds will not work as expected
- May cause visual differences when migrating code

**Current Workaround**:
- Well-documented in comments
- Suggests using `rectfill` to draw background before text
- Parameter is explicitly marked as unused

**Future Improvement**:
```cpp
// Add background color support to the graphics backend interface:
virtual void textout_with_bg(GraphicsBitmap bitmap, GraphicsFont font, 
                             const char* text, int x, int y, 
                             int fg_color, int bg_color) = 0;

// Or add runtime validation:
inline void wrapper_textout_ex(..., int bg) {
    if (bg != -1) {
        fprintf(stderr, "WARNING: Background color %d ignored in textout\n", bg);
    }
    // ... rest of code
}
```

### 3. Partial Backend Initialization

**Issue**: If backend initialization fails partway through, some backends may be initialized while others are not.

**Status**: ✅ FIXED
- Now properly cleans up successfully initialized backends on failure
- System is left in a consistent state

### 4. Static Global Backend Pointer

**Issue**: The `g_backend` global pointer could cause issues in multi-threaded environments or when multiple engine instances are needed.

**Impact**:
- Not thread-safe
- Cannot run multiple game instances in the same process
- Could cause issues with unit tests

**Current Workaround**:
- Works fine for single-threaded game execution
- Sufficient for current HAMOOPI usage

**Future Improvement**:
```cpp
// Pass backend manager as parameter instead of using global:
class GameEngine {
    BackendManager* backends;
public:
    GameEngine(BackendManager* mgr) : backends(mgr) {}
    // Use backends-> instead of g_backend->
};
```

### 5. Limited Graphics Backend Interface

**Issue**: The current graphics backend interface covers basic 2D operations but lacks support for:
- Hardware acceleration
- Shaders
- Advanced blending modes
- Texture filtering options
- Render targets
- Z-ordering/depth

**Impact**:
- Cannot easily add modern graphics features
- Limited to Allegro 4's capabilities

**Future Improvement**:
Add extended interfaces for modern features:
```cpp
class ModernGraphicsBackend : public GraphicsBackend {
public:
    virtual void set_shader(ShaderProgram* shader) = 0;
    virtual void set_blend_mode(BlendMode mode) = 0;
    virtual GraphicsBitmap create_render_target(int w, int h) = 0;
    // etc.
};
```

### 6. No Audio Streaming Support

**Issue**: Current audio backend only supports loading entire samples into memory.

**Impact**:
- High memory usage for long audio files
- Cannot stream background music
- Limited to small sound effects

**Future Improvement**:
```cpp
class AudioBackend {
public:
    virtual AudioStream* create_stream(const char* filename) = 0;
    virtual void play_stream(AudioStream* stream) = 0;
    virtual void stop_stream(AudioStream* stream) = 0;
};
```

### 7. Synchronous File Loading

**Issue**: All resource loading (bitmaps, fonts, samples) is synchronous and blocks execution.

**Impact**:
- Long loading times for large assets
- Potential for frame drops during loading
- Cannot show loading progress

**Future Improvement**:
```cpp
// Add async loading support:
virtual AsyncHandle load_bitmap_async(const char* filename) = 0;
virtual bool is_loaded(AsyncHandle handle) = 0;
virtual GraphicsBitmap get_loaded_bitmap(AsyncHandle handle) = 0;
```

## Non-Issues (Working as Designed)

### 1. Direct Allegro Usage in HAMOOPI.cpp

**Status**: Expected
- The main game file still uses Allegro directly
- This is intentional for Phase 1 of the migration
- Gradual migration will happen in future phases

### 2. No Breaking Changes

**Status**: Feature, not bug
- 100% backward compatibility maintained
- Original code works without modifications
- This is a design goal, not a limitation

## Mitigation Strategies

### Short Term (Current Release)
- ✅ Document all limitations clearly
- ✅ Provide workarounds where possible
- ✅ Add warnings for ignored parameters
- ✅ Ensure clean error handling

### Medium Term (Next Release)
- Implement proper KeyCode translation system
- Add background color support to text rendering
- Improve error reporting and logging
- Add runtime validation for ignored parameters

### Long Term (Future Versions)
- Extend backend interfaces for modern features
- Implement async resource loading
- Add audio streaming support
- Support multiple backend instances
- Thread-safe backend management

## Backward Compatibility Promise

Despite these limitations, we commit to:
1. **No Breaking Changes**: Existing code continues to work
2. **Clear Migration Path**: Documented steps for adopting new features
3. **Gradual Improvements**: Limitations addressed incrementally
4. **Transparent Communication**: All limitations documented

## Contributing

If you want to help address these limitations:
1. Check the issue tracker for related tasks
2. Propose design improvements in discussions
3. Submit PRs with proper tests and documentation
4. Maintain backward compatibility

## References

- [Backend Architecture](BACKEND_ARCHITECTURE.md)
- [Architecture Diagram](ARCHITECTURE_DIAGRAM.md)
- [Decoupling Summary](DECOUPLING_SUMMARY.md)
