\mainpage Main Page

---
# NINA-W152 Click

> NINA-W152 Click is a compact add-on board designed for seamless integration of Wi-Fi and Bluetooth communication into your projects. Based on the NINA-W152 multi-radio module from u-blox, this Click board™ provides dual-mode wireless connectivity, including Wi-Fi 802.11b/g/n and Bluetooth BR/EDR v4.2+EDR and Bluetooth Low Energy v4.2. It features an internal PIFA antenna for optimal performance and supports communication through UART and SPI interfaces, with secure boot and enterprise-level security protocols (WPA2/WPA3) ensuring reliable operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ninaw152_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/nina-w152-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : UART/SPI type


# Software Support

We provide a library for the NINA-W152 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NINA-W152 Click driver.

#### Standard key functions :

- `ninaw152_cfg_setup` Config Object Initialization function.
```c
void ninaw152_cfg_setup ( ninaw152_cfg_t *cfg );
```

- `ninaw152_init` Initialization function.
```c
err_t ninaw152_init ( ninaw152_t *ctx, ninaw152_cfg_t *cfg );
```

#### Example key functions :

- `ninaw152_reset_device` This function resets the device by toggling the RST pin state.
```c
void ninaw152_reset_device ( ninaw152_t *ctx );
```

- `ninaw152_send_cmd` This function sends a specified command to the Click module.
```c
void ninaw152_send_cmd ( ninaw152_t *ctx, uint8_t *cmd );
```

- `ninaw152_send_cmd_with_par` This function sends a command with specified parameter to the Click module.
```c
void ninaw152_send_cmd_with_par ( ninaw152_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );
```

## Example Description

> Application example shows device capability of connecting to a WiFi network and
sending TCP/UDP messages to an echo server, or processing data from a connected BT device.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ninaw152_cfg_t ninaw152_cfg;  /**< Click config object. */

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
    ninaw152_cfg_setup( &ninaw152_cfg );
    NINAW152_MAP_MIKROBUS( ninaw152_cfg, MIKROBUS_1 );
    if ( NINAW152_OK != ninaw152_init( &ninaw152, &ninaw152_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = NINAW152_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

```

### Application Task

> Application task is split in few stages:
 - NINAW152_POWER_UP: 
   > Powers up the device, performs a factory reset and reads system information.
 - NINAW152_CONFIGURE_CONNECTION: 
   > Configures connection to WiFi or BT depending on the selected example.
 - NINAW152_WAIT_FOR_CONNECTION:
   > Checks the connection to WiFi access point.
 - NINAW152_EXAMPLE:
   > Depending on the selected demo example, it sends a TCP/UDP message to an echo server over a WiFi network or processes all data from a connected BT device and sends back an adequate response message.

> By default, the WiFi TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case NINAW152_POWER_UP:
        {
            if ( NINAW152_OK == ninaw152_power_up( &ninaw152 ) )
            {
                app_state = NINAW152_CONFIGURE_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIGURE CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case NINAW152_CONFIGURE_CONNECTION:
        {
            if ( NINAW152_OK == ninaw152_config_connection( &ninaw152 ) )
            {
                app_state = NINAW152_WAIT_FOR_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case NINAW152_WAIT_FOR_CONNECTION:
        {
            if ( NINAW152_OK == ninaw152_check_connection( &ninaw152 ) )
            {
                app_state = NINAW152_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case NINAW152_EXAMPLE:
        {
            ninaw152_example( &ninaw152 );
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

## Note

> For the BT example, we have used the Serial Bluetooth Terminal smartphone application for the test. A smartphone and the Click board must be paired to exchange messages.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NINAW152

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
