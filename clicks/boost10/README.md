
---
# Boost 10 Click

> [Boost 10 Click](https://www.mikroe.com/?pid_product=MIKROE-6927) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6927&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Boost 10 Click board by dynamically
adjusting the output voltage using the onboard digital potentiometer.
The application gradually increases and decreases the output voltage
within the supported range and logs the set value to the serial terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost10

### Example Key Functions

- `boost10_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void boost10_cfg_setup ( boost10_cfg_t *cfg );
```

- `boost10_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t boost10_init ( boost10_t *ctx, boost10_cfg_t *cfg );
```

- `boost10_set_vout` This function calculates the required feedback resistance for the requested output voltage and updates the digital potentiometer accordingly.
```c
err_t boost10_set_vout ( boost10_t *ctx, float vout );
```

- `boost10_get_pg_pin` This function reads and returns the logic state of the PG pin.
```c
uint8_t boost10_get_pg_pin ( boost10_t *ctx );
```

### Application Init

> Initializes the logger and Boost 10 Click driver and configures SPI communication through the mikroBUS socket.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boost10_cfg_t boost10_cfg;  /**< Click config object. */

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
    boost10_cfg_setup( &boost10_cfg );
    BOOST10_MAP_MIKROBUS( boost10_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == boost10_init( &boost10, &boost10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically changes the output voltage between the minimum and maximum supported values in defined steps and logs the configured voltage.

```c
void application_task ( void )
{
    static float vout = BOOST10_VOUT_MIN;
    static float vout_step = 0.5;
    if ( BOOST10_OK == boost10_set_vout ( &boost10, vout ) )
    {
        log_printf ( &logger, " VOUT: %.1f V\r\n\n", vout );
        vout += vout_step;
        if ( vout > BOOST10_VOUT_MAX || vout < BOOST10_VOUT_MIN )
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
