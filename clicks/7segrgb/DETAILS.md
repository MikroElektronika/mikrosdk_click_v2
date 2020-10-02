
---
# 7-SEG RGB click

7-SEG RGB click carries a full color single 7 segment digit display. The click is designed to run on either 3.3V or 5V power supply. It communicates with the target microcontroller over the CS, and PWM pin on the mikroBUS™ line.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/7segrgb_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/7-seg-rgb-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the 7SegRgb Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 7SegRgb Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c7segrgb_cfg_setup ( c7segrgb_cfg_t *cfg ); 
 
- Initialization function.
> C7SEGRGB_RETVAL c7segrgb_init ( c7segrgb_t *ctx, c7segrgb_cfg_t *cfg );

- Click Default Configuration function.
> void c7segrgb_default_cfg ( c7segrgb_t *ctx );


#### Example key functions :

- This function get delay value which depending on device clock value in MHz.
> float c7segrgb_get_delay_value ( uint8_t cyc_num );
 

## Examples Description

> This click shows all ten digits on a full-color single 7 segment digit display. 
> Each segment has R, G, B LEDs that can be adjusted in 255 steps and the ability to control the brightness of all the LED.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - GPIO.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c7segrgb_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c7segrgb_cfg_setup( &cfg );
    C7SEGRGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c7segrgb_init( &c7segrgb, &cfg );

    Delay_ms( 100 );
    RGB_CONTROL_BIT = 0;
    CS_BIT = 0;
}
  
```

### Application Task

> This is an example which demonstrates the use of 7-SEG RGB Click board.
> This simple example shows all ten digits in different colors on 7-SEG RGB click.

```c

void application_task ( void )
{
    uint8_t cnt_i;
    uint8_t cnt_j;
    
    for ( cnt_i = 0; cnt_i < 10; cnt_i++ )
    {
        for ( cnt_j = 10; cnt_j > 0; cnt_j-- )
        {
            set_seven_segment( CHARACTER_TABLE[ cnt_i ], 4 * cnt_i, 4 * cnt_j, cnt_i * cnt_j );
            Delay_ms( 100 );
        }
    }
    
    set_seven_segment( C7SEGRGB_POINT, 10, 10, 10 );
    Delay_ms( 1000 );
    
    set_seven_segment( C7SEGRGB_ZERO, 40, 40, 40 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_ONE, 40, 0, 0 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_TWO, 0, 40, 0 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_THREE, 0, 0, 40 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_FOUR, 40, 0, 40 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_FIVE, 0, 40, 40 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_SIX, 40, 40, 0 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_SEVEN, 20, 30, 40 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_EIGHT, 40, 15, 31 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_NINE, 20, 10, 30 );
    Delay_ms( 1000 );
     
    RGB_CONTROL_BIT = 0;
}

```

## Note

> <pre>
> Additional Functions :
> void logic_one ( )  - Generic logic one function.
> void logic_zero ( ) - Generic logic zero function.
> void set_color ( uint8_t green, uint8_t red, uint8_t blue ) 
>                     - Set the color of the  LSB segment of the display function.
> void set_seven_segment ( uint8_t  character, uint8_t green_brightness, uint8_t red_brightness, uint8_t blue_brightness )
>                     -Set whole character and color function.
> </pre>

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.7SegRgb

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
