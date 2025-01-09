
---
# Magnetic Rotary 6 Click

> [Magnetic Rotary 6 Click](https://www.mikroe.com/?pid_product=MIKROE-5585) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5585&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Magnetic Rotary 6 Click board by reading and displaying the magnet's angular position in degrees measured by the bottom and top sensor dies.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MagneticRotary6

### Example Key Functions

- `magneticrotary6_cfg_setup` Config Object Initialization function.
```c
void magneticrotary6_cfg_setup ( magneticrotary6_cfg_t *cfg );
```

- `magneticrotary6_init` Initialization function.
```c
err_t magneticrotary6_init ( magneticrotary6_t *ctx, magneticrotary6_cfg_t *cfg );
```

- `magneticrotary6_default_cfg` Click Default Configuration function.
```c
err_t magneticrotary6_default_cfg ( magneticrotary6_t *ctx );
```

- `magneticrotary6_write_register` This function writes a desired data to the selected register of a desired sensor die by using SPI serial interface.
```c
err_t magneticrotary6_write_register ( magneticrotary6_t *ctx, uint8_t die_sel, uint16_t reg, uint16_t data_in );
```

- `magneticrotary6_get_angle` This function reads the absolute position raw data of a desired sensor die and converts it to degrees (Angle).
```c
err_t magneticrotary6_get_angle ( magneticrotary6_t *ctx, uint8_t die_sel, float *angle );
```

- `magneticrotary6_set_direction` This function sets the rotation direction of a desired sensor die.
```c
err_t magneticrotary6_set_direction ( magneticrotary6_t *ctx, uint8_t die_sel, uint8_t dir );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the magnet rotation direction for the bottom die to clockwise and for the top die to counter-clockwise.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary6_cfg_t magneticrotary6_cfg;  /**< Click config object. */

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
    magneticrotary6_cfg_setup( &magneticrotary6_cfg );
    MAGNETICROTARY6_MAP_MIKROBUS( magneticrotary6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneticrotary6_init( &magneticrotary6, &magneticrotary6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY6_ERROR == magneticrotary6_default_cfg ( &magneticrotary6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnet's angular position from both sensor dies in degrees every 100ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    float angle;
    if ( MAGNETICROTARY6_OK == magneticrotary6_get_angle ( &magneticrotary6, MAGNETICROTARY6_DIE_BOTTOM, &angle ) )
    {
        log_printf( &logger, " Angle (bottom die): %.1f degrees\r\n", angle );
    }
    if ( MAGNETICROTARY6_OK == magneticrotary6_get_angle ( &magneticrotary6, MAGNETICROTARY6_DIE_TOP, &angle ) )
    {
        log_printf( &logger, " Angle (top die): %.1f degrees\r\n\n", angle );
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
