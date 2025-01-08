
---
# Alcohol 3 Click

> [Alcohol 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3318) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3318&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Code of this sensor reacts to the presence of deoxidizing and reducing gases,
> such as ethanol (also known as alcohol).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Alcohol3

### Example Key Functions

- `alcohol3_cfg_setup` Config Object Initialization function. 
```c
void alcohol3_cfg_setup ( alcohol3_cfg_t *cfg );
``` 
 
- `alcohol3_init` Initialization function. 
```c
err_t alcohol3_init ( alcohol3_t *ctx, alcohol3_cfg_t *cfg );
```

- `alcohol3_default_cfg` Click Default Configuration function. 
```c
void alcohol3_default_cfg ( alcohol3_t *ctx );
```

- `alcohol3_get_co_in_ppm` This function reads CO (Carbon monoxide) data in ppm (1 ppm - 1000 ppm). 
```c
uint16_t alcohol3_get_co_in_ppm ( alcohol3_t *ctx );
```
 
- `alcohol3_get_percentage_bac` This function reads percentage of alcohol in the blood (BAC). 
```c
float alcohol3_get_percentage_bac ( alcohol3_t *ctx );
```

- `alcohol3_get_adc_data` This function reads 12bit ADC value. 
```c
uint16_t alcohol3_get_adc_data ( alcohol3_t *ctx );
```

### Application Init

> Application Init performs Logger and Click initialization.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    alcohol3_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 100 );

    //  Click initialization.

    alcohol3_cfg_setup( &cfg );
    ALCOHOL3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    alcohol3_init( &alcohol3, &cfg );

    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " ---- Alcohol 3 Click ----\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );

    log_printf( &logger, " ---- Initialization ---\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> Reads percentage of alcohol in the blood (BAC) 
> and this data logs to USBUART every 1 sec.

```c
void application_task ( void )
{
    uint16_t co_ppm;
    uint16_t p_bac;

    //  Task implementation.

    log_printf( &logger, " --- Alcohol diagnostics ---- \r\n" );

    co_ppm = alcohol3_get_co_in_ppm ( &alcohol3 );
    log_printf( &logger, " co in ppm  %d    | \r\n", co_ppm );

    p_bac = alcohol3_get_percentage_bac( &alcohol3 ) * 1000;

    if ( 10 > p_bac && p_bac < 100 )
    {
        log_printf( &logger, " BAC    %d  | 0.00\r\n", p_bac );
    }
    else if ( 100 <= p_bac && 1000 > p_bac )
    {
        log_printf( &logger, " BAC    %d  | 0.00\r\n", p_bac );
    }
    else if ( p_bac >= 1000 )
    {
        log_printf( &logger, " BAC    %d  | 0.\r\n", p_bac );
    }
    else
    {
        log_printf( &logger, " BAC  | 0.0000\r\n" );
    }
    log_printf( &logger, " ---------------------------- \r\n" );

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
