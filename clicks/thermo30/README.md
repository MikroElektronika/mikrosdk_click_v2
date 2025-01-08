
---
# Thermo 30 Click

> [Thermo 30 Click](https://www.mikroe.com/?pid_product=MIKROE-5736) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5736&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Thermo 30 Click board by reading and displaying
  the temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo30

### Example Key Functions

- `thermo30_cfg_setup` Config Object Initialization function.
```c
void thermo30_cfg_setup ( thermo30_cfg_t *cfg );
```

- `thermo30_init` Initialization function.
```c
err_t thermo30_init ( thermo30_t *ctx, thermo30_cfg_t *cfg );
```

- `thermo30_default_cfg` Click Default Configuration function.
```c
err_t thermo30_default_cfg ( thermo30_t *ctx );
```

- `thermo30_hw_reset` Thermo 30 hw reset device function.
```c
void thermo30_hw_reset ( thermo30_t *ctx );
```

- `thermo30_start_measurement` Thermo 30 start measurement function.
```c
err_t thermo30_start_measurement ( thermo30_t *ctx, uint16_t cmd );
```

- `thermo30_read_temperature` Thermo 30 read temperature function.
```c
err_t thermo30_read_temperature ( thermo30_t *ctx, float *temperature );
```

### Application Init

> Initializes the driver and resets the device, and
  starts the periodic measurements at 1 mps with high repeatability.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo30_cfg_t thermo30_cfg;  /**< Click config object. */

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
    thermo30_cfg_setup( &thermo30_cfg );
    THERMO30_MAP_MIKROBUS( thermo30_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo30_init( &thermo30, &thermo30_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
   
    if ( THERMO30_ERROR == thermo30_default_cfg( &thermo30 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature measurement in degrees Celsius and displays the results on the USB UART
  approximately once per second.

```c
void application_task ( void ) 
{
    float temperature;
    
    if ( THERMO30_OK == thermo30_read_temperature( &thermo30, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f deg C\r\n\n", temperature );
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
