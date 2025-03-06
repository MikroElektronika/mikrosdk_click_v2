
---
# Vela IF820 Click

> [Vela IF820 Click](https://www.mikroe.com/?pid_product=MIKROE-6513) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6513&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Vela IF820 Click board by processing data from a connected BT Classic device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VelaIF820

### Example Key Functions

- `velaif820_cfg_setup` Config Object Initialization function.
```c
void velaif820_cfg_setup ( velaif820_cfg_t *cfg );
```

- `velaif820_init` Initialization function.
```c
err_t velaif820_init ( velaif820_t *ctx, velaif820_cfg_t *cfg );
```

- `velaif820_cmd_set` This function sends a specified set command to the Click module.
```c
void velaif820_cmd_set ( velaif820_t *ctx, uint8_t *cmd, uint8_t *params );
```

- `velaif820_cmd_get` This function sends a specified get command to the Click module.
```c
void velaif820_cmd_get ( velaif820_t *ctx, uint8_t *cmd, uint8_t *params );
```

- `velaif820_read_packet` This function reads a response or event packet from the Click module and stores it in ctx->evt_pkt structure.
```c
err_t velaif820_read_packet ( velaif820_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    velaif820_cfg_t velaif820_cfg;  /**< Click config object. */

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
    velaif820_cfg_setup( &velaif820_cfg );
    VELAIF820_MAP_MIKROBUS( velaif820_cfg, MIKROBUS_1 );
    if ( UART_ERROR == velaif820_init( &velaif820, &velaif820_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = VELAIF820_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - VELAIF820_POWER_UP: 
   > Powers up the device and checks the communication.
 - VELAIF820_CONFIG_EXAMPLE: 
   > Restores factory settings, sets BT Classic flags and reads the BT address and name.
 - VELAIF820_EXAMPLE:
   > Performs a BT terminal example by processing all data from a connected BT Classic device and sending back an adequate response messages.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case VELAIF820_POWER_UP:
        {
            if ( VELAIF820_OK == velaif820_power_up( &velaif820 ) )
            {
                app_state = VELAIF820_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case VELAIF820_CONFIG_EXAMPLE:
        {
            if ( VELAIF820_OK == velaif820_config_example( &velaif820 ) )
            {
                app_state = VELAIF820_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case VELAIF820_EXAMPLE:
        {
            velaif820_example( &velaif820 );
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
A smartphone and the Click board must be paired in order to exchange messages with each other.

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
