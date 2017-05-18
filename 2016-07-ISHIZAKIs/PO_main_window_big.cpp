
#include "opencv2/opencv.hpp"
#include "opencv/cxcore.h"
#include "opencv/highgui.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <bcm2835.h>

using namespace cv;

void strike_picture();
void hit_picture();
void home_run_picture();
void runner_picture();

int  strike_counter=0,hit_checker,runner1 = 0,runner2 = 0,
     runner3 = 0,point = 0;

int i2c_connect() {
  bcm2835_init();
  bcm2835_i2c_begin();
  char address = 0x68;
  char buf[1];
  char addr[2];
  int value = 0;
  int ret;
  bcm2835_i2c_setSlaveAddress(address);
  addr[0] = 107;
  addr[1] = 0;
  bcm2835_i2c_write(addr,2);
  addr[0] = 59;
  ret = BCM2835_I2C_REASON_ERROR_DATA;
  while(ret != BCM2835_I2C_REASON_OK){
  		bcm2835_i2c_write(addr,1);
  		ret = bcm2835_i2c_read(buf,1);
  }
  value = buf[0]<<8;
  addr[0] = 60;
  ret = BCM2835_I2C_REASON_ERROR_DATA;
  while(buf[0] == 99){
  	bcm2835_i2c_write(addr,1);
  	ret = bcm2835_i2c_read(buf,1);
  }
  value += buf[0];
  	if(value & 1<<15){
  		value -= 1<<16;
  }
  double final_val = value;
  final_val = final_val / 16384;
  bcm2835_i2c_end();
  return final_val;
}

void throw_(){
  int x;
  double hantei1,hantei2,kekka;
  VideoCapture cap("piture.avi");
  namedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
  for(x=3;x>2;x++)
    {
      if(x==4){
	waitKey(0);
    }
       if(x==5){
	hantei1 = i2c_connect();
    }
      Mat Img_i;
      Mat Img_o;
      cap >> Img_i;  
resize(Img_i,Img_o,Size(),2.0,2.0);
    if (Img_i.empty()){
        hantei2 = i2c_connect();
	kekka = hantei1 - hantei2;
	//kekka = fabs(kekka);
	
      if(kekka >= 0.3){
	hit_checker = 1;
      }else {
	hit_checker = 0;
      }
	if(kekka <= -0.3){
	hit_checker = 1;
	}
	//printf("%f¥n",kekka);
	break;
      }
      imshow("yakyuban", Img_o);
      waitKey(30);
    }  
}

void knock() {
  VideoCapture cap("out.avi");
  namedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
  while (true)
    {
      Mat Img_i;
	Mat Img_o;
      cap >> Img_i;
resize(Img_i,Img_o,Size(),2.0,2.0);
      if (Img_i.empty()){
        break;
      }
      imshow("yakyuban", Img_o);
      waitKey(30);
    }
}
void hit_movie(){
  VideoCapture cap("hit.avi");
  namedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
  while (true)
    {
      Mat Img_i;
	Mat Img_o;
      cap >> Img_o;
resize(Img_i,Img_o,Size(),2.0,2.0);
      if (Img_i.empty()){
        break;
      }
      imshow("yakyuban", Img_o);
      waitKey(30);
    }
}
void home_run_movie() {
  VideoCapture cap("homerun.avi");
  namedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
  while (true)
    {
      Mat Img_i;
	Mat Img_o;
      cap >> Img_o;
resize(Img_i,Img_o,Size(),2.0,2.0);
      if (Img_i.empty()){
        break;
      }
      imshow("yakyuban", Img_o);
      waitKey(30);
    }
}
void strike_movie() {
  VideoCapture cap("strike.avi");
  namedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
  while (true)
    {
       Mat Img_i;
	Mat Img_o;
      cap >> Img_o;
resize(Img_i,Img_o,Size(),2.0,2.0);
      if (Img_i.empty()){
        break;
      }
      imshow("yakyuban", Img_o);
      waitKey(30);  }
}

