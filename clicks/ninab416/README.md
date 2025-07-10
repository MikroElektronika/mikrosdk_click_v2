
---
# NINA-B416 Click

> [NINA-B416 Click](https://www.mikroe.com/?pid_product=MIKROE-6618) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6618&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of NINA-B416 Click board by processing data from a connected BT device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NINAB416

### Example Key Functions

- `ninab416_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void ninab416_cfg_setup ( ninab416_cfg_t *cfg );
```

- `ninab416_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t ninab416_init ( ninab416_t *ctx, ninab416_cfg_t *cfg );
```

- `ninab416_cmd_run` This function sends a specified command to the Click module.
```c
void ninab416_cmd_run ( ninab416_t *ctx, uint8_t *cmd );
```

- `ninab416_cmd_set` This function sets a value to a specified command of the Click module.
```c
void ninab416_cmd_set ( ninab416_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `ninab416_cmd_get` This function is used to get the value of a given command from the Click module.
```c
void ninab416_cmd_get ( ninab416_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ninab416_cfg_t ninab416_cfg;  /**< Click config object. */

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
    ninab416_cfg_setup( &ninab416_cfg );
    NINAB416_MAP_MIKROBUS( ninab416_cfg, MIKROBUS_1 );
    if ( NINAB416_OK != ninab416_init( &ninab416, &ninab416_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = NINAB416_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - NINAB416_POWER_UP: 
   > Powers up the device, performs a factory reset and reads system information.
 - NINAB416_EXAMPLE: 
   > Performs a BT terminal example by processing all data from a connected BT device and sending back an adequate response messages.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case NINAB416_POWER_UP:
        {
            if ( NINAB416_OK == ninab416_power_up( &ninab416 ) )
            {
                app_state = NINAB416_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case NINAB416_EXAMPLE:
        {
            ninab416_example( &ninab416 );
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
A smartphone and the Click board must be paired to exchange messages.

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
