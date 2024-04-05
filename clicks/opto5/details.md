
---
# Opto 5 click

Opto 5 Click is a compact add-on board that provides uncomplicated safety isolation from the high voltage. This board features the FOD4216, a random phase snubberless Triac driver from ON Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/opto5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/opto-5-click)

---


#### Click library

- **Author**        : Stefan Nikolic
- **Date**          : dec 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Opto5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for Opto5 Click driver.
```

#### Standard key functions :

- Config Object Initialization function.
```
void opto5_cfg_setup ( opto5_cfg_t *cfg );
```

- Initialization function.
```
OPTO5_RETVAL opto5_init ( opto5_t *ctx, opto5_cfg_t *cfg );
```

- Click Default Configuration function.
```
void opto5_default_cfg ( opto5_t *ctx );
```

#### Example key functions :

- Opto 5 pin setting function.
```
void opto5_pin_set ( opto5_t *ctx );
```

- Opto 5 pin clearing function.
```
void opto5_pin_clear ( opto5_t *ctx );
```

- Opto 5 pin toggling function.
```
void opto5_pin_toggle ( opto5_t *ctx );
```

## Examples Description

This example demonstrates the use of Opto 5 click board.

**The demo application is composed of two sections :**

### Application Init

Initialization of UART LOG and GPIO pin drivers.
The output of PWM is set to high so the optocoupler
is not triggered by default.

```
void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    opto5_cfg_t opto5_cfg;          /**< Click config object. */

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

    opto5_cfg_setup( &opto5_cfg );
    OPTO5_MAP_MIKROBUS( opto5_cfg, MIKROBUS_1 );
    if ( opto5_init( &opto5, &opto5_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    opto5_default_cfg ( &opto5 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

The output pin is toggled every 5 seconds. 

```
void application_task ( void ) {
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Pin toggling...\r\n" );
    opto5_pin_toggle( &opto5 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Opto5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
