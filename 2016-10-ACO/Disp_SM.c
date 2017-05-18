#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include <stdio.h>
#include "EXRaspi.h"

char Input[2];
Uint8* keys;

int i, point_num;


/* 初期化する。
 * 成功したときは0を、失敗したときは-1を返す。
 */
int SM_Initialize(Image *NameFrame, Image *Arrow, Image *Back, Text *Name, RASPI raspi)
{
  SDL_Surface* load = NULL; //画像変換前の保存用変数
  int i,n;
  char buf;

  //位置情報などの変数初期化
  //===============================================================

  raspi->music_number = 0;

  NameFrame->rect.x = 300;
  NameFrame->rect.y = 0;
  NameFrame->zoom = 0.3;
  NameFrame->angle = 1;

  Arrow->rect.x = 90;
  Arrow->rect.y = 200;
  Arrow->zoom = 0.2;
  Arrow->angle = 270;

  Back->rect.x = 0;
  Back->rect.y = 0;
  Back->zoom = 3;
  Back->angle = 0;

  Name->fp = NULL;
  Name->font = NULL;
  //Name->color = {0x00, 0x00, 0x00};
  Name->rect.x = 0;
  Name->rect.y = 0;
  
  //===============================================================
  //画像の読み込み
  //================================================================
  //曲名の枠組み
  load = IMG_Load("nameframe.png");
  if(load == NULL){
    fprintf(stderr, "画像の読み込みに失敗しました:%s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }
  NameFrame->image = zoomSurface(load,NameFrame->zoom,NameFrame->zoom,1); //画像を変換
  SDL_FreeSurface(load);

  //背景
  load = IMG_Load("background.jpg");
  if(load == NULL){
    fprintf(stderr, "画像の読み込みに失敗しました:%s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }
  Back->image = zoomSurface(load,Back->zoom,Back->zoom,1); //画像を変換
  SDL_FreeSurface(load);

  //矢印
  load = IMG_Load("migi.png");
  if(load == NULL){
    fprintf(stderr, "画像の読み込みに失敗しました:%s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }
  Arrow->image = rotozoomSurface(load,Arrow->angle,Arrow->zoom,1); //画像を変換

  SDL_FreeSurface(load);

  //=================================================================
  //テキストファイルの読み取り
  //=================================================================
  if(NULL == (Name->fp = fopen("music_name.csv","r"))) {
    printf("csvファイルが開けませんでした\n");
    SDL_Quit();
    return -1;
  }

  Name->font = TTF_OpenFont("TakaoMincho.ttf",24);
  if(Name->font == NULL){
    fprintf(stderr,"error:%s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  for(i=0; i<MUSIC_VALUE; i++){
    for(n=0; n<MUSIC_FILE_NAME_SIZE; n++){
      if(EOF == (buf = fgetc(Name->fp))){
	printf("ファイルの読み取り中にエラーが発生しました。");
	SDL_Quit();
	return -1;
      }

      if(buf != ',') {
	raspi->music_filename[i][n] = buf;
	//printf("%c",music_filename[i][n]);
      }
      else {
	//printf("\n");
	break;
      }
    }
  }
  fclose(Name->fp);

  //===============================================================

  printf("SelectMusic内の初期化が成功しました\n");
  
  return 0;
}


/* 更新する */
char SM_Update(RASPI raspi)
{

  char input_button_data;

  /* TODO: ここにゲームの状態を更新する処理を書く */
  //=========================================================
  //キーボードから状態を更新
  //=========================================================
  
  read(raspi->pipe.fd_r,&input_button_data,sizeof(char));

  printf("%c",input_button_data);
  
  if(input_button_data == 'C') return 1;
  if(input_button_data == 'D'){
    if(raspi->music_number <= 0) raspi->music_number = MUSIC_VALUE-1;
    else raspi->music_number = raspi->music_number-1;
  }
  if(input_button_data == 'A') return 2;
  if(input_button_data == 'B'){
    if(raspi->music_number >= MUSIC_VALUE-1) raspi->music_number = 0; 
    else raspi->music_number = raspi->music_number+1;
  }

  //printf("music_number%d\n",music_number);

  //printf("SelectMusic内の更新が成功しました\n");
  
  return 0;
}

char SM_KeyUpdate(RASPI raspi)
{

  char input_button_data;

  /* TODO: ここにゲームの状態を更新する処理を書く */
  //=========================================================
  //キーボードから状態を更新
  //=========================================================

  keys = SDL_GetKeyState(NULL);

  Input[1] = Input[0];
  Input[0] = 'N';
  
  if(keys[SDLK_LEFT] == 1) Input[0] = 'L';
  if(keys[SDLK_UP] == 1) Input[0] = 'U';
  if(keys[SDLK_RIGHT] == 1) Input[0] = 'R';
  if(keys[SDLK_DOWN] == 1) Input[0] = 'D';

  
  if(Input[0] == 'L' && Input[0] != Input[1]) return 0;
  if(Input[0] == 'U' && Input[0] != Input[1]){
    if(raspi->music_number <= 0) raspi->music_number = MUSIC_VALUE-1;
    else raspi->music_number = raspi->music_number-1;
  }
  if(Input[0] == 'R' && Input[0] != Input[1]) return 2;
  if(Input[0] == 'D' && Input[0] != Input[1]){
    if(raspi->music_number >= MUSIC_VALUE-1) raspi->music_number = 0; 
    else raspi->music_number = raspi->music_number+1;
  }

  //printf("music_number%d\n",music_number);

  //printf("SelectMusic内の更新が成功しました\n");
  
  return 0;
}


/* 描画する */
void SM_Draw(Image *NameFrame, Image *Arrow, Image *Back, Text *Name, RASPI raspi)
{

  SDL_Color color = {0x00, 0x00, 0x00};

  /* 画面初期化 */
  SDL_FillRect(screen, NULL, SDL_MapRGB(SDL_GetVideoInfo()->vfmt,0,0,0));

  /* 背景を描画する */
  SDL_BlitSurface(Back->image, NULL, screen, NULL);
  
  /* TODO: ここに描画処理を書く */
  //文字作成
  for(i = -1*LIST; i<=LIST; i++){
    point_num = raspi->music_number + i;

    if(point_num<0)point_num += MUSIC_VALUE;
    else if(point_num>=MUSIC_VALUE) point_num -= MUSIC_VALUE;

    Name->image[i+LIST] = TTF_RenderUTF8_Blended(Name->font, raspi->music_filename[point_num], color);
  }

  //曲名の句形情報設定
  //Name->scr_rect.w = Name->image[0]->w;
  //Name->scr_rect.h = Name->image[0]->h;

  //曲名の位置を設定
  Name->rect.x = 320;
  Name->rect.y = 35;
  
  //枠組みの位置を設定
  NameFrame->rect.x = 300;
  NameFrame->rect.y = 0;

  /* 画像を描画  */
  //曲名の枠組みを描画
  for(i=0; i<ALL_LIST; i++){
    SDL_BlitSurface(NameFrame->image, NULL, screen, &NameFrame->rect);
    //描画位置をずらす
    NameFrame->rect.y += 60;
    if(i<3) NameFrame->rect.x -= 40;
    else NameFrame->rect.x += 40;
  }

  //曲名を描画
  for(i=0; i<ALL_LIST; i++){
    SDL_BlitSurface(Name->image[i], NULL, screen, &Name->rect);
    //描画位置をずらす
    Name->rect.y += 60;
    if(i<3) Name->rect.x -= 40;
    else Name->rect.x += 40;
  }

  //矢印を描画
  SDL_BlitSurface(Arrow->image, NULL, screen, &Arrow->rect);
  
  /* 画面を更新する */
  SDL_UpdateRect(screen, 0, 0, 0, 0);

  /* 後処理 */
  for(i=0; i<ALL_LIST; i++){
    SDL_FreeSurface(Name->image[i]);
  }
  
}


/* 終了処理を行う */
void SM_Finalize(Image *NameFrame, Image *Arrow, Image *Back, Text *Name)
{
  /* TODO: ここで画像や音声を解放する */
  //画像の解放
  SDL_FreeSurface(NameFrame->image);
  SDL_FreeSurface(Back->image);
  SDL_FreeSurface(Arrow->image);
  
  TTF_CloseFont(Name->font);

  printf("SelectMusic内の開放が成功しました\n");
  
}


/* メインループ */
void SM_MainLoop(Image *NameFrame, Image *Arrow, Image *Back, Text *Name, RASPI raspi)
{
  SDL_Event event;
  double next_frame = SDL_GetTicks();
  double wait = 1000.0 / 60;
  char flag;

  unsigned int test;

  for (;;) {
    /* すべてのイベントを処理する */
    while (SDL_PollEvent(&event)) {
      /* QUIT イベントが発生するか、ESC キーが押されたら終了する */
      if ((event.type == SDL_QUIT) ||
	  (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
	return;
    }

    /* 1秒間に60回Updateされるようにする */
    test = SDL_GetTicks();
    //printf("経過時間%d\n",test);
    if (SDL_GetTicks() >= next_frame) {
      //raspi->mode = SM_Update(raspi);
      raspi->mode = SM_KeyUpdate(raspi);
      if(raspi->mode != 0) return;

      //printf("Input%c\n",Input[1]);

      /* 時間がまだあるときはDrawする */
      if (SDL_GetTicks() < next_frame + wait) SM_Draw(NameFrame, Arrow, Back, Name, raspi);
      next_frame += wait;
      SDL_Delay(5);
    }
  }
}


/* メイン関数 */
int SelectMusic(RASPI raspi)
{
  //画像系
  Image NameFrame;
  Image Arrow;
  Image Back;
  Text Name;

  if (SM_Initialize(&NameFrame, &Arrow, &Back, &Name, raspi) < 0) return -1;
  SM_MainLoop(&NameFrame, &Arrow, &Back, &Name, raspi);
  SM_Finalize(&NameFrame, &Arrow, &Back, &Name);
  return 0;

}
