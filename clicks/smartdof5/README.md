
---
# Smart DOF 5 Click

> [Smart DOF 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6398) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6398&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Smart DOF 5 Click board by reading and displaying 
the accelerometer and gyroscope data (X, Y, and Z axis) as well as a temperature measurement in degrees Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartDOF5

### Example Key Functions

- `smartdof5_cfg_setup` Config Object Initialization function.
```c
void smartdof5_cfg_setup ( smartdof5_cfg_t *cfg );
```

- `smartdof5_init` Initialization function.
```c
err_t smartdof5_init ( smartdof5_t *ctx, smartdof5_cfg_t *cfg );
```

- `smartdof5_default_cfg` Click Default Configuration function.
```c
err_t smartdof5_default_cfg ( smartdof5_t *ctx );
```

- `smartdof5_get_int_pin` This function returns the interrupt 1 pin logic state.
```c
uint8_t smartdof5_get_int_pin ( smartdof5_t *ctx );
```

- `smartdof5_get_data` This function reads the accelerometer, gyroscope, and temperature measurement data.
```c
err_t smartdof5_get_data ( smartdof5_t *ctx, smartdof5_data_t *data_out );
```

- `smartdof5_set_accel_fsr` This function sets the accel measurement full scale range.
```c
err_t smartdof5_set_accel_fsr ( smartdof5_t *ctx, uint8_t fsr );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartdof5_cfg_t smartdof5_cfg;  /**< Click config object. */

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
    smartdof5_cfg_setup( &smartdof5_cfg );
    SMARTDOF5_MAP_MIKROBUS( smartdof5_cfg, MIKROBUS_1 );
    err_t init_flag = smartdof5_init( &smartdof5, &smartdof5_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTDOF5_ERROR == smartdof5_default_cfg ( &smartdof5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a data ready indication and then reads the accelerometer, gyroscope, and temperature
measurements. The results are displayed on the USB UART at 12.5 Hz output data rate.

```c
void application_task ( void )
{
    smartdof5_data_t meas_data;
    if ( smartdof5_get_int_pin ( &smartdof5 ) ) 
    {
        if ( SMARTDOF5_OK == smartdof5_get_data ( &smartdof5, &meas_data ) )
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
