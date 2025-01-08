
---
# SOLAR ENERGY Click

> [SOLAR ENERGY Click](https://www.mikroe.com/?pid_product=MIKROE-2814) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2814&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application charge the batery when is empty.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SolarEnergy

### Example Key Functions

- `solarenergy_cfg_setup` Config Object Initialization function. 
```c
void solarenergy_cfg_setup ( solarenergy_cfg_t *cfg );
``` 
 
- `solarenergy_init` Initialization function. 
```c
err_t solarenergy_init ( solarenergy_t *ctx, solarenergy_cfg_t *cfg );
```

- `solarenergy_charge_enable` Charge enable function. 
```c
void solarenergy_charge_enable ( solarenergy_t *ctx );
```
 
- `solarenergy_charge_disable` Charge disable functions. 
```c
void solarenergy_charge_disable ( solarenergy_t *ctx );
```

- `solarenergy_check_indicator` Battery good indicator functions. 
```c
uint8_t solarenergy_check_indicator ( solarenergy_t *ctx );
```

### Application Init

> Initialization driver enables - GPIO and start to write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    solarenergy_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    solarenergy_cfg_setup( &cfg );
    SOLARENERGY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    solarenergy_init( &solarenergy, &cfg );

    log_printf( &logger, "   Initialization   \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, " Charge the battery \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> This is an example which demonstrates the use of Solar Energy Click board. The following example will charge the battery if it is empty, and stop charging when the battery is full. When battery full status is detected, the device is disabled, but will check battery status every 10 seconds. Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    if ( solarenergy_check_indicator( &solarenergy ) )
    {
        solarenergy_charge_disable( &solarenergy );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        solarenergy_charge_enable( &solarenergy );
    }
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
