
---
# eFuse 8 Click

> [eFuse 8 Click](https://www.mikroe.com/?pid_product=MIKROE-7089) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7089&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jul 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the eFuse 8 Click board by changing
the current limit through a range of values, reading it back and monitoring 
the supply good indication.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.eFuse8

### Example Key Functions

- `efuse8_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void efuse8_cfg_setup ( efuse8_cfg_t *cfg );
```

- `efuse8_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t efuse8_init ( efuse8_t *ctx, efuse8_cfg_t *cfg );
```

- `efuse8_default_cfg` This function executes a default configuration of eFuse 8 Click board.
```c
err_t efuse8_default_cfg ( efuse8_t *ctx );
```

- `efuse8_set_wiper` This function reads the volatile wiper position.
```c
err_t efuse8_set_wiper ( efuse8_t *ctx, uint16_t wiper );
```

- `efuse8_set_current_limit` This function sets the overcurrent threshold by calculating the required wiper position.
```c
err_t efuse8_set_current_limit ( efuse8_t *ctx, uint16_t ilim_ma );
```

- `efuse8_get_current_limit` This function reads the wiper position and calculates the overcurrent threshold.
```c
err_t efuse8_get_current_limit ( efuse8_t *ctx, uint16_t *ilim_ma );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    efuse8_cfg_t efuse8_cfg;  /**< Click config object. */

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
    efuse8_cfg_setup( &efuse8_cfg );
    EFUSE8_MAP_MIKROBUS( efuse8_cfg, MIKROBUS_POSITION_EFUSE8 );
    if ( I2C_MASTER_ERROR == efuse8_init( &efuse8, &efuse8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EFUSE8_ERROR == efuse8_default_cfg ( &efuse8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Steps the current limit through a table of values from 1 to 8 A. For each
value it reads back the resulting current limit from the device
and logs them together with the state of the supply good pin.

```c
void application_task ( void ) 
{
    for ( uint8_t cnt = 0; cnt < EFUSE8_ILIM_TABLE_SIZE; cnt++ )
    {
        uint16_t ilim_ma = 0;
        err_t error_flag = EFUSE8_OK;

        error_flag |= efuse8_set_current_limit( &efuse8, ilim_table[ cnt ] );
        error_flag |= efuse8_get_current_limit( &efuse8, &ilim_ma );

        if ( EFUSE8_OK == error_flag )
        {
            log_printf( &logger, " Set limit  : %u mA\r\n", ilim_table[ cnt ] );
            log_printf( &logger, " Read limit : %u mA\r\n", ilim_ma );
            if ( EFUSE8_SUPPLY_GOOD == efuse8_get_pgd_pin( &efuse8 ) )
            {
                log_printf( &logger, " Supply good: YES\r\n" );
            }
            else
            {
                log_printf( &logger, " Supply good: NO\r\n" );
            }
            log_printf( &logger, " -------------------------------\r\n" );
        }
        else
        {
            log_error( &logger, " Communication." );
        }

        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
