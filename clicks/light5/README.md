
---
# Light 5 Click

> [Light 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6905) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6905&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Light 5 Click board for ambient
light measurement. The application waits for a data-ready interrupt and
then reads illuminance (lux) and wide-band light intensity values via the
I2C interface, displaying the results on the serial terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Light5

### Example Key Functions

- `light5_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void light5_cfg_setup ( light5_cfg_t *cfg );
```

- `light5_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t light5_init ( light5_t *ctx, light5_cfg_t *cfg );
```

- `light5_default_cfg` This function executes a default configuration of Light 5 Click board.
```c
err_t light5_default_cfg ( light5_t *ctx );
```

- `light5_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t light5_get_int_pin ( light5_t *ctx );
```

- `light5_read_data` This function reads the light intensity in lux and wide band measurement in uW/cm2.
```c
err_t light5_read_data ( light5_t *ctx, light5_data_t *data_out );
```

### Application Init

> Initializes the logger and Light 5 Click driver and applies the default device configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    light5_cfg_t light5_cfg;  /**< Click config object. */

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
    light5_cfg_setup( &light5_cfg );
    LIGHT5_MAP_MIKROBUS( light5_cfg, MIKROBUS_POSITION_LIGHT5 );
    if ( I2C_MASTER_ERROR == light5_init( &light5, &light5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHT5_ERROR == light5_default_cfg ( &light5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the interrupt signal indicating new measurement data and reads light measurement results, which are then logged to the serial terminal.

```c
void application_task ( void )
{
    light5_data_t light_data;

    // Wait for a data ready interrupt
    while ( light5_get_int_pin ( &light5 ) );

    if ( LIGHT5_OK == light5_read_data ( &light5, &light_data ) )
    {
        log_printf ( &logger, "Light: %.1f lux\r\n", light_data.lux );
        log_printf ( &logger, "Wide Band: %.1f uW/cm2\r\n\n", light_data.wide_band );
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
