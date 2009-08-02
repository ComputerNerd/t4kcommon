/*
  tux4kids-common

  Library of common functions used in Tux4Kids games.

  Part of "Tux4Kids" Project
  http://www.tux4kids.com/

  Copyright: See COPYING file that comes with this distribution.
*/

#ifndef TUX4KIDS_COMMON_H
#define TUX4KIDS_COMMON_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0xff000000
#define gmask 0x00ff0000
#define bmask 0x0000ff00
#define amask 0x000000ff
#else
#define rmask 0x000000ff
#define gmask 0x0000ff00
#define bmask 0x00ff0000
#define amask 0xff000000
#endif

#define _(String) gettext (String)

typedef enum { false, true } bool;

extern const int debug_loaders;
extern const int debug_menu;
extern const int debug_menu_parser;
extern const int debug_sdl;
extern const int debug_all;

#define MAX_SPRITE_FRAMES 10

typedef struct {
  SDL_Surface *frame[MAX_SPRITE_FRAMES];
  SDL_Surface *default_img;
  int num_frames;
  int cur;
} sprite;

/* from t4k-main.c */
void            InitT4KCommon(int debug_flags);

/* from tk4-menu.c */
extern SDL_Rect menu_rect, stop_rect, prev_rect, next_rect;
extern SDL_Surface *stop_button, *prev_arrow, *next_arrow, *prev_gray, *next_gray;

void            SetActivitiesList(int num, char** acts);
void            SetMenuSounds(Mix_Music* music, Mix_Chunk* click, Mix_Chunk* hover);
void            SetImagePathPrefix(char* pref);

void            CreateOneLevelMenu(int index, int items, char** item_names, char* title, char* trailer);
int             RunMenu(int index, bool return_choice, void (*draw_background)(), int (*handle_event)(SDL_Event*), void (*handle_animations)(), int (*handle_activity)(int, int));
void            PrerenderAll();
void            LoadMenu(int index, const char* file_name);
void            UnloadMenus(void);

/* from tk4-sdl.c */
SDL_Surface*    GetScreen();
void            DrawButton(SDL_Rect* target_rect, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void            DrawButtonOn(SDL_Surface* target, SDL_Rect* target_rect, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
SDL_Surface*    CreateButton(int w, int h, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void            RoundCorners(SDL_Surface* s, Uint16 radius);

SDL_Surface*    Flip(SDL_Surface *in, int x, int y);
SDL_Surface*    Blend(SDL_Surface *S1, SDL_Surface *S2, float gamma);

void            FreeSurfaceArray(SDL_Surface** surfs, int length);
int             inRect(SDL_Rect r, int x, int y);
void            SetRect(SDL_Rect* rect, const float* pos);
void            UpdateRect(SDL_Surface* surf, SDL_Rect* rect);

void            DarkenScreen(Uint8 bits);
//void            ChangeWindowSize(int new_res_x, int new_res_y);
//void            SwitchScreenMode(void);

SDL_EventType   WaitForEvent(SDL_EventMask events);
SDL_Surface*    zoom(SDL_Surface* src, int new_w, int new_h);

/*Text rendering functions: */
int             Setup_SDL_Text(void);
void            Cleanup_SDL_Text(void);
SDL_Surface*    BlackOutline(const char* t, int size, SDL_Color* c);
SDL_Surface*    SimpleText(const char *t, int size, SDL_Color* col);
SDL_Surface*    SimpleTextWithOffset(const char *t, int size, SDL_Color* col, int *glyph_offset);


/* from tk4-loaders.c */
#define IMG_REGULAR         0x01
#define IMG_COLORKEY        0x02
#define IMG_ALPHA           0x04
#define IMG_MODES           0x07

#define IMG_NOT_REQUIRED    0x10
#define IMG_NO_PNG_FALLBACK 0x20


SDL_Surface*    LoadImage(const char* file_name, int mode);
SDL_Surface*    LoadScaledImage(const char* file_name, int mode, int width, int height);
SDL_Surface*    LoadImageOfBoundingBox(const char* file_name, int mode, int max_width, int max_height);

SDL_Surface*    LoadBkgd(const char* file_name, int width, int height);

sprite*         LoadSprite(const char* name, int mode);
sprite*         LoadScaledSprite(const char* name, int mode, int width, int height);
sprite*         LoadSpriteOfBoundingBox(const char* name, int mode, int max_width, int max_height);
sprite*         FlipSprite(sprite* in, int X, int Y);
void            FreeSprite(sprite* gfx);
void            NextFrame(sprite* s);

Mix_Chunk*      LoadSound(char* datafile);
Mix_Music*      LoadMusic(char *datafile);

/* from tk4-loaders.c */

void            PlaySound(Mix_Chunk* sound);
void            AudioMusicLoad(Mix_Music* music, int loops);
void            AudioMusicUnload();
bool            IsPlayingMusic();
void            AudioMusicPlay(Mix_Music *musicData, int loops);

#endif
