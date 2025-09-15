
---
# Smart Buck 6 Click

> [Smart Buck 6 Click](https://www.mikroe.com/?pid_product=MIKROE-6707) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6707&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Smart Buck 6 Click board. The application changes 
the output voltage of all three buck converters (A, B, and C) in a periodic manner and logs 
the output current of each. It also monitors the PG (Power Good) pin to detect and log any 
fault conditions such as over-temperature, overvoltage, undervoltage, or overcurrent.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartBuck6

### Example Key Functions

- `smartbuck6_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void smartbuck6_cfg_setup ( smartbuck6_cfg_t *cfg );
```

- `smartbuck6_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t smartbuck6_init ( smartbuck6_t *ctx, smartbuck6_cfg_t *cfg );
```

- `smartbuck6_default_cfg` This function executes a default configuration of Smart Buck 6 Click board.
```c
err_t smartbuck6_default_cfg ( smartbuck6_t *ctx );
```

- `smartbuck6_set_buck_vout` This function sets the output voltage for one or more buck regulators.
```c
err_t smartbuck6_set_buck_vout ( smartbuck6_t *ctx, uint8_t buck_sel, uint16_t vout_mv );
```

- `smartbuck6_read_buck_current` This function reads and returns the output current of the selected buck regulator.
```c
err_t smartbuck6_read_buck_current ( smartbuck6_t *ctx, uint8_t buck_sel, uint16_t *current_ma );
```

- `smartbuck6_get_pg_pin` This function reads the logic level of the PG pin.
```c
uint8_t smartbuck6_get_pg_pin ( smartbuck6_t *ctx );
```

### Application Init

> Initializes the logger and the Smart Buck 6 Click driver and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck6_cfg_t smartbuck6_cfg;  /**< Click config object. */

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
    smartbuck6_cfg_setup( &smartbuck6_cfg );
    SMARTBUCK6_MAP_MIKROBUS( smartbuck6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck6_init( &smartbuck6, &smartbuck6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK6_ERROR == smartbuck6_default_cfg ( &smartbuck6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically increases or decreases the output voltage, reads and logs the output current for
each buck channel, and checks for any fault conditions indicated via the PG pin and status registers.

```c
void application_task ( void )
{
    smartbuck6_status_t status;
    static uint16_t vout = SMARTBUCK6_VOUT_MV_MIN;
    static int16_t vout_step = 200;
    uint16_t current = 0;
    if ( smartbuck6_get_pg_pin ( &smartbuck6 ) )
    {
        log_printf( &logger, "\r\n Fault indication detected via PG pin!\r\n" );
        if ( SMARTBUCK6_OK == smartbuck6_read_status ( &smartbuck6, &status ) )
        {
            smartbuck6_display_status ( status );
        }
        smartbuck6_clear_status( &smartbuck6 );
    }
    if ( SMARTBUCK6_OK == smartbuck6_set_buck_vout ( &smartbuck6, SMARTBUCK6_BUCK_ALL, vout ) )
    {
        log_printf ( &logger, "\r\n All outputs voltage: %u mV\r\n", vout );
        vout += vout_step;
        if ( ( vout > SMARTBUCK6_VOUT_MV_MAX ) || ( vout < SMARTBUCK6_VOUT_MV_MIN ) )
        {
            vout_step = -vout_step;
            vout += vout_step;
            vout += vout_step;
        }
        Delay_ms ( 100 );
        if ( SMARTBUCK6_OK == smartbuck6_read_buck_current ( &smartbuck6, SMARTBUCK6_BUCK_A, &current ) )
        {
            log_printf ( &logger, " Buck A current: %u mA\r\n", current );
        }
        if ( SMARTBUCK6_OK == smartbuck6_read_buck_current ( &smartbuck6, SMARTBUCK6_BUCK_B, &current ) )
        {
            log_printf ( &logger, " Buck B current: %u mA\r\n", current );
        }
        if ( SMARTBUCK6_OK == smartbuck6_read_buck_current ( &smartbuck6, SMARTBUCK6_BUCK_C, &current ) )
        {
            log_printf ( &logger, " Buck C current: %u mA\r\n", current );
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Ensure that a valid power supply and appropriate load are connected to the Click board
to observe proper current and fault condition readings.

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
