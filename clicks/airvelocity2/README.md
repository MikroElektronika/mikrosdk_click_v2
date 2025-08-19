
---
# Air Velocity 2 Click

> [Air Velocity 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6577) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6577&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Air Velocity 2 Click board by reading and displaying the output counts and air velocity in m/sec.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AirVelocity2

### Example Key Functions

- `airvelocity2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void airvelocity2_cfg_setup ( airvelocity2_cfg_t *cfg );
```

- `airvelocity2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t airvelocity2_init ( airvelocity2_t *ctx, airvelocity2_cfg_t *cfg );
```

- `airvelocity2_read_output` This function reads the raw output counts by using I2C serial interface.
```c
err_t airvelocity2_read_output ( airvelocity2_t *ctx, uint16_t *out_counts );
```

- `airvelocity2_counts_to_mps` This function converts raw output counts to velocity in m/sec (0-15).
```c
float airvelocity2_counts_to_mps ( uint16_t out_counts );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airvelocity2_cfg_t airvelocity2_cfg;  /**< Click config object. */

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
    airvelocity2_cfg_setup( &airvelocity2_cfg );
    AIRVELOCITY2_MAP_MIKROBUS( airvelocity2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == airvelocity2_init( &airvelocity2, &airvelocity2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the output counts and converts it to air velocity in m/sec. Both values will be displayed on the USB UART approximately every 125ms.

```c
void application_task ( void )
{
    uint16_t out_counts = 0;
    if ( AIRVELOCITY2_OK == airvelocity2_read_output ( &airvelocity2, &out_counts ) )
    {
        log_printf ( &logger, " Out counts: %u\r\n", out_counts );
        log_printf ( &logger, " Air velocity: %.2f m/s\r\n\n", airvelocity2_counts_to_mps ( out_counts ) );
        Delay_ms ( 125 );
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
