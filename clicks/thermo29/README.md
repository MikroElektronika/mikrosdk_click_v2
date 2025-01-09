
---
# Thermo 29 Click

> [Thermo 29 Click](https://www.mikroe.com/?pid_product=MIKROE-5586) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5586&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Thermo 29 Click board by reading and displaying the temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo29

### Example Key Functions

- `thermo29_cfg_setup` Config Object Initialization function.
```c
void thermo29_cfg_setup ( thermo29_cfg_t *cfg );
```

- `thermo29_init` Initialization function.
```c
err_t thermo29_init ( thermo29_t *ctx, thermo29_cfg_t *cfg );
```

- `thermo29_default_cfg` Click Default Configuration function.
```c
err_t thermo29_default_cfg ( thermo29_t *ctx );
```

- `thermo29_read_unique_id` This function reads the device unique ID words (6 bytes in total).
```c
err_t thermo29_read_unique_id ( thermo29_t *ctx, uint16_t *unique_id );
```

- `thermo29_get_alert_pin` This function returns the alert pin logic state.
```c
uint8_t thermo29_get_alert_pin ( thermo29_t *ctx );
```

- `thermo29_read_temperature` This function reads the temperature measurement in degrees Celsius.
```c
err_t thermo29_read_temperature ( thermo29_t *ctx, float *temperature );
```

### Application Init

> Initializes the driver and logger, and performs the Click default configuration which enables
continuous conversion and sets the conversion rate to 1 Hz with a data ready flag enabled on
the alert pin. After that, reads and displays the device 48-bit unique ID.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo29_cfg_t thermo29_cfg;  /**< Click config object. */

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
    thermo29_cfg_setup( &thermo29_cfg );
    THERMO29_MAP_MIKROBUS( thermo29_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermo29_init( &thermo29, &thermo29_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO29_ERROR == thermo29_default_cfg ( &thermo29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint16_t unique_id[ 3 ];
    if ( THERMO29_OK == thermo29_read_unique_id ( &thermo29, unique_id ) )
    {
        log_printf ( &logger, " Device Unique ID: 0x%.2X%.2X%.2X\r\n", 
                     unique_id[ 0 ], unique_id[ 1 ], unique_id[ 2 ] );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready alert flag, then reads the temperature measurement in Celsius
and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature;
    // Wait for the data ready alert flag
    while ( thermo29_get_alert_pin ( &thermo29 ) );
    
    if ( ( THERMO29_OK == thermo29_clear_alert_status ( &thermo29 ) ) && 
         ( THERMO29_OK == thermo29_read_temperature ( &thermo29, &temperature ) ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n\n", temperature );
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
