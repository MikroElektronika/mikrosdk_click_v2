
---
# Angle 10 Click

> [Angle 10 Click](https://www.mikroe.com/?pid_product=MIKROE-5387) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5387&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of Angle 10 Click board by reading and displaying the magnet's angular position in degrees and analog voltage output.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle10

### Example Key Functions

- `angle10_cfg_setup` Config Object Initialization function.
```c
void angle10_cfg_setup ( angle10_cfg_t *cfg );
```

- `angle10_init` Initialization function.
```c
err_t angle10_init ( angle10_t *ctx, angle10_cfg_t *cfg );
```

- `angle10_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t angle10_read_voltage ( angle10_t *ctx, float *voltage );
```

- `angle10_get_angle` This function reads the magnetic angular position in degrees based on @b ANGLE10_NUM_CONVERSIONS of voltage measurements.
```c
err_t angle10_get_angle ( angle10_t *ctx, float *angle );
```

- `angle10_set_vref` This function sets the voltage reference for Angle 10 Click driver.
```c
err_t angle10_set_vref ( angle10_t *ctx, float vref );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle10_cfg_t angle10_cfg;  /**< Click config object. */

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
    angle10_cfg_setup( &angle10_cfg );
    ANGLE10_MAP_MIKROBUS( angle10_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == angle10_init( &angle10, &angle10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnet's angular position in degrees and analog voltage output and displays the results on the USB UART approximately every 500ms.

```c
void application_task ( void )
{
    float voltage, angle;
    if ( ANGLE10_OK == angle10_read_voltage ( &angle10, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f V\r\n", voltage );
    }
    if ( ANGLE10_OK == angle10_get_angle ( &angle10, &angle ) )
    {
        log_printf ( &logger, " Angle: %.2f Degrees\r\n\n", angle );
    }
    Delay_ms ( 500 );
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
