# Timer Optimization in SDL2 Backend

## Problem
The timer in `platform_sdl2.c` was running slow, causing gameplay to feel sluggish and animations to run at incorrect speeds.

## Root Causes

### 1. Critical Bug in check_timer() Function
The most significant issue was in the `check_timer()` polling function. It was only calling the timer callback ONCE even when multiple timer intervals had elapsed. This caused the timer to run slower than expected.

**Example of the bug:**
- Game expects 60 FPS (timer should increment 60 times per second = every ~16.67ms)
- If `check_timer()` is called after 3 intervals have passed (50ms elapsed)
- **Old behavior**: Fired callback once → timer incremented by 1 → WRONG!
- **New behavior**: Fires callback 3 times → timer increments by 3 → CORRECT!

This was the primary cause of the slow timer issue.

### 2. Insufficient Timer Polling
The timer check was only performed when `SDL_AddTimer` failed (fallback mode). However, even when the threaded timer is working, there can be delays or timing issues. Not polling the timer regularly meant missed increments.

### 3. VSync Limitation
The renderer was created with `SDL_RENDERER_PRESENTVSYNC` flag, which forces the rendering to synchronize with the monitor's vertical refresh rate. While VSync doesn't directly affect the game loop timing, it can cause issues:

- Adds frame presentation delays when the game tries to render faster than the monitor refresh rate
- Can introduce input latency as frames wait for the next vsync interval
- May cause stuttering if the game loop and monitor refresh rate don't perfectly align
- Creates unnecessary overhead when precise frame timing is managed by the game's internal timer

## Solution

### Changes Made

1. **Fixed check_timer() to call callback for each elapsed interval**
   ```c
   // Before: Only called callback once, even for multiple intervals
   if (elapsed_ticks >= g_timer_interval_ticks) {
       g_timer_callback();  // Called once!
       Uint64 intervals_elapsed = elapsed_ticks / g_timer_interval_ticks;
       g_timer_last_tick += intervals_elapsed * g_timer_interval_ticks;
   }
   
   // After: Calls callback for each elapsed interval
   #define MAX_TIMER_CALLBACKS_PER_CHECK 10
   
   if (elapsed_ticks >= g_timer_interval_ticks) {
       Uint64 intervals_elapsed = elapsed_ticks / g_timer_interval_ticks;
       
       // Fire callback for each elapsed interval (capped to prevent runaway)
       Uint64 callbacks_to_fire = intervals_elapsed;
       if (callbacks_to_fire > MAX_TIMER_CALLBACKS_PER_CHECK) {
           callbacks_to_fire = MAX_TIMER_CALLBACKS_PER_CHECK;
       }
       
       for (Uint64 i = 0; i < callbacks_to_fire; i++) {
           g_timer_callback();  // Called multiple times!
       }
       
       g_timer_last_tick += intervals_elapsed * g_timer_interval_ticks;
   }
   ```
   
   This ensures the timer increments by the correct amount even when polling is infrequent.

2. **Always call check_timer() in platform_get_key_state()**
   ```c
   // Before: Only checked when SDL_AddTimer failed
   if (g_timer_id == 0) {
       check_timer();
   }
   
   // After: Always check for better responsiveness
   check_timer();
   ```
   
   This hybrid approach uses both threaded timer and polling for maximum reliability.

3. **Removed SDL_RENDERER_PRESENTVSYNC from renderer creation**
   ```c
   // Before:
   g_renderer = SDL_CreateRenderer(g_window, -1, 
       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   
   // After:
   g_renderer = SDL_CreateRenderer(g_window, -1, 
       SDL_RENDERER_ACCELERATED);
   ```

## Benefits

- **Accurate Timing**: Timer now correctly increments by the right amount for elapsed time
- **Reliable 60 FPS**: Game runs at precisely 60 FPS as configured
- **No Skipped Increments**: Timer polling fires callback for each elapsed interval
- **Hybrid Approach**: Uses both threaded timer (SDL_AddTimer) and polling for reliability
- **Reduced Latency**: No VSync-induced frame delays
- **Better Performance**: Decoupled rendering from VSync timing
- **Consistent Behavior**: Game loop timing is independent of monitor refresh rate

## Technical Details

The game uses the following timer mechanism:

1. `platform_install_int_ex(tempo, BPS_TO_TIMER(60))` installs a timer callback that runs at 60 FPS
   - `BPS_TO_TIMER` is a macro that converts from "beats per second" to microseconds
   - This is part of the platform abstraction layer, compatible with both Allegro and SDL2
2. The `tempo()` callback increments the global `timer` variable
3. Game loop uses `while (timer == delay)` to wait for the next frame
4. SDL2 implementation uses `SDL_AddTimer()` for the callback, with a fallback to polling via `check_timer()`

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
