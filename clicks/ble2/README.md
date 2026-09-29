
---
# BLE2 Click

> [BLE2 Click](https://www.mikroe.com/?pid_product=MIKROE-1715) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1715&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of BLE2 Click by processing data from a
connected BLE terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BLE2

### Example Key Functions

- `ble2_cfg_setup` This function initializes the Click configuration structure to its default values.
```c
void ble2_cfg_setup ( ble2_cfg_t *cfg );
```

- `ble2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t ble2_init ( ble2_t *ctx, ble2_cfg_t *cfg );
```

- `ble2_default_cfg` This function places BLE2 Click in Command mode and wakes the module.
```c
err_t ble2_default_cfg ( ble2_t *ctx );
```

- `ble2_cmd_run` This function sends an ASCII command followed by a carriage return.
```c
err_t ble2_cmd_run ( ble2_t *ctx, uint8_t *cmd );
```

- `ble2_cmd_set` This function builds and sends a BLE2 Click set command.
```c
err_t ble2_cmd_set ( ble2_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `ble2_cmd_get` This function builds and sends a BLE2 Click get command.
```c
err_t ble2_cmd_get ( ble2_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ble2_cfg_t ble2_cfg;  /**< Click config object. */

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
    ble2_cfg_setup( &ble2_cfg );
    BLE2_MAP_MIKROBUS( ble2_cfg, MIKROBUS_POSITION_BLE2 );
    if ( UART_ERROR == ble2_init( &ble2, &ble2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BLE2_ERROR == ble2_default_cfg( &ble2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = BLE2_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split into three stages:
>  - BLE2_POWER_UP:
> Wakes the module and checks UART communication.
>  - BLE2_CONFIG_EXAMPLE:
> Restores factory settings, enables MLDP, sets the device name, and starts advertising.
>  - BLE2_EXAMPLE:
> Exchanges text with a connected BLE terminal and restarts advertising after disconnection.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case BLE2_POWER_UP:
        {
            if ( BLE2_OK == ble2_power_up( &ble2 ) )
            {
                app_state = BLE2_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BLE2_CONFIG_EXAMPLE:
        {
            if ( BLE2_OK == ble2_config_example( &ble2 ) )
            {
                app_state = BLE2_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BLE2_EXAMPLE:
        {
            ble2_example( &ble2 );
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

> We have used the Serial Bluetooth Terminal smartphone application for the test.
The short device name leaves room for the MLDP UUID in the advertising packet.

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
