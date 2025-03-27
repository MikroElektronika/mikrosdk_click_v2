
---
# Accel 34 Click

> [Accel 34 Click](https://www.mikroe.com/?pid_product=MIKROE-6566) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6566&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Accel 34 Click board by reading and
displaying the accelerometer data (X, Y, and Z axis) and a temperature
measurement in degrees Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel34

### Example Key Functions

- `accel34_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void accel34_cfg_setup ( accel34_cfg_t *cfg );
```

- `accel34_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t accel34_init ( accel34_t *ctx, accel34_cfg_t *cfg );
```

- `accel34_default_cfg` This function executes a default configuration of Accel 34 Click board.
```c
err_t accel34_default_cfg ( accel34_t *ctx );
```

- `accel34_set_accel_fsr` This function sets the accel measurement full scale range.
```c
err_t accel34_set_accel_fsr ( accel34_t *ctx, uint8_t fsr );
```

- `accel34_get_data` This function reads both accelerometer and temperature data from the device.
```c
err_t accel34_get_data ( accel34_t *ctx, accel34_data_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel34_cfg_t accel34_cfg;  /**< Click config object. */

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
    accel34_cfg_setup( &accel34_cfg );
    ACCEL34_MAP_MIKROBUS( accel34_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == accel34_init( &accel34, &accel34_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL34_ERROR == accel34_default_cfg ( &accel34 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the accelerometer and temperature measurements. The results are displayed on the USB UART every 100 ms.

```c
void application_task ( void )
{
    accel34_data_t meas_data;
    if ( ACCEL34_OK == accel34_get_data ( &accel34, &meas_data ) )
    {
        log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
        log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
        log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
        log_printf( &logger, " Temperature: %.1f degC\r\n\n", meas_data.temperature );
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
