
---
# Magneto 10 Click

> [Magneto 10 Click](https://www.mikroe.com/?pid_product=MIKROE-4866) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4866&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Magneto 10 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto10

### Example Key Functions

- `magneto10_cfg_setup` Config Object Initialization function.
```c
void magneto10_cfg_setup ( magneto10_cfg_t *cfg );
```

- `magneto10_init` Initialization function.
```c
err_t magneto10_init ( magneto10_t *ctx, magneto10_cfg_t *cfg );
```

- `magneto10_default_cfg` Click Default Configuration function.
```c
err_t magneto10_default_cfg ( magneto10_t *ctx );
```

- `magneto10_get_magnetic_flux` This function reads the raw values of X, Y, and Z axis and converts them to magnetic flux data in microTesla.
```c
err_t magneto10_get_magnetic_flux ( magneto10_t *ctx, float *x_axis, float *y_axis, float *z_axis );
```

- `magneto10_get_temperature` This function reads the raw temperature value and converts it to Celsius.
```c
err_t magneto10_get_temperature ( magneto10_t *ctx, float *temperature );
```

- `magneto10_set_operating_mode` This function sets the device operating mode.
```c
err_t magneto10_set_operating_mode ( magneto10_t *ctx, uint8_t mode );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    magneto10_cfg_t magneto10_cfg;  /**< Click config object. */

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
    magneto10_cfg_setup( &magneto10_cfg );
    MAGNETO10_MAP_MIKROBUS( magneto10_cfg, MIKROBUS_1 );
    
    if ( I2C_MASTER_ERROR == magneto10_init( &magneto10, &magneto10_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    if ( MAGNETO10_ERROR == magneto10_default_cfg( &magneto10 ) ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnetic flux as well as the internal temperature data every 100ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    float x_axis, y_axis, z_axis, temperature;
    if ( MAGNETO10_OK == magneto10_get_magnetic_flux ( &magneto10, &x_axis, &y_axis, &z_axis ) )
    {
        log_printf( &logger, " X-axis: %.2f uT\r\n Y-axis: %.2f uT\r\n Z-axis: %.2f uT\r\n", 
                    x_axis, y_axis, z_axis );
    }
    if ( MAGNETO10_OK == magneto10_get_temperature ( &magneto10, &temperature ) )
    {
        log_printf( &logger, " Internal temperature: %.2f C\r\n\n", temperature );
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
