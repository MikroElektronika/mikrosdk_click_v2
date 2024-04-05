
---
# Buck 10 click

Buck 10 Click is a high-efficiency step-down converter which provides a highly regulated output voltage derived from the connected power source, rated from 4V to 18V. The regulated output voltage can be selected between two values: 3.3V and 5V. These are voltage values ​​that are most commonly used in many embedded designs. This click is based around an integrated DC-DC converter, labeled as MPM3632C.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buck-10-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the Buck10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Buck10 Click driver.

#### Standard key functions :

- `buck10_cfg_setup` Config Object Initialization function.
```c
void buck10_cfg_setup ( buck10_cfg_t *cfg );
```

- `buck10_init` Initialization function.
```c
err_t buck10_init ( buck10_t *ctx, buck10_cfg_t *cfg );
```

#### Example key functions :

- `buck10_set_device_mode` This function enables and disables output of this click board.
```c
void buck10_set_device_mode ( buck10_t *ctx, uint8_t mode);
```

## Example Description

> Demo application shows basic usage of Buck 10 click.

**The demo application is composed of two sections :**

### Application Init

> Configuring clicks and log objects. Settings the click in the default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck10_cfg_t buck10_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.

    buck10_cfg_setup( &buck10_cfg );
    BUCK10_MAP_MIKROBUS( buck10_cfg, MIKROBUS_1 );
    if ( buck10_init( &buck10, &buck10_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Enable and Disable device every 5 seconds.

```c

void application_task ( void ) 
{
    buck10_set_device_mode ( &buck10, BUCK10_DEVICE_ENABLE );
    log_printf(&logger, "Output:\t ENABLED\r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck10_set_device_mode ( &buck10, BUCK10_DEVICE_DISABLE );
    log_printf(&logger, "Output:\t DISABLED\r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

## Note

> Input voltage recommended range - from 4V to 18V Low-side valley current limit - from 3A to 3.9A Low-side negative current limit - (-2.5A) Output voltage - 3.3V or 5V

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
