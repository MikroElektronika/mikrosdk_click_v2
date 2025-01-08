
---
# Thermo 26 Click

> [Thermo 26 Click](https://www.mikroe.com/?pid_product=MIKROE-5384) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5384&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Thermo 26 Click board by reading and displaying the temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo26

### Example Key Functions

- `thermo26_cfg_setup` Config Object Initialization function.
```c
void thermo26_cfg_setup ( thermo26_cfg_t *cfg );
```

- `thermo26_init` Initialization function.
```c
err_t thermo26_init ( thermo26_t *ctx, thermo26_cfg_t *cfg );
```

- `thermo26_read_serial_num` This function reads the 32-bit unique serial number.
```c
err_t thermo26_read_serial_num ( thermo26_t *ctx, uint32_t *serial_num );
```

- `thermo26_start_measurement` This function starts the measurements by sending the specified command.
```c
err_t thermo26_start_measurement ( thermo26_t *ctx, uint16_t cmd );
```

- `thermo26_read_temperature` This function reads the temperature raw data measurements and converts it to degrees Celsius.
```c
err_t thermo26_read_temperature ( thermo26_t *ctx, float *temperature );
```

### Application Init

> Initializes the driver and resets the device, and after that reads the serial number and starts the periodic measurements at 2 mps with high repeatability.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo26_cfg_t thermo26_cfg;  /**< Click config object. */

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
    thermo26_cfg_setup( &thermo26_cfg );
    THERMO26_MAP_MIKROBUS( thermo26_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo26_init( &thermo26, &thermo26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    thermo26_reset_device ( &thermo26 );
    
    uint32_t serial_num;
    if ( THERMO26_ERROR == thermo26_read_serial_num ( &thermo26, &serial_num ) )
    {
        log_error( &logger, " Read serial number." );
        for ( ; ; );
    }
    log_printf ( &logger, " Serial number: 0x%.8LX\r\n", serial_num );
    
    if ( THERMO26_ERROR == thermo26_start_measurement ( &thermo26, THERMO26_CMD_PERIODIC_2_MPS_REP_HIGH ) )
    {
        log_error( &logger, " Start measurement." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature measurement in degrees Celsius and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature;
    if ( THERMO26_OK == thermo26_read_temperature ( &thermo26, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f\r\n\n", temperature );
    }
    Delay_ms ( 1000 );
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
