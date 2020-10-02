
---
# LED Driver 8 click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the LedDriver8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LedDriver8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void leddriver8_cfg_setup ( leddriver8_cfg_t *cfg ); 
 
- Initialization function.
> LEDDRIVER8_RETVAL leddriver8_init ( leddriver8_t *ctx, leddriver8_cfg_t *cfg );

#### Example key functions :

- Function for set Brightness
> void leddriver8_set_brightness ( leddriver8_t *ctx, uint8_t num_led, uint8_t value );
 
- Function for set output gain
> void leddriver8_set_output_gain ( leddriver8_t *ctx, uint8_t num_led, uint8_t value );

- Function for set mode registers
> void leddriver8_set_mode_register( leddriver8_t *ctx, uint8_t mode_1, uint8_t mode_2 );

## Examples Description

> This demo app sets brightness.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and sets module for working

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver8_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    leddriver8_cfg_setup( &cfg );
    LEDDRIVER8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver8_init( &leddriver8, &cfg );

    leddriver8_reset( &leddriver8 );
    Delay_ms( 500 );
    
    leddriver8_output_enable_pin( &leddriver8, LEDDRIVER8_ENABLE_LED_OUTPUTS );
    leddriver8_set_output_gain( &leddriver8, LEDDRIVER8_OUTPUT_GAIN_ALL_LED, LEDDRIVER8_FULL_OUTPUT_CURRENT_GAIN );
    leddriver8_set_mode_register( &leddriver8, LEDDRIVER8_MODE1_NORMAL_MODE, LEDDRIVER8_MODE2_DMBLNK_DIMMING |
                                  LEDDRIVER8_MODE2_CLRERR_ALL | LEDDRIVER8_MODE2_EXP_DISABLE );
}
  
```

### Application Task

> Changes brightness on all LEDs. 
> Controls are blinking on one LED.

```c

void application_task ( void )
{
    uint8_t cnt;

    for ( cnt = 0; cnt < 0xFF; cnt++ )
    {
        leddriver8_set_brightness( &leddriver8, LEDDRIVER8_BRIGHTNESS_ALL_LED, cnt );
        Delay_ms( 15 );
    }
    
    for ( cnt = 0; cnt < 5; cnt++ )
    {
       leddriver8_set_brightness( &leddriver8, LEDDRIVER8_LED_0, 200 );
       Delay_ms( 1000 );
       leddriver8_set_brightness( &leddriver8, LEDDRIVER8_LED_0, 0 );
       Delay_ms( 1000 );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver8

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
