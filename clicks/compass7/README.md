
---
# Compass 7 Click

> [Compass 7 Click](https://www.mikroe.com/?pid_product=MIKROE-5190) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5190&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Compass 7 Click board by reading and displaying the magnetic field strength of 3-axis as well as the temperature measurements in Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass7

### Example Key Functions

- `compass7_cfg_setup` Config Object Initialization function.
```c
void compass7_cfg_setup ( compass7_cfg_t *cfg );
```

- `compass7_init` Initialization function.
```c
err_t compass7_init ( compass7_t *ctx, compass7_cfg_t *cfg );
```

- `compass7_default_cfg` Click Default Configuration function.
```c
err_t compass7_default_cfg ( compass7_t *ctx );
```

- `compass7_set_measurement_mode` This function sets the control and ODR registers for the selected measurement mode.
```c
err_t compass7_set_measurement_mode ( compass7_t *ctx, uint8_t mode );
```

- `compass7_get_magnetic_flux` This function reads the raw values of X, Y, and Z axis and converts them to magnetic flux data in Gauss.
```c
err_t compass7_get_magnetic_flux ( compass7_t *ctx, compass7_magnetic_flux_t *flux );
```

- `compass7_get_temperature` This function reads the temperature measurements in Celsius.
```c
err_t compass7_get_temperature ( compass7_t *ctx, float *temperature );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    compass7_cfg_t compass7_cfg;  /**< Click config object. */

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
    compass7_cfg_setup( &compass7_cfg );
    COMPASS7_MAP_MIKROBUS( compass7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == compass7_init( &compass7, &compass7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COMPASS7_ERROR == compass7_default_cfg ( &compass7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Starts the single magnetic measurement and reads the magnetic field strength of 3-axis in Gauss, then starts the temperature measurement and reads the temperature in Celsius.
The results are being displayed on the USB UART every 100ms approximately.

```c
void application_task ( void )
{
    compass7_magnetic_flux_t magnetic_flux;
    float temperature;
    if ( ( COMPASS7_OK == compass7_set_measurement_mode ( &compass7, COMPASS7_MEAS_SINGLE_M ) ) &&
         ( COMPASS7_OK == compass7_get_magnetic_flux ( &compass7, &magnetic_flux ) ) )
    {
        log_printf ( &logger, " X: %.2f G\r\n", magnetic_flux.x_axis );
        log_printf ( &logger, " Y: %.2f G\r\n", magnetic_flux.y_axis );
        log_printf ( &logger, " Z: %.2f G\r\n", magnetic_flux.z_axis );
    }
    if ( ( COMPASS7_OK == compass7_set_measurement_mode ( &compass7, COMPASS7_MEAS_SINGLE_T ) ) &&
         ( COMPASS7_OK == compass7_get_temperature ( &compass7, &temperature ) ) )
    {
        log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
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
