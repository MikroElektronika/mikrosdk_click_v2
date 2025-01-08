
---
# Single Cell Click

> [Single Cell Click](https://www.mikroe.com/?pid_product=MIKROE-3844) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3844&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> 
> Demo application is used to shows basic controls Single Cell Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SingleCell

### Example Key Functions

- `singlecell_cfg_setup` Config Object Initialization function. 
```c
void singlecell_cfg_setup ( singlecell_cfg_t *cfg );
``` 
 
- `singlecell_init` Initialization function. 
```c
err_t singlecell_init ( singlecell_t *ctx, singlecell_cfg_t *cfg );
```

- `singlecell_default_cfg` Click Default Configuration function. 
```c
void singlecell_default_cfg ( singlecell_t *ctx );
```

- `singlecell_set_power_mode` Set power mode function. 
```c
void singlecell_set_power_mode ( singlecell_t *ctx, uint8_t en_mode );
```

### Application Init

>
> Initializes GPIO and LOG structures,
> set CS pin as output and start write log.
> Initialization driver enable's - GPIO, also write log.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    singlecell_cfg_t cfg;

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
    log_printf(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    singlecell_cfg_setup( &cfg );
    SINGLECELL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    singlecell_init( &singlecell, &cfg );
    singlecell_default_cfg ( &singlecell );
   
    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "    Single Cell Click    \r\n");
    log_printf(&logger, "-------------------------\r\n");

    Delay_ms ( 100 );
}
```

### Application Task

>
> This is a example which demonstrates the use of Single Cell board.
> This example shows the automatic control of the Single Cell Click,
> enable and disable power the regulator output on 10 sec. 
> 

```c
void application_task ( void )
{
    log_printf(&logger, "         Enable\r\n");
    singlecell_set_power_mode ( &singlecell, SINGLECELL_ENABLE );
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
    
    log_printf(&logger, "         Disable\r\n");
    singlecell_set_power_mode ( &singlecell, SINGLECELL_DISABLE );
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
 

```

### Note

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
