
---
# Watchdog Click

> [Watchdog Click](https://www.mikroe.com/?pid_product=MIKROE-4416) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4416&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Watchdog Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Watchdog

### Example Key Functions

- `watchdog_cfg_setup` Config Object Initialization function.
```c
void watchdog_cfg_setup ( watchdog_cfg_t *cfg );
```

- `watchdog_init` Initialization function.
```c
err_t watchdog_init ( watchdog_t *ctx, watchdog_cfg_t *cfg );
```

- `watchdog_default_cfg` Click Default Configuration function.
```c
err_t watchdog_default_cfg ( watchdog_t *ctx );
```

- `watchdog_set_set0` Set S0 ( RST ) pin state function.
```c
void watchdog_set_set0 ( watchdog_t *ctx, uint8_t set0_state );
```

- `watchdog_get_wdo` Get WDO ( INT ) pin state function.
```c
uint8_t watchdog_get_wdo ( watchdog_t *ctx );
```

- `watchdog_send_pulse` Send pulse function.
```c
void watchdog_send_pulse ( watchdog_t *ctx, uint16_t p_duration_ms );
```

### Application Init

> Initialization driver enables - GPIO, configure the watchdog window, enable watchdog, also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    watchdog_cfg_t watchdog_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    watchdog_cfg_setup( &watchdog_cfg );
    WATCHDOG_MAP_MIKROBUS( watchdog_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == watchdog_init( &watchdog, &watchdog_cfg ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    watchdog_default_cfg ( &watchdog );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   Configure of the  \r\n" );
    log_printf( &logger, "   watchdog window   \r\n" );
    watchdog_setup_time( &watchdog, WATCHDOG_SETUP_TIME_MODE_2 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   Watchdog enabled  \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> In the first part of the example, we send pulses in a valid time window (Correct Operation).
> The second part of the example sends pulses outside the valid time window and then the watchdog detects a fault condition, display "Fault",
> performs the reset and turn on the LED ( WDT FLT ) on the Watchdog Click board.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    log_printf( &logger, "  Correct Operation  \r\n" );
    uint8_t n_cnt = 40;
    while ( n_cnt > 0 ) {
        watchdog_send_pulse( &watchdog, 1 );
        Delay_ms ( 50 );
        n_cnt--;
    }
    log_printf( &logger, "---------------------\r\n" );

    log_printf( &logger, "        Fault        \r\n" );
    n_cnt = 8;
    while ( n_cnt > 0 ) {
        watchdog_send_pulse( &watchdog, 1 );
        Delay_ms ( 250 );
        n_cnt--;
    }
    log_printf( &logger, "---------------------\r\n" );
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
