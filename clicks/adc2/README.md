
---
# ADC 2 Click

> [ADC 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1893) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1893&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application enables usage of the 22bit ADC.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc2

### Example Key Functions

- `adc2_cfg_setup` Config Object Initialization function. 
```c
void adc2_cfg_setup ( adc2_cfg_t *cfg );
``` 
 
- `adc2_init` Initialization function. 
```c
err_t adc2_init ( adc2_t *ctx, adc2_cfg_t *cfg );
```

- `adc2_default_cfg` Click Default Configuration function. 
```c
void adc2_default_cfg ( adc2_t *ctx );
```

- `adc2_check_over_high` Function is used to check overflow high state. 
```c
uint8_t adc2_check_over_high ( adc2_t *ctx );
```
 
- `adc2_check_over_low` Function is used to check overflow low state. 
```c
uint8_t adc2_check_over_low ( adc2_t *ctx );
```

- `adc2_adc_value_read` Function is used to read specific data from ADC convertor. 
```c
uint32_t adc2_adc_value_read ( adc2_t *ctx );
```

### Application Init

> Initalizes SPI driver and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    adc2_cfg_t cfg;

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

    adc2_cfg_setup( &cfg );
    ADC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc2_init( &adc2, &cfg );

    Delay_ms ( 100 );

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "    ADC 2 Click   \r\n" );
    log_printf( &logger, "------------------\r\n" );
}
```

### Application Task

> This is an example that shows the capabilities of the ADC 2 Click

```c
void application_task ( void )
{
    uint32_t adc_val;

    //  Task implementation.

    adc_val = adc2_adc_value_read( &adc2 );

    log_printf( &logger, "Value : %d", adc_val );
    log_printf( &logger, "------------------\r\n" );
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
