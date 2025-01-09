
---
# Angle 6 Click

> [Angle 6 Click](https://www.mikroe.com/?pid_product=MIKROE-5282) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5282&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Angle 6 Click board by reading and displaying the magnet's angular position in degrees.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle6

### Example Key Functions

- `angle6_cfg_setup` Config Object Initialization function.
```c
void angle6_cfg_setup ( angle6_cfg_t *cfg );
```

- `angle6_init` Initialization function.
```c
err_t angle6_init ( angle6_t *ctx, angle6_cfg_t *cfg );
```

- `angle6_default_cfg` Click Default Configuration function.
```c
err_t angle6_default_cfg ( angle6_t *ctx );
```

- `angle6_write_register` This function writes a data byte to the selected register by using SPI serial interface.
```c
err_t angle6_write_register ( angle6_t *ctx, uint8_t reg, uint8_t data_in );
```

- `angle6_read_register` This function reads a data byte from the selected register by using SPI serial interface.
```c
err_t angle6_read_register ( angle6_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `angle6_read_angle` This function reads raw angle data and converts it to degrees.
```c
err_t angle6_read_angle ( angle6_t *ctx, float *angle );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the rotation direction to clockwise.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle6_cfg_t angle6_cfg;  /**< Click config object. */

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
    angle6_cfg_setup( &angle6_cfg );
    ANGLE6_MAP_MIKROBUS( angle6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == angle6_init( &angle6, &angle6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANGLE6_ERROR == angle6_default_cfg ( &angle6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnet's angular position in degrees and displays the results on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    float angle = 0;
    if ( ANGLE6_OK == angle6_read_angle ( &angle6, &angle ) )
    {
        log_printf ( &logger, " Angle: %.2f Deg \r\n\n", angle );
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
