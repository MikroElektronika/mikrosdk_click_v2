\mainpage Main Page
 
---
# Expand 6 click

EXPAND 6 Click is a compact add-on board that contains an I2C configurable multi-port I/O expander with independently configurable pins as bi-directional input/outputs or PWM outputs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand6_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/expand-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Expand6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void expand6_cfg_setup ( expand6_cfg_t *cfg ); 
 
- Initialization function.
> EXPAND6_RETVAL expand6_init ( expand6_t *ctx, expand6_cfg_t *cfg );

#### Example key functions :

- Set all OUTPUT pins' logic levels in one port function
> void expand6_write_port ( expand6_t *ctx, uint8_t port, uint8_t value );
 
- Reset function
> void expand6_reset ( expand6_t *ctx );

- Set a single OUTPUT pin's logic level function
> void expand6_write_pin ( expand6_t *ctx, uint16_t pin, uint8_t pin_val );

## Examples Description

> This example demonstrates the use of EXPAND 6 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    expand6_cfg_setup( &cfg );
    EXPAND6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand6_init( &expand6, &cfg );

    expand6_reset ( &expand6 );
    Delay_ms( 1000 );
    
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   EXPAND 6 click   \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}
  
```

### Application Task

> This example shows the capabilities of the EXPAND 6 click by toggling each of the 20 available pins.

```c

void application_task ( void )
{
    expand6_write_port( &expand6, EXPAND6_PORT_0, 0xFF );
    expand6_write_port( &expand6, EXPAND6_PORT_1, 0xFF );
    expand6_write_port( &expand6, EXPAND6_PORT_2, 0xFF );
    
    log_printf( &logger, "All pins set to HIGH logic level!\r\n" );
    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms( 2000 );
    
    for ( pin_num = 0; pin_num < 20; pin_num++ )
    {
        expand6_write_pin( &expand6, pin_num, EXPAND6_LOW );
        log_printf( &logger, "Pin %u is set to LOW logic level!\r\n", ( uint16_t) pin_num );
        Delay_ms( 300 );
    }

    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand6

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
