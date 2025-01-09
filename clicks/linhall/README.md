
---
# LIN HALL Click

> [LIN HALL Click](https://www.mikroe.com/?pid_product=MIKROE-1648) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1648&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> 
> This is a example which demonstrates the use of Lin Hall Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LinHall

### Example Key Functions

- `linhall_cfg_setup` Config Object Initialization function. 
```c
void linhall_cfg_setup ( linhall_cfg_t *cfg );
``` 
 
- `linhall_init` Initialization function. 
```c
err_t linhall_init ( linhall_t *ctx, linhall_cfg_t *cfg );
```

- `linhall_default_cfg` Click Default Configuration function. 
```c
void linhall_default_cfg ( linhall_t *ctx );
```

- `linhall_read_data` Read 12-bit data function. 
```c
uint16_t linhall_read_data ( linhall_t *ctx );
```
 
### Application Init

>
> Initializes SPI and LOG structures, initialization driver enable's 
> SPI and start write log.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    linhall_cfg_t cfg;

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
    log_printf( &logger, " Application Init \r\n" );

    //  Click initialization.

    linhall_cfg_setup( &cfg );
    LINHALL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    linhall_init( &linhall, &cfg );
    
    log_printf( &logger, "  Lin Hall Click  \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms ( 100 );
    
    value_adc_old = 0;
    sensitivity = 30;
}
```

### Application Task

>
> Read 12-bit ADC value from the MCP3201 chip.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 100 ms when the ADC value changes.
> 

```c
void application_task ( void )
{
    value_adc = linhall_read_data( &linhall );

    if ( ( ( value_adc - value_adc_old ) > sensitivity ) && ( ( value_adc_old - value_adc ) > sensitivity ) )
    {
        log_printf( &logger, "  ADC Value : %4d \r\n", value_adc );
        log_printf( &logger, "------------------\r\n" );

        value_adc_old = value_adc;
        Delay_ms ( 100 );
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
