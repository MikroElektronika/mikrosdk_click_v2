
---
# Accel 32 Click

> [Accel 32 Click](https://www.mikroe.com/?pid_product=MIKROE-6565) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6565&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Accel 32 Click board by reading and
displaying the accelerometer data (X, Y, and Z axis) and a temperature
measurement in degrees Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel32

### Example Key Functions

- `accel32_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void accel32_cfg_setup ( accel32_cfg_t *cfg );
```

- `accel32_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t accel32_init ( accel32_t *ctx, accel32_cfg_t *cfg );
```

- `accel32_default_cfg` Click Default Configuration function.
```c
err_t accel32_default_cfg ( accel32_t *ctx );
```

- `accel32_set_accel_fsr` This function sets the accel measurement full scale range.
```c
err_t accel32_set_accel_fsr ( accel32_t *ctx, uint8_t fsr );
```

- `accel32_get_data` This function reads both accelerometer and temperature data from the device.
```c
err_t accel32_get_data ( accel32_t *ctx, accel32_data_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel32_cfg_t accel32_cfg;  /**< Click config object. */

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
    accel32_cfg_setup( &accel32_cfg );
    ACCEL32_MAP_MIKROBUS( accel32_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == accel32_init( &accel32, &accel32_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL32_ERROR == accel32_default_cfg ( &accel32 ) )
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
    accel32_data_t meas_data;
    if ( ACCEL32_OK == accel32_get_data ( &accel32, &meas_data ) )
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
