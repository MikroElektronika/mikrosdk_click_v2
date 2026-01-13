
---
# Proximity 23 Click

> [Proximity 23 Click](https://www.mikroe.com/?pid_product=MIKROE-6860) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6860&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Proximity 23 Click board by reading and 
displaying the proximity data on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity23

### Example Key Functions

- `proximity23_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void proximity23_cfg_setup ( proximity23_cfg_t *cfg );
```

- `proximity23_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t proximity23_init ( proximity23_t *ctx, proximity23_cfg_t *cfg );
```

- `proximity23_default_cfg` This function executes a default configuration of Proximity 23 Click board.
```c
err_t proximity23_default_cfg ( proximity23_t *ctx );
```

- `proximity23_read_proximity` This function reads the proximity data.
```c
err_t proximity23_read_proximity ( proximity23_t *ctx, uint16_t *ps_data );
```

### Application Init

> Initializes the driver and logger, and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity23_cfg_t proximity23_cfg;  /**< Click config object. */

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
    proximity23_cfg_setup( &proximity23_cfg );
    PROXIMITY23_MAP_MIKROBUS( proximity23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity23_init( &proximity23, &proximity23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY23_ERROR == proximity23_default_cfg ( &proximity23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the proximity data and displays the results on the USB UART every 200ms.
The higher the proximity value, the closer the detected object.

```c
void application_task ( void )
{
    uint16_t ps_data = 0;
    if ( PROXIMITY23_OK == proximity23_read_proximity ( &proximity23, &ps_data ) )
    {
        log_printf ( &logger, " PS data: %u\r\n\n", ps_data );
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
