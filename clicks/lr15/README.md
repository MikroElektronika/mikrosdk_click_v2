
---
# LR 15 Click

> [LR 15 Click](https://www.mikroe.com/?pid_product=MIKROE-6422) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of LR 15 Click board by showing the communication between two Click boards configured in TEST mode.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LR15

### Example Key Functions

- `lr15_cfg_setup` Config Object Initialization function.
```c
void lr15_cfg_setup ( lr15_cfg_t *cfg );
```

- `lr15_init` Initialization function.
```c
err_t lr15_init ( lr15_t *ctx, lr15_cfg_t *cfg );
```

- `lr15_reset_device` This function resets the device by toggling the reset pin logic state.
```c
void lr15_reset_device ( lr15_t *ctx );
```

- `lr15_cmd_run` This function sends a specified command to the Click module.
```c
void lr15_cmd_run ( lr15_t *ctx, uint8_t *cmd );
```

- `lr15_cmd_set` This function sets a value to a specified command of the Click module.
```c
void lr15_cmd_set ( lr15_t *ctx, uint8_t *cmd, uint8_t *value );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr15_cfg_t lr15_cfg;  /**< Click config object. */

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
    lr15_cfg_setup( &lr15_cfg );
    LR15_MAP_MIKROBUS( lr15_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr15_init( &lr15, &lr15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = LR15_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - LR15_POWER_UP: 
   > Powers up the device, performs a device factory reset and reads system information.
 - LR15_CONFIG_EXAMPLE: 
   > Configures device for the LoRa P2P network mode.
 - LR15_EXAMPLE:
   > Performs a LoRa P2P test example by exchanging messages with another LR 14 Click board.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case LR15_POWER_UP:
        {
            if ( LR15_OK == lr15_power_up( &lr15 ) )
            {
                app_state = LR15_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR15_CONFIG_EXAMPLE:
        {
            if ( LR15_OK == lr15_config_example( &lr15 ) )
            {
                app_state = LR15_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR15_EXAMPLE:
        {
            lr15_example( &lr15 );
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
