\mainpage Main Page
 
 

---
# LED Driver 3 click

LED Driver 3 click is an RGB LED driver, capable of driving RGB LEDs with up to 30mA per segment, via the digital I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver3_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/led-driver-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the LedDriver3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LedDriver3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void leddriver3_cfg_setup ( leddriver3_cfg_t *cfg ); 
 
- Initialization function.
> LEDDRIVER3_RETVAL leddriver3_init ( leddriver3_t *ctx, leddriver3_cfg_t *cfg );

- Click Default Configuration function.
> void leddriver3_default_cfg ( leddriver3_t *ctx );


#### Example key functions :

- This function sets the color of the rgb LEDs through the parameters for red, green and blue.
> void leddriver3_set_rgb_color ( leddriver3_t *ctx, rgb_t *rgb );
 
- This function sets color.
> void leddriver3_set_color ( leddriver3_t *ctx, uint32_t color );

- This function sets timer for increase or decrease light.
> void leddriver3_set_timer ( leddriver3_t *ctx, uint8_t time );

## Examples Description

> This app changes color and intensity of light.

**The demo application is composed of two sections :**

### Application Init 

> Driver initialize.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver3_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    leddriver3_cfg_setup( &cfg );
    LEDDRIVER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver3_init( &leddriver3, &cfg );
}
  
```

### Application Task

> Changes color and intensity of light.

```c

void application_task ( void )
{
    rgb.red = 0x40;
    rgb.green = 0x7F;
    rgb.blue = 0x80;

    leddriver3_set_intensity( &leddriver3, LEDDRIVER3_INCREMENT | LEDDRIVER3_INTENSITY_8 );
    leddriver3_set_timer( &leddriver3, LEDDRIVER3_TIMER_8ms | LEDDRIVER3_TIMER_16ms );
    leddriver3_set_color( &leddriver3, LEDDRIVER3_COLOR_RED );
    Delay_1sec( );
    
    leddriver3_set_intensity( &leddriver3, LEDDRIVER3_CONSTANT | LEDDRIVER3_INTENSITY_16 );
    leddriver3_set_color( &leddriver3, LEDDRIVER3_COLOR_YELLOW );
    Delay_1sec( );
    leddriver3_set_color( &leddriver3, LEDDRIVER3_COLOR_BLUE );
    Delay_1sec( );

    leddriver3_set_rgb_color( &leddriver3, &rgb );
    Delay_1sec( );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver3

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
