
 

---
# 16x9 click

16x9 click is an array of 144 LEDs, driven by a single IC with relatively low pin count (28).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/16x9g_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/16x9-g-click)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the 16x9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 16x9 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c16x9_cfg_setup ( c16x9_cfg_t *cfg ); 
 
- Initialization function.
> C16X9_RETVAL c16x9_init ( c16x9_t *ctx, c16x9_cfg_t *cfg );


#### Example key functions :

- Draw rectangle.
> void c16x9_draw_rectangle( c16x9_t *ctx,  c16x9_rectangle_t *rectangle );
 
- Image display function.
> void c16x9_display_image ( c16x9_t *ctx, c16x9_image_t *image );

- Functions for draw point.
> void c16x9_draw_point ( c16x9_t *ctx, c16x9_point_t *point );

## Examples Description

> Demo application is used to shows basic controls 16x9 click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Set basic images and characters to be drawn on the screen.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c16x9_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c16x9_cfg_setup( &cfg );
    C16X9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c16x9_init( &c16x9, &cfg );

    // Image ON

    image_on.buf[ 0 ] = 0x0000;
    image_on.buf[ 1 ] = 0xC630;
    image_on.buf[ 2 ] = 0x6318;
    image_on.buf[ 3 ] = 0x318C;
    image_on.buf[ 4 ] = 0x18C6;
    image_on.buf[ 5 ] = 0x318C;
    image_on.buf[ 6 ] = 0x6318;
    image_on.buf[ 7 ] = 0xC630;
    image_on.buf[ 8 ] = 0x0000;

    image_on.frame = C16X9_FRAME_1;
    image_on.pwm = 250;

    // Image OFF

    image_off.buf[ 0 ] = 0xFFFF;
    image_off.buf[ 1 ] = 0x39CF;
    image_off.buf[ 2 ] = 0x9CE7;
    image_off.buf[ 3 ] = 0xCE73;
    image_off.buf[ 4 ] = 0xE739;
    image_off.buf[ 5 ] = 0xCE73;
    image_off.buf[ 6 ] = 0x9CE7;
    image_off.buf[ 7 ] = 0x39CF;
    image_off.buf[ 8 ] = 0xFFFF;

    image_off.frame = C16X9_FRAME_1;
    image_off.pwm = 250;

    // Char

    data_char.character = 'G';
    data_char.frame = C16X9_FRAME_1;
    data_char.pwm = 250;

    // Rectangle

    rectangle.x = 1;
    rectangle.y = 4;
    rectangle.width = 6;
    rectangle.height = 4;
    rectangle.frame = C16X9_FRAME_1;
    rectangle.pwm = 250;
}
```

### Application Task

> Display character, image and rectangle every 1 second.

```c
void application_task ( void )
{
    //  Task implementation.

    c16x9_display_refresh( &c16x9 );
    c16x9_display_byte( &c16x9, &data_char );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    c16x9_display_refresh( &c16x9 );
    c16x9_display_image( &c16x9, &image_on );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    c16x9_display_refresh( &c16x9 );
    c16x9_display_image( &c16x9, &image_off );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    c16x9_display_refresh( &c16x9 );
    c16x9_draw_rectangle( &c16x9, &rectangle );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.16x9

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


