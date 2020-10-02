\mainpage Main Page
 
---
# eINK 1.54 inch click

eINK click is an adapter Click board™, used to interface a compatible eINK display with the host MCU.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](<https://www.mikroe.com/eink-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Eink154Inch Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Eink154Inch Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void eink_154inch_cfg_setup ( eink_154inch_cfg_t *cfg ); 
 
- Initialization function.
> EINK_154INCH_RETVAL eink_154inch_init ( eink_154inch_t *ctx, eink_154inch_cfg_t *cfg );

#### Example key functions :

- Set LUT table
> void eink154_set_lut ( eink_154inch_t *ctx, const uint8_t *lut, uint8_t n_bytes );
 
- Displays image
> void eink154_display_image ( eink_154inch_t *ctx, const uint8_t* image_buffer );

- Settings font
> void eink154_set_font ( eink_154inch_t *ctx, eink_154inch_font_t *cfg_font );

## Examples Description

> This application write a text and draw an image on eINK display.

**The demo application is composed of two sections :**

### Application Init 

> Driver initialization - basic procedure for starting e-ink display.
> Start the display settings and select communication, write LUT table.
> Print text to the display by changing font size

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    eink_154inch_cfg_t cfg;   
    eink_154inch_font_t cfg_font;
    eink_154_text_set_t text_set;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.
    
    eink_154inch_cfg_setup( &cfg );
    EINK_154INCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eink_154inch_init( &eink_154inch, &cfg );

    eink154_start_config( &eink_154inch );
    eink154_set_lut( &eink_154inch, EINK154_LUT_TABLE, 30 );
    
    cfg_font.p_font = &guiFont_Tahoma_18_Regular[ 0 ];
    cfg_font.color = EINK154_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK154_FO_HORIZONTAL;  
    
    eink154_set_font( &eink_154inch, &cfg_font );
    text_set.n_char = 4;
    text_set.text_x = 22;
    text_set.text_y = 50;
    eink154_text( &eink_154inch, &demo_text[ 0 ], &text_set );
    Delay_ms( 1000 );
    eink154_set_font( &eink_154inch, &cfg_font );
    text_set.n_char = 7;
    text_set.text_x = 18;
    text_set.text_y = 90;
    eink154_text( &eink_154inch, &demo_text1[ 0 ], &text_set );
    Delay_ms( 1000 );
    eink154_set_font( &eink_154inch, &cfg_font );
    text_set.n_char = 8;
    text_set.text_x = 13;
    text_set.text_y = 130;
    eink154_text( &eink_154inch, &demo_text2[ 0 ], &text_set ); 
    Delay_ms( 5000 );
}
  
```

### Application Task

> Drawing an image to the display every 1 second.

```c

void application_task ( void )
{
    eink154_display_image( &eink_154inch, &demoImage_light[ 0 ] );
    Delay_1sec( );
    eink154_display_image( &eink_154inch, &demoImage_dark[ 0 ] );
    Delay_1sec( );
}

```

## Note

> - Create Image:
>    Save the image in resolution of 200x200 px with the extension  > (monochrome bmp) ...
>    Upload the image to Image2Lcd program
>    Set parameters to:
>           1. Output file type : C array
>           2. Scan Mode : Horisontal scan
>           3. Bits Pixel : monochrome
>           4. Max width and height : 200x200
>           5. Check only MSB first
>           6. Check Reverse color and adjust Normal type
>    The image to be generated should contain about 5000 bytes ...
>    Insert the image into the file eINK_154_display_image.h
> 
> - Create Font:
>    Close existing project, open a new VTFT project
>    Add label and adjust text font
>    Generate source code
>    Copy the font from resource.c file to this project in file> eINK_154_display_font.h
> 
> - Create new functions:
>    At the beginning of your new function, set eink154_setMemoryArea and> eink154_setMemoryPointer
>    Create new pixels and create a new image buffer
>    Send command to write to RAM ( EINK154_CMD_WRITE_RAM )
>    Forward 5000 data bytes ..
>        1. By using eink154_sendDataBurst (max 200 bytes by single sending)
>        2. By using the eink154_sendData function (sending one by one byte)
>    Finally call the eink154_updateDisplay function to see the image on the> display
> 
> *** Changing the LUT table can lead to loss of display performance .... 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Eink154Inch

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
