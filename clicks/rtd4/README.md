
---
# RTD 4 Click

> [RTD 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6966) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6966&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example initializes RTD 4 Click and configures the ADS122U04 for a
3-wire PT100 RTD measurement. The application reads the conversion result,
calculates RTD resistance and displays an approximate temperature value.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTD4

### Example Key Functions

- `rtd4_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void rtd4_cfg_setup ( rtd4_cfg_t *cfg );
```

- `rtd4_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t rtd4_init ( rtd4_t *ctx, rtd4_cfg_t *cfg );
```

- `rtd4_default_cfg` This function executes a default configuration of RTD 4 Click board.
```c
err_t rtd4_default_cfg ( rtd4_t *ctx );
```

- `rtd4_read_temp` This function reads RTD resistance and calculates approximate PT100 temperature using a linear coefficient.
```c
err_t rtd4_read_temp ( rtd4_t *ctx, float *temperature, float *resistance );
```

### Application Init

> Initializes the logger, click driver and default ADS122U04 configuration for the RTD 4 Click 3-wire measurement circuit.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtd4_cfg_t rtd4_cfg;  /**< Click config object. */

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
    rtd4_cfg_setup( &rtd4_cfg );
    RTD4_MAP_MIKROBUS( rtd4_cfg, MIKROBUS_POSITION_RTD4 );
    if ( UART_ERROR == rtd4_init( &rtd4, &rtd4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTD4_ERROR == rtd4_default_cfg ( &rtd4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the ADC result, converts it to RTD resistance and prints the calculated
resistance and approximate PT100 temperature once per second.

```c
void application_task ( void )
{
    float resistance = 0.0f;
    float temperature = 0.0f;

    if ( RTD4_OK == rtd4_read_temp( &rtd4, &temperature, &resistance ) )
    {
        log_printf( &logger, "RTD resistance: %.2f Ohm\r\n", resistance );
        log_printf( &logger, "Temperature: %.2f degC\r\n\n", temperature );
    }

    Delay_ms( 1000 );
}
```

### Note

> Connect a 3-wire PT100 RTD sensor to the terminal block pins R+, R- and F before running the example.

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
