#include "VGAX.h"

#include "img_bar.h"
#include "img_ball.h"

VGAX vga;

void setup() {
  // put your setup code here, to run once:
  vga.begin();
  pinMode(A5, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
}

uint8_t cnt;
unsigned last_millis = 0;
unsigned last_millis_ball = 0;

int8_t bar_y=0;

int8_t ball_x= VGAX_WIDTH/2;
int8_t ball_y= VGAX_HEIGHT/2;

//ball speed and direction


int8_t ball_dir_x = 1;
int8_t ball_dir_y = 1;

void loop() {
  int8_t up = digitalRead(A5);
  int8_t down = digitalRead(A4);
  unsigned current_millis = vga.millis();

  if ((current_millis - last_millis_ball) >=  50)
  {  
  //vertical border collision
    if(ball_dir_x > 0)
    {
      if(ball_x >= (VGAX_WIDTH-IMG_BALL_WIDTH)) ball_dir_x *= -1;
    }
    else
    {
      if(ball_x <= 0 ) ball_dir_x *= -1;
    }
    ball_x += ball_dir_x;

    //horizontal border collision
    if(ball_dir_y > 0)
    {
      if(ball_y >= (VGAX_HEIGHT-IMG_BALL_HEIGHT)) ball_dir_y *= -1;
    }
    else
    {
      if(ball_y <= 0 ) ball_dir_y *= -1;
    }   
    ball_y += ball_dir_y;
    last_millis_ball = current_millis;
  }
  
  
  if ((current_millis - last_millis) >=  1)
  {
    vga.clear(0x01);
    if( up == LOW and  bar_y > 0) bar_y--;
    if( down == LOW and bar_y < (VGAX_HEIGHT - IMG_BAR_HEIGHT)) bar_y++;

    
    
    vga.blit((byte*)(img_bar_data[0]), IMG_BAR_WIDTH, IMG_BAR_HEIGHT, 0, bar_y);
    vga.blit((byte*)(img_bar_data[0]), IMG_BAR_WIDTH, IMG_BAR_HEIGHT, 119, bar_y);
    vga.blit((byte*)(img_ball_data[0]), IMG_BALL_WIDTH, IMG_BALL_HEIGHT, ball_x, ball_y);
  //vga.copy((byte*)img_logology_data);
    last_millis = current_millis;
  }

}
