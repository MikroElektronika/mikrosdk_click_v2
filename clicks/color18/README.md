
---
# Color 18 Click

> [Color 18 Click](https://www.mikroe.com/?pid_product=MIKROE-6284) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6284&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Color 18 Click by reading and displaying the values from all 8 modulator channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color18

### Example Key Functions

- `color18_cfg_setup` Config Object Initialization function.
```c
void color18_cfg_setup ( color18_cfg_t *cfg );
```

- `color18_init` Initialization function.
```c
err_t color18_init ( color18_t *ctx, color18_cfg_t *cfg );
```

- `color18_default_cfg` Click Default Configuration function.
```c
err_t color18_default_cfg ( color18_t *ctx );
```

- `color18_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t color18_get_int_pin ( color18_t *ctx );
```

- `color18_read_data` This function checks if the color measurement data are ready for all channels and reads them.
```c
err_t color18_read_data ( color18_t *ctx, color18_data_t *data_out );
```

- `color18_clear_fifo` This function clears the FIFO buffers and interrupts.
```c
err_t color18_clear_fifo ( color18_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color18_cfg_t color18_cfg;  /**< Click config object. */

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
    color18_cfg_setup( &color18_cfg );
    COLOR18_MAP_MIKROBUS( color18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color18_init( &color18, &color18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR18_ERROR == color18_default_cfg ( &color18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a data ready interrupt then reads data from all 8 modulator channels and displays the results on the USB UART every 200ms approximately.

```c
void application_task ( void )
{
    color18_data_t color_data;

    // Wait for a data ready interrupt
    while ( color18_get_int_pin ( &color18 ) );

    if ( COLOR18_OK == color18_read_data ( &color18, &color_data ) )
    {
        log_printf ( &logger, "X: %u\r\n", color_data.x );
        log_printf ( &logger, "Y: %u\r\n", color_data.y );
        log_printf ( &logger, "Z: %u\r\n", color_data.z );
        log_printf ( &logger, "IR: %u\r\n", color_data.ir );
        log_printf ( &logger, "HgL: %u\r\n", color_data.hgl );
        log_printf ( &logger, "HgH: %u\r\n", color_data.hgh );
        log_printf ( &logger, "Clear: %u\r\n", color_data.clear );
        log_printf ( &logger, "Flicker: %u\r\n\n", color_data.flicker );
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
