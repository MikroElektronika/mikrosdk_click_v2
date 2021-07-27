
---
# eINK 2.00 inch display

eINK click is an adapter Click board™, used to interface a compatible eINK display with the host MCU.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eink_click_bundle20inch.png">
</p>

[click Product page](https://www.mikroe.com/eink-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Eink200Inch Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Eink200Inch Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void eink_200inch_cfg_setup ( eink_200inch_cfg_t *cfg ); 
 
- Initialization function.
> EINK_200INCH_RETVAL eink_200inch_init ( eink_200inch_t *ctx, eink_200inch_cfg_t *cfg );

#### Example key functions :

- Set LUT table
> void eink200_set_lut ( eink_200inch_t *ctx, const uint8_t *lut, uint8_t n_bytes );
 
- Displays image
> void eink200_display_image ( eink_200inch_t *ctx, const uint8_t* image_buffer );

- Set text font
> void eink200_set_font ( eink_200inch_t *ctx, eink_200inch_font_t *cfg_font );

## Examples Description

> This application demonstrates the use of eINK click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the click board for 2.00 inch eINK display.
> After that, if the TEXT mode is supported, shows a desired text messages on the display.

```c

void application_init ( void )
{
    eink_200inch_cfg_t cfg;   
    eink_200inch_font_t cfg_font;
    eink_200_text_set_t text_set;

    //  Click initialization.
    
    eink_200inch_cfg_setup( &cfg );
    EINK_200INCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eink_200inch_init( &eink_200inch, &cfg );

    eink200_start_config( &eink_200inch );
    eink200_set_lut( &eink_200inch, EINK200_LUT_TABLE, 90 );
    Delay_ms( 1000 );

#ifndef IMAGE_MODE_ONLY
    cfg_font.p_font = &guiFont_Tahoma_10_Regular[ 0 ];
    cfg_font.color = EINK200_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK200_FO_HORIZONTAL;  
    eink200_set_font( &eink_200inch, &cfg_font );
    
    text_set.n_char = 4;
    text_set.text_x = 10;
    text_set.text_y = 50;
    eink200_text( &eink_200inch, &demo_text[ 0 ], &text_set );
    text_set.n_char = 7;
    text_set.text_x = 10;
    text_set.text_y = 90;
    eink200_text( &eink_200inch, &demo_text1[ 0 ], &text_set );
    text_set.n_char = 8;
    text_set.text_x = 10;
    text_set.text_y = 130;
    eink200_text( &eink_200inch, &demo_text2[ 0 ], &text_set ); 
    Delay_ms( 5000 );
#endif
}
  
```

### Application Task

> Draws two demo images to the display with a one-second delay between each drawing.

```c

void application_task ( void )
{
    eink200_display_image ( &eink_200inch, demo_image_black );
    Delay_1sec( );
    eink200_display_image ( &eink_200inch, demo_image_white );
    Delay_1sec( );
}

```

## Note

> Due to insuficient RAM memory, only the IMAGE mode is supported with 8-bit PIC microcontrollers.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Eink200Inch

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
