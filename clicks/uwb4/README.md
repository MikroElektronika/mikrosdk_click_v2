
---
# UWB 4 Click

> [UWB 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6305) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6305&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of UWB 4 Click board by showing the UWB ranging between two Click boards configured as initiator and responder.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UWB4

### Example Key Functions

- `uwb4_cfg_setup` Config Object Initialization function.
```c
void uwb4_cfg_setup ( uwb4_cfg_t *cfg );
```

- `uwb4_init` Initialization function.
```c
err_t uwb4_init ( uwb4_t *ctx, uwb4_cfg_t *cfg );
```

- `uwb4_cmd_run` This function sends a specified command to the Click module.
```c
void uwb4_cmd_run ( uwb4_t *ctx, uint8_t *cmd );
```

- `uwb4_cmd_set` This function sets a value to a specified command of the Click module.
```c
void uwb4_cmd_set ( uwb4_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `uwb4_reset_device` This function resets the device by toggling the reset pin logic state.
```c
void uwb4_reset_device ( uwb4_t *ctx );
```

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
