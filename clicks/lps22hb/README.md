
---
# LPS22HB Click

> [LPS22HB Click](https://www.mikroe.com/?pid_product=MIKROE-2665) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2665&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : Jan 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> 
> The demo application measures temperature and pressure.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Lps22hb

### Example Key Functions

- `lps22hb_cfg_setup` Config Object Initialization function. 
```c
void lps22hb_cfg_setup ( lps22hb_cfg_t *cfg );
``` 
 
- `lps22hb_init` Initialization function. 
```c
err_t lps22hb_init ( lps22hb_t *ctx, lps22hb_cfg_t *cfg );
```

- `lps22hb_default_cfg` Click Default Configuration function. 
```c
void lps22hb_default_cfg ( lps22hb_t *ctx );
```

- `lps22hb_default_cfg` Click Default Configuration function. 
```c
void lps22hb_default_cfg ( lps22hb_t *ctx );
```
 
- `lps22hb_get_pressure` Function gets pressure data, calculates and returns pressure. 
```c
float lps22hb_get_pressure ( lps22hb_t *ctx );
```
 
- `lps22hb_get_temp` Function gets temperature returns value in degrees Celsius. 
```c
float lps22hb_get_temp ( lps22hb_t *ctx );
```

### Application Init

>
> Initalizes Click driver, resets the device, applies default settings
> and makes an initial log.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lps22hb_cfg_t cfg;

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

    lps22hb_cfg_setup( &cfg );
    LPS22HB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lps22hb_init( &lps22hb, &cfg );
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " ------ LPS22HB Click ------\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
    
    lps22hb_default_cfg ( &lps22hb, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, " -- Initialization  done. --\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> This is a example which demonstrates the use of LPS22HB Click board. By 
> measuring temperature and pressure. The results are being sent to the USART 
> terminal where you can track their changes.
> 

```c
void application_task ( void )
{
    pressure = lps22hb_get_pressure( &lps22hb );
    temperature = lps22hb_get_temp( &lps22hb );
    
    log_printf( &logger, "** Pressure is %.2f mBar\r\n", pressure );
    log_printf( &logger, "** Temperature is %.2f C \r\n", temperature );
    
    log_printf( &logger, "----------------------------\r\n" );

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
