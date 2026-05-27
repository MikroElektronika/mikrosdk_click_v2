
---
# ST67W Click

> [ST67W Click](https://www.mikroe.com/?pid_product=MIKROE-6921) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6921&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> Application example shows device capability of connecting to a WiFi network and
sending TCP/UDP messages to an echo server, or processing data from a connected BLE device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ST67W

### Example Key Functions

- `st67w_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void st67w_cfg_setup ( st67w_cfg_t *cfg );
```

- `st67w_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t st67w_init ( st67w_t *ctx, st67w_cfg_t *cfg );
```

- `st67w_cmd_run` This function sends a specified command to the Click module.
```c
void st67w_cmd_run ( st67w_t *ctx, uint8_t *cmd );
```

- `st67w_cmd_set` This function sets a value to a specified command of the Click module.
```c
void st67w_cmd_set ( st67w_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `st67w_cmd_get` This function is used to get the value of a given command from the Click module.
```c
void st67w_cmd_get ( st67w_t *ctx, uint8_t *cmd );
```

- `st67w_generic_read` This function reads a desired number of data bytes by using SPI serial interface.
```c
err_t st67w_generic_read ( st67w_t *ctx, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    st67w_cfg_t st67w_cfg;  /**< Click config object. */

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
    st67w_cfg_setup( &st67w_cfg );
    ST67W_MAP_MIKROBUS( st67w_cfg, MIKROBUS_POSITION_ST67W );
    if ( SPI_MASTER_ERROR == st67w_init( &st67w, &st67w_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = ST67W_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - ST67W_POWER_UP: 
   > Powers up the device, performs a factory reset and reads system information.
 - ST67W_CONFIG_CONNECTION: 
   > Configures connection to WiFi or BLE depending on the selected example.
 - ST67W_EXAMPLE:
   > Depending on the selected demo example, it sends a TCP/UDP message to an echo server over a WiFi network or 
   processes all data from a connected BLE device and sends back an adequate response message.

> By default, the WiFi TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case ST67W_POWER_UP:
        {
            if ( ST67W_OK == st67w_power_up( &st67w ) )
            {
                app_state = ST67W_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case ST67W_CONFIG_CONNECTION:
        {
            if ( ST67W_OK == st67w_config_connection( &st67w ) )
            {
                app_state = ST67W_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case ST67W_EXAMPLE:
        {
            st67w_example( &st67w );
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

> We have used the Serial Bluetooth Terminal smartphone application for the BLE example test.

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
