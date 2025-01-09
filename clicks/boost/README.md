
---
# BOOST Click

> [BOOST Click](https://www.mikroe.com/?pid_product=MIKROE-2780) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2780&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> Boost Click provides an adjustable output voltage through the onboard DAC that drives the FB pin of the MIC2606 to set desired output voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost

### Example Key Functions

- `boost_cfg_setup` Config Object Initialization function. 
```c
void boost_cfg_setup ( boost_cfg_t *cfg );
``` 
 
- `boost_init` Initialization function. 
```c
err_t boost_init ( boost_t *ctx, boost_cfg_t *cfg );
```

- `boost_default_cfg` Click Default Configuration function. 
```c
void boost_default_cfg ( boost_t *ctx );
```

- `boost_write_byte` Generic write 14-bit data function. 
```c
void boost_write_byte ( boost_t *ctx, uint16_t write_data );
```
 
- `boost_read_byte` Generic read 22-bit of data function. 
```c
uint32_t boost_read_byte ( boost_t *ctx );
```

- `boost_set_configuration` Set configuration function. 
```c
void boost_set_configuration ( boost_t *ctx, uint8_t pwr_src );
```

### Application Init

> Initialization driver enable's - SPI, set configuration and start write log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    boost_cfg_t cfg;

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

    boost_cfg_setup( &cfg );
    BOOST_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost_init( &boost, &cfg );

    boost_default_cfg ( &boost );

    Delay_100ms( );
}
```

### Application Task

> This is a example which demonstrates the use of Boost Click board.
  Boost Click communicates with register via SPI by read from MCP3551 chip and write DAC value to the MCP4921 chip.
  This example periodicaly increases and decreases voltage in range between 15 and 30 Volts.
  All data logs write on usb uart for aproximetly every 3 sec. 

```c
void application_task ( void )
{
  log_printf( &logger, " Setting voltage to 15000 mV \r\n" );

  boost_set_voltage( &boost, 15000 );
  Delay_ms ( 1000 );
  Delay_ms ( 1000 );
  Delay_ms ( 1000 );
  Delay_ms ( 1000 );
  Delay_ms ( 1000 );

  log_printf( &logger, " Setting voltage to 30000 mV \r\n" );

  boost_set_voltage( &boost, 30000 );
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
