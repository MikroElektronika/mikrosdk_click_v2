
---
# Stephano-I Click

> [Stephano-I Click](https://www.mikroe.com/?pid_product=MIKROE-6594) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6594&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to a WiFi network and
sending TCP/UDP messages to an echo server, or processing data from a connected BLE device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StephanoI

### Example Key Functions

- `stephanoi_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void stephanoi_cfg_setup ( stephanoi_cfg_t *cfg );
```

- `stephanoi_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t stephanoi_init ( stephanoi_t *ctx, stephanoi_cfg_t *cfg );
```

- `stephanoi_cmd_run` This function sends a specified command to the Click module.
```c
void stephanoi_cmd_run ( stephanoi_t *ctx, uint8_t *cmd );
```

- `stephanoi_cmd_set` This function sets a value to a specified command of the Click module.
```c
void stephanoi_cmd_set ( stephanoi_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `stephanoi_cmd_get` This function is used to get the value of a given command from the Click module.
```c
void stephanoi_cmd_get ( stephanoi_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stephanoi_cfg_t stephanoi_cfg;  /**< Click config object. */

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
    stephanoi_cfg_setup( &stephanoi_cfg );
    STEPHANOI_MAP_MIKROBUS( stephanoi_cfg, MIKROBUS_1 );
    if ( UART_ERROR == stephanoi_init( &stephanoi, &stephanoi_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = STEPHANOI_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - STEPHANOI_POWER_UP: 
   > Powers up the device, performs a factory reset and reads system information.
 - STEPHANOI_CONFIGURE_CONNECTION: 
   > Configures connection to WiFi or BLE depending on the selected example.
 - STEPHANOI_EXAMPLE:
   > Depending on the selected demo example, it sends a TCP/UDP message to an echo server over a WiFi network or 
   processes all data from a connected BLE device and sends back an adequate response message.

> By default, the WiFi TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case STEPHANOI_POWER_UP:
        {
            if ( STEPHANOI_OK == stephanoi_power_up( &stephanoi ) )
            {
                app_state = STEPHANOI_CONFIGURE_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIGURE CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case STEPHANOI_CONFIGURE_CONNECTION:
        {
            if ( STEPHANOI_OK == stephanoi_config_connection( &stephanoi ) )
            {
                app_state = STEPHANOI_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case STEPHANOI_EXAMPLE:
        {
            stephanoi_example( &stephanoi );
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
