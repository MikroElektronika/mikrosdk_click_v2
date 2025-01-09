
---
# Thermo 25 Click

> [Thermo 25 Click](https://www.mikroe.com/?pid_product=MIKROE-5335) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5335&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Thermo 25 Click board by reading and displaying the temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo25

### Example Key Functions

- `thermo25_cfg_setup` Config Object Initialization function.
```c
void thermo25_cfg_setup ( thermo25_cfg_t *cfg );
```

- `thermo25_init` Initialization function.
```c
err_t thermo25_init ( thermo25_t *ctx, thermo25_cfg_t *cfg );
```

- `thermo25_check_communication` This function sets the operating mode to shutdown, then reads and verifies the device ID, and switches back to the continuous mode.
```c
err_t thermo25_check_communication ( thermo25_t *ctx );
```

- `thermo25_read_temperature` This function reads the temperature measurements in degrees Celsius.
```c
err_t thermo25_read_temperature ( thermo25_t *ctx, float *temperature );
```

- `thermo25_set_mode` This function sets the device operating mode to shutdown or continuous mode by using SPI serial interface.
```c
err_t thermo25_set_mode ( thermo25_t *ctx, uint8_t mode );
```

### Application Init

> Initializes the driver and logger, and checks the communication by setting the operating mode to shutdown, reading and verifying the device ID, and switching back to the continuous mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo25_cfg_t thermo25_cfg;  /**< Click config object. */

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
    thermo25_cfg_setup( &thermo25_cfg );
    THERMO25_MAP_MIKROBUS( thermo25_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermo25_init( &thermo25, &thermo25_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO25_ERROR == thermo25_check_communication ( &thermo25 ) )
    {
        log_error( &logger, " Check communication." );
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
    if ( THERMO25_OK == thermo25_read_temperature ( &thermo25, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n\n", temperature );
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
