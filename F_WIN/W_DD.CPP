#include "w_all.h"
#include <SDL.h>
#include <SDL_syswm.h>

SDL_Surface* SDLSurfaceMain;
SDL_Surface* SDLSurfacePaletted;
SDL_Window* SDLWindow;

// Ha igaz, alulrol indul y (kirajz320 allitja igazba):
int Locky0_alul = 0;

/*void uzenet( char* text1, char* text2, char* text3 ) {
    hiba( text1, text2, text3 );
} */

int sdl_init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        printf("[%s]\n", SDL_GetError());
        return 1;
    }

    SDLWindow = SDL_CreateWindow("Elasto Mania", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 640, 480, 0);
    if (!SDLWindow) {
        printf("[%s]\n", SDL_GetError());
        return 1;
    }

    SDL_EventState(SDL_DROPFILE, SDL_DISABLE);
    SDL_EventState(SDL_DROPTEXT, SDL_DISABLE);

    SDLSurfaceMain = SDL_GetWindowSurface(SDLWindow);
    if (!SDLSurfaceMain) {
        printf("[%s]\n", SDL_GetError());
        return 1;
    }
    SDL_LockSurface(SDLSurfaceMain);
    for (int i = 0; i < (SDLSurfaceMain->w * SDLSurfaceMain->h * 4); i++) {
        ((unsigned char*)SDLSurfaceMain->pixels)[i] = 0xFF;
    }
    SDL_UnlockSurface(SDLSurfaceMain);
    SDL_UpdateWindowSurface(SDLWindow);

    SDLSurfacePaletted = SDL_CreateRGBSurfaceWithFormat(0, SDLSurfaceMain->w, SDLSurfaceMain->h, 0,
                                                        SDL_PIXELFORMAT_INDEX8);
    if (!SDLSurfacePaletted) {
        printf("[%s]\n", SDL_GetError());
        return 1;
    }

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(SDLWindow, &wmInfo);
    GhWnd = wmInfo.info.win.window;

    return 0;
}

static unsigned char* Mutbuffer[480];
static int Bufflocked = 0;

unsigned char** lockbackbuffer(int fizikai) {
    fizikai++;

    if (Bufflocked) {
        hiba("lockbackbuffer-ben Bufflocked!");
    }
    Bufflocked = 1;

    unsigned char* mut = (unsigned char*)SDLSurfacePaletted->pixels;
    if (Locky0_alul) {
        // Load screen upside-down
        for (int y = 0; y < 480; y++) {
            Mutbuffer[480 - 1 - y] = mut;
            mut += SDLSurfacePaletted->w;
        }
    } else {
        // Load screen rightside-up
        for (int y = 0; y < 480; y++) {
            Mutbuffer[y] = mut;
            mut += SDLSurfacePaletted->w;
        }
    }
    return Mutbuffer;
}

void unlockbackbuffer(void) {
    if (!Bufflocked) {
        hiba("unlockbackbuffer-ben !Bufflocked!");
    }
    Bufflocked = 0;

    SDL_BlitSurface(SDLSurfacePaletted, NULL, SDLSurfaceMain, NULL);
    SDL_UpdateWindowSurface(SDLWindow);
}

unsigned char** lockfrontbuffer(void) {
    if (Bufflocked) {
        hiba("lockfrontbuffer-ben Bufflocked!");
    }

    return lockbackbuffer(NULL);
}

void unlockfrontbuffer(void) {
    if (!Bufflocked) {
        hiba("unlockbackbuffer-ben !Bufflocked!");
    }

    unlockbackbuffer();
}

// PALETTA:

//	LPDIRECTDRAWPALETTE pddpal;
ddpal::ddpal(unsigned char* tomb) {
    for (int i = 0; i < 256; i++) {
        pal[i].r = tomb[3 * i] << 2;
        pal[i].g = tomb[3 * i + 1] << 2;
        pal[i].b = tomb[3 * i + 2] << 2;
        pal[i].a = 0xFF;
    }
}

void ddpal::set(void) { SDL_SetPaletteColors(SDLSurfacePaletted->format->palette, pal, 0, 256); }
