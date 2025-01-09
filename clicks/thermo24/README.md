
---
# Thermo 24 Click

> [Thermo 24 Click](https://www.mikroe.com/?pid_product=MIKROE-5110) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5110&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Thermo 24 Click board by reading and displaying the temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo24

### Example Key Functions

- `thermo24_cfg_setup` Config Object Initialization function.
```c
void thermo24_cfg_setup ( thermo24_cfg_t *cfg );
```

- `thermo24_init` Initialization function.
```c
err_t thermo24_init ( thermo24_t *ctx, thermo24_cfg_t *cfg );
```

- `thermo24_soft_reset` This function performs the software reset by sending the soft reset command by using I2C serial interface.
```c
err_t thermo24_soft_reset ( thermo24_t *ctx );
```

- `thermo24_read_serial` This function reads the 4-byte chip serial number by using I2C serial interface.
```c
err_t thermo24_read_serial ( thermo24_t *ctx, uint32_t *serial_num );
```

- `thermo24_read_temperature` This function reads the temperature in Celsius with the specified measurement precision.
```c
err_t thermo24_read_temperature ( thermo24_t *ctx, uint8_t precision, float *temperature );
```

### Application Init

> Initializes the driver and logger, then performs the software reset of the Click board and reads and displays its serial number.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo24_cfg_t thermo24_cfg;  /**< Click config object. */

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
    thermo24_cfg_setup( &thermo24_cfg );
    THERMO24_MAP_MIKROBUS( thermo24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo24_init( &thermo24, &thermo24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO24_ERROR == thermo24_soft_reset ( &thermo24 ) )
    {
        log_error( &logger, " Software reset." );
        for ( ; ; );
    }

    uint32_t serial_num;
    if ( THERMO24_OK == thermo24_read_serial ( &thermo24, &serial_num ) )
    {
        log_printf ( &logger, " Serial Number: 0x%.8LX\r\n", serial_num );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature measurement in Celsius and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature;
    if ( THERMO24_OK == thermo24_read_temperature ( &thermo24, THERMO24_MEASURE_PRECISION_HIGH, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
        Delay_ms ( 1000 );
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
