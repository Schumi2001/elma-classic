#if defined(_WIN32) && !defined(_WIN64)

#define WIN32_LEAN_AND_MEAN

#define STRICT
#include <windows.h>
#include <mmsystem.h>

#endif

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <math.h>

#if defined(_WIN32) && !defined(_WIN64)

#define DIRECTDRAW_VERSION 0x0300

#define DIRECTINPUT_VERSION 0x0300

#include "dxinc\ddraw.h"
#include "dxinc\dsound.h"
// #include	"dsound50.h"
#include "dxinc\dinput.h"

#endif

#include "w_nempub.h"

#include "..\m_v.h"
#include "..\m_k.h"
#include "..\m_dd.h"

#include "m_sound.h"

#include "..\hanghigh.h"
#include "..\qopen.h"

#include "..\main.h"
