
---
# MCP73213 Click

> [MCP73213 Click](https://www.mikroe.com/?pid_product=MIKROE-2575) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2575&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application is polymer battery charge management controller.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mcp73213

### Example Key Functions

- `mcp73213_cfg_setup` Config Object Initialization function. 
```c
void mcp73213_cfg_setup ( mcp73213_cfg_t *cfg );
``` 
 
- `mcp73213_init` Initialization function. 
```c
err_t mcp73213_init ( mcp73213_t *ctx, mcp73213_cfg_t *cfg );
```

- `mcp73213_set_current_output` Set values for output current function. 
```c
void mcp73213_set_current_output ( mcp73213_t *ctx, uint8_t out_data );
```
 
- `mcp73213_get_status` Get the status register data function. 
```c
uint8_t mcp73213_get_status ( mcp73213_t *ctx );
```

- `mcp73213_convert_output` Convert ADC value to volatage. 
```c
float mcp73213_convert_output ( uint8_t value_adc, float v_ref );
```

### Application Init

> Initialization driver enable's - SPI, also write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp73213_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mcp73213_cfg_setup( &cfg );
    MCP73213_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp73213_init( &mcp73213, &cfg );

    log_printf( &logger, "   SPI Driver Init     \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "  Set Current Output   \r\n" );
}
```

### Application Task

> This is a example which demonstrates the use of MCP73213 Click board.
> This example sets the resistance to a given value, thus affecting the output current.
> Controls output current using internal digital potentiometer.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on usb uart changes for every 3 sec.

```c
void application_task ( void )
{
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "   10 kOhm - 130 mA    \r\n" );
    mcp73213_set_current_output( &mcp73213, MCP73213_OUTPUT_130_mA );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "    5 kOhm - 250 mA    \r\n" );
    mcp73213_set_current_output( &mcp73213, MCP73213_OUTPUT_250_mA );
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
