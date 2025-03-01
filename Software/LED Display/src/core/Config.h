#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <stdint.h>
#include <string>

// Json document size to hold the commands send between client/server
#define COMMAND_DOC_SIZE 255
// Json document size to hold the config (depends on config size)
#define CONFIG_DOC_SIZE 20000
/*-----------------------------------------------------------------------------
 * Global parameters
 *
 * These parameters are used for dynamically changing runtime operation. They
 * can (optionally) be loaded from and writen to persistant storage.
 *
 * Animation init or draw routines need to apply these parameters to
 * dynamically set runtime parameters. Init only gets called when an animation
 * starts or restarts draw gets called every animation frame so choose wisely
 * where to apply. And let these parameters take effect. (Be careful of Timers)
 *
 * After creation of the config object, call load() to load the configuration
 * from the "config.json" file and apply the values to the config struct.
 *
 * If no "config.json" exists the config structs keeps the values supplied in
 * the code. After saveing a "config.json" is freshly created.
 *---------------------------------------------------------------------------*/
struct Config {
    struct {
    uint16_t max_milliamps = 18000;
    float brightness = 1;
    int16_t motor_speed = -150;
  } power;

  struct {
    char ssid[32] = "-^..^-";
    char password[64] = "qazwsxedc";
    char hostname[64] = "MegaCube";
    uint16_t port = 80;
  } network;

  struct {
    // Do not serialize changed to disk/gui
    boolean changed = false;
    boolean play_one = false;
    // Only serialize animation to disk
    uint8_t animation = 0;
    struct {
      float runtime = 30.0f;
      float radius = 7.5f;
      uint8_t brightness = 255;
      uint8_t motionBlur = 220;
    } accelerometer;
    struct {
      float starttime = 5.0f;
      float runtime = 30.0f;
      float endtime = 3.0f;
      float angle_speed = -180.0f;
      float radius = 7.5f;
      float radius_start = 2.0f;
      float distance = 1.5f;
      int8_t hue_speed = 25;
      uint8_t brightness = 200;
      uint8_t motionBlur = 220;
    } arrows;
    struct {
      float starttime = 5.0f;
      float runtime = 30.0f;
      float endtime = 3.0f;
      float angle_speed = 120.0f;
      float radius = 7.5f;
      float radius_start = 1.0f;
      float distance = 4.0f;
      int8_t hue_speed = 25;
      uint8_t brightness = 255;
      uint8_t motionBlur = 200;
    } atoms;
    struct {
      float starttime = 5.0f;
      float runtime = 30.0f;
      float endtime = 5.0f;
      float angle_speed = 160.0f;
      float radius = 7.0f;
      float radius_start = 1.0f;
      float distance = 1.0f;
      int8_t hue_speed = -50;
      uint8_t brightness = 255;
      uint8_t motionBlur = 0;
    } cube;
    struct {
      float runtime = 30.0f;
      float radius = 7.5f;
      uint8_t brightness = 255;
      uint8_t motionBlur = 220;
    } fireworks;
    struct {
      float runtime = 30.0f;
      float interval = 0.2f;
      float phase_speed = 5.0f;
      float angle = 0.0f;
      float angle_speed = 0.0f;
      float radius = 7.5f;
      float resolution = 30;
      uint8_t thickness = 16;
      int8_t hue_speed = 30;
      uint8_t brightness = 255;
      uint8_t motionBlur = 230;
    } helix;
    struct {
      float runtime = 30.0f;
      float interval = 0.20f;
      uint8_t brightness = 255;
      uint8_t motionBlur = 0;
    } life;
    struct {
      float starttime = 5.0f;
      float runtime = 30.0f;
      float endtime = 3.0f;
      float interval = 0.15f;
      float angle_speed = -70.0f;
      float radius = 7.5f;
      float radius_start = 1.0f;
      uint8_t brightness = 200;
      uint8_t motionBlur = 220;
    } mario;
    struct {
      float starttime = 5.0f;
      float runtime = 30.0f;
      float endtime = 10.0f;
      float scale_p = 0.15f;
      float speed_x = 0.1f;
      float speed_y = 0.2f;
      float speed_z = 0.3f;
      float speed_w = 0.4f;
      float speed_offset_speed = 0.02f;
      int8_t hue_speed = 30;
      uint8_t brightness = 70;
      uint8_t motionBlur = 0;
    } plasma;
    struct {
      float starttime = 2.0f;
      float runtime = 30.0f;
      float endtime = 2.0f;
      int8_t hue_speed = 25;
      uint8_t brightness = 200;
      uint8_t motionBlur = 200;
    } pong;
    struct {
      float starttime = 0.5f;
      float runtime = 30.0f;
      float endtime = 2.0f;
      float rotation_speed = 90.0f;
      float radius = 15.0f;
      uint8_t brightness = 200;
      uint8_t motionBlur = 220;
    } arc_scroller;
    struct {
      float starttime = 0.5f;
      float runtime = 30.0f;
      float endtime = 2.0f;
      float interval = 0.1f;
      int8_t hue_speed = -50;
      uint8_t brightness = 255;
      uint8_t motionBlur = 220;
    } box_scroller;
    struct {
      float starttime = 5.0f;
      float runtime = 30.0f;
      float endtime = 10.0f;
      float phase_speed = PI;
      float resolution = 30;
      float radius = 7.5f;
      int8_t hue_speed = -50;
      uint8_t brightness = 200;
      uint8_t motionBlur = 0;
    } sinus;
    struct {
      float starttime = 5.0f;
      float runtime = 30.0f;
      float endtime = 5.0f;
      int8_t hue_speed = -25;
      uint8_t brightness = 200;
      uint8_t motionBlur = 220;
    } spectrum;
    struct {
      float starttime = 3.0f;
      float runtime = 30.0f;
      float endtime = 5.0f;
      float phase_speed = 0.3f;
      float body_diagonal = 13.0f;
      int8_t hue_speed = 30;
      uint8_t brightness = 200;
      uint8_t motionBlur = 230;
    } starfield;
    struct {
      float runtime = 30.0f;
      float interval = 0.1f;
      float fade_in_speed = 1.0f;
      float fade_out_speed = 2.0f;
      uint8_t brightness = 255;
      uint8_t motionBlur = 0;
    } twinkels;
  } animation;

  // Do not serialize devices
  struct {
    struct {
      float x = 0;
      float y = 0;
      float z = 0;
    } accelerometer;
    struct {
      float x = 0;
      float y = 0;
    } joystick;
    struct {
      volatile float level[64];
    } fft;
  } devices;
 
};
// All cpp files that include this link to a single config struct
extern struct Config config;
#endif