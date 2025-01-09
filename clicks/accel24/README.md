
---
# Accel 24 Click

> [Accel 24 Click](https://www.mikroe.com/?pid_product=MIKROE-5336) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5336&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Accel 24 Click board by reading and displaying accel data (X, Y, and Z axis) as well as temperature measurements on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel24

### Example Key Functions

- `accel24_cfg_setup` Config Object Initialization function.
```c
void accel24_cfg_setup ( accel24_cfg_t *cfg );
```

- `accel24_init` Initialization function.
```c
err_t accel24_init ( accel24_t *ctx, accel24_cfg_t *cfg );
```

- `accel24_default_cfg` Click Default Configuration function.
```c
err_t accel24_default_cfg ( accel24_t *ctx );
```

- `accel24_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t accel24_get_int_pin ( accel24_t *ctx );
```

- `accel24_read_data` This function checks the data ready bit, clears it, and then reads the accel (X, Y, Z) and temperature measurements.
```c
err_t accel24_read_data ( accel24_t *ctx, accel24_data_t *data_out );
```

- `accel24_set_full_scale_range` This function sets the full scale range resolution.
```c
err_t accel24_set_full_scale_range ( accel24_t *ctx, uint8_t fsr );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel24_cfg_t accel24_cfg;  /**< Click config object. */

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
    accel24_cfg_setup( &accel24_cfg );
    ACCEL24_MAP_MIKROBUS( accel24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == accel24_init( &accel24, &accel24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL24_ERROR == accel24_default_cfg ( &accel24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the accel data (X, Y, and Z axis) as well as temperature measurements on the USB UART every 100ms approximately.

```c
void application_task ( void )
{
    accel24_data_t meas_data;
    // Wait for data ready indication
    while ( accel24_get_int_pin ( &accel24 ) );
    
    if ( ACCEL24_OK == accel24_read_data ( &accel24, &meas_data ) )
    {
        log_printf( &logger, " X: %.3f g\r\n", meas_data.x );
        log_printf( &logger, " Y: %.3f g\r\n", meas_data.y );
        log_printf( &logger, " Z: %.3f g\r\n", meas_data.z );
        log_printf( &logger, " Temperature: %.2f degC\r\n", meas_data.temperature );
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
