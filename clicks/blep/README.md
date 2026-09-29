
---
# BLE P Click

> [BLE P Click](https://www.mikroe.com/?pid_product=MIKROE-1597) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1597&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of BLE P Click by exchanging text with a
> connected Nordic UART terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BLEP

### Example Key Functions

- `blep_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void blep_cfg_setup ( blep_cfg_t *cfg );
```

- `blep_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t blep_init ( blep_t *ctx, blep_cfg_t *cfg );
```

- `blep_uart_cfg` This function loads the BLE P Click Nordic UART profile and waits for standby mode.
```c
err_t blep_uart_cfg ( blep_t *ctx );
```

- `blep_read_event` This function reads one queued or pending BLE P Click event and updates link and credit state.
```c
err_t blep_read_event ( blep_t *ctx, blep_event_t *evt );
```

- `blep_send_data` This function sends one BLE P Click notification using one available transmit credit.
```c
err_t blep_send_data ( blep_t *ctx, uint8_t pipe, uint8_t *data_in, uint8_t len );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    blep_cfg_t blep_cfg;  /**< Click config object. */

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
    blep_cfg_setup( &blep_cfg );
    BLEP_MAP_MIKROBUS( blep_cfg, MIKROBUS_POSITION_BLEP );
    if ( SPI_MASTER_ERROR == blep_init( &blep, &blep_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\r\n" );
}
```

### Application Task

> Application task is split into three stages:
>  - BLEP_POWER_UP:
> Waits for the module startup event.
>  - BLEP_CONFIG_EXAMPLE:
> Loads the Nordic UART profile, displays device information, sets the name, and starts
> advertising.
>  - BLEP_EXAMPLE:
> Echoes received text, sends periodic messages, and restarts advertising after disconnection.
> The connection closes on the "END" string or after 60 seconds without received terminal data.

```c
void application_task ( void )
{
    err_t error_flag = BLEP_OK;

    switch ( app_state )
    {
        case BLEP_POWER_UP:
        {
            error_flag = blep_power_up( &blep );
            if ( BLEP_OK == error_flag )
            {
                app_state = BLEP_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\r\n" );
            }
            break;
        }
        case BLEP_CONFIG_EXAMPLE:
        {
            error_flag = blep_config_example( &blep );
            if ( BLEP_OK == error_flag )
            {
                app_state = BLEP_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\r\n" );
            }
            break;
        }
        case BLEP_EXAMPLE:
        {
            error_flag = blep_example( &blep );
            break;
        }
        default:
        {
            error_flag = BLEP_ERROR;
            break;
        }
    }
    if ( error_flag < 0 )
    {
        log_error( &logger, " Communication error: %d. Restarting module.", ( int16_t ) error_flag );
        app_state = BLEP_POWER_UP;
        Delay_ms( 1000 );
        blep_reset( &blep );
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
