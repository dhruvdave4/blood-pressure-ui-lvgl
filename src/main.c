/**
 * @file main.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#ifndef _DEFAULT_SOURCE
  #define _DEFAULT_SOURCE /* needed for usleep() */
#endif

#include <stdlib.h>
#include <stdio.h>
#ifdef _MSC_VER
  #include <Windows.h>
#else
  #include <unistd.h>
  #include <pthread.h>
#endif
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include <SDL.h>

#include "hal/hal.h" 


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
 static lv_obj_t *hr_label;  
 static int hr_level =72; 
 static bool show_value=false;  
 static lv_obj_t *status_label;
/**********************
 *      MACROS
 **********************/

/**********************)
 *   GLOBAL FUNCTIONS
 **********************/

#if LV_USE_OS != LV_OS_FREERTOS
  
static void hr_timer(lv_timer_t * timer)  
{   
   if (show_value == true) 
    {
    hr_level += 1; 
    if (hr_level >= 80 && hr_level <= 89)   
    {
          lv_obj_set_style_text_color(hr_label,lv_palette_main(LV_PALETTE_RED),0);
    }
    if(hr_level >= 99)   
    {
        hr_level = 72;    
             lv_obj_set_style_text_color(hr_label,lv_palette_main(LV_PALETTE_GREEN),0);
    }
    char buf[20];  
    sprintf(buf, "heart_rate: %d bpm", hr_level);  
    lv_label_set_text(hr_label, buf);   
   } 

}
// static void text_show(void)  
// { 
//           hr_label = lv_label_create(lv_screen_active());
//            lv_label_set_text(hr_label, "heart_rate: 72 bpm"); 
//              lv_obj_align(hr_label,LV_ALIGN_CENTER,0,30);
// }

static void btn_event_cb(lv_event_t *e)
{
    if(lv_event_get_code(e) == LV_EVENT_CLICKED)
    { 
       
        printf("START Button Pressed!\n");  
        // lv_obj_t *label = lv_label_create(lv_screen_active());  

       
           lv_label_set_text(status_label, "Measurement Started");  
           lv_obj_align(status_label,LV_ALIGN_CENTER,10,200);   
          // text_show();   
        
        
          show_value = true;   

    } 
  
}  


static void stop_btn_event_cb(lv_event_t *e)
{  


  
    if(lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        printf("STOP Button Pressed!\n");  
       
       
        lv_label_set_text(status_label, "Measurement Stopped");  
         lv_obj_align(status_label,LV_ALIGN_CENTER,10,200);    
      

          // text_show();   
          show_value = false;   

    } 
  
}


int main(int argc, char **argv)
{
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/

  /*Initialize LVGL*/
  lv_init();

  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  sdl_hal_init(320, 480);

  /* Run the default demo */
  /* To try a different demo or example, replace this with one of: */
  /* - lv_demo_benchmark(); */
  /* - lv_demo_stress(); */
  /* - lv_example_label_1(); */
  /* - etc. */  


/* status_label */ 
status_label = lv_label_create(lv_screen_active());

lv_label_set_text(status_label,"System Idle");

lv_obj_align(status_label,LV_ALIGN_CENTER,0,200); 
lv_obj_set_style_text_color(status_label,lv_palette_main(LV_PALETTE_PURPLE), 0);   




  lv_obj_t *label = lv_label_create(lv_screen_active());

  lv_label_set_text(label, "Blood Pressure Monitor");
 lv_obj_set_style_text_font(label,&lv_font_montserrat_20,0);
      lv_obj_align(label,LV_ALIGN_TOP_MID,0,20); 
      lv_obj_set_style_text_color(label,lv_palette_main(LV_PALETTE_INDIGO), 0);   


/* start button */
    lv_obj_t *btn = lv_btn_create(lv_screen_active()); 
    lv_obj_set_size(btn, 100, 50);  
    lv_obj_align(btn,LV_ALIGN_CENTER,0,80);  
    lv_obj_set_style_bg_color(
    btn,
    lv_palette_main(LV_PALETTE_GREEN),
    0);


    lv_obj_t *btn_label = lv_label_create(btn);

   lv_label_set_text(btn_label, "START");

   lv_obj_center(btn_label);   
  
   lv_obj_add_event_cb(btn,btn_event_cb,LV_EVENT_CLICKED,NULL);  
/*stat button end*/   



lv_obj_t *stop_btn = lv_btn_create(lv_screen_active()); 
    lv_obj_set_size(stop_btn, 100, 50);  
    lv_obj_align(stop_btn,LV_ALIGN_CENTER,0,160); 
lv_obj_set_style_bg_color(
    stop_btn,
    lv_palette_main(LV_PALETTE_RED),
    0);

    lv_obj_t *btn_label_1 = lv_label_create(stop_btn);

   lv_label_set_text(btn_label_1, "STOP");

   lv_obj_center(btn_label_1);   

   lv_obj_add_event_cb(stop_btn,stop_btn_event_cb,LV_EVENT_CLICKED,NULL); 
/*stop_button begin*/  




/*stop_button end */
   /* deing custom container*/ 
   lv_obj_t *hr_panel =
    lv_obj_create(lv_screen_active());

lv_obj_set_size(hr_panel,250,80);

lv_obj_align(hr_panel,LV_ALIGN_TOP_MID,0,70);
  /*craet heard read consept  herer */  
  
          hr_label = lv_label_create(hr_panel);
           lv_label_set_text(hr_label, "heart_rate: 72 bpm");  

            //  lv_obj_align(hr_label,LV_ALIGN_CENTER,0,10);  
            lv_obj_center(hr_panel);
            lv_obj_set_style_text_color(hr_label,lv_palette_main(LV_PALETTE_GREEN),0);
            lv_timer_create(hr_timer,1000,NULL);
  

    
  while(1) 
  {
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/ 
   
    uint32_t sleep_time_ms = lv_timer_handler();
    if(sleep_time_ms == LV_NO_TIMER_READY){
	   sleep_time_ms =  LV_DEF_REFR_PERIOD;
       }
#ifdef _MSC_VER
    Sleep(sleep_time_ms);
#else
    usleep(sleep_time_ms * 1000);
#endif
  }

  return 0;
}


#endif

/**********************
 *   STATIC FUNCTIONS
 **********************/

