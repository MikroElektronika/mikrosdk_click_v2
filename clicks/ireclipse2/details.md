
---
# IR Eclipse 2 Click

> IR Eclipse 2 Click is a compact add-on board that adds photo interrupter ability to any application. This board features the EE-SX1330, a transmissive photomicrosensor with a phototransistor output from OMRON. This compact interrupter sensor senses objects or object positions with an optical beam. It can sense any object less than 3mm as it is the space between the photomicrosensor and phototransistor in which an object can fit.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ireclipse2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ir-eclipse-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the IR Eclipse 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IR Eclipse 2 Click driver.

#### Standard key functions :

- `ireclipse2_cfg_setup` Config Object Initialization function.
```c
void ireclipse2_cfg_setup ( ireclipse2_cfg_t *cfg );
```

- `ireclipse2_init` Initialization function.
```c
err_t ireclipse2_init ( ireclipse2_t *ctx, ireclipse2_cfg_t *cfg );
```

#### Example key functions :

- `ireclipse2_get_state` This function detects eclipse states.
```c
uint8_t ireclipse2_get_state ( ireclipse2_t *ctx );
```

- `ireclipse2_enable` This function enables the transmitter of the photo-microsensor.
```c
void ireclipse2_enable ( ireclipse2_t *ctx );
```

- `ireclipse2_disable` This function disables the transmitter of the photo-microsensor.
```c
void ireclipse2_disable ( ireclipse2_t *ctx );
```

## Example Description

> This example demonstrates the use of the IR Eclipse 2 Click board
> by detecting eclipse states.

**The demo application is composed of two sections :**

### Application Init

> Initialization of GPIO module, log UART and enables the transmitter of the photo-microsensor.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ireclipse2_cfg_t ireclipse2_cfg;  /**< Click config object. */

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
    ireclipse2_cfg_setup( &ireclipse2_cfg );
    IRECLIPSE2_MAP_MIKROBUS( ireclipse2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ireclipse2_init( &ireclipse2, &ireclipse2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ireclipse2_enable( &ireclipse2 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> When the beam from the transmitter is eclipsed by placing an object in
> the gap ( like a piece of paper ), the counter is incremented by one 
> when the sensor is triggered.

```c
void application_task ( void ) 
{
    ecls_state = ireclipse2_get_state( &ireclipse2 );
    if ( cmp_state != ecls_state )
    {
        if ( IRECLIPSE2_STATE_ECLIPSE == ecls_state )
        {
            log_printf( &logger, " Counter: %u\n", cnt );
            cnt++;
        }
        cmp_state = ecls_state;
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IREclipse2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
