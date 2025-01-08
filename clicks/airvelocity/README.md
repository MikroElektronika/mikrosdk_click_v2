
---
# Air Velocity Click

> [Air Velocity Click](https://www.mikroe.com/?pid_product=MIKROE-5448) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5448&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Air Velocity Click board by reading and displaying the output counts and air velocity in m/sec.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AirVelocity

### Example Key Functions

- `airvelocity_cfg_setup` Config Object Initialization function.
```c
void airvelocity_cfg_setup ( airvelocity_cfg_t *cfg );
```

- `airvelocity_init` Initialization function.
```c
err_t airvelocity_init ( airvelocity_t *ctx, airvelocity_cfg_t *cfg );
```

- `airvelocity_read_output` This function reads the raw output counts by using I2C serial interface.
```c
err_t airvelocity_read_output ( airvelocity_t *ctx, uint16_t *out_counts );
```

- `airvelocity_convert_counts_to_mps` This function converts raw output counts to velocity in m/sec (0-7.23).
```c
float airvelocity_convert_counts_to_mps ( uint16_t out_counts );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airvelocity_cfg_t airvelocity_cfg;  /**< Click config object. */

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
    airvelocity_cfg_setup( &airvelocity_cfg );
    AIRVELOCITY_MAP_MIKROBUS( airvelocity_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == airvelocity_init( &airvelocity, &airvelocity_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the output counts and converts it to air velocity in m/sec. Both values will be displayed on the USB UART approximately every 250ms.

```c
void application_task ( void )
{
    uint16_t out_counts;
    if ( AIRVELOCITY_OK == airvelocity_read_output ( &airvelocity, &out_counts ) )
    {
        log_printf ( &logger, " Out counts: %u\r\n", out_counts );
        log_printf ( &logger, " Air velocity: %.2f m/s\r\n\n", airvelocity_convert_counts_to_mps ( out_counts ) );
        Delay_ms ( 250 );
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
