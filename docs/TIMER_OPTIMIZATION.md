# Timer Optimization in SDL2 Backend

## Problem
The timer in `platform_sdl2.c` was running slow, causing gameplay to feel sluggish and animations to run at incorrect speeds. The issue was particularly noticeable on macOS.

## Root Cause: VSync Interference

The primary issue was that the renderer was created with `SDL_RENDERER_PRESENTVSYNC` flag, which forces rendering to synchronize with the monitor's vertical refresh rate. This caused timing issues:

- Frame presentation is locked to monitor refresh rate (typically 60Hz)
- Added input latency as frames wait for vsync interval
- Can cause stuttering if game loop and monitor refresh don't align
- Interferes with the game's internal timer-based frame pacing

## Platform-Specific Issues

### macOS Timer Performance
macOS has known issues with SDL2 timer precision:
- SDL_AddTimer callbacks can have higher latency on macOS
- Thread scheduling on macOS may delay timer callbacks
- Metal renderer provides better performance than OpenGL

## Solution

### 1. Removed SDL_RENDERER_PRESENTVSYNC

The primary fix: remove the VSync flag from renderer creation to let the game loop control its own frame timing.

**Change made:**
```c
// Before:
g_renderer = SDL_CreateRenderer(g_window, -1, 
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

// After:
g_renderer = SDL_CreateRenderer(g_window, -1, 
    SDL_RENDERER_ACCELERATED);
```

### 2. macOS-Specific Optimizations

**Enable Metal renderer on macOS:**
```c
#ifdef __APPLE__
    // On macOS, prefer Metal renderer for better performance
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
#endif
```

**Hybrid timer approach on macOS:**
```c
#ifdef __APPLE__
    check_timer();  // Always poll on macOS for better timing
#else
    if (g_timer_id == 0) {
        check_timer();  // Only poll as fallback on other platforms
    }
#endif
```

This combines SDL_AddTimer with polling on macOS to ensure consistent timer updates even if the threaded timer has delays.

## Why This Works

The game uses its own timer-based frame pacing with SDL_AddTimer:
1. Timer callback increments a global `timer` variable at 60 FPS
2. Game loop waits: `while (timer == delay) {}`
3. This provides precise 60 FPS timing independent of display refresh rate

With VSync enabled, frame presentation conflicts with this internal timing, causing slowdown. Removing VSync allows the game's timer to control the frame rate properly.

## Benefits

- **Correct 60 FPS**: Timer-controlled frame pacing works as designed
- **No VSync Delays**: Frames present immediately without waiting for vsync
- **Reduced Latency**: No additional frame buffering delays
- **Cross-Platform**: Works correctly on displays with any refresh rate
- **macOS Optimized**: Metal renderer and hybrid timer approach for better macOS performance
- **Simple Fix**: Minimal code changes with maximum impact
- **No Crashes**: Original timer logic preserved, no black screens or freezing

## Platform-Specific Behavior

| Platform | Timer Approach | Renderer |
|----------|---------------|----------|
| Linux | SDL_AddTimer with polling fallback | OpenGL |
| macOS | SDL_AddTimer + always-on polling | Metal (preferred) |
| Windows | SDL_AddTimer with polling fallback | Direct3D/OpenGL |

The hybrid approach on macOS compensates for platform-specific timer latency issues.

## Timer Implementation Details

The SDL2 backend uses SDL_AddTimer for accurate timing:
- `SDL_AddTimer()` creates a threaded timer that fires at 60 FPS
- Timer callback increments the game's timer variable
- Fallback to `check_timer()` polling if SDL_AddTimer fails
- Original Allegro timer implementation unchanged

## Testing

To verify the optimization:

1. Build the game with SDL2 backend: `make`
2. Run the game and observe:
   - Smooth 60 FPS gameplay
   - Responsive controls
   - Correct animation timing
   - No black screens or freezing

## Notes

- Timer uses SDL_AddTimer() for threaded callbacks at 60 FPS
- Fallback to polling with check_timer() if SDL_AddTimer fails
- VSync removal was the key optimization
- Allegro backend timer implementation unchanged
