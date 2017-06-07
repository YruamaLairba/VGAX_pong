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

unsigned last_millis_bars = 0;
unsigned last_millis_ball = 0;
unsigned last_millis_display = 0;

//bar 1 position
const int8_t bar1_x = 0;
int8_t bar1_y = 0;

//bar 2 position
const int8_t bar2_x = 119;
int8_t bar2_y = 0;

//ball position
int8_t ball_x= VGAX_WIDTH/2;
int8_t ball_y= VGAX_HEIGHT/2;

//ball speed and direction
int8_t ball_dir_x = 1;
int8_t ball_dir_y = 1;

void loop() {

  //player 1 input
  int8_t up1 = digitalRead(A5);
  int8_t down1 = digitalRead(A4);

  //player 1 input
  int8_t up2 = digitalRead(A5);
  int8_t down2 = digitalRead(A4);
  
  unsigned current_millis = vga.millis();

  //ball management
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

    //bars collision
    if(ball_dir_x > 0)
    {
      if((ball_x+ IMG_BALL_WIDTH)>= (bar2_x-IMG_BAR_WIDTH))
      {
        if ((ball_y > bar2_y) and (ball_y < (bar2_y < (IMG_BAR_HEIGHT + 8))))
        {
          ball_dir_x *= -1;
        }
      }
    }
    else
    {
      if((ball_x <= (bar1_x + IMG_BAR_WIDTH)))
      {
        if((ball_y > bar1_y) and (ball_y < (bar1_y < (IMG_BAR_HEIGHT + 8))))
        {
          ball_dir_x *= -1;
        } 
      }
    }
    last_millis_ball = current_millis;    
  }
  
  //bars management
  if ((current_millis - last_millis_bars) >=  1)
  {
    if( up1 == LOW and  bar1_y > 0) bar1_y--;
    if( down1 == LOW and bar1_y < (VGAX_HEIGHT - IMG_BAR_HEIGHT)) bar1_y++;
    if( up2 == LOW and  bar2_y > 0) bar2_y--;
    if( down2 == LOW and bar2_y < (VGAX_HEIGHT - IMG_BAR_HEIGHT)) bar2_y++;
    last_millis_bars = current_millis;
  }

  //display management
  if ((current_millis - last_millis_display) >= 15 )
  {
    vga.clear(0x01); //background
    vga.blit((byte*)(img_bar_data[0]), IMG_BAR_WIDTH, IMG_BAR_HEIGHT, bar1_x, bar1_y);
    vga.blit((byte*)(img_bar_data[0]), IMG_BAR_WIDTH, IMG_BAR_HEIGHT, bar2_x, bar2_y);
    vga.blit((byte*)(img_ball_data[0]), IMG_BALL_WIDTH, IMG_BALL_HEIGHT, ball_x, ball_y);
    last_millis_display = current_millis;
  }
}
