
---
# Expand 4 Click

> [Expand 4 Click](https://www.mikroe.com/?pid_product=MIKROE-1910) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1910&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> Example demonstrates use of Expand 4 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand4

### Example Key Functions

- `expand4_cfg_setup` Config Object Initialization function. 
```c
void expand4_cfg_setup ( expand4_cfg_t *cfg );
``` 
 
- `expand4_init` Initialization function. 
```c
err_t expand4_init ( expand4_t *ctx, expand4_cfg_t *cfg );
```

- `expand4_default_cfg` Click Default Configuration function. 
```c
void expand4_default_cfg ( expand4_t *ctx );
```

- `expand4_write_data` Function write 8-bit data function to TPIC6A595 shift register. 
```c
void expand4_write_data ( expand4_t *ctx, uint8_t write_command );
```
 
- `expand4_enable_output` Function turn on output buffers - set PWM pin low. 
```c
void expand4_enable_output ( expand4_t *ctx );
```

- `expand4_reset` Function clear input TPIC6A595 shift register. 
```c
void expand4_reset ( expand4_t *ctx );
```

### Application Init

> Initialization driver enable's - Clear TPIC6A595 register and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    expand4_cfg_t cfg;

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

    expand4_cfg_setup( &cfg );
    EXPAND4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand4_init( &expand4, &cfg );
    expand4_reset( &expand4 );
}
```

### Application Task

> This is a example which demonstrates the use of Expand 4 Click board.
> In this example, the LED pin mask is transferred via SPI bus,
> LEDs connected to D0-D7 pins are lit accordingly by turning ON LEDs from D0 to D7 for 3 sec.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 3 sec. when the change pin who is connected.

```c
void application_task ( void )
{
    uint8_t pin_position;

    for ( pin_position = 0; pin_position < 8; pin_position++ )
    {
        expand4_disable_output( &expand4 );
        Delay_ms ( 100 );

        expand4_turn_on_by_position( &expand4, pin_position );
        Delay_ms ( 100 );

        log_printf( &logger, " D%d", pin_position );

        expand4_enable_output( &expand4 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    log_printf( &logger, "\n----------------------------------\n");
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
