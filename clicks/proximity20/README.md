
---
# Proximity 20 Click

> [Proximity 20 Click](https://www.mikroe.com/?pid_product=MIKROE-6243) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6243&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Proximity 20 Click board by reading and displaying the proximity data on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity20

### Example Key Functions

- `proximity20_cfg_setup` Config Object Initialization function.
```c
void proximity20_cfg_setup ( proximity20_cfg_t *cfg );
```

- `proximity20_init` Initialization function.
```c
err_t proximity20_init ( proximity20_t *ctx, proximity20_cfg_t *cfg );
```

- `proximity20_default_cfg` Click Default Configuration function.
```c
err_t proximity20_default_cfg ( proximity20_t *ctx );
```

- `proximity20_read_proximity` This function reads the proximity data from U2 and U3 sensors.
```c
err_t proximity20_read_proximity ( proximity20_t *ctx, uint16_t *ps_data_u2, uint16_t *ps_data_u3 );
```

- `proximity20_set_device_address` This function sets the device slave address.
```c
err_t proximity20_set_device_address ( proximity20_t *ctx, uint8_t dev_addr );
```

- `proximity20_enable_device` This function enables the device by setting the EN pin to high logic state.
```c
void proximity20_enable_device ( proximity20_t *ctx );
```

### Application Init

> Initializes the driver and logger, and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity20_cfg_t proximity20_cfg;  /**< Click config object. */

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
    proximity20_cfg_setup( &proximity20_cfg );
    PROXIMITY20_MAP_MIKROBUS( proximity20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity20_init( &proximity20, &proximity20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY20_ERROR == proximity20_default_cfg ( &proximity20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the proximity data from 2 sensors and displays the results on the USB UART every 200ms. The higher the proximity value, the closer the detected object.

```c
void application_task ( void )
{
    uint16_t ps_data_u2 = 0;
    uint16_t ps_data_u3 = 0;
    if ( PROXIMITY20_OK == proximity20_read_proximity ( &proximity20, &ps_data_u2, &ps_data_u3 ) )
    {
        log_printf ( &logger, " PS data [U2]: %u\r\n", ps_data_u2 );
        log_printf ( &logger, " PS data [U3]: %u\r\n\n", ps_data_u3 );
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
