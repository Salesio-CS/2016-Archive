#ifndef EXRASPI_H
#define EXRASPI_H

#include "Raspi.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_rotozoom.h>

//曲詳細決定定義

#define LIST 3
//ALL_LIST = LIST * 2 + 1
#define ALL_LIST 7 
#define MAX_target 15
#define PI 3.141592
#define Laptime 10000
#define FILE_MAX 100

//エラー判定用定義
#ifndef CANT_INITIALIZATION_SDL
#define CANT_INITIALIZATION_SDL 0xffffffff
#endif

#ifndef CANT_INITIALIZATION_SCREEN
#define CANT_INITIALIZATION_SCREEN 0xfffffffe
#endif

#ifndef CANT_LOAD_IMAGE
#define CANT_LOAD_IMAGE 0xfffffffd
#endif

//画像管理用構造体
typedef struct{
  SDL_Surface* image; //画像情報
  SDL_Rect rect; //配置位置情報
  double zoom, angle; //拡大率、角度
} Image;

typedef struct A{
  SDL_Surface* image;
  SDL_Rect rect;
  double zoom, angle; //拡大率,角度
  int time; //生成から何f表示しない時間を作るか,または何f表示するか
  char flag; //表示するかしないか
  char type; //画像の種類

  void (*free)(struct A *pI);

} Another_Image;

typedef Another_Image *pImage;

//文字管理用構造体
typedef struct{
  FILE *fp;
  SDL_Surface* image[ALL_LIST]; //文字画像情報
  TTF_Font* font; //フォント
  SDL_Color color; //色の指定
  SDL_Rect rect, scr_rect; //位置情報、矩形
} Text;

//ゲーム時の細かな変数
typedef struct{
  int time[2]; //曲が始まってからの時間を記録する
  int elapsed_time; //
  int set_time; //次の●を設置する時間（ファイルから読み込む）(番兵-1)
  
  double rad; //ゲーム内で円移動する円(画像)の角度
  double ratio; //角度を決めるために用いる
  int timing[FILE_MAX]; //譜面の保存先
  char type[FILE_MAX]; //譜面の保存先

  int los_time; //ロスタイム
  int score; //スコア
} GAME;

SDL_Surface* screen; //背景画像

//Disp_MAIN内
int Initialize(RASPI raspi);
void Finalize(void);
int DisplayMainLoop(RASPI raspi);
int main(int argc, char* argv[]);

//Disp_SM内
int SelectMusic(RASPI);
void SM_MainLoop(Image *, Image *, Image *, Text *, RASPI);
int SM_Initialize(Image *, Image *, Image*, Text *, RASPI);
void SM_Draw(Image *, Image *, Image *, Text *, RASPI);
char SM_Update(RASPI);
void SM_Finalize(Image *, Image *, Image *, Text *);

//Disp_PG内
int PlayGame(RASPI);
int PG_Initialize(Image *);
void PG_Draw(Image *);
char PG_Update();
void PG_Finalize(Image *);


#endif