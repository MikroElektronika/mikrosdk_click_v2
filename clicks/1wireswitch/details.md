
---
# 1-Wire Switch click

> 1-Wire Switch Click is a compact add-on board that allows you to switch a device remotely using a 1-wire signal. This board features the DS2413, a dual-channel programmable I/O 1-Wire switch from Analog Devices. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/1wireswitch_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/1-wire-switch-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2023.
- **Type**          : One Wire type


# Software Support

We provide a library for the 1-Wire Switch Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 1-Wire Switch Click driver.

#### Standard key functions :

- `c1wireswitch_cfg_setup` Config Object Initialization function.
```c
void c1wireswitch_cfg_setup ( c1wireswitch_cfg_t *cfg );
```

- `c1wireswitch_init` Initialization function.
```c
err_t c1wireswitch_init ( c1wireswitch_t *ctx, c1wireswitch_cfg_t *cfg );
```

- `c1wireswitch_default_cfg` Click Default Configuration function.
```c
err_t c1wireswitch_default_cfg ( c1wireswitch_t *ctx );
```

#### Example key functions :

- `c1wireswitch_set_pio_state` 1-Wire Switch write specific programmable I/O state function.
```c
err_t c1wireswitch_set_pio_state ( c1wireswitch_t *ctx, uint8_t pio_a, uint8_t pio_b );
```

- `c1wireswitch_get_pio_state` 1-Wire Switch read specific programmable I/O state function.
```c
err_t c1wireswitch_get_pio_state ( c1wireswitch_t *ctx, uint8_t *pio_a, uint8_t *pio_b );
```

- `c1wireswitch_get_pio_latch_state` 1-Wire Switch read programmable I/O latch state function.
```c
err_t c1wireswitch_get_pio_latch_state ( c1wireswitch_t *ctx, uint8_t *pio_a_latch, uint8_t *pio_b_latch );
```

## Example Description

> This library contains API for 1-Wire Switch Click driver. 
The library initializes and defines the 1-Wire bus drivers to 
write and read data for state programmable I/O, 
as well as the default configuration.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs default configuration and sets 
the PIO A to OFF and PIO B to ON state.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c1wireswitch_cfg_t c1wireswitch_cfg;  /**< Click config object. */

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
    c1wireswitch_cfg_setup( &c1wireswitch_cfg );
    C1WIRESWITCH_MAP_MIKROBUS( c1wireswitch_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == c1wireswitch_init( &c1wireswitch, &c1wireswitch_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C1WIRESWITCH_ERROR == c1wireswitch_default_cfg ( &c1wireswitch ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    c1wireswitch_set_pio_state( &c1wireswitch, C1WIRESWITCH_PIOA_OFF, C1WIRESWITCH_PIOB_ON );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the 1-Wire Switch Click board by changing the PIO A state, 
which is controlling the LED, every time the state of PIO B changes. 
Change on the PIO B happens when the button is pushed.

```c
void application_task ( void ) 
{
    uint8_t pio_a = 0;
    uint8_t pio_b = 0;
    
    c1wireswitch_get_pio_state( &c1wireswitch, &pio_a, &pio_b );
    
    if ( pio_b == C1WIRESWITCH_PIOB_OFF )
    {
        if ( state == 0 )
        {
            c1wireswitch_set_pio_state( &c1wireswitch, C1WIRESWITCH_PIOA_ON, C1WIRESWITCH_PIOB_ON );
            log_printf( &logger, " Button is pressed, LED is ON. \r\n " );
            state = 1;
        }
        else
        {
            c1wireswitch_set_pio_state( &c1wireswitch, C1WIRESWITCH_PIOA_OFF, C1WIRESWITCH_PIOB_ON );
            log_printf( &logger, " Button is pressed, LED is OFF. \r\n " );
            state = 0;
        }
        Delay_ms ( 100 );
    }
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.c1WireSwitch

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
