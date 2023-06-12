/* DEPENDENCIES */

SDL2.h, SDL_image.h, stdio.h <-- main.h <-- main.c
variables.h <-- main.c & variables.o // declares (external variables) & (functions to initialize them in variables.o)

/* OBJECT FILES */

/* initialize() */
initializes sdl2, defines/creates a window, renderer, map_texture, player_texture, playerDestRect, and also draws
to the front buffer by calling SDL_RenderPresent().
