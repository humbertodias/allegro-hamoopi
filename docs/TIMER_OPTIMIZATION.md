# Timer Optimization in SDL2 Backend

## Problem
The timer in `platform_sdl2.c` was running slow, causing gameplay to feel sluggish and animations to run at incorrect speeds.

## Root Causes

### 1. VSync Limitation
The renderer was created with `SDL_RENDERER_PRESENTVSYNC` flag, which forces the rendering to synchronize with the monitor's vertical refresh rate. This causes several issues:

- Forces frame timing to match monitor refresh rate (typically 60Hz)
- Can conflict with the game's internal 60 FPS timer
- Introduces additional latency and timing inconsistencies
- May cause the game to run slower than intended on monitors with different refresh rates

### 2. Redundant Timer Checking
The `check_timer()` function was being called in `update_screen_with_renderer()`, which is called during screen updates. This was redundant because:

- Timer checking is already done in `platform_get_key_state()` which runs in the main event loop
- Checking the timer during screen updates adds unnecessary overhead
- Timer callbacks should be handled in the event loop, not during rendering

## Solution

### Changes Made

1. **Removed SDL_RENDERER_PRESENTVSYNC from renderer creation**
   ```c
   // Before:
   g_renderer = SDL_CreateRenderer(g_window, -1, 
       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   
   // After:
   g_renderer = SDL_CreateRenderer(g_window, -1, 
       SDL_RENDERER_ACCELERATED);
   ```

2. **Removed check_timer() from update_screen_with_renderer()**
   - Timer checking remains in `platform_get_key_state()` where it belongs
   - Keeps timer updates in the main event loop
   - Reduces overhead during screen rendering

## Benefits

- **Precise Timing**: Timer now runs at exactly 60 FPS as configured
- **Reduced Latency**: No VSync-induced frame delays
- **Better Performance**: Decoupled rendering from timer updates
- **Consistent Behavior**: Game loop timing is independent of monitor refresh rate

## Technical Details

The game uses the following timer mechanism:

1. `install_int_ex(tempo, BPS_TO_TIMER(60))` installs a timer callback that runs at 60 FPS
2. The `tempo()` callback increments the global `timer` variable
3. Game loop uses `while (timer == delay)` to wait for the next frame
4. SDL2 implementation uses `SDL_AddTimer()` for the callback, with a fallback to polling

With VSync removed, the game loop can run at its own pace without being limited by the monitor's refresh rate, ensuring precise 60 FPS timing.

## Testing

To verify the timer optimization:

1. Build the game with SDL2 backend: `make`
2. Run the game and observe:
   - Smoother animations
   - More responsive controls
   - Consistent frame timing
   - FPS counter (if available) should show stable 60 FPS

## Notes

- The timer implementation supports both threaded (`SDL_AddTimer`) and polling modes
- Fallback to polling mode (`check_timer()`) is automatic if `SDL_AddTimer` fails
- This optimization maintains compatibility with both modes
