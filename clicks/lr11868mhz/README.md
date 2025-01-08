
---
# LR 11 868MHz Click

> [LR 11 868MHz Click](https://www.mikroe.com/?pid_product=MIKROE-6318) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6318&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of LR 11 868MHz Click board by showing the communication between two Click boards configured in P2P network mode.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LR11868MHz

### Example Key Functions

- `lr11868mhz_cfg_setup` Config Object Initialization function.
```c
void lr11868mhz_cfg_setup ( lr11868mhz_cfg_t *cfg );
```

- `lr11868mhz_init` Initialization function.
```c
err_t lr11868mhz_init ( lr11868mhz_t *ctx, lr11868mhz_cfg_t *cfg );
```

- `lr11868mhz_reset_device` This function resets the device by toggling the reset pin logic state.
```c
void lr11868mhz_reset_device ( lr11868mhz_t *ctx );
```

- `lr11868mhz_cmd_run` This function sends a specified command with or without parameters to the Click module.
```c
void lr11868mhz_cmd_run ( lr11868mhz_t *ctx, uint8_t *cmd, uint8_t *param );
```

- `lr11868mhz_cmd_set` This function sets a value to a specified command parameter of the Click module.
```c
void lr11868mhz_cmd_set ( lr11868mhz_t *ctx, uint8_t *cmd, uint8_t *param_id, uint8_t *value );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr11868mhz_cfg_t lr11868mhz_cfg;  /**< Click config object. */

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
    lr11868mhz_cfg_setup( &lr11868mhz_cfg );
    LR11868MHZ_MAP_MIKROBUS( lr11868mhz_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr11868mhz_init( &lr11868mhz, &lr11868mhz_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LR11868MHZ_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - LR11868MHZ_POWER_UP: 
   > Powers up the device, performs a device factory reset and reads system information.
 - LR11868MHZ_CONFIG_EXAMPLE: 
   > Configures device for the LoRa P2P network mode.
 - LR11868MHZ_EXAMPLE:
   > Performs a LoRa P2P example by exchanging messages with another LR 11 868MHz Click board.
> One device should be set to NODE_0_ADDRESS, and the other to NODE_1_ADDRESS.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case LR11868MHZ_POWER_UP:
        {
            if ( LR11868MHZ_OK == lr11868mhz_power_up( &lr11868mhz ) )
            {
                app_state = LR11868MHZ_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR11868MHZ_CONFIG_EXAMPLE:
        {
            if ( LR11868MHZ_OK == lr11868mhz_config_example( &lr11868mhz ) )
            {
                app_state = LR11868MHZ_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR11868MHZ_EXAMPLE:
        {
            lr11868mhz_example( &lr11868mhz );
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
