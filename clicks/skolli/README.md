
---
# Skoll-I Click

> [Skoll-I Click](https://www.mikroe.com/?pid_product=MIKROE-6830) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6830&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Skoll-I Click board by processing data from a connected BLE device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SkollI

### Example Key Functions

- `skolli_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void skolli_cfg_setup ( skolli_cfg_t *cfg );
```

- `skolli_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t skolli_init ( skolli_t *ctx, skolli_cfg_t *cfg );
```

- `skolli_cmd_action` This function sends a specified action command to the Click module.
```c
void skolli_cmd_action ( skolli_t *ctx, uint8_t *cmd, uint8_t *params );
```

- `skolli_cmd_set` This function sends a specified set command to the Click module.
```c
void skolli_cmd_set ( skolli_t *ctx, uint8_t *cmd, uint8_t *params );
```

- `skolli_read_packet` This function reads a response or event packet from the Click module and stores it in ctx->evt_pkt structure.
```c
err_t skolli_read_packet ( skolli_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    skolli_cfg_t skolli_cfg;  /**< Click config object. */

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
    skolli_cfg_setup( &skolli_cfg );
    SKOLLI_MAP_MIKROBUS( skolli_cfg, MIKROBUS_1 );
    if ( UART_ERROR == skolli_init( &skolli, &skolli_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = SKOLLI_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - SKOLLI_POWER_UP: 
   > Powers up the device and checks the communication.
 - SKOLLI_CONFIG_EXAMPLE: 
   > Restores factory settings and reads the BT address and name.
 - SKOLLI_EXAMPLE:
   > Performs a BT terminal example by processing all data from a connected BLE device and sending back an adequate response messages.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case SKOLLI_POWER_UP:
        {
            if ( SKOLLI_OK == skolli_power_up( &skolli ) )
            {
                app_state = SKOLLI_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case SKOLLI_CONFIG_EXAMPLE:
        {
            if ( SKOLLI_OK == skolli_config_example( &skolli ) )
            {
                app_state = SKOLLI_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case SKOLLI_EXAMPLE:
        {
            skolli_example( &skolli );
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
