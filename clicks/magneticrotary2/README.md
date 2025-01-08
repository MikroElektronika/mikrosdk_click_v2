
---
# Magnetic Rotary 2 Click

> [Magnetic Rotary 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4952) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4952&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Magnetic Rotary 2 Click board by reading and displaying the magnet's angular position in degrees.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MagneticRotary2

### Example Key Functions

- `magneticrotary2_cfg_setup` Config Object Initialization function.
```c
void magneticrotary2_cfg_setup ( magneticrotary2_cfg_t *cfg );
```

- `magneticrotary2_init` Initialization function.
```c
err_t magneticrotary2_init ( magneticrotary2_t *ctx, magneticrotary2_cfg_t *cfg );
```

- `magneticrotary2_default_cfg` Click Default Configuration function.
```c
err_t magneticrotary2_default_cfg ( magneticrotary2_t *ctx );
```

- `magneticrotary2_write_register` This function writes a data byte to the selected register by using SPI serial interface.
```c
err_t magneticrotary2_write_register ( magneticrotary2_t *ctx, uint8_t reg, uint8_t data_in );
```

- `magneticrotary2_read_register` This function reads a data byte from the selected register by using SPI serial interface.
```c
err_t magneticrotary2_read_register ( magneticrotary2_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `magneticrotary2_get_angle` This function reads the absolute position raw data and converts it to degrees (Angle).
```c
err_t magneticrotary2_get_angle ( magneticrotary2_t *ctx, float *angle );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary2_cfg_t magneticrotary2_cfg;  /**< Click config object. */

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
    magneticrotary2_cfg_setup( &magneticrotary2_cfg );
    MAGNETICROTARY2_MAP_MIKROBUS( magneticrotary2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneticrotary2_init( &magneticrotary2, &magneticrotary2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY2_ERROR == magneticrotary2_default_cfg ( &magneticrotary2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnet's angular position in degrees every 100ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    float angle = 0;
    
    if ( MAGNETICROTARY2_OK == magneticrotary2_get_angle ( &magneticrotary2, &angle ) )
    {
        log_printf( &logger, " Angle: %.2f degrees\r\n\n", angle );
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
