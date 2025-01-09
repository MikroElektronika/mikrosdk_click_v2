
---
# Magnetic Rotary 4 Click

> [Magnetic Rotary 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5223) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5223&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Magnetic Rotary 4 Click board by reading and displaying the magnet (potentiometer) angular position in degrees.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MagneticRotary4

### Example Key Functions

- `magneticrotary4_cfg_setup` Config Object Initialization function.
```c
void magneticrotary4_cfg_setup ( magneticrotary4_cfg_t *cfg );
```

- `magneticrotary4_init` Initialization function.
```c
err_t magneticrotary4_init ( magneticrotary4_t *ctx, magneticrotary4_cfg_t *cfg );
```

- `magneticrotary4_set_rotation_direction` This function sets the magnet rotation direction to clockwise or counter-clockwise.
```c
err_t magneticrotary4_set_rotation_direction ( magneticrotary4_t *ctx, uint8_t direction );
```

- `magneticrotary4_calibrate_zero_position` This function calibrates the sensor to zero Angle position.
```c
err_t magneticrotary4_calibrate_zero_position ( magneticrotary4_t *ctx );
```

- `magneticrotary4_get_angle` This function reads the absolute position raw data and converts it to degrees (Angle).
```c
err_t magneticrotary4_get_angle ( magneticrotary4_t *ctx, float *angle );
```

### Application Init

> Initializes the driver, sets the rotation direction, and calibrates the sensor for potentiometer zero position.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary4_cfg_t magneticrotary4_cfg;  /**< Click config object. */

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
    magneticrotary4_cfg_setup( &magneticrotary4_cfg );
    MAGNETICROTARY4_MAP_MIKROBUS( magneticrotary4_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneticrotary4_init( &magneticrotary4, &magneticrotary4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY4_ERROR == magneticrotary4_set_rotation_direction ( &magneticrotary4, MAGNETICROTARY4_DIRECTION_CW ) )
    {
        log_error( &logger, " Set rotation direction." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY4_ERROR == magneticrotary4_calibrate_zero_position ( &magneticrotary4 ) )
    {
        log_error( &logger, " Calibrate zero position." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnet (potentiometer) angular position in degrees every 100ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    float angle;
    if ( MAGNETICROTARY4_OK == magneticrotary4_get_angle ( &magneticrotary4, &angle ) )
    {
        log_printf( &logger, " Angle: %.1f degrees\r\n\n", angle );
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
