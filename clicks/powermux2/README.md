
---
# Power MUX 2 Click

> [Power MUX 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4575) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4575&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the Power MUX 2 Click driver. 
> The Power MUX 2 operates in automatic switchover mode with a priority prioritizing supply 1 
> when present and quickly switches to supply 2 when supply 1 drops below approximately 6V.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerMux2

### Example Key Functions

- `powermux2_cfg_setup` Config Object Initialization function.
```c
void powermux2_cfg_setup ( powermux2_cfg_t *cfg );
```

- `powermux2_init` Initialization function.
```c
err_t powermux2_init ( powermux2_t *ctx, powermux2_cfg_t *cfg );
```

- `powermux2_default_cfg` Click Default Configuration function.
```c
void powermux2_default_cfg ( powermux2_t *ctx );
```

- `powermux2_generic_write` Power MUX 2 data writing function.
```c
err_t powermux2_generic_write ( powermux2_t *ctx, uint8_t data_in );
```

- `powermux2_set_resistance` Power MUX 2 set resistance function.
```c
err_t powermux2_set_resistance ( powermux2_t *ctx, float resistance );
```

### Application Init

> The application init consist of initialization of SPI driver and logger.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    powermux2_cfg_t powermux2_cfg;  /**< Click config object.  */

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

    powermux2_cfg_setup( &powermux2_cfg );
    POWERMUX2_MAP_MIKROBUS( powermux2_cfg, MIKROBUS_1 );
    err_t init_flag  = powermux2_init( &powermux2, &powermux2_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> This is an example that demonstrates the use of the Power MUX 2 Click board&trade;. 
> In this example, we set the resistance of the 100kΩ 
> for the output current limit of approximately 1.23A 
> and lower the resistance to 50kΩ, which fits the current limit of 2.25 A. 
> Results are sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " Resistance    ~ 100 kOhm \r\n" );
    log_printf( &logger, " Current Limit ~   1.23 A \r\n" );
    powermux2_set_resistance( &powermux2, 100 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " Resistance    ~  50 kOhm \r\n" );
    log_printf( &logger, " Current Limit ~   2.25 A \r\n" );
    powermux2_set_resistance( &powermux2, 50 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
