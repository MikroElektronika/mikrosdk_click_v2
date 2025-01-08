
---
# Thermo 23 Click

> [Thermo 23 Click](https://www.mikroe.com/?pid_product=MIKROE-4979) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4979&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Thermo 23 Click board by reading and displaying the temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo23

### Example Key Functions

- `thermo23_cfg_setup` Config Object Initialization function.
```c
void thermo23_cfg_setup ( thermo23_cfg_t *cfg );
```

- `thermo23_init` Initialization function.
```c
err_t thermo23_init ( thermo23_t *ctx, thermo23_cfg_t *cfg );
```

- `thermo23_default_cfg` Click Default Configuration function.
```c
err_t thermo23_default_cfg ( thermo23_t *ctx );
```

- `thermo23_set_config` This function sets the configuration register.
```c
err_t thermo23_set_config ( thermo23_t *ctx, uint16_t config );
```

- `thermo23_read_temperature` This function reads the temperature value in Celsius.
```c
err_t thermo23_read_temperature ( thermo23_t *ctx, float *temperature );
```

- `thermo23_read_command` This function reads data from the selected command by using UART serial interface.
```c
err_t thermo23_read_command ( thermo23_t *ctx, uint8_t cmd, uint16_t *data_out );
```

### Application Init

> Initializes the driver and logger, and performs the Click default configuration which enables continuous conversion and sets the conversion rate to 1 Hz.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo23_cfg_t thermo23_cfg;  /**< Click config object. */

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
    thermo23_cfg_setup( &thermo23_cfg );
    THERMO23_MAP_MIKROBUS( thermo23_cfg, MIKROBUS_1 );
    if ( UART_ERROR == thermo23_init( &thermo23, &thermo23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO23_ERROR == thermo23_default_cfg ( &thermo23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature measurement in Celsius and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature;
    if ( THERMO23_OK == thermo23_read_temperature ( &thermo23, &temperature ) ) 
    {
        log_printf( &logger, " Temperature : %.2f C\r\n\n", temperature );
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
