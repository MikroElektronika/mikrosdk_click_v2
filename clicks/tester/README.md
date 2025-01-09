
---
# Tester Click

> [Tester Click](https://www.mikroe.com/?pid_product=MIKROE-3083) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3083&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example showcases how to initialize, configure and use the Tester Click. It is a simple
  GPIO Click which is used to test if all the pins on a MikroBUS are working correctly. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Tester

### Example Key Functions

- `tester_cfg_setup` Config Object Initialization function. 
```c
void tester_cfg_setup ( tester_cfg_t *cfg );
``` 
 
- `tester_init` Initialization function. 
```c
err_t tester_init ( tester_t *ctx, tester_cfg_t *cfg );
```

- `tester_default_cfg` Click Default Configuration function. 
```c
void tester_default_cfg ( tester_t *ctx );
```

- `tester_set_pin_high` This function sets the output voltage on the specified pin to high. 
```c
void tester_set_pin_high ( digital_out_t *pin );
```
 
- `tester_set_pin_low` This function sets the output voltage on the specified pin to low. 
```c
void tester_set_pin_low ( digital_out_t *pin );
```

### Application Init

> This function initializes and configures the Click and logger modules. 

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    tester_cfg_t cfg;

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

    tester_cfg_setup( &cfg );
    TESTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tester_init( &tester, &cfg );
}
```

### Application Task

> This function sets the output on all the pins (one by one) on the left side to high, going
  from top to bottom and then does the same with the ones on the right side, after which it 
  sets all pins to high and after one second sets them back to low.

```c
void application_task ( )
{
    int i;

    for( i = 0; i < 12; i++ )
    {
        blink( pin_addr[ i ] );
    }

    all_on( );
    Delay_1sec( );
    all_off( );
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