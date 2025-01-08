
---
# POT 2 Click

> [POT 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3325) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3325&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : nov 2019.
- **Type**          : ADC type

# Software Support

## Example Description

> This demo-app shows the ADC values using POT 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pot2

### Example Key Functions

- `pot2_cfg_setup` Config Object Initialization function. 
```c
void pot2_cfg_setup ( pot2_cfg_t *cfg );
``` 
 
- `pot2_init` Initialization function. 
```c
err_t pot2_init ( pot2_t *ctx, pot2_cfg_t *cfg );
```

- `pot2_generic_read` Generic read function. 
```c
pot2_data_t pot2_generic_read ( pot2_t *ctx );
```

### Application Init

> Configures Clicks and log objects.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pot2_cfg_t cfg;

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

    pot2_cfg_setup( &cfg );
    POT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pot2_init( &pot2, &cfg );
}
```

### Application Task

> Demo app reads ADC data and displays them as dec and hex values every second.

```c
void application_task ( void )
{
    pot2_data_t tmp;
    
    tmp = pot2_generic_read ( &pot2 );
    log_printf( &logger, " ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
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
