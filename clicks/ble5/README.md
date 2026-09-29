
---
# BLE 5 Click

> [BLE 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4120) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4120&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of BLE 5 Click board as a Nordic UART
terminal for sending and receiving data with a connected BLE peer.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BLE5

### Example Key Functions

- `ble5_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void ble5_cfg_setup ( ble5_cfg_t *cfg );
```

- `ble5_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t ble5_init ( ble5_t *ctx, ble5_cfg_t *cfg );
```

- `ble5_default_cfg` This function sets the BLE 5 Click wake-up and RTS outputs high, then resets the module to start its preprogrammed AT firmware.
```c
err_t ble5_default_cfg ( ble5_t *ctx );
```

- `ble5_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t ble5_generic_write ( ble5_t *ctx, uint8_t *data_in, uint16_t len );
```

- `ble5_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t ble5_generic_read ( ble5_t *ctx, uint8_t *data_out, uint16_t len );
```

- `ble5_cmd_run` This function sends a BLE 5 Click command without parameters, including the packet length and CR/LF terminator.
```c
err_t ble5_cmd_run ( ble5_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and logger and resets the module.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ble5_cfg_t ble5_cfg;  /**< Click config object. */

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
    ble5_cfg_setup( &ble5_cfg );
    BLE5_MAP_MIKROBUS( ble5_cfg, MIKROBUS_POSITION_BLE5 );
    if ( UART_ERROR == ble5_init( &ble5, &ble5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BLE5_ERROR == ble5_default_cfg( &ble5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split into three stages:
>  - BLE5_POWER_UP:
> Waits for the module and displays the firmware version and Bluetooth address.
>  - BLE5_CONFIG_EXAMPLE:
> Configures the device name and Nordic UART service and starts advertising.
>  - BLE5_EXAMPLE:
> Echoes received text, periodically sends a message, and restarts advertising after disconnection.

```c
void application_task ( void ) 
{
    err_t error_flag = BLE5_OK;

    switch ( app_state )
    {
        case BLE5_POWER_UP:
        {
            error_flag = ble5_power_up( &ble5 );
            if ( BLE5_OK == error_flag )
            {
                app_state = BLE5_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BLE5_CONFIG_EXAMPLE:
        {
            error_flag = ble5_config_example( &ble5 );
            if ( BLE5_OK == error_flag )
            {
                app_state = BLE5_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BLE5_EXAMPLE:
        {
            error_flag = ble5_example( &ble5 );
            break;
        }
        default:
        {
            error_flag = BLE5_ERROR;
            break;
        }
    }

    if ( BLE5_OK != error_flag )
    {
        log_error( &logger, " Communication error: %d. Restarting module.", error_flag );
        // A failed profile build must restart from an empty module database.
        Delay_1sec( );
        ble5_clear_app_buf( );
        ble5_default_cfg( &ble5 );
        app_state = BLE5_POWER_UP;
    }
}
```

### Note

> Set MODE to Standalone and use the preprogrammed AT firmware with mikroBUS UART.
> We have used the Serial Bluetooth Terminal smartphone application for the test.
> This example does not require bonding.

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
