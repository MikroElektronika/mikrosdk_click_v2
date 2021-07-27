\mainpage Main Page

---
# SolidSwitch click

SolidSwitch Click is a compact add-on board that contains load switch devices. This board features the TPS22918, four single-channel load switches from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/solidswitch_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/solidswitch-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the SolidSwitch Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SolidSwitch Click driver.

#### Standard key functions :

- `solidswitch_cfg_setup` Config Object Initialization function.
```c
void solidswitch_cfg_setup ( solidswitch_cfg_t *cfg );
```

- `solidswitch_init` Initialization function.
```c
err_t solidswitch_init ( solidswitch_t *ctx, solidswitch_cfg_t *cfg );
```

- `solidswitch_default_cfg` Click Default Configuration function.
```c
err_t solidswitch_default_cfg ( solidswitch_t *ctx );
```

#### Example key functions :

- `solidswitch_write_single` SolidSwitch I2C writing logic state function.
```c
err_t solidswitch_write_single ( solidswitch_t *ctx, uint8_t logic_state );
```

- `solidswitch_read_single` SolidSwitch I2C reading logic state function.
```c
err_t solidswitch_read_single ( solidswitch_t *ctx, uint8_t *logic_state );
```

- `solidswitch_reset` SolidSwitch reset function.
```c
void solidswitch_reset ( solidswitch_t *ctx );
```

## Example Description

> This example demonstrates the use of SolidSwitch click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch_cfg_t solidswitch_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    solidswitch_cfg_setup( &solidswitch_cfg );
    SOLIDSWITCH_MAP_MIKROBUS( solidswitch_cfg, MIKROBUS_1 );
    err_t init_flag = solidswitch_init( &solidswitch, &solidswitch_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    solidswitch_default_cfg ( &solidswitch );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Enables different outputs every 3 seconds and displays all enabled outputs on USB UART.

```c

void application_task ( void )
{
    solidswitch_write_single ( &solidswitch, SOLIDSWITCH_ENABLE_OUT0 | SOLIDSWITCH_ENABLE_OUT1 );
    solidswitch_display_enabled_channels( );
    Delay_ms ( 3000 );
    solidswitch_write_single ( &solidswitch, SOLIDSWITCH_ENABLE_OUT6 | SOLIDSWITCH_ENABLE_OUT7 );
    solidswitch_display_enabled_channels( );
    Delay_ms ( 3000 );
    solidswitch_write_single ( &solidswitch, SOLIDSWITCH_ENABLE_ALL_OUTPUTS );
    solidswitch_display_enabled_channels( );
    Delay_ms ( 3000 );
    solidswitch_write_single ( &solidswitch, SOLIDSWITCH_DISABLE_ALL_OUTPUTS );
    solidswitch_display_enabled_channels( );
    Delay_ms ( 3000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SolidSwitch

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
