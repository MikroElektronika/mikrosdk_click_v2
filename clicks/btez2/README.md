
---
# BT-EZ 2 Click

> [BT-EZ 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6583) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6583&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of BT-EZ 2 Click board by processing data from a connected BLE device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BTEZ2

### Example Key Functions

- `btez2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void btez2_cfg_setup ( btez2_cfg_t *cfg );
```

- `btez2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t btez2_init ( btez2_t *ctx, btez2_cfg_t *cfg );
```

- `btez2_cmd_action` This function sends a specified action command to the Click module.
```c
void btez2_cmd_action ( btez2_t *ctx, uint8_t *cmd, uint8_t *params );
```

- `btez2_cmd_set` This function sends a specified set command to the Click module.
```c
void btez2_cmd_set ( btez2_t *ctx, uint8_t *cmd, uint8_t *params );
```

- `btez2_read_packet` This function reads a response or event packet from the Click module and stores it in ctx->evt_pkt structure.
```c
err_t btez2_read_packet ( btez2_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    btez2_cfg_t btez2_cfg;  /**< Click config object. */

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
    btez2_cfg_setup( &btez2_cfg );
    BTEZ2_MAP_MIKROBUS( btez2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == btez2_init( &btez2, &btez2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = BTEZ2_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - BTEZ2_POWER_UP: 
   > Powers up the device and checks the communication.
 - BTEZ2_CONFIG_EXAMPLE: 
   > Restores factory settings and reads the BT address and name.
 - BTEZ2_EXAMPLE:
   > Performs a BT terminal example by processing all data from a connected BLE device and sending back an adequate response messages.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case BTEZ2_POWER_UP:
        {
            if ( BTEZ2_OK == btez2_power_up( &btez2 ) )
            {
                app_state = BTEZ2_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BTEZ2_CONFIG_EXAMPLE:
        {
            if ( BTEZ2_OK == btez2_config_example( &btez2 ) )
            {
                app_state = BTEZ2_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BTEZ2_EXAMPLE:
        {
            btez2_example( &btez2 );
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
