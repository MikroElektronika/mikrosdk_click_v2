
---
# eINK 1.54 inch display

eINK click is an adapter Click board™, used to interface a compatible eINK display with the host MCU.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eink_click_bundle154inch.png">
</p>

[click Product page](https://www.mikroe.com/e-paper-bundle-1)

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

- `eink154inch_cfg_setup` Config Object Initialization function.
```c
void eink154inch_cfg_setup ( eink154inch_cfg_t *cfg ); 
```

- `eink154inch_init` Initialization function.
```c
err_t eink154inch_init ( eink154inch_t *ctx, eink154inch_cfg_t *cfg );
```

#### Example key functions :

- `eink154inch_set_lut` Set LUT table
```c
void eink154inch_set_lut ( eink154inch_t *ctx, const uint8_t *lut, uint8_t n_bytes );
```

- `eink154inch_image` Displays image
```c
void eink154inch_image ( eink154inch_t *ctx, const uint8_t* image_buffer );
```

- `eink154inch_set_font` Set text font
```c
void eink154inch_set_font ( eink154inch_t *ctx, eink154inch_font_t *cfg_font );
```

## Examples Description

> This application demonstrates the use of eINK click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the click board for 1.54 inch eINK display.
> After that, if the TEXT mode is supported, shows a desired text messages on the display.

```c

void application_init ( void )
{
    eink154inch_cfg_t cfg;   
    eink154inch_font_t cfg_font;
    eink154inch_text_set_t text_set;

    //  Click initialization.
    eink154inch_cfg_setup( &cfg );
    EINK154INCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eink154inch_init( &eink154inch, &cfg );

    eink154inch_start_config( &eink154inch );
    eink154inch_set_lut( &eink154inch, eink154inch_lut_table, 30 );
    Delay_ms( 1000 );
    
#ifndef IMAGE_MODE_ONLY
    cfg_font.p_font = &guiFont_Tahoma_18_Regular[ 0 ];
    cfg_font.color = EINK154INCH_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK154INCH_FO_HORIZONTAL;  
    
    eink154inch_set_font( &eink154inch, &cfg_font );
    text_set.n_char = 4;
    text_set.text_x = 10;
    text_set.text_y = 50;
    eink154inch_text( &eink154inch, &demo_text[ 0 ], &text_set );
    text_set.n_char = 7;
    text_set.text_x = 10;
    text_set.text_y = 90;
    eink154inch_text( &eink154inch, &demo_text1[ 0 ], &text_set );
    text_set.n_char = 8;
    text_set.text_x = 10;
    text_set.text_y = 130;
    eink154inch_text( &eink154inch, &demo_text2[ 0 ], &text_set ); 
    Delay_ms( 5000 );
#endif
}
  
```

### Application Task

> Draws two demo images to the display with a one-second delay between each drawing.

```c

void application_task ( void )
{
    eink154inch_image( &eink154inch, &demoImage_light[ 0 ] );
    Delay_1sec( );
    eink154inch_image( &eink154inch, &demoImage_dark[ 0 ] );
    Delay_1sec( );
}

```

## Note

> Due to insuficient RAM memory, only the IMAGE mode is supported with 8-bit PIC and AVR microcontrollers.

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
