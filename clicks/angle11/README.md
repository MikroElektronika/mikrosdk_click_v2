
---
# Angle 11 Click

> [Angle 11 Click](https://www.mikroe.com/?pid_product=MIKROE-6888) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6888&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Angle 11 Click board by reading and displaying
the magnet's angular position in degrees, field strength in gauss, and the internal
sensor temperature in degrees celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle11

### Example Key Functions

- `angle11_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void angle11_cfg_setup ( angle11_cfg_t *cfg );
```

- `angle11_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t angle11_init ( angle11_t *ctx, angle11_cfg_t *cfg );
```

- `angle11_read_angle` This function reads the magnetic angular position in degrees.
```c
err_t angle11_read_angle ( angle11_t *ctx, float *angle );
```

- `angle11_read_temperature` This function reads the sensor internal temperature in degrees celsius.
```c
err_t angle11_read_temperature ( angle11_t *ctx, float *temperature );
```

- `angle11_read_field_strength` This function reads the magnetic field strength in gauss.
```c
err_t angle11_read_field_strength ( angle11_t *ctx, uint16_t *field_str );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle11_cfg_t angle11_cfg;  /**< Click config object. */

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
    angle11_cfg_setup( &angle11_cfg );
    ANGLE11_MAP_MIKROBUS( angle11_cfg, MIKROBUS_POSITION_ANGLE11 );
    if ( SPI_MASTER_ERROR == angle11_init( &angle11, &angle11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnet's angular position in degrees, magnetic field strength in gauss,
and the internal sensor temperature in degrees celsius and displays the results
on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    float angle = 0;
    float int_temp = 0;
    uint16_t field_str = 0;
    if ( ANGLE11_OK == angle11_read_angle ( &angle11, &angle ) )
    {
        log_printf ( &logger, " Angle: %.1f deg\r\n", angle );
        if ( ANGLE11_OK == angle11_read_field_strength ( &angle11, &field_str ) )
        {
            log_printf ( &logger, " Field strength: %u Gauss\r\n", field_str );
        }
        if ( ANGLE11_OK == angle11_read_temperature ( &angle11, &int_temp ) )
        {
            log_printf ( &logger, " Internal temperature: %.2f degC\r\n\n", int_temp );
        }
        Delay_ms ( 100 );
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
