
---
# IR Grid 4 Click

> [IR Grid 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6306) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6306&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of IR Grid 4 Click by reading and displaying
the ambient and object temperature measurements in a 16x12 pixels grid format.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IRGrid4

### Example Key Functions

- `irgrid4_cfg_setup` Config Object Initialization function.
```c
void irgrid4_cfg_setup ( irgrid4_cfg_t *cfg );
```

- `irgrid4_init` Initialization function.
```c
err_t irgrid4_init ( irgrid4_t *ctx, irgrid4_cfg_t *cfg );
```

- `irgrid4_default_cfg` Click Default Configuration function.
```c
err_t irgrid4_default_cfg ( irgrid4_t *ctx );
```

- `irgrid4_get_measurement` This function reads the RAM frame data and calculates ambient temperature and a 16x12 IR grid object temperature.
```c
err_t irgrid4_get_measurement ( irgrid4_t *ctx, float *t_amb, float *t_obj );
```

- `irgrid4_set_refresh_rate` This function sets the IR data refresh rate.
```c
err_t irgrid4_set_refresh_rate ( irgrid4_t *ctx, uint8_t refresh_rate );
```

- `irgrid4_enable_led1` This function enables the LED1.
```c
void irgrid4_enable_led1 ( irgrid4_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgrid4_cfg_t irgrid4_cfg;  /**< Click config object. */

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
    irgrid4_cfg_setup( &irgrid4_cfg );
    IRGRID4_MAP_MIKROBUS( irgrid4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irgrid4_init( &irgrid4, &irgrid4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRGRID4_ERROR == irgrid4_default_cfg ( &irgrid4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the ambient and object temperature measurements every 500ms and displays the results on the USB UART in a form of a 16x12 pixels grid.

```c
void application_task ( void )
{
    float image[ 192 ] = { 0 };
    float ambient_temp = 0;
    if ( IRGRID4_OK == irgrid4_get_measurement ( &irgrid4, &ambient_temp, image ) )
    {
        log_printf( &logger, " Ambient temperature: %.2f degC\r\n", ambient_temp );
        log_printf( &logger, "--- Object temperature image ---\r\n" );
        for ( uint8_t pixel_cnt = 0; pixel_cnt < 192; pixel_cnt++ ) 
        {
            log_printf( &logger, "%.2f", image[ pixel_cnt ] );
            if ( 15 == ( pixel_cnt % 16 ) ) 
            {
                log_printf( &logger, "\r\n" );
            }
            else 
            {
                log_printf( &logger, " | " );
            }
        }
        log_printf( &logger, "--------------------------------\r\n" );
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
