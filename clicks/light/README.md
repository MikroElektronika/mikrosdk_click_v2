
---
# Light Click

> [Light Click](https://www.mikroe.com/?pid_product=MIKROE-1424) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1424&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application return the ambient light intensity.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Light

### Example Key Functions

- `light_cfg_setup` Config Object Initialization function. 
```c
void light_cfg_setup ( light_cfg_t *cfg );
``` 
 
- `light_init` Initialization function. 
```c
err_t light_init ( light_t *ctx, light_cfg_t *cfg );
```

- `light_write_data` Generic write data function. 
```c
void light_write_data ( light_t *ctx, uint8_t address, uint8_t write_command );
```
 
- `light_read_data` Generic read data function. 
```c
uint16_t light_read_data ( light_t *ctx );
```

- `light_calculate_percent` Function calculate percent. 
```c
uint8_t light_calculate_percent ( light_t *ctx, uint16_t light_value );
```

### Application Init

> Initialization driver enable's - SPI and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    light_cfg_t cfg;

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

    light_cfg_setup( &cfg );
    LIGHT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    light_init( &light, &cfg );
}
```

### Application Task

> This is a example which demonstrates the use of Light Click board. Measured light intensity and calculate light intensity percent from sensor, results are being sent to the Usart Terminal where you can track their changes. All data logs on usb uart for aproximetly every 100 ms when the data value changes.

```c
void application_task ( void )
{
    uint16_t light_value;
    uint8_t light_percent;
    uint8_t percent_old = 1;

    light_value = light_read_data( &light );
    light_percent = light_calculate_percent( &light, light_value );
    

    if ( percent_old != light_percent )
    {
        log_printf( &logger, " Light Intensity : %d \r\n", light_percent );

        log_printf( &logger, " Light Value     : %d\r\n", light_value );

        percent_old = light_percent;
        Delay_100ms();
    }
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
