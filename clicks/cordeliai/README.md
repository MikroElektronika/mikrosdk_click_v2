
---
# Cordelia-I Click

> [Cordelia-I Click](https://www.mikroe.com/?pid_product=MIKROE-6909) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6909&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of the Cordelia-I Click board to connect to
a WiFi access point and establish an MQTT connection to a public broker. After
the initial device setup and network configuration, the application publishes
a predefined message to the selected MQTT topic and waits for an echo/receive
indication from the module, printing all responses on the UART terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CordeliaI

### Example Key Functions

- `cordeliai_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void cordeliai_cfg_setup ( cordeliai_cfg_t *cfg );
```

- `cordeliai_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t cordeliai_init ( cordeliai_t *ctx, cordeliai_cfg_t *cfg );
```

- `cordeliai_reset_device` This function resets the device by toggling the RST pin state.
```c
void cordeliai_reset_device ( cordeliai_t *ctx );
```

- `cordeliai_cmd_run` This function sends a specified command to the Click module.
```c
void cordeliai_cmd_run ( cordeliai_t *ctx, uint8_t *cmd );
```

- `cordeliai_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t cordeliai_generic_read ( cordeliai_t *ctx, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the logger and Cordelia-I Click driver, then prepares the example
state machine. The application starts in the POWER UP state, where the device
is reset, communication is verified, factory settings are restored, and system
information is read. After successful initialization, the application proceeds
to the connection configuration state.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    cordeliai_cfg_t cordeliai_cfg;  /**< Click config object. */

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
    cordeliai_cfg_setup( &cordeliai_cfg );
    CORDELIAI_MAP_MIKROBUS( cordeliai_cfg, MIKROBUS_POSITION_CORDELIAI );
    if ( UART_ERROR == cordeliai_init( &cordeliai, &cordeliai_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = CORDELIAI_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - CORDELIAI_POWER_UP: 
   > Performs device reset, factory reset, and reads version info.
 - CORDELIAI_CONFIG_CONNECTION:
   > Connects to the configured WiFi network and sets MQTT parameters (endpoint, port, client ID, 
   flags, subscribe/publish topic names), then connects to the MQTT server.
 - CORDELIAI_EXAMPLE: 
   > Periodically publishes a message to the MQTT topic and waits for the module receive indication, 
   logging all traffic to the UART terminal.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case CORDELIAI_POWER_UP:
        {
            if ( CORDELIAI_OK == cordeliai_power_up( &cordeliai ) )
            {
                app_state = CORDELIAI_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case CORDELIAI_CONFIG_CONNECTION:
        {
            if ( CORDELIAI_OK == cordeliai_config_connection( &cordeliai ) )
            {
                app_state = CORDELIAI_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case CORDELIAI_EXAMPLE:
        {
            cordeliai_example( &cordeliai );
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
