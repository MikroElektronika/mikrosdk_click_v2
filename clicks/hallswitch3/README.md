
---
# Hall Switch 3 Click

> [Hall Switch 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6017) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6017&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Hall Switch 3 Click board 
> by reading and displaying the magnetic field strength value.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallSwitch3

### Example Key Functions

- `hallswitch3_cfg_setup` Config Object Initialization function.
```c
void hallswitch3_cfg_setup ( hallswitch3_cfg_t *cfg );
```

- `hallswitch3_init` Initialization function.
```c
err_t hallswitch3_init ( hallswitch3_t *ctx, hallswitch3_cfg_t *cfg );
```

- `hallswitch3_default_cfg` Click Default Configuration function.
```c
err_t hallswitch3_default_cfg ( hallswitch3_t *ctx );
```

- `hallswitch3_get_mag_data` This function is used to indicates a relative magnetic field strength.
```c
err_t hallswitch3_get_mag_data ( hallswitch3_t *ctx, int8_t *mag_data );
```

- `hallswitch3_set_out_data_rate` This function provides the capability for the user to override the fixed sample rate controlling the sleep-compare-Vout cycle time.
```c
err_t hallswitch3_set_out_data_rate ( hallswitch3_t *ctx, uint8_t odr );
```

- `hallswitch3_get_status` This function reads a status reporting of modes and selections.
```c
err_t hallswitch3_get_status ( hallswitch3_t *ctx, uint8_t *status );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallswitch3_cfg_t hallswitch3_cfg;  /**< Click config object. */

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
    hallswitch3_cfg_setup( &hallswitch3_cfg );
    HALLSWITCH3_MAP_MIKROBUS( hallswitch3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hallswitch3_init( &hallswitch3, &hallswitch3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HALLSWITCH3_ERROR == hallswitch3_default_cfg ( &hallswitch3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Hall Switch 3 Click board.
> The demo application reads and displays the relative magnetic field strength value [Gaussian units] 
> and detects when the magnetic field strength is not in the configured range. 
> The results are sent to the UART terminal, where you can monitor their changes.

```c
void application_task ( void ) 
{
    int8_t mag_data = 0;
    if ( HALLSWITCH3_OK == hallswitch3_get_mag_data( &hallswitch3, &mag_data ) )
    {
        log_printf( &logger, " Magnetic Field: %d [Gs]\r\n", ( int16_t ) mag_data );
        if ( HALLSWITCH3_OUT_STATE_LOW == hallswitch3_check_mag_field( &hallswitch3 ) )
        {
            log_printf( &logger, " The switch is open.\r\n" );
        }
    }
    Delay_ms ( 1000 );
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
