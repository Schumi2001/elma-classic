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

    SDL_Color pal[256];
    for (int i = 0; i < 256; i++) {
        pal[i].r = i & 0b00000111 << 5;
        pal[i].g = i & 0b00111000 << 2;
        pal[i].b = i & 0b11000000 << 0;
        pal[i].a = 0xFF;
    }
    SDL_SetPaletteColors(SDLSurfacePaletted->format->palette, pal, 0, 256);

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
#if 0
    pddpal = NULL;

    PALETTEENTRY pe[256];
    for (int i = 0; i < 256; i++) {
        pe[i].peRed = (unsigned char)(tomb[3 * i] << 2);
        pe[i].peGreen = (unsigned char)(tomb[3 * i + 1] << 2);
        pe[i].peBlue = (unsigned char)(tomb[3 * i + 2] << 2);
    }
    HRESULT ddrval = Pdd->CreatePalette(DDPCAPS_8BIT, pe, (LPDIRECTDRAWPALETTE*)&(pddpal), NULL);
    if (ddrval != DD_OK) {
        hiba("CreatePalette did not succeed!");
    }
#endif
}

ddpal::~ddpal(void) {
#if 0
    if (pddpal) {
        ((LPDIRECTDRAWPALETTE)pddpal)->Release();
    }
#endif
}

void ddpal::set(void) {
#if 0
    HRESULT ddrval = Pddsprimary->SetPalette((LPDIRECTDRAWPALETTE)pddpal);
    // Egyszer ez elojott, ugyhogy kiveszem:
    // if( ddrval != DD_OK )
    //	hiba( "SetPalette did not succeed!" );
#endif
}
