
---
# Accel 25 Click

> [Accel 25 Click](https://www.mikroe.com/?pid_product=MIKROE-5602) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5602&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Accel 25 Click board by reading and displaying 
 accel data (X, Y, and Z axis) as well as temperature measurements on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel25

### Example Key Functions

- `accel25_cfg_setup` Config Object Initialization function.
```c
void accel25_cfg_setup ( accel25_cfg_t *cfg );
```

- `accel25_init` Initialization function.
```c
err_t accel25_init ( accel25_t *ctx, accel25_cfg_t *cfg );
```

- `accel25_default_cfg` Click Default Configuration function.
```c
err_t accel25_default_cfg ( accel25_t *ctx );
```

- `accel25_soft_reset` Accel 25 soft reset function.
```c
err_t accel25_soft_reset ( accel25_t *ctx );
```

- `accel25_set_full_scale_range` Accel 25 set full scale range function.
```c
err_t accel25_set_full_scale_range ( accel25_t *ctx, uint8_t fsr );
```

- `accel25_read_data` Accel 25 read data function.
```c
err_t accel25_read_data ( accel25_t *ctx, accel25_data_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel25_cfg_t accel25_cfg;  /**< Click config object. */

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
    accel25_cfg_setup( &accel25_cfg );
    ACCEL25_MAP_MIKROBUS( accel25_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == accel25_init( &accel25, &accel25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL25_ERROR == accel25_default_cfg ( &accel25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the accel data (X, Y, and Z axis) as well as temperature measurements
 on the USB UART every 100ms approximately.

```c
void application_task ( void ) 
{
    accel25_data_t meas_data;
    // Wait for data ready indication
    if ( ACCEL25_PIN_STATE_LOW == accel25_get_int_pin ( &accel25 ) );
    {
        if ( ACCEL25_OK == accel25_read_data ( &accel25, &meas_data ) )
        {
            log_printf( &logger, " X: %.3f g\r\n", meas_data.x );
            log_printf( &logger, " Y: %.3f g\r\n", meas_data.y );
            log_printf( &logger, " Z: %.3f g\r\n", meas_data.z );
            log_printf( &logger, " Temperature: %.2f degC\r\n", meas_data.temperature );
        }
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
