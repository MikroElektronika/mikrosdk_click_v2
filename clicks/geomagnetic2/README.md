
---
# GeoMagnetic 2 Click

> [GeoMagnetic 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6925) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6925&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Mar 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the GeoMagnetic 2 Click board by
reading compensated 3-axis magnetic field data and die temperature from
the BMM350 sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GeoMagnetic2

### Example Key Functions

- `geomagnetic2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void geomagnetic2_cfg_setup ( geomagnetic2_cfg_t *cfg );
```

- `geomagnetic2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t geomagnetic2_init ( geomagnetic2_t *ctx, geomagnetic2_cfg_t *cfg );
```

- `geomagnetic2_default_cfg` This function executes a default configuration of GeoMagnetic 2 Click board.
```c
err_t geomagnetic2_default_cfg ( geomagnetic2_t *ctx );
```

- `geomagnetic2_set_powermode` This function transitions the device to the requested power mode with proper delays and state checks.
```c
err_t geomagnetic2_set_powermode ( geomagnetic2_t *ctx, uint8_t powermode );
```

- `geomagnetic2_enable_axes` This function enables individual measurement axes.
```c
err_t geomagnetic2_enable_axes ( geomagnetic2_t *ctx, uint8_t axes );
```

- `geomagnetic2_read_data` This function reads raw 24-bit magnetic and temperature data via burst read and applies the full OTP compensation algorithm.
```c
err_t geomagnetic2_read_data ( geomagnetic2_t *ctx, geomagnetic2_data_t *mag_data );
```

### Application Init

> Initializes the logger and the GeoMagnetic 2 driver,
then applies the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    geomagnetic2_cfg_t geomagnetic2_cfg;  /**< Click config object. */

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
    geomagnetic2_cfg_setup( &geomagnetic2_cfg );
    GEOMAGNETIC2_MAP_MIKROBUS( geomagnetic2_cfg, MIKROBUS_POSITION_GEOMAGNETIC2 );
    if ( I2C_MASTER_ERROR == geomagnetic2_init( &geomagnetic2, &geomagnetic2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GEOMAGNETIC2_ERROR == geomagnetic2_default_cfg ( &geomagnetic2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    /* Enable interrupt */
    geomagnetic2_enable_interrupt( &geomagnetic2, 1 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the compensated magnetic field data and die temperature from the BMM350 sensor
when a data-ready interrupt is received on the INT pin and logs them
to the UART terminal.

```c
void application_task ( void )
{
    geomagnetic2_data_t mag_data;
    uint8_t int_status = 0;

    if ( geomagnetic2_get_int_pin( &geomagnetic2 ) )
    {   
        if ( GEOMAGNETIC2_OK == geomagnetic2_get_int_status( &geomagnetic2, &int_status ) )
        {
            if ( int_status & GEOMAGNETIC2_INT_DRDY_MASK )
            {   
                if ( GEOMAGNETIC2_OK == geomagnetic2_read_data( &geomagnetic2, &mag_data ) )
                {            
                    if ( mag_data.mag_x > GEOMAGNETIC2_FIELD_LIMIT_MAX_UT || mag_data.mag_x < GEOMAGNETIC2_FIELD_LIMIT_MIN_UT ||
                         mag_data.mag_y > GEOMAGNETIC2_FIELD_LIMIT_MAX_UT || mag_data.mag_y < GEOMAGNETIC2_FIELD_LIMIT_MIN_UT ||
                         mag_data.mag_z > GEOMAGNETIC2_FIELD_LIMIT_MAX_UT || mag_data.mag_z < GEOMAGNETIC2_FIELD_LIMIT_MIN_UT )
                    {
                        log_info( &logger, "High field detected -> magnetic reset" );
                        geomagnetic2_magnetic_reset( &geomagnetic2 );
                        return;
                    }

                    log_printf( &logger, "X: %.2f uT\r\n", mag_data.mag_x );
                    log_printf( &logger, "Y: %.2f uT\r\n", mag_data.mag_y );
                    log_printf( &logger, "Z: %.2f uT\r\n", mag_data.mag_z );
                    log_printf( &logger, "T: %.2f degC\r\n", mag_data.temperature );
                    log_printf( &logger, "--------------------\r\n" );
                }
            }
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
