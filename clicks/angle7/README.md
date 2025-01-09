
---
# Angle 7 Click

> [Angle 7 Click](https://www.mikroe.com/?pid_product=MIKROE-5196) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5196&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Angle 7 Click board by reading and displaying
the magnet's angular position in degrees and analog voltage output as well as
the magnet's status and magnitude.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle7

### Example Key Functions

- `angle7_cfg_setup` Config Object Initialization function.
```c
void angle7_cfg_setup ( angle7_cfg_t *cfg );
```

- `angle7_init` Initialization function.
```c
err_t angle7_init ( angle7_t *ctx, angle7_cfg_t *cfg );
```

- `angle7_default_cfg` Click Default Configuration function.
```c
err_t angle7_default_cfg ( angle7_t *ctx );
```

- `angle7_get_status` This function reads the status data.
```c
err_t angle7_get_status ( angle7_t *ctx, uint8_t *status );
```

- `angle7_get_angle` This function reads the calculated angle in degrees.
```c
err_t angle7_get_angle ( angle7_t *ctx, float *angle );
```

- `angle7_get_magnitude` This function reads the magnitude data.
```c
err_t angle7_get_magnitude ( angle7_t *ctx, uint16_t *magnitude );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle7_cfg_t angle7_cfg;  /**< Click config object. */

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
    angle7_cfg_setup( &angle7_cfg );
    ANGLE7_MAP_MIKROBUS( angle7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == angle7_init( &angle7, &angle7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANGLE7_ERROR == angle7_default_cfg ( &angle7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnet's angular position in degrees and analog voltage output
as well as the magnet's status and magnitude and displays the results on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    float voltage, raw_angle, angle;
    uint16_t magnitude;
    uint8_t status;
    if ( ADC_ERROR != angle7_read_an_pin_voltage ( &angle7, &voltage ) ) 
    {
        log_printf( &logger, " AN voltage: %.3f V\r\n", voltage );
    }
    if ( ANGLE7_OK == angle7_get_angle ( &angle7, &angle ) )
    {
        log_printf ( &logger, " Angle: %.2f Degrees\r\n", angle );
    }
    if ( ANGLE7_OK == angle7_get_magnitude ( &angle7, &magnitude ) )
    {
        log_printf ( &logger, " Magnitude: %u\r\n", magnitude );
    }
    if ( ANGLE7_OK == angle7_get_status ( &angle7, &status ) )
    {
        log_printf ( &logger, " Status:" );
        if ( status & ANGLE7_STATUS_MAGNET_DETECTED )
        {
            log_printf ( &logger, " Magnet Detected \r\n Magnet Strength:" );
            if ( status & ANGLE7_STATUS_MAGNET_TOO_STRONG )
            {
                log_printf ( &logger, " Too Strong \r\n\n" );
            }
            else if ( status & ANGLE7_STATUS_MAGNET_TOO_WEAK )
            {
                log_printf ( &logger, " Too Weak \r\n\n" );
            }
            else
            {
                log_printf ( &logger, " Good \r\n\n" );
            }
        }
        else
        {
            log_printf ( &logger, " Magnet Not Detected \r\n\n" );
        }
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
