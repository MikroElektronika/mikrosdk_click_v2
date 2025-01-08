
---
# GSR Click

> [GSR Click](https://www.mikroe.com/?pid_product=MIKROE-2860) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2860&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This app measure the electrodermal activity.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gsr

### Example Key Functions

- `gsr_cfg_setup` Config Object Initialization function. 
```c
void gsr_cfg_setup ( gsr_cfg_t *cfg );
``` 
 
- `gsr_init` Initialization function. 
```c
err_t gsr_init ( gsr_t *ctx, gsr_cfg_t *cfg );
```

- `gsr_default_cfg` Click Default Configuration function. 
```c
void gsr_default_cfg ( gsr_t *ctx );
```

- `gsr_read_value` This function read measurement using MCP3201 ADC integrated on Click board. 
```c
uint16_t gsr_read_value ( gsr_t *ctx );
```

### Application Init

> Initializes GSR driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    gsr_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    gsr_cfg_setup( &cfg );
    GSR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsr_init( &gsr, &cfg );
}
```

### Application Task

> Sequential reading of ADC and logging data 
> to UART. Operation is repeated each 500 ms.

```c
void application_task ( void )
{
    uint16_t adc_value;

    adc_value = gsr_read_value( &gsr );

    log_printf( &logger, "ADC Measurements: %u \r\n", adc_value );
    Delay_ms ( 500 );
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
