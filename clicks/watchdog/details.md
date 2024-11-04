
---
# Watchdog Click

> Watchdog Click is a compact add-on board that contains a simple countdown timer for a wide variety of applications. This board features the TPS3430, a standalone watchdog timer with a programmable watchdog window and programmable reset delay from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/watchdog_click.png" height=300px>
</p>

[Click Product page](mikroe.com/watchdog-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the Watchdog Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Watchdog Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This is an example that demonstrates the use of the Watchdog Click board.

**The demo application is composed of two sections :**

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


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Watchdog

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
