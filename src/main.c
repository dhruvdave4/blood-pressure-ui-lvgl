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

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

#if LV_USE_OS != LV_OS_FREERTOS
 

static void btn_event_cb(lv_event_t *e)
{
    if(lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        printf("START Button Pressed!\n");  
        lv_obj_t *label = lv_label_create(lv_screen_active());
        lv_label_set_text(label, "button_press!");  
         lv_obj_align(label,LV_ALIGN_CENTER,0,250); 

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
  lv_obj_t *label = lv_label_create(lv_screen_active());

  lv_label_set_text(label, "Hello Dhruv!");

    lv_obj_center(label);  
    lv_obj_t *btn = lv_btn_create(lv_screen_active()); 
    lv_obj_set_size(btn, 100, 50);  
    lv_obj_align(btn,LV_ALIGN_CENTER,0,50); 


    lv_obj_t *btn_label = lv_label_create(btn);

   lv_label_set_text(btn_label, "START");

   lv_obj_center(btn_label);   

   lv_obj_add_event_cb(btn,btn_event_cb,LV_EVENT_CLICKED,NULL);
    
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

