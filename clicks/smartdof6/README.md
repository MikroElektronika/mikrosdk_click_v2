
---
# Smart DOF 6 Click

> [Smart DOF 6 Click](https://www.mikroe.com/?pid_product=MIKROE-6853) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6853&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2025.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Smart DOF 6 Click board by reading and displaying 
the accelerometer and gyroscope data (X, Y, and Z axis) as well as a temperature measurement
in degrees Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartDOF6

### Example Key Functions

- `smartdof6_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void smartdof6_cfg_setup ( smartdof6_cfg_t *cfg );
```

- `smartdof6_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t smartdof6_init ( smartdof6_t *ctx, smartdof6_cfg_t *cfg );
```

- `smartdof6_default_cfg` This function executes a default configuration of Smart DOF 6 Click board.
```c
err_t smartdof6_default_cfg ( smartdof6_t *ctx );
```

- `smartdof6_get_int_pin` This function returns the interrupt 1 pin logic state.
```c
uint8_t smartdof6_get_int_pin ( smartdof6_t *ctx );
```

- `smartdof6_get_data` This function reads the accelerometer, gyroscope, and temperature measurement data.
```c
err_t smartdof6_get_data ( smartdof6_t *ctx, smartdof6_data_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartdof6_cfg_t smartdof6_cfg;  /**< Click config object. */

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
    smartdof6_cfg_setup( &smartdof6_cfg );
    SMARTDOF6_MAP_MIKROBUS( smartdof6_cfg, MIKROBUS_POSITION_SMARTDOF6 );
    err_t init_flag = smartdof6_init( &smartdof6, &smartdof6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTDOF6_ERROR == smartdof6_default_cfg ( &smartdof6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a data ready indication and then reads the accelerometer, gyroscope, and temperature
measurements. The results are displayed on the USB UART at 7.5 Hz output data rate.

```c
void application_task ( void )
{
    smartdof6_data_t meas_data;
    if ( smartdof6_get_int_pin ( &smartdof6 ) ) 
    {
        if ( SMARTDOF6_OK == smartdof6_get_data ( &smartdof6, &meas_data ) )
        {
            log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
            log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
            log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
            log_printf( &logger, " Gyro X: %.1f dps\r\n", meas_data.gyro.x );
            log_printf( &logger, " Gyro Y: %.1f dps\r\n", meas_data.gyro.y );
            log_printf( &logger, " Gyro Z: %.1f dps\r\n", meas_data.gyro.z );
            log_printf( &logger, " Temperature: %.2f degC\r\n\n", meas_data.temperature );
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
