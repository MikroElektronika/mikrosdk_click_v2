
---
# Color 20 Click

> [Color 20 Click](https://www.mikroe.com/?pid_product=MIKROE-6547) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6547&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Color 20 Click board by reading
and displaying the ambient light levels in the red, green, blue, and infrared (IR) spectrum.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color20

### Example Key Functions

- `color20_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void color20_cfg_setup ( color20_cfg_t *cfg );
```

- `color20_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t color20_init ( color20_t *ctx, color20_cfg_t *cfg );
```

- `color20_default_cfg` This function executes a default configuration of Color 20 Click board.
```c
err_t color20_default_cfg ( color20_t *ctx );
```

- `color20_get_data` This function the raw IR data and red, green, and blue light intensity in lux based on raw RGB data.
```c
err_t color20_get_data ( color20_t *ctx, float *red, float *green, float *blue, uint16_t *ir_data );
```

### Application Init

> Initializes the logger and the Color 20 Click driver, then applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color20_cfg_t color20_cfg;  /**< Click config object. */

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
    color20_cfg_setup( &color20_cfg );
    COLOR20_MAP_MIKROBUS( color20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color20_init( &color20, &color20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR20_ERROR == color20_default_cfg ( &color20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the red, green, blue (in lux), and IR raw values every 200 ms.

```c
void application_task ( void )
{
    float red = 0;
    float green = 0;
    float blue = 0;
    uint16_t ir_data = 0;
    if ( COLOR20_OK == color20_get_data ( &color20, &red, &green, &blue, &ir_data ) )
    {
        log_printf ( &logger, " Red: %.1f lux\r\n", red );
        log_printf ( &logger, " Green: %.1f lux\r\n", green );
        log_printf ( &logger, " Blue: %.1f lux\r\n", blue );
        log_printf ( &logger, " IR Data: %u\r\n\n", ir_data );
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
