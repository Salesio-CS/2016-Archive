#include "EXRaspi.h"

//初期化を行う 成功=0　失敗=-1
int Initialize(RASPI raspi){

  raspi->music_number = 0;
  
  //SDLを初期化
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0){
    fprintf(stderr, "SDLの初期化に失敗しました:%s\n", SDL_GetError());
    return -1;
  }

  //TTFを初期化
  if(TTF_Init() == -1){
    fprintf(stderr, "SDL_TTFの初期化に失敗しました:%s\n", SDL_GetError());
    return -1;
  }

  //タイトル変更
  SDL_WM_SetCaption("OTOTAS", NULL);

  //画面を初期化
  screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
  if (screen == NULL){
    fprintf(stderr, "画面の初期化に失敗しました:%s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  printf("sdlの初期化に成功しました\n");

  return 0;
  
}

//終了処理
void Finalize(void){
  
  //終了
  SDL_Quit();
  TTF_Quit();

  printf("sdlを終了しました\n");
}

//メインループ
int DisplayMainLoop(RASPI raspi){

  if(Initialize(raspi) < 0) return -1;
  
  raspi->mode=1;

  while(1){
    if(raspi->mode == 1){
      if(SelectMusic(raspi)==-1) return -1;
     }
    else if(raspi->mode == 2){
      printf("debug1¥n");
      if(PlayGame(raspi)==-1) return -1;
     }
    else if(raspi->mode == 0){
      printf("ゲームを終了します\n");
      break;
     }
    else{
      printf("error");
      return -1;
    }
  }
  
  //解放
  Finalize();
  return 0;
}
/*
//メイン関数
int main(int argc, char* argv[]){
  RASPI raspi;
  if(MainLoop(raspi) < 0) return -1;
  return 0;
}
*/
