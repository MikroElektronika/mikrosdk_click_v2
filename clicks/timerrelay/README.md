\mainpage Main Page

---
# Timer Relay Click

> Timer Relay Click is a compact add-on board that allows you to control the load with a timer. This board features the NE5555, a precision timer from Diodes Incorporated. It is a precision timing circuit capable of producing accurate time delays in a monostable mode of operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/timerrelay_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/timer-relay-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Timer Relay Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Timer Relay Click driver.

#### Standard key functions :

- `timerrelay_cfg_setup` Config Object Initialization function.
```c
void timerrelay_cfg_setup ( timerrelay_cfg_t *cfg );
```

- `timerrelay_init` Initialization function.
```c
err_t timerrelay_init ( timerrelay_t *ctx, timerrelay_cfg_t *cfg );
```

- `timerrelay_default_cfg` Click Default Configuration function.
```c
err_t timerrelay_default_cfg ( timerrelay_t *ctx );
```

#### Example key functions :

- `timerrelay_set_wiper_pos` Timer Relay set wiper position function.
```c
err_t timerrelay_set_wiper_pos ( timerrelay_t *ctx, uint8_t wiper_pos );
```

- `timerrelay_activate_reset` Timer Relay reset timer function.
```c
void timerrelay_activate_reset ( timerrelay_t *ctx );
```

- `timerrelay_activate_trigger` Timer Relay activate trigger function.
```c
void timerrelay_activate_trigger ( timerrelay_t *ctx );
```

## Example Description

> This example demonstrates the use of the Timer Relay Click board by
  setting the relay timer to 2 seconds ON time, then holding it OFF for 2 more seconds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration,
  then setting the ON time to 2 seconds.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    timerrelay_cfg_t timerrelay_cfg;  /**< Click config object. */

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
    timerrelay_cfg_setup( &timerrelay_cfg );
    TIMERRELAY_MAP_MIKROBUS( timerrelay_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == timerrelay_init( &timerrelay, &timerrelay_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TIMERRELAY_ERROR == timerrelay_default_cfg ( &timerrelay ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( TIMERRELAY_ERROR == timerrelay_set_delay( &timerrelay, 2 ) )
    {
        log_error( &logger, " Value configuration." );
        for ( ; ; );
    }
    
    timerrelay_activate_reset( &timerrelay );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example is activating the trigger every 4 seconds activating the relay timer.

```c
void application_task ( void )
{
    timerrelay_activate_trigger( &timerrelay );
    log_printf( &logger, " Trigger activated. \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TimerRelay

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
