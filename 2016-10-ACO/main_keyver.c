#include"Raspi.h"

int main(){
  RASPI raspi=NULL;

  raspi=CreateRaspi();
  if(raspi==NULL){
     Error(MEMORY_CANT_GET_ERROR);
     return MEMORY_CANT_GET_ERROR;
  }

  DisplayMainLoop(raspi);

  /*
	//main関数　処理
        raspi->LoadMusicList(raspi)
	raspi->SelectMusic(raspi);//SDL
	raspi->StartButton(Raspi);//別プロセスに分かれる
	raspi->StartMusic(raspi);//処理は持っていかれる
	raspi->EndButton(raspi);//やらないと死亡
	*/
  raspi->Free(raspi);//やれ
  return 0;

}
