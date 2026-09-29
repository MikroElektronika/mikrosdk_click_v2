
---
# DeviceDrive Click

> [DeviceDrive Click](https://www.mikroe.com/?pid_product=MIKROE-3663) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3663&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of DeviceDrive Click by sending numbered JSON messages to an HTTPS echo endpoint and displaying the server responses.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DeviceDrive

### Example Key Functions

- `devicedrive_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void devicedrive_cfg_setup ( devicedrive_cfg_t *cfg );
```

- `devicedrive_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t devicedrive_init ( devicedrive_t *ctx, devicedrive_cfg_t *cfg );
```

- `devicedrive_hw_reset` This function enables the module, holds reset low for 300 ms, clears the UART buffers, and releases reset.
```c
void devicedrive_hw_reset ( devicedrive_t *ctx );
```

- `devicedrive_set_network` This function sends the WiFi network name and password in one setup command.
```c
err_t devicedrive_set_network ( devicedrive_t *ctx, char *ssid, char *password );
```

- `devicedrive_set_server` This function sends the HTTPS master endpoint URL in a setup command.
```c
err_t devicedrive_set_server ( devicedrive_t *ctx, char *url );
```

- `devicedrive_send_message` This function sends a cloud payload followed by EOT in receive mode, or ETX and EOT in send-only mode.
```c
err_t devicedrive_send_message ( devicedrive_t *ctx, char *message, uint8_t mode );
```

### Application Init

> Initializes the logger and the Click UART driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    devicedrive_cfg_t devicedrive_cfg;  /**< Click config object. */

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
    devicedrive_cfg_setup( &devicedrive_cfg );
    DEVICEDRIVE_MAP_MIKROBUS( devicedrive_cfg, MIKROBUS_POSITION_DEVICEDRIVE );
    if ( UART_ERROR == devicedrive_init( &devicedrive, &devicedrive_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Application task is split into four states:
> - `DEVICEDRIVE_POWER_UP`: Resets the module and waits for its startup-ready sequence.
> - `DEVICEDRIVE_CONFIG_EXAMPLE`: Configures the HTTPS endpoint and WiFi network without using the DeviceDrive cloud.
> - `DEVICEDRIVE_EXAMPLE`: Checks the WiFi connection, sends a numbered message, and displays the echo response.
> - `DEVICEDRIVE_STOPPED`: Stops cloud transfers after an unexpected module restart.

```c
void application_task ( void )
{
    err_t error_flag = DEVICEDRIVE_OK;

    switch ( app_state )
    {
        case DEVICEDRIVE_POWER_UP:
        {
            log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\r\n" );
            error_flag = devicedrive_power_up( &devicedrive );
            if ( DEVICEDRIVE_OK == error_flag )
            {
                app_state = DEVICEDRIVE_CONFIG_EXAMPLE;
            }
            break;
        }
        case DEVICEDRIVE_CONFIG_EXAMPLE:
        {
            log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\r\n" );
            error_flag = devicedrive_config_example( &devicedrive );
            if ( DEVICEDRIVE_OK == error_flag )
            {
                app_state = DEVICEDRIVE_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\r\n" );
            }
            break;
        }
        case DEVICEDRIVE_EXAMPLE:
        {
            error_flag = devicedrive_example( &devicedrive );
            break;
        }
        case DEVICEDRIVE_STOPPED:
        {
            break;
        }
        default:
        {
            app_state = DEVICEDRIVE_POWER_UP;
            break;
        }
    }

    if ( DEVICEDRIVE_ERROR_RESTARTED == error_flag )
    {
        log_error( &logger, " Module restarted during the cloud request. Transfers stopped." );
        log_info( &logger, " Check module firmware and 3.3 V supply before restarting." );
        app_state = DEVICEDRIVE_STOPPED;
    }
    else if ( DEVICEDRIVE_OK != error_flag )
    {
        log_error( &logger, " Communication error: %d. Restarting module.", ( int16_t ) error_flag );
        app_state = DEVICEDRIVE_POWER_UP;
        Delay_ms( 1000 );
        Delay_ms( 1000 );
        Delay_ms( 1000 );
        Delay_ms( 1000 );
        Delay_ms( 1000 );
    }
}
```

### Note

> Set `APP_WIFI_SSID` and `APP_WIFI_PASSWORD` for a 2.4 GHz WiFi network before running.
> The example uses the WRF01 native JSON protocol; command availability depends on the installed firmware.
> HTTPBin (`https://httpbin.org/post`) is a public test service; send demo data only.
> Its fixed-length response supports WRF01 firmware without chunked HTTP support.
> The module sends its MAC address and firmware information with each HTTPS request.
> The example replaces saved WiFi/server settings and clears `token` and `product_key`.

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
