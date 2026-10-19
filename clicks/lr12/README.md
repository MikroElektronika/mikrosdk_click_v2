
---
# LR 12 Click

> [LR 12 Click](https://www.mikroe.com/?pid_product=MIKROE-7045) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7045&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of the LR 12 Click board as a LoRaWAN
end device. The device initializes, performs a factory reset, configures
OTAA parameters (AppEUI and AppKey), joins the LoRaWAN network, and then
periodically sends confirmed uplink messages containing sample data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LR12

### Example Key Functions

- `lr12_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void lr12_cfg_setup ( lr12_cfg_t *cfg );
```

- `lr12_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t lr12_init ( lr12_t *ctx, lr12_cfg_t *cfg );
```

- `lr12_cmd_run` This function sends a specified command with or without parameters to the Click module.
```c
void lr12_cmd_run ( lr12_t *ctx, uint8_t *cmd, uint8_t *param );
```

- `lr12_cmd_set` This function sets data and parameters to a specified command of the Click module.
```c
void lr12_cmd_set ( lr12_t *ctx, uint8_t *cmd, uint8_t *param, uint8_t *value );
```

- `lr12_cmd_get` This function is used to get the value of a given command from the Click module.
```c
void lr12_cmd_get ( lr12_t *ctx, uint8_t *cmd );
```

- `lr12_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t lr12_generic_read ( lr12_t *ctx, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the logger and LR 12 Click driver, then sets the application state machine to power-up state.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr12_cfg_t lr12_cfg;  /**< Click config object. */

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
    lr12_cfg_setup( &lr12_cfg );
    LR12_MAP_MIKROBUS( lr12_cfg, MIKROBUS_POSITION_LR12 );
    if ( UART_ERROR == lr12_init( &lr12, &lr12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LR12_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Implements a state machine that performs device reset, communication check,
network configuration, OTAA join procedure, and periodically sends confirmed
LoRaWAN messages with incrementing counters and example sensor data.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case LR12_POWER_UP:
        {
            if ( LR12_OK == lr12_power_up( &lr12 ) )
            {
                app_state = LR12_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR12_CONFIG_EXAMPLE:
        {
            if ( LR12_OK == lr12_config_example( &lr12 ) )
            {
                app_state = LR12_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR12_EXAMPLE:
        {
            lr12_example( &lr12 );
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

> Replace LR12_APP_EUI and LR12_APP_KEY with values generated on your LoRaWAN server.
Ensure the device is within network coverage and properly registered on the network
server using the printed DevEUI and configured AppEUI and AppKey.

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
