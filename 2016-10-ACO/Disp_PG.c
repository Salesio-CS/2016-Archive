#include "EXRaspi.h"

//初期化を行う 成功=0　失敗=-1
int PG_Initialize(Image *CD){

  SDL_Surface* load = NULL; //画像変換前の保存用変数
  
  //位置情報などの変数初期化
  //===============================================================
  
  CD->rect.x = 60;
  CD->rect.y = 0;
  CD->zoom = 0.9;
  CD->angle = 0;

  //画像の読み込み
  //================================================================
  load = IMG_Load("CD.png");
  if(load == NULL){
    fprintf(stderr, "画像の読み込みに失敗しました:%s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }
  CD->image = zoomSurface(load,CD->zoom,CD->zoom,1); //画像を変換

  return 0;
}

//入力を受け取り更新する 0=続行,1=曲決定,2=曲選択を止める
char PG_Update(){
  /*
  InputData prev;
  
  Uint8* keys = SDL_GetKeyState(NULL);

  prev = *Key;
  
  Key->left = keys[SDLK_LEFT];
  Key->up = keys[SDLK_UP];
  Key->right = keys[SDLK_RIGHT];
  Key->down = keys[SDLK_DOWN];
  
  if(Key->left && !prev.left) return 1;
  if(Key->up && !prev.up){
    if(pivot_num <= 0) pivot_num = MUSIC_VALUE-1;
    else pivot_num = pivot_num-1;
  }
  if(Key->right && !prev.right) return 2;
  if(Key->down && !prev.down){
    if(pivot_num >= MUSIC_VALUE-1) pivot_num = 0; 
    else pivot_num = pivot_num+1;
  }

  //printf("pivot_num%d\n",pivot_num);
  */
  return 0;
  
}

void PG_Draw(Image *CD){

  //static int i;
  SDL_FillRect(screen, NULL, SDL_MapRGB(SDL_GetVideoInfo()->vfmt,0,0,0));
 
  //CD
  SDL_BlitSurface(CD->image,  NULL, screen, &CD->rect);
 
  //画面の更新
  SDL_UpdateRect(screen, 0, 0, 0, 0);
}

//終了処理
void PG_Finalize(Image *CD){
  
  //画像の解放
  SDL_FreeSurface(CD->image);
  
}

//メインループ
int PlayGame(RASPI raspi){
  
  Image CD;

  if(PG_Initialize(&CD) < 0) return -1;

  PG_Draw(&CD);
 
  raspi->Error(raspi->StartMusic(raspi));
  raspi->mode=1;

  //解放
  PG_Finalize(&CD);
  return 1;
}

