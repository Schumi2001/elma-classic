#include "ALL.H"

int mk_kbhit(void) { return 0; }
int mk_getstate(int unused) { return 0; }
int mk_getextchar(void) { return 0; }

void mk_emptychar(void) {}

void mk_init() {}
void mkw_getDIstate() {}
void mkw_setkeydown() {}
void initDI() {}
void releaseDI() {}

void initdsound(int secondaryeloir) {}
int controlaltnyomva(void) { return 0; }

void GetDXVersion(unsigned long* pdwDXVersion, unsigned long* pdwDXPlatform) {
    *pdwDXVersion = 0x300;
    *pdwDXPlatform = 0;
}
