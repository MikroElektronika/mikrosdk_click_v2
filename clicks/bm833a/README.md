
---
# BM833A Click

> [BM833A Click](https://www.mikroe.com/?pid_product=MIKROE-7002) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7002&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of BM833A Click board by processing data from a connected BT device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BM833A

### Example Key Functions

- `bm833a_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void bm833a_cfg_setup ( bm833a_cfg_t *cfg );
```

- `bm833a_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t bm833a_init ( bm833a_t *ctx, bm833a_cfg_t *cfg );
```

- `bm833a_cmd_run` This function sends a specified command to the Click module.
```c
void bm833a_cmd_run ( bm833a_t *ctx, uint8_t *cmd );
```

- `bm833a_cmd_set` This function sets a value to a specified command of the Click module.
```c
void bm833a_cmd_set ( bm833a_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `bm833a_cmd_get` This function is used to get the value of a given command from the Click module.
```c
void bm833a_cmd_get ( bm833a_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bm833a_cfg_t bm833a_cfg;  /**< Click config object. */

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
    bm833a_cfg_setup( &bm833a_cfg );
    BM833A_MAP_MIKROBUS( bm833a_cfg, MIKROBUS_POSITION_BM833A );
    if ( UART_ERROR == bm833a_init( &bm833a, &bm833a_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = BM833A_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - BM833A_POWER_UP: 
   > Powers up the device and reads the system information.
 - BM833A_CONFIG_EXAMPLE: 
   > Sets the BT device name.
 - BM833A_EXAMPLE:
   > Performs a BT terminal example by processing all data from a connected BT device and sending back an adequate response messages.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case BM833A_POWER_UP:
        {
            if ( BM833A_OK == bm833a_power_up( &bm833a ) )
            {
                app_state = BM833A_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BM833A_CONFIG_EXAMPLE:
        {
            if ( BM833A_OK == bm833a_config_example( &bm833a ) )
            {
                app_state = BM833A_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BM833A_EXAMPLE:
        {
            bm833a_example( &bm833a );
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
