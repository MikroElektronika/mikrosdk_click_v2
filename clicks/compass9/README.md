
---
# Compass 9 Click

> [Compass 9 Click](https://www.mikroe.com/?pid_product=MIKROE-6575) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6575&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2025.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Compass 9 Click board.
It periodically measures and logs the magnetic flux density on
the X, Y, and Z axes, as well as the ambient temperature values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass9

### Example Key Functions

- `compass9_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void compass9_cfg_setup ( compass9_cfg_t *cfg );
```

- `compass9_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t compass9_init ( compass9_t *ctx, compass9_cfg_t *cfg );
```

- `compass9_default_cfg` This function executes a default configuration of Compass 9 Click board.
```c
err_t compass9_default_cfg ( compass9_t *ctx );
```

- `compass9_start_measurement` This function starts a measurement in a selected operating mode.
```c
err_t compass9_start_measurement ( compass9_t *ctx, uint8_t mode );
```

- `compass9_get_magnetic_flux` This function reads magnetic flux density values (X, Y, Z axes).
```c
err_t compass9_get_magnetic_flux ( compass9_t *ctx, compass9_magnetic_flux_t *flux );
```

- `compass9_get_temperature` This function reads the device temperature value in Celsius.
```c
err_t compass9_get_temperature ( compass9_t *ctx, float *temperature );
```

### Application Init

> Initializes the driver, checks communication, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    compass9_cfg_t compass9_cfg;  /**< Click config object. */

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
    compass9_cfg_setup( &compass9_cfg );
    COMPASS9_MAP_MIKROBUS( compass9_cfg, MIKROBUS_1 );
    err_t init_flag = compass9_init( &compass9, &compass9_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COMPASS9_ERROR == compass9_default_cfg ( &compass9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and logs the magnetic flux density for all 3 axes in Gauss and the temperature in degrees Celsius every 200 ms.

```c
void application_task ( void )
{
    compass9_magnetic_flux_t magnetic_flux;
    float temperature = 0;
    if ( COMPASS9_OK == compass9_start_measurement ( &compass9, COMPASS9_MEAS_SINGLE_M ) )
    {
        if ( COMPASS9_OK == compass9_get_magnetic_flux ( &compass9, &magnetic_flux ) )
        {
            log_printf ( &logger, " X: %.2f G\r\n", magnetic_flux.x_axis );
            log_printf ( &logger, " Y: %.2f G\r\n", magnetic_flux.y_axis );
            log_printf ( &logger, " Z: %.2f G\r\n", magnetic_flux.z_axis );
        }
    }
    if ( COMPASS9_OK == compass9_start_measurement ( &compass9, COMPASS9_MEAS_SINGLE_T ) )
    {
        if ( COMPASS9_OK == compass9_get_temperature ( &compass9, &temperature ) )
        {
            log_printf ( &logger, " Temperature: %.2f degC\r\n\n", temperature );
        }
    }
    Delay_ms ( 200 );
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
