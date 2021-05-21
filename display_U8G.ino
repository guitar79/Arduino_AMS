//https://github.com/olikraus/u8glib/wiki/fontsize
//https://github.com/olikraus/u8glib/wiki/userreference#setprintpos

#include <U8glib.h>
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);

void u8gStart()
  {
    u8g.setFont(u8g_font_5x8);
    u8g.setColorIndex(1);
    u8g.setFontPosTop();

    //draw();
  }

void u8gDraw()
  {
    u8g.firstPage();   
    do {
      u8g.setFont(u8g_font_5x8);
      //u8g.setFontPosTop(); u8g.drawStr(0,0,"A");
      u8g.setFontPosBottom();
      
      u8g.drawStr(-1,26,"TEMP : "); 
        u8g.setPrintPos(34,26);
        u8g.print(Temperature);
        u8g.drawStr(55,26,"\xb0");
        u8g.drawStr(60,26,"C");
        
      u8g.drawStr(70,26,"HUM : "); 
        u8g.setPrintPos(100,26);
        u8g.print(Humidity);
        u8g.drawStr(120,26,"%");

      u8g.drawStr(0,35, "PM2.5: "); 
        u8g.setPrintPos(55,35); 
        u8g.print("PM2.5 value");
        }
    while( u8g.nextPage() ); 
  }
