
---
# IPD 2017 Click

> [IPD 2017 Click](https://www.mikroe.com/?pid_product=MIKROE-6075) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6075&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of IPD 2017 Click board by toggling the output state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IPD2017

### Example Key Functions

- `ipd2017_cfg_setup` Config Object Initialization function.
```c
void ipd2017_cfg_setup ( ipd2017_cfg_t *cfg );
```

- `ipd2017_init` Initialization function.
```c
err_t ipd2017_init ( ipd2017_t *ctx, ipd2017_cfg_t *cfg );
```

- `ipd2017_all_pins_set` IPD 2017 pin setting function.
```c
void ipd2017_all_pins_set ( ipd2017_t *ctx );
```

- `ipd2017_set_out_level` IPD 2017 set output level function.
```c
err_t ipd2017_set_out_level ( ipd2017_t *ctx, uint8_t out_sel, uint8_t state );
```

- `ipd2017_get_out_state` IPD 2017 get output level function.
```c
uint8_t ipd2017_get_out_state ( ipd2017_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ipd2017_cfg_t ipd2017_cfg;  /**< Click config object. */

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
    ipd2017_cfg_setup( &ipd2017_cfg );
    IPD2017_MAP_MIKROBUS( ipd2017_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ipd2017_init( &ipd2017, &ipd2017_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Switches on all output pins state for 2 seconds, then switches them off, and turns them on one by one.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Turning OUT 1 to OUT 4 HIGH \r\n" );
    ipd2017_all_pins_set( &ipd2017 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning OUT 1 to OUT 4 LOW \r\n" );
    ipd2017_all_pins_clear( &ipd2017 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning OUT 1 to OUT 4 one by one \r\n" );
    uint8_t out_sel = IPD2017_OUT1_PIN_MASK;
    do
    {
        ipd2017_set_out_level( &ipd2017, out_sel, IPD2017_PIN_STATE_HIGH );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        ipd2017_set_out_level( &ipd2017, out_sel, IPD2017_PIN_STATE_LOW );
        out_sel <<=  1;
    }
    while ( out_sel <= IPD2017_OUT4_PIN_MASK );
    
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
