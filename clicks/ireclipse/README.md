
---
# Ir Eclipse Click

> [Ir Eclipse Click](https://www.mikroe.com/?pid_product=MIKROE-1711) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1711&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> 
> This is an example of IR ECLIPSE Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrEclipse

### Example Key Functions

- `ireclipse_cfg_setup` Config Object Initialization function. 
```c
void ireclipse_cfg_setup ( ireclipse_cfg_t *cfg );
``` 
 
- `ireclipse_init` Initialization function. 
```c
err_t ireclipse_init ( ireclipse_t *ctx, ireclipse_cfg_t *cfg );
```

- `ireclipse_default_cfg` Click Default Configuration function. 
```c
void ireclipse_default_cfg ( ireclipse_t *ctx );
```

- `ireclipse_int_status` Detecting states of IR beam from EE-SX198 photo interrupter sensor. 
```c
uint8_t ireclipse_int_status ( ireclipse_t *ctx );
```

### Application Init

>
> Configuring Clicks and log objects.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ireclipse_cfg_t cfg;

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
    log_printf(&logger, "- Application Init -\r\n");

    //  Click initialization.

    ireclipse_cfg_setup( &cfg );
    IRECLIPSE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ireclipse_init( &ireclipse, &cfg );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "   Start counting:  \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    
    n_cnt = IRECLIPSE_START_CNT_VAL;
    state_old = IRECLIPSE_LOW;
    state_new = IRECLIPSE_LOW;
}
```

### Application Task

>
> This is a example which demonstrates the use of IR eclipse Click board.
> When the beam from the transmitter is eclipsed by placing an object in
> the gap ( like a piece of paper ), when the sensor is triggered, the 
> counter is incremented by one. Results are being sent to the Usart 
> Terminal where you can track their changes. Data logs on usb uart 
> when the sensor is triggered.
> 

```c
void application_task ( void )
{
    state_new = ireclipse_int_status( &ireclipse );

    if ( ( state_new == IRECLIPSE_HIGH ) && ( state_old == IRECLIPSE_LOW ) )
    {
        state_old = IRECLIPSE_HIGH;
        log_printf( &logger, "  Counter = %d \r\n", n_cnt );
    
        n_cnt++;
    }

    if ( ( state_new == IRECLIPSE_LOW ) && ( state_old == IRECLIPSE_HIGH ) )
    {
        log_printf( &logger, "--------------------\r\n" );
        state_old = IRECLIPSE_LOW;
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
