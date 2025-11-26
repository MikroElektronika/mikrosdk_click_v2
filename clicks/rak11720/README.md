
---
# RAK11720 Click

> [RAK11720 Click](https://www.mikroe.com/?pid_product=MIKROE-6627) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6627&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of RAK11720 Click board by showing
the communication between two Click boards configured in P2P network mode.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RAK11720

### Example Key Functions

- `rak11720_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void rak11720_cfg_setup ( rak11720_cfg_t *cfg );
```

- `rak11720_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t rak11720_init ( rak11720_t *ctx, rak11720_cfg_t *cfg );
```

- `rak11720_cmd_run` This function sends a specified command to the Click module.
```c
void rak11720_cmd_run ( rak11720_t *ctx, uint8_t *cmd );
```

- `rak11720_cmd_set` This function sets a value to a specified command of the Click module.
```c
void rak11720_cmd_set ( rak11720_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `rak11720_cmd_get` This function is used to get the value of a given command from the Click module.
```c
void rak11720_cmd_get ( rak11720_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rak11720_cfg_t rak11720_cfg;  /**< Click config object. */

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
    rak11720_cfg_setup( &rak11720_cfg );
    RAK11720_MAP_MIKROBUS( rak11720_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rak11720_init( &rak11720, &rak11720_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = RAK11720_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - RAK11720_POWER_UP: 
   > Powers up the device, performs a device factory reset and reads system information.
 - RAK11720_CONFIG_EXAMPLE: 
   > Configures device for the LoRa P2P network mode.
 - RAK11720_EXAMPLE:
   > Performs a LoRa P2P example by exchanging messages with another RAK11720 Click board.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case RAK11720_POWER_UP:
        {
            if ( RAK11720_OK == rak11720_power_up( &rak11720 ) )
            {
                app_state = RAK11720_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case RAK11720_CONFIG_EXAMPLE:
        {
            if ( RAK11720_OK == rak11720_config_example( &rak11720 ) )
            {
                app_state = RAK11720_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case RAK11720_EXAMPLE:
        {
            rak11720_example( &rak11720 );
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
