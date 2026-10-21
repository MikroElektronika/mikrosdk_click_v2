
---
# Proximity 26 Click

> [Proximity 26 Click](https://www.mikroe.com/?pid_product=MIKROE-7116) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7116&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Aug 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Proximity 26 Click board by reading and 
displaying the proximity data on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity26

### Example Key Functions

- `proximity26_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void proximity26_cfg_setup ( proximity26_cfg_t *cfg );
```

- `proximity26_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t proximity26_init ( proximity26_t *ctx, proximity26_cfg_t *cfg );
```

- `proximity26_default_cfg` This function executes a default configuration of Proximity 26 Click board.
```c
err_t proximity26_default_cfg ( proximity26_t *ctx );
```

- `proximity26_read_proximity` This function reads the raw proximity data.
```c
err_t proximity26_read_proximity ( proximity26_t *ctx, uint16_t *ps_data );
```

- `proximity26_check_com` This function checks the communication by reading and verifying the device ID.
```c
err_t proximity26_check_com ( proximity26_t *ctx );
```

- `proximity26_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t proximity26_get_int_pin ( proximity26_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity26_cfg_t proximity26_cfg;  /**< Click config object. */

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
    proximity26_cfg_setup( &proximity26_cfg );
    PROXIMITY26_MAP_MIKROBUS( proximity26_cfg, MIKROBUS_POSITION_PROXIMITY26 );
    if ( I2C_MASTER_ERROR == proximity26_init( &proximity26, &proximity26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY26_ERROR == proximity26_default_cfg ( &proximity26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the proximity data and displays the results on the USB UART every 200ms.
The proximity data is a relative value, the higher the value the closer the detected object.

```c
void application_task ( void ) 
{
    uint16_t ps_data = 0;
    if ( PROXIMITY26_OK == proximity26_read_proximity ( &proximity26, &ps_data ) )
    {
        log_printf ( &logger, " PS data: %u\r\n\n", ps_data );
    }
    else
    {
        log_printf ( &logger, " Failed to read PS data\r\n\n" );
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
