
---
# Ammeter Click

> [Ammeter Click](https://www.mikroe.com/?pid_product=MIKROE-2377) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2377&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> 
> Demo app measures and displays current by using Ammeter Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ammeter

### Example Key Functions

- `ammeter_cfg_setup` Config Object Initialization function. 
```c
void ammeter_cfg_setup ( ammeter_cfg_t *cfg );
``` 
 
- `ammeter_init` Initialization function. 
```c
err_t ammeter_init ( ammeter_t *ctx, ammeter_cfg_t *cfg );
```

- `ammeter_amperage` Function is used to measure amperage of a power consumer connected to the Click board. 
```c
float ammeter_amperage ( ammeter_t *ctx );
```

### Application Init

>
> Initalizes SPI, LOG and Click drivers.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ammeter_cfg_t cfg;

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
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    ammeter_cfg_setup( &cfg );
    AMMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ammeter_init( &ammeter, &cfg );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    Ammeter  Click     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}
```

### Application Task

>
> This is an example that shows the capabilities of the Ammeter Click by 
  measuring amperage in miliampers. Ammeter Click board can be used to saftly 
  measure current up to 1A both AC and DC, in the case of AC, for peak to peak value.
> 

```c
void application_task ( void )
{
    amperage = ammeter_amperage( &ammeter );
    log_printf( &logger, " Current: %.2f mA \r\n", amperage );
    
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Note

> 
> It is important to notice that this Click board has its' own electronic 
  circuit, and may not be powered from the same source which we are measuring.
  Result will not be correct in that case.
> 

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
