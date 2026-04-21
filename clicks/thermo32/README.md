
---
# Thermo 32 Click

> [Thermo 32 Click](https://www.mikroe.com/?pid_product=MIKROE-6941) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6941&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates how to read temperature data and detect ALERT events using the Thermo 32 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo32

### Example Key Functions

- `thermo32_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void thermo32_cfg_setup ( thermo32_cfg_t *cfg );
```

- `thermo32_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t thermo32_init ( thermo32_t *ctx, thermo32_cfg_t *cfg );
```

- `thermo32_default_cfg` This function executes a default configuration of Thermo 32 Click board.
```c
err_t thermo32_default_cfg ( thermo32_t *ctx );
```

- `thermo32_get_alert_pin` This function reads the digital state of the ALERT pin.
```c
uint8_t thermo32_get_alert_pin ( thermo32_t *ctx );
```

- `thermo32_clear_alert` This function clears the alert interrupt by reading the configuration register.
```c
err_t thermo32_clear_alert ( thermo32_t *ctx );
```

- `thermo32_get_temp` This function reads the temperature and converts it to degrees Celsius.
```c
err_t thermo32_get_temp ( thermo32_t *ctx, float *temp );
```

### Application Init

> Initializes the driver and configures the Thermo 32 Click for temperature measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo32_cfg_t thermo32_cfg;  /**< Click config object. */

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
    thermo32_cfg_setup( &thermo32_cfg );
    THERMO32_MAP_MIKROBUS( thermo32_cfg, MIKROBUS_POSITION_THERMO32 );
    if ( I2C_MASTER_ERROR == thermo32_init( &thermo32, &thermo32_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO32_ERROR == thermo32_default_cfg ( &thermo32 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature value periodically and logs an ALERT message when the alert pin becomes active.

```c
void application_task ( void )
{
    float temperature = 0;
    if ( !thermo32_get_alert_pin ( &thermo32 ) )
    {
        log_printf ( &logger, " ALERT Detected!\r\n" );
        thermo32_clear_alert ( &thermo32 );
    }
    if ( THERMO32_OK == thermo32_get_temp ( &thermo32, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n\n", temperature );
    }
    Delay_ms ( 1000 );
}
```

### Note

> The temperature is measured once per second. An alert condition becomes active when
the temperature exceeds THERMO32_TEMP_LIMIT_HIGH or drops below THERMO32_TEMP_LIMIT_LOW.

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
