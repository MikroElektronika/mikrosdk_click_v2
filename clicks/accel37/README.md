
---
# Accel 37 Click

> [Accel 37 Click](https://www.mikroe.com/?pid_product=MIKROE-6945) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6945&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Apr 2026.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Accel 37 Click board by reading and
displaying the accelerometer data (X, Y, and Z axis) and an internal temperature
measurement in degrees Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel37

### Example Key Functions

- `accel37_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void accel37_cfg_setup ( accel37_cfg_t *cfg );
```

- `accel37_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t accel37_init ( accel37_t *ctx, accel37_cfg_t *cfg );
```

- `accel37_default_cfg` This function executes a default configuration of Accel 37 Click board.
```c
err_t accel37_default_cfg ( accel37_t *ctx );
```

- `accel37_get_accel` This function reads and converts the X, Y, Z acceleration data.
```c
err_t accel37_get_accel ( accel37_t *ctx, accel37_axes_t *accel );
```

- `accel37_get_temp` This function reads and calculates the temperature value in Celsius.
```c
err_t accel37_get_temp ( accel37_t *ctx, float *temp );
```

- `accel37_get_temp` This function retrieves acceleration and temperature data from the device.
```c
err_t accel37_get_temp ( accel37_t *ctx, float *temp );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel37_cfg_t accel37_cfg;  /**< Click config object. */

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
    accel37_cfg_setup( &accel37_cfg );
    ACCEL37_MAP_MIKROBUS( accel37_cfg, MIKROBUS_POSITION_ACCEL37 );
    err_t init_flag = accel37_init( &accel37, &accel37_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL37_ERROR == accel37_default_cfg ( &accel37 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the accelerometer and temperature measurements.
The results are displayed on the USB UART every 100 ms.

```c
void application_task ( void )
{
    accel37_data_t meas_data;

    if ( ACCEL37_OK == accel37_get_data( &accel37, &meas_data ) )
    {
        log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
        log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
        log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
        log_printf( &logger, " Temperature: %.1f degC\r\n\n", meas_data.temperature );
        log_printf( &logger, " ----------------- \r\n" );

        Delay_ms( 100 );
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
