
---
# Qi RX Click

> [Qi RX Click](https://www.mikroe.com/?pid_product=MIKROE-4345) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4345&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Qi RX Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.QiRX

### Example Key Functions

- `qirx_cfg_setup` Config Object Initialization function.
```c
void qirx_cfg_setup ( qirx_cfg_t *cfg );
```

- `qirx_init` Initialization function.
```c
err_t qirx_init ( qirx_t *ctx, qirx_cfg_t *cfg );
```

- `qirx_read_data` Read data function.
```c
uint16_t qirx_read_data ( qirx_t *ctx );
```

- `qirx_read_voltage` Read voltage function.
```c
uint16_t qirx_read_voltage ( qirx_t *ctx, uint16_t v_ref );
```

### Application Init

> Initalizes I2C driver and makes an initial log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    qirx_cfg_t qirx_cfg;  /**< Click config object. */

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
    qirx_cfg_setup( &qirx_cfg );
    QIRX_MAP_MIKROBUS( qirx_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == qirx_init( &qirx, &qirx_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, "----------------------- \r\n" );
    log_printf( &logger, "      Qi RX Click       \r\n" );
    log_printf( &logger, "----------------------- \r\n" );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------- \r\n" );
}
```

### Application Task

> This example shows the capabilities of the Qi RX Click by measuring voltage of the connected
> battery. In order to get correct calculations user should change "v_ref" value 
> to his own power supply voltage.

```c
void application_task ( void ) 
{
    voltage = qirx_read_voltage( &qirx, v_ref );
    log_printf( &logger, " Battery voltage: %d mV \r\n", voltage );
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
