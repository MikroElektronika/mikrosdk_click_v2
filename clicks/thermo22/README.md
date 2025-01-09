
---
# Thermo 22 Click

> [Thermo 22 Click](https://www.mikroe.com/?pid_product=MIKROE-5068) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5068&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Thermo 22 Click board by reading and displaying the temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo22

### Example Key Functions

- `thermo22_cfg_setup` Config Object Initialization function.
```c
void thermo22_cfg_setup ( thermo22_cfg_t *cfg );
```

- `thermo22_init` Initialization function.
```c
err_t thermo22_init ( thermo22_t *ctx, thermo22_cfg_t *cfg );
```

- `thermo22_default_cfg` Click Default Configuration function.
```c
err_t thermo22_default_cfg ( thermo22_t *ctx );
```

- `thermo22_read_temperature` This function reads the temperature data in Celsius.
```c
err_t thermo22_read_temperature ( thermo22_t *ctx, float *temperature );
```

- `thermo22_set_temperature_high_limit` This function sets the temperature high limit at which the overtemperature alert flag is being set.
```c
err_t thermo22_set_temperature_high_limit ( thermo22_t *ctx, float high_limit );
```

- `thermo22_get_int_pin` This function returns the INT pin logic state which indicates the overtemperature alert.
```c
uint8_t thermo22_get_int_pin ( thermo22_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration which enables continuous conversation and sets the overtemperature limits to 35.0 Celsius.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo22_cfg_t thermo22_cfg;  /**< Click config object. */

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
    thermo22_cfg_setup( &thermo22_cfg );
    THERMO22_MAP_MIKROBUS( thermo22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo22_init( &thermo22, &thermo22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO22_ERROR == thermo22_default_cfg ( &thermo22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature measurement in Celsius and displays the results on the USB UART
every 200ms approximately. It also checks the overtemperature alert indicator and displays
an appropriate message if the indicator is active.

```c
void application_task ( void )
{
    float temperature;
    if ( THERMO22_OK == thermo22_read_temperature ( &thermo22, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f C \r\n\n", temperature );
        if ( !thermo22_get_int_pin ( &thermo22 ) )
        {
            log_printf ( &logger, " Over temperature alert! \r\n\n" );
        }
        Delay_ms ( 200 );
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
