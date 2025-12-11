# Timer Optimization in SDL2 Backend

## Problem
The timer in `platform_sdl2.c` was running slow, causing gameplay to feel sluggish and animations to run at incorrect speeds.

## Final Solution: Pure Polling-Based Timer

After testing with the threaded timer approach (SDL_AddTimer) and hybrid solutions, the most reliable and performant solution is to use a **pure polling-based timer** using `SDL_GetPerformanceCounter()`.

### Why Pure Polling?

1. **No Thread Overhead**: SDL_AddTimer runs in a separate thread with context switching overhead
2. **Deterministic Timing**: Polling in the main thread provides more predictable timing
3. **Better Performance**: Eliminates thread management and callback marshalling overhead
4. **Simpler Code**: Single timer path without fallback complexity

## Root Causes (Previous Issues)

### 1. SDL_AddTimer Thread Overhead
Using SDL_AddTimer introduced threading overhead:
- Timer callback runs in separate thread, separate from game logic
- Context switching between threads adds latency
- Unpredictable timing due to OS thread scheduling

### 2. Critical Bug in check_timer() Function (Now Fixed)
The polling function had a bug where it only called the callback ONCE even when multiple intervals had elapsed:

**Example of the bug:**
- Game expects 60 FPS (timer should increment 60 times per second)
- If `check_timer()` is called after 3 intervals (50ms elapsed)
- **Old behavior**: Fired callback once → timer incremented by 1 → WRONG!
- **New behavior**: Fires callback 3 times → timer increments by 3 → CORRECT!

### 3. VSync Limitation (Fixed)
The renderer was created with `SDL_RENDERER_PRESENTVSYNC` which added frame presentation delays.

## Solution

### Final Implementation: Pure Polling-Based Timer

The SDL2 backend now uses **only** polling with `SDL_GetPerformanceCounter()` for maximum performance and accuracy. SDL_AddTimer has been completely removed.

**Key changes:**

1. **Removed SDL_AddTimer completely**
   ```c
   // Removed:
   // - static SDL_TimerID g_timer_id = 0;
   // - static Uint32 timer_callback_wrapper()
   // - SDL_AddTimer() call
   // - SDL_RemoveTimer() calls
   
   // Now using pure polling
   static Uint64 g_timer_last_tick = 0;
   static Uint64 g_timer_interval_ticks = 0;
   ```

2. **Simplified platform_install_int_ex()**
   ```c
   void platform_install_int_ex(void (*callback)(void), int interval_us) {
       g_timer_callback = callback;
       
       // Convert interval to performance counter ticks
       Uint64 freq = SDL_GetPerformanceFrequency();
       g_timer_interval_ticks = ((Uint64)interval_us * freq) / 1000000ULL;
       g_timer_last_tick = SDL_GetPerformanceCounter();
   }
   ```

3. **Fixed check_timer() to call callback for each elapsed interval**
   ```c
   static void check_timer(void) {
       if (g_timer_callback && g_timer_interval_ticks > 0) {
           Uint64 current_tick = SDL_GetPerformanceCounter();
           Uint64 elapsed_ticks = current_tick - g_timer_last_tick;
           
           if (elapsed_ticks >= g_timer_interval_ticks) {
               Uint64 intervals_elapsed = elapsed_ticks / g_timer_interval_ticks;
               
               // Fire callback for each elapsed interval (capped)
               Uint64 callbacks_to_fire = intervals_elapsed;
               if (callbacks_to_fire > MAX_TIMER_CALLBACKS_PER_CHECK) {
                   callbacks_to_fire = MAX_TIMER_CALLBACKS_PER_CHECK;
               }
               
               for (Uint64 i = 0; i < callbacks_to_fire; i++) {
                   g_timer_callback();
               }
               
               g_timer_last_tick += intervals_elapsed * g_timer_interval_ticks;
           }
       }
   }
   ```

4. **Call check_timer() in platform_get_key_state()**
   ```c
   volatile char* platform_get_key_state(void) {
       SDL_PumpEvents();
       check_timer();  // Poll timer every time keys are checked
       // ... rest of function
   }
   ```

5. **Removed SDL_RENDERER_PRESENTVSYNC**
   ```c
   // Before:
   g_renderer = SDL_CreateRenderer(g_window, -1, 
       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   
   // After:
   g_renderer = SDL_CreateRenderer(g_window, -1, 
       SDL_RENDERER_ACCELERATED);
   ```

## Benefits

- **Maximum Performance**: Pure polling eliminates thread overhead from SDL_AddTimer
- **Deterministic Timing**: Timer runs in main thread with predictable behavior
- **Accurate 60 FPS**: Timer correctly increments for each elapsed interval
- **No Thread Synchronization**: Eliminates potential race conditions and context switching
- **Simpler Code**: Single timer implementation path without fallback complexity
- **Reduced Latency**: No VSync-induced frame delays
- **Consistent Behavior**: Game loop timing is independent of monitor refresh rate

## Comparison: SDL2 vs Allegro

| Aspect | Allegro 4 | SDL2 (New) |
|--------|-----------|------------|
| Timer Type | Hardware timer with OS support | Pure polling with SDL_GetPerformanceCounter() |
| Implementation | install_int_ex() → OS timer | Polling in platform_get_key_state() |
| Thread Model | Timer callback in separate thread | Main thread polling |
| Accuracy | OS-dependent, generally good | High precision, main-thread deterministic |
| Overhead | Low (hardware timer) | Very low (simple counter check) |

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
