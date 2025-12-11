# Timer Optimization in SDL2 Backend

## Problem
The timer in `platform_sdl2.c` was running slow, causing gameplay to feel sluggish and animations to run at incorrect speeds.

## Root Cause: VSync Interference

The primary issue was that the renderer was created with `SDL_RENDERER_PRESENTVSYNC` flag, which forces rendering to synchronize with the monitor's vertical refresh rate. This caused timing issues:

- Frame presentation is locked to monitor refresh rate (typically 60Hz)
- Added input latency as frames wait for vsync interval
- Can cause stuttering if game loop and monitor refresh don't align
- Interferes with the game's internal timer-based frame pacing

## Solution

### Removed SDL_RENDERER_PRESENTVSYNC

The fix is simple: remove the VSync flag from renderer creation to let the game loop control its own frame timing.

**Change made:**
```c
// Before:
g_renderer = SDL_CreateRenderer(g_window, -1, 
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

// After:
g_renderer = SDL_CreateRenderer(g_window, -1, 
    SDL_RENDERER_ACCELERATED);
```

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
- **Simple Fix**: Minimal code change with maximum impact

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
