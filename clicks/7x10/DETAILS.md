

---
# 7x10 click

7x10 click is a LED dot matrix display click, which can be used to display graphics or letters in a very simple and easy way. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/7x10-click-groupp.png" height=300px>
</p>

> - [Product page - 7x10 Y click](https://www.mikroe.com/7x10-y-click)
> - [Product page - 7x10 G click](https://www.mikroe.com/7x10-g-click)
> - [Product page - 7x10 B click](https://www.mikroe.com/7x10-b-click)
> - [Product page - 7x10 R click](https://www.mikroe.com/7x10-r-click)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the 7x10 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 7x10 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c7x10_cfg_setup ( c7x10_cfg_t *cfg ); 
 
- Initialization function.
> C7X10_RETVAL c7x10_init ( c7x10_t *ctx, c7x10_cfg_t *cfg );


#### Example key functions :

- Draw pixel (function).
> void c7x10_draw_pixel ( c7x10_t *ctx, c7x10_pixel_t *pixel, uint8_t mode, uint8_t px_delay );
 
- Draw char (function).
> void c7x10_draw_char ( c7x10_t *ctx, char ch, uint8_t pos, uint8_t ch_delay );

- Draw number (function).
> void c7x10_draw_number ( c7x10_t *ctx, uint8_t num, uint16_t num_delay );

## Examples Description

> This demo example shows a drawing of pixels, characters and a number on the screen.

**The demo application is composed of two sections :**

### Application Init 

> Configuring the click board.

```c
void application_init ( void )
{
    c7x10_cfg_t cfg;

    //  Click initialization.

    c7x10_cfg_setup( &cfg );
    C7X10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c7x10_init( &c7x10, &cfg );
}
```

### Application Task

> Draws characters, numbers, and pixels to the display.

```c
void application_task ( void )
{
    c7x10_pixel_t pixel;
    uint8_t cnt;
    uint8_t cnt_x;
    uint8_t cnt_y;
    
    // CHAR PROCEDURE
    for ( cnt = 'A'; cnt < 'Z'; cnt+=2 )
    {
        c7x10_draw_char( &c7x10, cnt, C7X10_DISPLAY_LEFT, C7X10_DISPLAY_DELAY_50MS );
        c7x10_draw_char( &c7x10, cnt + 1, C7X10_DISPLAY_RIGHT |
                                          C7X10_DISPLAY_REFRESH,
                                          C7X10_DISPLAY_DELAY_50MS );
        Delay_ms( 1000 );
    }

    // COUNTER PROCEDURE
    for ( cnt = 0; cnt < 15; cnt++ )
    {
        c7x10_draw_number( &c7x10, cnt, C7X10_DISPLAY_DELAY_50MS );
        Delay_ms( 500 );
    }
    
    // PIXELS PROCEDURE
    for ( cnt_x = 0; cnt_x <= 7; cnt_x++ )
    {
        for ( cnt_y = 0; cnt_y <= 10; cnt_y++ )
        {
            pixel.cord_x = cnt_x;
            pixel.cord_y = cnt_y;
            c7x10_draw_pixel( &c7x10, &pixel, C7X10_DISPLAY_PIXEL_STORAGE,
                                              C7X10_DISPLAY_DELAY_20MS );

            pixel.cord_x = cnt_x;
            pixel.cord_y = cnt_y + 1;
            c7x10_draw_pixel( &c7x10, &pixel, C7X10_DISPLAY_PIXEL_REFRESH,
                                              C7X10_DISPLAY_DELAY_20MS );
        }
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.7x10

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
