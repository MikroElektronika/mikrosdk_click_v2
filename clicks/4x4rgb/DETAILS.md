
---
# 4x4 RGB click

4x4 RGB click is a matrix of 16 intelligent RGB elements, forming a 4x4 display screen. 

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/4x4rgb_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/4x4-rgb-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the 4x4Rgb Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 4x4Rgb Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c4x4rgb_cfg_setup ( c4x4rgb_cfg_t *cfg ); 
 
- Initialization function.
> C4X4RGB_RETVAL c4x4rgb_init ( c4x4rgb_t *ctx, c4x4rgb_cfg_t *cfg );

#### Example key functions :

- Function for logic one.
> void c4x4rgb_logic_one ( c4x4rgb_t *ctx );
 
- Function for custom delay.
> void c4x4rgb_delay ( uint16_t delay_time, char delay_unit );  

- Get device clock.
> void c4x4rgb_get_device_clock ( c4x4rgb_t *ctx );

## Examples Description

> This application is used for powering 4x4 RGB LED matrices.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - GPIO. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c4x4rgb_cfg_t cfg;
    
    unsigned long clk;
    float one_cyc;
    uint8_t tmp;
    float first_delay;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    c4x4rgb_cfg_setup( &cfg );
    C4X4RGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c4x4rgb_init( &c4x4rgb, &cfg );

    log_printf( &logger, "  GPIO Driver Init   \r\n" );
    log_printf( &logger, "---------------------\r\n" );

    log_printf( &logger, " Fill Screen speed:  \r\n" );
    log_printf( &logger, "  25 x 5 ms = 125 ms \r\n" );
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "      ~ White ~      \r\n" );
    
    s_speed = 25;
    temp_color = C4X4RGB_COLOR_WHITE;
    c4x4rgb_fill_screen( );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

> This is an example which demonstrates the use of 4x4 RGB Click board.
> This simple example shows all ten numbers in different colors on 4x4 RGB click.
> The 4x4 RGB click carries a matrix of 16 RGB LEDs and an MCP1826 low dropout regulator.
> These LEDs actually consist of three single colored LEDs ( Red, Green and Blue ) in a single package.
> Various colors can be reproduced by mixing the intensity of each LED.

```c

void application_task ( void )
{
    log_printf( &logger, "   Set snake speed:  \r\n" );
    log_printf( &logger, "  20 x 5 ms = 100 ms \r\n" );
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "      ~ Blue ~      \r\n" );
    s_speed = 20;
    temp_color = C4X4RGB_COLOR_BLUE;
    c4x4rgb_snake( );
    log_printf( &logger, "---------------------\r\n" );
    
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "   ~ Light Blue ~    \r\n" );
    temp_color = C4X4RGB_COLOR_LIGHT_BLUE;
    c4x4rgb_snake_return( );
    log_printf( &logger, "---------------------\r\n" );

    log_printf( &logger, "   Set snake speed:  \r\n" );
    log_printf( &logger, "  15 x 5 ms = 75 ms  \r\n" );
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "      ~ Green ~      \r\n" );
    s_speed = 15;
    temp_color = C4X4RGB_COLOR_GREEN;
    c4x4rgb_snake( );
    log_printf( &logger, "---------------------\r\n" );
    
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "     ~ Yellow ~      \r\n" );
    temp_color = C4X4RGB_COLOR_YELLOW;
    c4x4rgb_snake_return( );
    log_printf( &logger, "---------------------\r\n" );

    log_printf( &logger, "   Set snake speed:  \r\n" );
    log_printf( &logger, "  10 x 5 ms = 50 ms  \r\n" );
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "       ~ Red ~       \r\n" );
    s_speed = 10;
    temp_color = C4X4RGB_COLOR_RED;
    c4x4rgb_snake( );
    log_printf( &logger, "---------------------\r\n" );
    
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "     ~ Purpule ~     \r\n" );
    temp_color = C4X4RGB_COLOR_PURPLE;
    c4x4rgb_snake_return( );
    log_printf( &logger, "---------------------\r\n" );

    log_printf( &logger, " Fill Screen speed:  \r\n" );
    log_printf( &logger, "  5 x 5 ms = 25 ms   \r\n" );
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "      ~ White ~      \r\n" );
    s_speed = 5;
    temp_color = C4X4RGB_COLOR_WHITE;
    c4x4rgb_fill_screen( );
    log_printf( &logger, "---------------------\r\n" );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.4x4Rgb

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
