
---
# Proximity 24 Click

> [Proximity 24 Click](https://www.mikroe.com/?pid_product=MIKROE-6872) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6872&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Proximity 24 Click board by reading and displaying the proximity and ALS data on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity24

### Example Key Functions

- `proximity24_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void proximity24_cfg_setup ( proximity24_cfg_t *cfg );
```

- `proximity24_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t proximity24_init ( proximity24_t *ctx, proximity24_cfg_t *cfg );
```

- `proximity24_default_cfg` This function executes a default configuration of Proximity 24 Click board.
```c
err_t proximity24_default_cfg ( proximity24_t *ctx );
```

- `proximity24_read_proximity` This function reads the proximity data.
```c
err_t proximity24_read_proximity ( proximity24_t *ctx, uint16_t *ps_data );
```

- `proximity24_read_als_data` This function reads the ALS data.
```c
err_t proximity24_read_als_data ( proximity24_t *ctx, uint16_t *als_data );
```

- `proximity24_read_white_data` This function reads the white data.
```c
err_t proximity24_read_white_data ( proximity24_t *ctx, uint16_t *white_data );
```

### Application Init

> Initializes the driver and logger, and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity24_cfg_t proximity24_cfg;  /**< Click config object. */

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
    proximity24_cfg_setup( &proximity24_cfg );
    PROXIMITY24_MAP_MIKROBUS( proximity24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity24_init( &proximity24, &proximity24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY24_ERROR == proximity24_default_cfg ( &proximity24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the proximity and ALS data and displays the results on the USB UART every 200ms.
The higher the proximity value, the closer the detected object.

```c
void application_task ( void )
{
    uint16_t ps_data = 0;
    uint16_t als_data = 0;
    uint16_t white_data = 0;
    if ( PROXIMITY24_OK == proximity24_read_proximity ( &proximity24, &ps_data ) )
    {
        log_printf ( &logger, " PS data: %u\r\n", ps_data );
    }
    if ( PROXIMITY24_OK == proximity24_read_als_data ( &proximity24, &als_data ) )
    {
        log_printf ( &logger, " ALS data: %.1f lux\r\n", als_data * proximity24.als_sens );
    }
    if ( PROXIMITY24_OK == proximity24_read_white_data ( &proximity24, &white_data ) )
    {
        log_printf ( &logger, " White data: %u\r\n\n", white_data );
    }
    Delay_ms ( 200 );
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
