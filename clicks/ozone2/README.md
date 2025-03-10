
---
# Ozone 2 Click

> [Ozone 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2767) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2767&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example reads data from the MCP 3351 sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ozone2

### Example Key Functions

- `ozone2_cfg_setup` Config Object Initialization function. 
```c
void ozone2_cfg_setup ( ozone2_cfg_t *cfg );
``` 
 
- `ozone2_init` Initialization function. 
```c
err_t ozone2_init ( ozone2_t *ctx, ozone2_cfg_t *cfg );
```

- `ozone2_default_cfg` Click Default Configuration function. 
```c
void ozone2_default_cfg ( ozone2_t *ctx );
```

- `ozone2_read` Function reads from MCP 3351 ADC and returns 32 bit read value. 
```c
uint32_t ozone2_read ( ozone2_t *ctx );
```
 
### Application Init

> Driver initialization.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ozone2_cfg_t cfg;

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

    ozone2_cfg_setup( &cfg );
    OZONE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ozone2_init( &ozone2, &cfg );
}
```

### Application Task

> Reading ADC value and displaying it via UART.

```c
void application_task ( void )
{
    read_value = ozone2_read( &ozone2 );
    log_printf( &logger, "Read Value: %u\r\n", read_value);
    
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
