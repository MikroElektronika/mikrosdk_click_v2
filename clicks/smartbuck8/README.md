
---
# Smart Buck 8 Click

> [Smart Buck 8 Click](https://www.mikroe.com/?pid_product=MIKROE-6624) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6624&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Smart Buck 8 Click board. The application cyclically adjusts 
the output voltage between its minimum and maximum values in steps and monitors the PG (Power Good) pin 
for any fault conditions. It logs any detected faults including undervoltage lockout, thermal warning, 
or hiccup event status.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartBuck8

### Example Key Functions

- `smartbuck8_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void smartbuck8_cfg_setup ( smartbuck8_cfg_t *cfg );
```

- `smartbuck8_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t smartbuck8_init ( smartbuck8_t *ctx, smartbuck8_cfg_t *cfg );
```

- `smartbuck8_default_cfg` This function executes a default configuration of Smart Buck 8 Click board.
```c
err_t smartbuck8_default_cfg ( smartbuck8_t *ctx );
```

- `smartbuck8_get_pg_pin` This function reads the logic level of the PG (power-good) pin.
```c
uint8_t smartbuck8_get_pg_pin ( smartbuck8_t *ctx );
```

- `smartbuck8_read_status` This function reads the value of the STATUS register and returns it via output pointer.
```c
err_t smartbuck8_read_status ( smartbuck8_t *ctx, uint8_t *status );
```

- `smartbuck8_set_vout` This function sets the output voltage by writing a scaled value to the VOUT register.
```c
err_t smartbuck8_set_vout ( smartbuck8_t *ctx, uint16_t vout_mv );
```

### Application Init

> Initializes the logger and the Smart Buck 8 Click driver, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck8_cfg_t smartbuck8_cfg;  /**< Click config object. */

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
    smartbuck8_cfg_setup( &smartbuck8_cfg );
    SMARTBUCK8_MAP_MIKROBUS( smartbuck8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck8_init( &smartbuck8, &smartbuck8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK8_ERROR == smartbuck8_default_cfg ( &smartbuck8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Cycles the output voltage up and down between the minimum and maximum supported values. 
Checks for fault conditions via the PG pin and logs detailed status flags if any fault is detected.

```c
void application_task ( void )
{
    static uint16_t vout = SMARTBUCK8_VOUT_MV_MIN;
    static int16_t vout_step = 50;
    static uint8_t status = 0;
    if ( !smartbuck8_get_pg_pin ( &smartbuck8 ) )
    {
        log_printf( &logger, "\r\n Fault indication detected via PG pin!\r\n" );
        if ( SMARTBUCK8_OK == smartbuck8_read_status ( &smartbuck8, &status ) )
        {
            if ( status & SMARTBUCK8_STATUS_THERMAL_WARNING )
            {
                log_printf ( &logger, " Junction temperature is higher than 130C\r\n" );
            }
            if ( status & SMARTBUCK8_STATUS_HICCUP )
            {
                log_printf ( &logger, " Device has HICCUP status once\r\n" );
            }
            if ( status & SMARTBUCK8_STATUS_UVLO )
            {
                log_printf ( &logger, " The input voltage is less than UVLO threshold (falling edge)\r\n" );
            }
        }
    }
    if ( SMARTBUCK8_OK == smartbuck8_set_vout ( &smartbuck8, vout ) )
    {
        log_printf ( &logger, "\r\n VOUT: %u mV\r\n", vout );
        vout += vout_step;
        if ( ( vout > SMARTBUCK8_VOUT_MV_MAX ) || ( vout < SMARTBUCK8_VOUT_MV_MIN ) )
        {
            vout_step = -vout_step;
            vout += vout_step;
            vout += vout_step;
        }
    }
    Delay_ms ( 1000 );
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
