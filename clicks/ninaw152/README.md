
---
# NINA-W152 Click

> [NINA-W152 Click](https://www.mikroe.com/?pid_product=MIKROE-6154) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6154&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : UART/SPI type

# Software Support

## Example Description

> Application example shows device capability of connecting to a WiFi network and
sending TCP/UDP messages to an echo server, or processing data from a connected BT device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NINAW152

### Example Key Functions

- `ninaw152_cfg_setup` Config Object Initialization function.
```c
void ninaw152_cfg_setup ( ninaw152_cfg_t *cfg );
```

- `ninaw152_init` Initialization function.
```c
err_t ninaw152_init ( ninaw152_t *ctx, ninaw152_cfg_t *cfg );
```

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

### Note

> For the BT example, we have used the Serial Bluetooth Terminal smartphone application for the test. A smartphone and the Click board must be paired to exchange messages.

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
