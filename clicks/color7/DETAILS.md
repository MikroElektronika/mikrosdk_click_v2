
 

---
# Color 7 click

Color 7 click is a very accurate color sensing Click board which features the TCS3472 color light to digital converter with IR filter, from ams. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/color-7-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Color7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Color7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void color7_cfg_setup ( color7_cfg_t *cfg ); 
 
- Initialization function.
> COLOR7_RETVAL color7_init ( color7_t *ctx, color7_cfg_t *cfg );

- Click Default Configuration function.
> void color7_default_cfg ( color7_t *ctx );


#### Example key functions :

- Functions for detect colors
> uint8_t color7_get_color( color7_t *ctx );
 
- Get interrut pin state
> uint8_t color7_get_interrupt_state ( color7_t *ctx );

- Functions for read color ratio
> float color7_read_color_ratio ( color7_t *ctx, uint8_t color );

## Examples Description

> Demo application reads and detects colors - detected color logs on USBUART.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    color7_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    color7_cfg_setup( &cfg );
    COLOR7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color7_init( &color7, &cfg );

    color7_default_cfg( &color7 );
    log_info( &logger, "---- Start measurement ----" );
}
```

### Application Task

> Reads light color and checks which color of light is detected by the sensor
> If the light color is detected, the detected color message is logged on the USBUART.

```c
void application_task ( void )
{
    uint8_t color;

    //  Task implementation.

    color = color7_get_color( &color7 );

    switch( color )
    {
        case 1:
        {
            log_printf( &logger, "--- Color: ORANGE \r\n" );
            break;
        }
        case 2:
        {
            log_printf( &logger, "--- Color: RED \r\n" );
            break;
        }
        case 3:
        {
            log_printf( &logger, "--- Color: PINK \r\n" );
            break;
        }
        case 4:
        {
            log_printf( &logger, "--- Color: PURPLE \r\n" );
            break;
        }
        case 5:
        {
            log_printf( &logger, "--- Color: BLUE \r\n" );
            break;
        }
        case 6:
        {
            log_printf( &logger, "--- Color: CYAN \r\n" );
            break;
        }
        case 7:
        {
            log_printf( &logger, "--- Color: GREEN \r\n" );
            break;
        }
        case 8:
        {
            log_printf( &logger, "--- Color: YELLOW \r\n" );
            break;
        }
    }
    Delay_100ms();
}
```

## Note

> Light source must be pointed towards sensor in order for sensor to 
> detect light source color correctly.
> We used the HSL color palette on the monitor as an example.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Color7

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
