
---
# Balancer 7 Click

> [Balancer 7 Click](https://www.mikroe.com/?pid_product=MIKROE-7075) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7075&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jul 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Balancer 7 Click board by cycling the
on-board MP2642 active balancer through buck-balance and boost-balance modes.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Balancer7

### Example Key Functions

- `balancer7_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void balancer7_cfg_setup ( balancer7_cfg_t *cfg );
```

- `balancer7_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t balancer7_init ( balancer7_t *ctx, balancer7_cfg_t *cfg );
```

- `balancer7_enable_device` This function enables the device by setting the MB_EN pin to the high logic level.
```c
void balancer7_enable_device ( balancer7_t *ctx );
```

- `balancer7_disable_device` This function disables the device by setting the MB_EN pin to the low logic level.
```c
void balancer7_disable_device ( balancer7_t *ctx );
```

- `balancer7_set_mode` This function selects the balancing mode by setting the MB_MD pin logic level.
```c
void balancer7_set_mode ( balancer7_t *ctx, uint8_t mode );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    balancer7_cfg_t balancer7_cfg;  /**< Click config object. */

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
    balancer7_cfg_setup( &balancer7_cfg );
    BALANCER7_MAP_MIKROBUS( balancer7_cfg, MIKROBUS_POSITION_BALANCER7 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == balancer7_init( &balancer7, &balancer7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Runs one buck-balance window and then one boost-balance window per cycle. In
each window the corresponding mode is selected and logged via USB UART.

```c
void application_task ( void ) 
{
    log_printf ( &logger, " Buck-balance mode\r\n" );
    balancer7_set_mode ( &balancer7, BALANCER7_MODE_BUCK );
    balancer7_enable_device ( &balancer7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    balancer7_disable_device ( &balancer7 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Boost-balance mode\r\n" );
    balancer7_set_mode ( &balancer7, BALANCER7_MODE_BOOST );
    balancer7_enable_device ( &balancer7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    balancer7_disable_device ( &balancer7 );
    Delay_ms ( 1000 );
}
```

### Note

> The Click board must be connected to two adjacent series Li-ion cells for the
balancer to transfer charge. The balancing currents and the upper voltage limit
are fixed by on-board resistors and are not software-configurable.

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