void strike_picture(){
  if(strike_counter==1){
      IplImage *img;
      char imgfile[] = "strike_1.jpg";
      img = cvLoadImage(imgfile, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
      cvNamedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
      cvShowImage("yakyuban", img);
      cvWaitKey(0);
      
      cvReleaseImage(&img);
  }
  if(strike_counter==2){
    IplImage *img;
    char imgfile[] = "strike_2.jpg";
    img = cvLoadImage(imgfile, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
    cvNamedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
    cvShowImage("yakyuban", img);
    cvWaitKey(0);
    
    cvReleaseImage(&img);
  }
  if(strike_counter==3){
    IplImage *img;
    char imgfile[] = "strike_3.jpg";
    img = cvLoadImage(imgfile, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
    cvNamedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
    cvShowImage("yakyuban", img);
    cvWaitKey(0);
  
    cvReleaseImage(&img);
  }
}

void runner_picture_1() {
  strike_picture();
  IplImage *img;
  char imgfile[] = "runner_1.jpg";
  img = cvLoadImage(imgfile, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
  cvNamedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
  cvShowImage("yakyuban", img);
  cvWaitKey(0);
 
  cvReleaseImage(&img);
}
void runner_picture_12(){
  strike_picture();
  IplImage *img;
  char imgfile[] = "runner_12.jpg";
  img = cvLoadImage(imgfile, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
  cvNamedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
  cvShowImage("yakyuban", img);
  cvWaitKey(0);
 
  cvReleaseImage(&img);
}

void runner_picture_123(){
  IplImage *img;
  char imgfile[] = "runner_123.jpg";
  img = cvLoadImage(imgfile, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
  cvNamedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
  cvShowImage("yakyuban", img);
  cvWaitKey(0);
 
  cvReleaseImage(&img);
}

void point_picture(){
   IplImage *img;
   if(point==1){
   strike_picture();
    char imgfile[] = "1-0.jpg";
    img = cvLoadImage(imgfile, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
    cvNamedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
    cvShowImage("yakyuban", img);
    cvWaitKey(0);
   
    cvReleaseImage(&img);
  }

  if(point==2){
    char imgfile[] = "2-0.jpg";
    img = cvLoadImage(imgfile, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
    cvNamedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
    cvShowImage("yakyuban", img);
    cvWaitKey(0);
   
    cvReleaseImage(&img);
  }
  if(point==3){
    char imgfile[] = "3-0.jpg";
    img = cvLoadImage(imgfile, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
    cvNamedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
    cvShowImage("yakyuban", img);
    cvWaitKey(0);
   
    cvReleaseImage(&img);
  }
  if(point==4){
    char imgfile[] = "4-0.jpg";
    img = cvLoadImage(imgfile, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
    cvNamedWindow("yakyuban", CV_WINDOW_AUTOSIZE);
    cvShowImage("yakyuban", img);
    cvWaitKey(0);
    
    cvReleaseImage(&img);
  }
}

void result_picture(){
  point_picture();
}

int rundum() {
	return rand() % 10 + 1;
}


int main() {

int null;
for (strike_counter = 0; strike_counter <= 2;) {	
 throw_();	
 if (hit_checker==1) {
	null = rundum();		
	if (null => 5 ) {
		hit_movie();
		strike_counter = 0;
		if (runner1 == 0) {
			runner1 = 1;
          		runner_picture_1();
			}else if(runner2 == 0) {
				runner2 = 1;
				runner1 = 1;
            			runner_picture_12();

			}else if(runner3 == 0) {
				runner1 = 1;
              			runner2 = 1;
              			runner3 = 1;
              			runner_picture_123();
			}else if(runner3 == 1){
				point++;
				runner1 = 1;
				runner2 = 1;
				runner3 = 1;
			}
			}else if(null <=7 ){
				knock();
				break;
			}else{
				home_run_movie();
				point++;
				if (runner1 = 1) { point++; }
				if (runner2 = 1) { point++; }
				if (runner3 = 1) { point++; }
      			strike_counter=0; //strik ni natteta
		}
		}else if(hit_checker==0){
			strike_movie();
			strike_counter++;	//strik ni
			strike_picture();
	}
	result_picture();
}
  return 0;
}

