
---
# RF Meter Click

> [RF Meter Click](https://www.mikroe.com/?pid_product=MIKROE-2034) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2034&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> 
> Demo app measures and displays signal strenght by using RF Meter Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rfmeter

### Example Key Functions

- `rfmeter_cfg_setup` Config Object Initialization function. 
```c
void rfmeter_cfg_setup ( rfmeter_cfg_t *cfg );
``` 
 
- `rfmeter_init` Initialization function. 
```c
err_t rfmeter_init ( rfmeter_t *ctx, rfmeter_cfg_t *cfg );
```

- `rfmeter_get_signal_strenght` Function is used to calculate radio frequency signal strenght in a vicinity. 
```c
float rfmeter_get_signal_strenght ( rfmeter_t *ctx, float slope, float intercept );
```

### Application Init

>
> Initalizes SPI, LOG and Click drivers.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rfmeter_cfg_t cfg;

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
    log_printf( &logger, "---- Application Init ----" );

    //  Click initialization.

    rfmeter_cfg_setup( &cfg );
    RFMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rfmeter_init( &rfmeter, &cfg );
    log_printf( &logger, "----------------------- \r\n" );
    log_printf( &logger, "    RF Meter Click      \r\n" );
    log_printf( &logger, "----------------------- \r\n" );
}
```

### Application Task

>
> This is an example that shows the capabilities of the RF Meter Click by
> measuring radio frequency signal strenght.
> 

```c
void application_task ( void )
{
    signal = rfmeter_get_signal_strenght( &rfmeter, RFMETER_DEF_SLOPE, RFMETER_DEF_INTERCEPT );
    
    log_printf( &logger, "Signal strenght: %.2f dBm \r\n", signal );
    
    Delay_ms ( 1000 );
    log_printf( &logger, "-----------------------\r\n" );
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
