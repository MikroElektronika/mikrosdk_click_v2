
---
# Cap Slider 3 Click

> [Cap Slider 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6645) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6645&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Cap Slider 3 Click board by initializing
the device and reading the current slider position. The application logs the detected
slider position in real-time.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CapSlider3

### Example Key Functions

- `capslider3_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void capslider3_cfg_setup ( capslider3_cfg_t *cfg );
```

- `capslider3_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t capslider3_init ( capslider3_t *ctx, capslider3_cfg_t *cfg );
```

- `capslider3_default_cfg` This function executes a default configuration of Cap Slider 3 Click board.
```c
err_t capslider3_default_cfg ( capslider3_t *ctx );
```

- `capslider3_read_data` This function reads various system information and sensor data from the Click board.
```c
err_t capslider3_read_data ( capslider3_t *ctx, capslider3_data_t *data_out );
```

### Application Init

> Initializes the logger and the Cap Slider 3 Click driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    capslider3_cfg_t capslider3_cfg;  /**< Click config object. */

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
    capslider3_cfg_setup( &capslider3_cfg );
    CAPSLIDER3_MAP_MIKROBUS( capslider3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == capslider3_init( &capslider3, &capslider3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CAPSLIDER3_ERROR == capslider3_default_cfg ( &capslider3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads and logs the slider position detected by the Cap Slider 3 Click board.

```c
void application_task ( void )
{
    capslider3_data_t sys_info;
    if ( CAPSLIDER3_OK == capslider3_read_data ( &capslider3, &sys_info ) )
    {
        if ( CAPSLIDER3_SLIDER_IDLE != sys_info.slider )
        {
            log_printf ( &logger, " Slider: - %u -\r\n\n", sys_info.slider );
        }
    }
}
```

### Note

> Functions for logging gestures and statuses are available but not used in this example.

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
