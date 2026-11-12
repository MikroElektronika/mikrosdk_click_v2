
---
# WiFi 4 Click

> [WiFi 4 Click](https://www.mikroe.com/?pid_product=MIKROE-1913) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1913&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example connects WiFi 4 Click to a Wi-Fi access point. It sends a message to an echo server
> over TCP and UDP and compares each reply with the sent message.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Conversions
- MikroSDK.GenericPointer
- MikroSDK.Log
- Click.WiFi4

### Example Key Functions

- `wifi4_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void wifi4_cfg_setup ( wifi4_cfg_t *cfg );
```

- `wifi4_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t wifi4_init ( wifi4_t *ctx, wifi4_cfg_t *cfg );
```

- `wifi4_hw_reset` This function asserts reset for 100 ms, clears the UART buffers, and releases reset.
```c
void wifi4_hw_reset ( wifi4_t *ctx );
```

- `wifi4_cmd_run` This function sends a specified command to the Click module, followed by a carriage return.
```c
err_t wifi4_cmd_run ( wifi4_t *ctx, char *cmd );
```

- `wifi4_cmd_set` This function appends an equals sign and a value string to a command, then sends it using `wifi4_cmd_run`.
```c
err_t wifi4_cmd_set ( wifi4_t *ctx, char *cmd, char *value );
```

- `wifi4_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t wifi4_generic_write ( wifi4_t *ctx, uint8_t *data_in, uint16_t len );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wifi4_cfg_t wifi4_cfg;  /**< Click config object. */

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
    wifi4_cfg_setup( &wifi4_cfg );
    WIFI4_MAP_MIKROBUS( wifi4_cfg, MIKROBUS_POSITION_WIFI4 );
    if ( UART_ERROR == wifi4_init( &wifi4, &wifi4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = WIFI4_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - WIFI4_POWER_UP:
   > Resets the device and waits for the AT console. Reads the firmware version before configuring a profile.
 - WIFI4_CONFIGURE_CONNECTION:
   > Configures station mode for the selected access point using DHCP.
   > A saved profile starts at module boot and skips this stage.
 - WIFI4_WAIT_FOR_CONNECTION:
   > Waits for association and an assigned IPv4 address.
 - WIFI4_EXAMPLE:
   > Repeats the TCP and UDP echo exchanges with a five-second pause between rounds.
   > If no UDP reply arrives within the poll limit, it logs a warning and continues after closing the socket.

> Other errors halt the application until restart.

```c
void application_task ( void )
{
    err_t error_flag = WIFI4_OK;

    switch ( app_state )
    {
        case WIFI4_POWER_UP:
        {
            error_flag = wifi4_power_up( &wifi4 );
            if ( WIFI4_OK == error_flag )
            {
                if ( WIFI_PROFILE_SAVED == WIFI_PROFILE_MODE )
                {
                    app_state = WIFI4_WAIT_FOR_CONNECTION;
                    log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
                }
                else
                {
                    app_state = WIFI4_CONFIGURE_CONNECTION;
                    log_printf( &logger, ">>> APP STATE - CONFIGURE CONNECTION <<<\r\n\n" );
                }
            }
            break;
        }
        case WIFI4_CONFIGURE_CONNECTION:
        {
            error_flag = wifi4_config_connection( &wifi4 );
            if ( WIFI4_OK == error_flag )
            {
                app_state = WIFI4_WAIT_FOR_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case WIFI4_WAIT_FOR_CONNECTION:
        {
            error_flag = wifi4_check_connection( &wifi4 );
            if ( WIFI4_OK == error_flag )
            {
                app_state = WIFI4_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case WIFI4_EXAMPLE:
        {
            error_flag = wifi4_example( &wifi4 );
            break;
        }
        default:
        {
            error_flag = WIFI4_ERROR;
            break;
        }
    }

    if ( WIFI4_OK != error_flag )
    {
        log_error( &logger, " Example failed (%d). Restart the application to retry.",
                   ( int16_t ) error_flag );
        for ( ; ; );
    }
}
```

### Note

> Set WIFI_SSID and WIFI_PASSWORD for a 2.4 GHz network in volatile or save profile mode.
> An empty password selects an open network; otherwise use an 8-63 character WPA/WPA2 passphrase.
> Set REMOTE_IP and REMOTE_PORT for a reachable server that echoes the message over both TCP and UDP.
> Use printable credentials without CR, LF, or commas. Password command echoes are not logged.
> Select WIFI_PROFILE_VOLATILE for RAM-only configuration. Use WIFI_PROFILE_SAVE for one run to
> save a configured station profile, including credentials, and restart via the hardware reset pin.
> Use WIFI_PROFILE_SAVED to boot from the stored station profile without another flash write.

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
