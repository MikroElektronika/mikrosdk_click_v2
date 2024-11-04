\mainpage Main Page

---
# Buck 9 Click

Buck 9 Click is a high-efficiency step-down converter which provides a highly regulated output voltage derived from the connected power source, rated from 4V to 36V. The regulated output voltage can be selected between two values: 3.3V and 5V. These are voltage values ​​that are most commonly used in many embedded designs. Buck 9 Click is based around an integrated DC-DC converter, labeled as MP9943. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck9_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/buck-9-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the Buck9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Buck9 Click driver.

#### Standard key functions :

- `buck9_cfg_setup` Config Object Initialization function.
```c
void buck9_cfg_setup ( buck9_cfg_t *cfg );
```

- `buck9_init` Initialization function.
```c
err_t buck9_init ( buck9_t *ctx, buck9_cfg_t *cfg );
```

#### Example key functions :

- `buck9_set_device_mode` This function enables and disables output of this Click board.
```c
void buck9_set_device_mode ( buck9_t *ctx, uint8_t mode);
```

## Example Description

> Demo application shows basic usage of Buck 9 Click.

**The demo application is composed of two sections :**

### Application Init

> Configuring clicks and log objects. Settings the Click in the default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck9_cfg_t buck9_cfg;  /**< Click config object. */

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

    buck9_cfg_setup( &buck9_cfg );
    BUCK9_MAP_MIKROBUS( buck9_cfg, MIKROBUS_1 );
    if ( buck9_init( &buck9, &buck9_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
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
    buck9_set_device_mode ( &buck9, BUCK9_DEVICE_ENABLE );
    log_printf(&logger, "Output:\t ENABLED\r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck9_set_device_mode ( &buck9, BUCK9_DEVICE_DISABLE );
    log_printf(&logger, "Output:\t DISABLED\r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

## Note

> User can connect from 3v3 or 5v to 36V on the input(VIN) and when enable the device get 3v3 or 5v voltage on the output(VOUT). On the VOUT connect the load to 3A.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
