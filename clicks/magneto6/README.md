
---
# Magneto 6 Click

> [Magneto 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4139) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4139&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Magneto 6 Click board by reading the magnetic field strength from 3 axes as well as the ambient temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto6

### Example Key Functions

- `magneto6_cfg_setup` Config Object Initialization function.
```c
void magneto6_cfg_setup ( magneto6_cfg_t *cfg );
```

- `magneto6_init` Initialization function.
```c
err_t magneto6_init ( magneto6_t *ctx, magneto6_cfg_t *cfg );
```

- `magneto6_default_cfg` Click Default Configuration function.
```c
err_t magneto6_default_cfg ( magneto6_t *ctx );
```

- `magneto6_read_data` This function reads the measurements of the 3-axes magnetic field sensor in mT and the temperature sensor in degrees Celsius.
```c
err_t magneto6_read_data ( magneto6_t *ctx, magneto6_data_t *data_out );
```

- `magneto6_read_reg` This function reads a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
err_t magneto6_read_reg ( magneto6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
```

- `magneto6_write_reg` This function writes a data byte to the selected register by using I2C serial interface.
```c
err_t magneto6_write_reg ( magneto6_t *ctx, uint8_t reg, uint8_t data_in );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto6_cfg_t magneto6_cfg;  /**< Click config object. */

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
    magneto6_cfg_setup( &magneto6_cfg );
    MAGNETO6_MAP_MIKROBUS( magneto6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == magneto6_init( &magneto6, &magneto6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETO6_ERROR == magneto6_default_cfg ( &magneto6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads data from the sensor and displays them on the USB UART once per second.

```c
void application_task ( void )
{
    magneto6_data_t data_res;
    if ( MAGNETO6_OK == magneto6_read_data ( &magneto6, &data_res ) )
    {
        log_printf( &logger, " X data: %.1f mT\r\n", data_res.x_data );
        log_printf( &logger, " Y data: %.1f mT\r\n", data_res.y_data );
        log_printf( &logger, " Z data: %.1f mT\r\n", data_res.z_data );
        log_printf( &logger, " Temperature: %.2f degC\r\n\n", data_res.temperature );
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
