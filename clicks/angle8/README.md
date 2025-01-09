
---
# Angle 8 Click

> [Angle 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4971) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4971&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Angle 8 Click board by reading and displaying the magnet's angular position in degrees.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle8

### Example Key Functions

- `angle8_cfg_setup` Config Object Initialization function.
```c
void angle8_cfg_setup ( angle8_cfg_t *cfg );
```

- `angle8_init` Initialization function.
```c
err_t angle8_init ( angle8_t *ctx, angle8_cfg_t *cfg );
```

- `angle8_default_cfg` Click Default Configuration function.
```c
err_t angle8_default_cfg ( angle8_t *ctx );
```

- `angle8_get_nd_pin` This function returns the new data ready (ND) pin logic state.
```c
uint8_t angle8_get_nd_pin ( angle8_t *ctx );
```

- `angle8_set_cycle_time` This function sets the sensor cycle time (measurement rate) in milliseconds.
```c
err_t angle8_set_cycle_time ( angle8_t *ctx, float time_ms );
```

- `angle8_read_angle` This function reads raw angle data and converts it to degrees.
```c
err_t angle8_read_angle ( angle8_t *ctx, float *angle );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the clockwise rotation direction and cycle time to 100ms.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle8_cfg_t angle8_cfg;  /**< Click config object. */

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
    angle8_cfg_setup( &angle8_cfg );
    ANGLE8_MAP_MIKROBUS( angle8_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == angle8_init( &angle8, &angle8_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANGLE8_ERROR == angle8_default_cfg ( &angle8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the new data ready flag and then reads the magnet's angular position in degrees and displays the results on the USB UART.

```c
void application_task ( void )
{
    if ( angle8_get_nd_pin ( &angle8 ) )
    {
        float angle = 0;
        if ( ANGLE8_OK == angle8_read_angle ( &angle8, &angle ) )
        {
            log_printf ( &logger, " Angle: %.2f Deg \r\n\n", angle );
        }
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
