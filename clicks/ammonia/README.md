
---
# Ammonia Click

> [Ammonia Click](https://www.mikroe.com/?pid_product=MIKROE-4151) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4151&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This demo application reads ADC value.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ammonia

### Example Key Functions

- `ammonia_cfg_setup` Config Object Initialization function. 
```c
void ammonia_cfg_setup ( ammonia_cfg_t *cfg );
``` 
 
- `ammonia_init` Initialization function. 
```c
err_t ammonia_init ( ammonia_t *ctx, ammonia_cfg_t *cfg );
```

- `ammonia_heater` Sensor heater function. 
```c
void ammonia_heater( ammonia_t *ctx, uint8_t state );
```

- `ammonia_data_read` Read data function. 
```c
uint32_t ammonia_data_read( ammonia_t *ctx );
```

### Application Init

> Initalizes SPI driver, turns on the heater, and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ammonia_cfg_t cfg;

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

    ammonia_cfg_setup( &cfg );
    AMMONIA_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ammonia_init( &ammonia, &cfg );
    Delay_ms ( 100 );

    ammonia_heater( &ammonia, AMMONIA_HEATER_ON );
    Delay_ms ( 1000 );

    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, "   Ammonia  Click    \r\n" );
    log_printf( &logger, "-------------------- \r\n" );
}
```

### Application Task

> This is an example that shows the capabilities of the ADC 9 Click by reading ADC value and displaying it via UART.

```c
void application_task ( void )
{
    spi_adc_value = ammonia_data_read( &ammonia );

    log_printf( &logger, "ADC value: %s \r\n", spi_adc_value );

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
