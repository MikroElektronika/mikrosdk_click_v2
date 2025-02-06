
---
# BT840 Click

> [BT840 Click](https://www.mikroe.com/?pid_product=MIKROE-6454) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6454&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of BT840 Click board by processing data from a connected BT device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BT840

### Example Key Functions

- `bt840_cfg_setup` Config Object Initialization function.
```c
void bt840_cfg_setup ( bt840_cfg_t *cfg );
```

- `bt840_init` Initialization function.
```c
err_t bt840_init ( bt840_t *ctx, bt840_cfg_t *cfg );
```

- `bt840_cmd_run` This function sends a specified command to the Click module.
```c
void bt840_cmd_run ( bt840_t *ctx, uint8_t *cmd );
```

- `bt840_cmd_set` This function sets a value to a specified command of the Click module.
```c
void bt840_cmd_set ( bt840_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `bt840_cmd_get` This function is used to get the value of a given command from the Click module.
```c
void bt840_cmd_get ( bt840_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bt840_cfg_t bt840_cfg;  /**< Click config object. */

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
    bt840_cfg_setup( &bt840_cfg );
    BT840_MAP_MIKROBUS( bt840_cfg, MIKROBUS_1 );
    if ( UART_ERROR == bt840_init( &bt840, &bt840_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = BT840_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - BT840_POWER_UP: 
   > Powers up the device and reads the system information.
 - BT840_CONFIG_EXAMPLE: 
   > Sets the BT device name.
 - BT840_EXAMPLE:
   > Performs a BT terminal example by processing all data from a connected BT device and sending back an adequate response messages.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case BT840_POWER_UP:
        {
            if ( BT840_OK == bt840_power_up( &bt840 ) )
            {
                app_state = BT840_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BT840_CONFIG_EXAMPLE:
        {
            if ( BT840_OK == bt840_config_example( &bt840 ) )
            {
                app_state = BT840_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BT840_EXAMPLE:
        {
            bt840_example( &bt840 );
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
