
---
# Cap Touch 6 click

> Cap Touch 6 Click is a compact add-on board that easily integrates projected capacitive touch into users' applications. This board features the IQS227D, a single-channel capacitive controller with an internal voltage regular and reference capacitor from Azoteq. Besides the capacitive sensing area, this board also has output pins for proximity and touch events with their corresponding LED indicators. The IQS227D automatically tracks slow varying environmental changes via various filters.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/captouch6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/cap-touch-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2022.
- **Type**          : GPIO type


# Software Support

We provide a library for the Cap Touch 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Cap Touch 6 Click driver.

#### Standard key functions :

- `captouch6_cfg_setup` Config Object Initialization function.
```c
void captouch6_cfg_setup ( captouch6_cfg_t *cfg );
```

- `captouch6_init` Initialization function.
```c
err_t captouch6_init ( captouch6_t *ctx, captouch6_cfg_t *cfg );
```

#### Example key functions :

- `captouch6_get_tout_pin` This function returns the TOUT pin logic state.
```c
uint8_t captouch6_get_tout_pin ( captouch6_t *ctx );
```

- `captouch6_get_pout_pin` This function returns the POUT pin logic state.
```c
uint8_t captouch6_get_pout_pin ( captouch6_t *ctx );
```

## Example Description

> This example demonstrates the use of Cap Touch 6 click board by reading and displaying the touch and proximity events.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    captouch6_cfg_t captouch6_cfg;  /**< Click config object. */

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
    captouch6_cfg_setup( &captouch6_cfg );
    CAPTOUCH6_MAP_MIKROBUS( captouch6_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == captouch6_init( &captouch6, &captouch6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the touch and proximity event pins state and displays them on the USB UART on changes.

```c
void application_task ( void )
{
    static uint8_t old_touch_state = 0, old_prox_state = 0;
    uint8_t touch_state = captouch6_get_tout_pin ( &captouch6 );
    uint8_t prox_state = captouch6_get_pout_pin ( &captouch6 );
    if ( ( old_touch_state != touch_state ) || ( old_prox_state != prox_state ) )
    {
        log_printf( &logger, " Touch: %s\r\n", ( char * ) ( !touch_state ? "detected" : "idle" ) );
        log_printf( &logger, " Proximity: %s\r\n\n", ( char * ) ( !prox_state ? "detected" : "idle" ) );
        old_touch_state = touch_state;
        old_prox_state = prox_state;
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CapTouch6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
