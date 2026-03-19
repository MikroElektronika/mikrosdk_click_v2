
---
# TPS Pressure 040MY Click

> [TPS Pressure 040MY Click](https://www.mikroe.com/?pid_product=MIKROE-6824) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6824&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the TPS Pressure 040MY Click board.
The application continuously measures and logs the pressure in millibars
and the temperature in degrees Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TPSPressure040MY

### Example Key Functions

- `tpspressure040my_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void tpspressure040my_cfg_setup ( tpspressure040my_cfg_t *cfg );
```

- `tpspressure040my_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t tpspressure040my_init ( tpspressure040my_t *ctx, tpspressure040my_cfg_t *cfg );
```

- `tpspressure040my_default_cfg` This function executes a default configuration of TPS Pressure 040MY Click board.
```c
err_t tpspressure040my_default_cfg ( tpspressure040my_t *ctx );
```

- `tpspressure040my_read_data` This function reads pressure (mBar) and temperature (degC) values.
```c
err_t tpspressure040my_read_data ( tpspressure040my_t *ctx, float *press, float *temp );
```

### Application Init

> Initializes the driver, checks communication, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tpspressure040my_cfg_t tpspressure040my_cfg;  /**< Click config object. */

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
    tpspressure040my_cfg_setup( &tpspressure040my_cfg );
    TPSPRESSURE040MY_MAP_MIKROBUS( tpspressure040my_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == tpspressure040my_init( &tpspressure040my, &tpspressure040my_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TPSPRESSURE040MY_ERROR == tpspressure040my_default_cfg ( &tpspressure040my ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and logs pressure and temperature values every 100 ms.

```c
void application_task ( void )
{
    float pressure = 0;
    float temperature = 0;
    if ( TPSPRESSURE040MY_OK == tpspressure040my_read_data ( &tpspressure040my, &pressure, &temperature ) )
    {
        log_printf( &logger, " Pressure: %.2f mBar\r\n", pressure );
        log_printf( &logger, " Temperature: %.2f degC\r\n\n", temperature );
    }
    Delay_ms ( 100 );
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
