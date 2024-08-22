\mainpage Main Page

---
# UWB 4 click

> UWB 4 Click is a compact add-on board for precise indoor positioning and location-based applications. This board features the Sera NX040 (453-00174C) from Ezurio, featuring NXP's SR040 chipset for ultra-wideband (UWB) and Nordic Semiconductor's nRF52833 for Bluetooth LE. The module supports IEEE 802.15.4/4z HPR UWB operations, providing exceptional ranging accuracy of less than ±10 cm with a typical receiver sensitivity of -92 dBm.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uwb4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uwb-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : UART type


# Software Support

We provide a library for the UWB 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for UWB 4 Click driver.

#### Standard key functions :

- `uwb4_cfg_setup` Config Object Initialization function.
```c
void uwb4_cfg_setup ( uwb4_cfg_t *cfg );
```

- `uwb4_init` Initialization function.
```c
err_t uwb4_init ( uwb4_t *ctx, uwb4_cfg_t *cfg );
```

#### Example key functions :

- `uwb4_cmd_run` This function sends a specified command to the click module.
```c
void uwb4_cmd_run ( uwb4_t *ctx, uint8_t *cmd );
```

- `uwb4_cmd_set` This function sets a value to a specified command of the click module.
```c
void uwb4_cmd_set ( uwb4_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `uwb4_reset_device` This function resets the device by toggling the reset pin logic state.
```c
void uwb4_reset_device ( uwb4_t *ctx );
```

## Example Description

> This example demonstrates the use of UWB 4 click board by showing the UWB ranging between two click boards configured as initiator and responder.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uwb4_cfg_t uwb4_cfg;  /**< Click config object. */

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
    uwb4_cfg_setup( &uwb4_cfg );
    UWB4_MAP_MIKROBUS( uwb4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == uwb4_init( &uwb4, &uwb4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = UWB4_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

```

### Application Task

> Application task is split in few stages:
 - UWB4_POWER_UP: 
   > Powers up the device and reads system information.
 - UWB4_CONFIG_EXAMPLE: 
   > Configures device for UWB ranging.
 - UWB4_EXAMPLE:
   > Reads and parses the UWB ranging information.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case UWB4_POWER_UP:
        {
            if ( UWB4_OK == uwb4_power_up( &uwb4 ) )
            {
                app_state = UWB4_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case UWB4_CONFIG_EXAMPLE:
        {
            if ( UWB4_OK == uwb4_config_example( &uwb4 ) )
            {
                app_state = UWB4_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case UWB4_EXAMPLE:
        {
            uwb4_example( &uwb4 );
            break;
        }
        default:
        {
            log_error( &logger, " APP STATE." );
            break;
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.UWB4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
