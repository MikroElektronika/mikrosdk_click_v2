
---
# RYB080I Click

> [RYB080I Click](https://www.mikroe.com/?pid_product=MIKROE-6352) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6352&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of RYB080I Click board by processing data from a connected BT device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RYB080I

### Example Key Functions

- `ryb080i_cfg_setup` Config Object Initialization function.
```c
void ryb080i_cfg_setup ( ryb080i_cfg_t *cfg );
```

- `ryb080i_init` Initialization function.
```c
err_t ryb080i_init ( ryb080i_t *ctx, ryb080i_cfg_t *cfg );
```

- `ryb080i_default_cfg` Click Default Configuration function.
```c
err_t ryb080i_default_cfg ( ryb080i_t *ctx );
```

- `ryb080i_cmd_run` This function sends a specified command to the Click module.
```c
void ryb080i_cmd_run ( ryb080i_t *ctx, uint8_t *cmd );
```

- `ryb080i_cmd_set` This function sets a value to a specified command of the Click module.
```c
void ryb080i_cmd_set ( ryb080i_t *ctx, uint8_t *cmd, uint8_t *param );
```

- `ryb080i_cmd_get` This function is used to get the value of a given command from the Click module.
```c
void ryb080i_cmd_get ( ryb080i_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ryb080i_cfg_t ryb080i_cfg;  /**< Click config object. */

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
    ryb080i_cfg_setup( &ryb080i_cfg );
    RYB080I_MAP_MIKROBUS( ryb080i_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ryb080i_init( &ryb080i, &ryb080i_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = RYB080I_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - RYB080I_POWER_UP: 
   > Powers up the device and reads the system information.
 - RYB080I_CONFIG_EXAMPLE: 
   > Sets the BT device name and enables the full power mode.
 - RYB080I_EXAMPLE:
   > Performs a BT terminal example by processing all data from connected BT devices and sending back an adequate response messages.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case RYB080I_POWER_UP:
        {
            if ( RYB080I_OK == ryb080i_power_up( &ryb080i ) )
            {
                app_state = RYB080I_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case RYB080I_CONFIG_EXAMPLE:
        {
            if ( RYB080I_OK == ryb080i_config_example( &ryb080i ) )
            {
                app_state = RYB080I_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case RYB080I_EXAMPLE:
        {
            ryb080i_example( &ryb080i );
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

> We have used the Serial Bluetooth Terminal smartphone application for the test. A smartphone and the Click board must be paired to exchange messages.

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
