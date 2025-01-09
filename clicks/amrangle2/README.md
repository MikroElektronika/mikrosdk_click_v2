
---
# AMR Angle 2 Click

> [AMR Angle 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4981) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4981&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of AMR Angle 2 Click board by reading and displaying the magnet's angular position in Degrees and a system temperature in Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AMRAngle2

### Example Key Functions

- `amrangle2_cfg_setup` Config Object Initialization function.
```c
void amrangle2_cfg_setup ( amrangle2_cfg_t *cfg );
```

- `amrangle2_init` Initialization function.
```c
err_t amrangle2_init ( amrangle2_t *ctx, amrangle2_cfg_t *cfg );
```

- `amrangle2_default_cfg` Click Default Configuration function.
```c
err_t amrangle2_default_cfg ( amrangle2_t *ctx );
```

- `amrangle2_read_angle` This function reads a Vsin and Vcos voltages and converts them to angle in Degrees.
```c
err_t amrangle2_read_angle ( amrangle2_t *ctx, float *angle );
```

- `amrangle2_read_temperature` This function reads a temperature measurements in Celsius.
```c
err_t amrangle2_read_temperature ( amrangle2_t *ctx, float *temperature );
```

- `amrangle2_read_vsin_vcos` This function reads a voltage of sine and cosine differential signal outputs.
```c
err_t amrangle2_read_vsin_vcos ( amrangle2_t *ctx, float *vsin, float *vcos );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    amrangle2_cfg_t amrangle2_cfg;  /**< Click config object. */

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
    amrangle2_cfg_setup( &amrangle2_cfg );
    AMRANGLE2_MAP_MIKROBUS( amrangle2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == amrangle2_init( &amrangle2, &amrangle2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMRANGLE2_ERROR == amrangle2_default_cfg ( &amrangle2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnet's angular position in degrees and a system temperature in Celsius and displays the results on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    float angle, temperature;
    if ( AMRANGLE2_OK == amrangle2_read_angle ( &amrangle2, &angle ) ) 
    {
        log_printf( &logger, " Angle: %.2f Degrees\r\n", angle );
    }
    if ( AMRANGLE2_OK == amrangle2_read_temperature ( &amrangle2, &temperature ) ) 
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
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
