
---
# Tilt 3 click

> Tilt 3 Click is a compact add-on board used for measuring the tilt in multiple axes in relation to an absolute level plane. This board features the DSBA1P, a tilt sensor switch that breaks the circuit when tilted to an angle from ±30° to ±60° from NKK Switches.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tilt3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/tilt-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the Tilt3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Tilt3 Click driver.

#### Standard key functions :

- `tilt3_cfg_setup` Config Object Initialization function.
```c
void tilt3_cfg_setup ( tilt3_cfg_t *cfg );
```

- `tilt3_init` Initialization function.
```c
err_t tilt3_init ( tilt3_t *ctx, tilt3_cfg_t *cfg );
```

#### Example key functions :

- `tilt3_enable_switch` This function enables the tilt switch by setting the EN pin to the high logic state.
```c
void tilt3_enable_switch ( tilt3_t *ctx );
```

- `tilt3_disable_switch` This function disables the tilt switch by setting the EN pin to the low logic state.
```c
void tilt3_disable_switch ( tilt3_t *ctx );
```

- `tilt3_get_switch_state` This function returns the INT pin logic state which indicates the tilt switch state. 
```c
uint8_t tilt3_get_switch_state ( tilt3_t *ctx );
```

## Example Description

> This example demonstrates the use of Tilt 3 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the tilt switch.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    tilt3_cfg_t tilt3_cfg;  /**< Click config object. */

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
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    tilt3_cfg_setup( &tilt3_cfg );
    TILT3_MAP_MIKROBUS( tilt3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == tilt3_init( &tilt3, &tilt3_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    tilt3_enable_switch( &tilt3 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> As soon as the tilt switch state changes, it displays a corresponding message on the USB UART.

```c

void application_task ( void )
{
    uint8_t state = tilt3_get_switch_state ( &tilt3 );
    if ( tilt3_switch_state != state )
    {
        tilt3_switch_state = state;
        
        if ( TILT3_SWITCH_ON == tilt3_switch_state )
        {
            log_printf( &logger, " Tilt switch ON!\r\n\n" );
        }
        else
        {
            log_printf( &logger, " Tilt switch OFF!\r\n\n" );
        }
        Delay_ms( 500 );
    }
}

```

## Note

> Tilt switches OFF at an angle of 60 degrees minimum and switches ON at the horizontal position (up to 10 degrees).
> The tilt LED will turn ON when the tilt switch is OFF. 

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Tilt3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
