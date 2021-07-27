
---
# Fan 3 click

Fan 3 click is the perfect choice for fan speed control and it can operate in seven discrete speed steps.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fan3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/fan-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Fan3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Fan3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void fan3_cfg_setup ( fan3_cfg_t *cfg ); 
 
- Initialization function.
> FAN3_RETVAL fan3_init ( fan3_t *ctx, fan3_cfg_t *cfg );

#### Example key functions :

- Set speed
> void fan3_set_speed ( fan3_t *ctx, uint8_t new_speed );

## Examples Description

> This application controls the fan speed.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the click device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    fan3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    fan3_cfg_setup( &cfg );
    FAN3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fan3_init( &fan3, &cfg );

    log_printf( &logger, ">>> Initialized...\r\n" );
}
  
```

### Application Task

> Cycles through different fan speeds, including 0 - stopped.

```c

void application_task ( )
{
    log_printf( &logger, "Speed 1...\r\n" );
    fan3_set_speed( ctx, FAN3_SPEED1 );
    Delay_ms( 4000 );
    log_printf( &logger, "Speed 3...\r\n" );
    fan3_set_speed( ctx, FAN3_SPEED3 );
    Delay_ms( 4000 );
    log_printf( &logger, "Speed 5...\r\n" );
    fan3_set_speed( ctx, FAN3_SPEED5 );
    Delay_ms( 4000 );
    log_printf( &logger, "Speed 7...\r\n" );
    fan3_set_speed( ctx, FAN3_SPEED7 );
    Delay_ms( 4000 );
    log_printf( &logger, "Stopped...\r\n" );
    fan3_set_speed( ctx, FAN3_STOPPED );
    Delay_ms( 4000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Fan3

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
