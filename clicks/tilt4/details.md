
---
# Tilt 4 click

> Tilt 4 Click is a compact add-on board designed for reliable tilt detection applications. This board features the RB-231X2, a rolling ball tilt switch from C&K Components, ensuring accurate and safe tilt detection. The RB-231X2 features a compact, shielded design with a detection angle of up to 10° and an operating life of 100,000 cycles. It interfaces with the MCU using only the INT and LED pins, providing real-time interrupt signals and visual tilt indication through a red LED.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tilt4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/tilt-4-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the Tilt 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Tilt 4 Click driver.

#### Standard key functions :

- `tilt4_cfg_setup` Config Object Initialization function.
```c
void tilt4_cfg_setup ( tilt4_cfg_t *cfg );
```

- `tilt4_init` Initialization function.
```c
err_t tilt4_init ( tilt4_t *ctx, tilt4_cfg_t *cfg );
```

#### Example key functions :

- `tilt4_read_int_state` This function reads the state of the interrupt pin of Tilt 4 click board.
```c
uint8_t tilt4_read_int_state ( tilt4_t *ctx );
```

- `tilt4_set_led_state` This function sets the LED pin on the selected level level of Tilt 4 click board.
```c
void tilt4_set_led_state ( tilt4_t *ctx, uint8_t pin_state );
```

## Example Description

> This example demonstrates the use of Tilt 4 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and USB UART logger.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tilt4_cfg_t tilt4_cfg;  /**< Click config object. */

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
    tilt4_cfg_setup( &tilt4_cfg );
    TILT4_MAP_MIKROBUS( tilt4_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == tilt4_init( &tilt4, &tilt4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> As soon as the tilt switch state changes, it displays a corresponding message on the USB UART.

```c
void application_task ( void ) 
{
    uint8_t state = tilt4_read_int_state ( &tilt4 );
    if ( tilt4_switch_state != state )
    {
        tilt4_switch_state = state;
        
        if ( TILT4_SWITCH_ON == tilt4_switch_state )
        {
            log_printf( &logger, " Tilt switch ON!\r\n\n" );
            tilt4_set_led_state( &tilt4, TILT4_PIN_STATE_HIGH );
        }
        else
        {
            log_printf( &logger, " Tilt switch OFF!\r\n\n" );
            tilt4_set_led_state( &tilt4, TILT4_PIN_STATE_LOW );
        }
        Delay_ms ( 500 );
    }
    
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Tilt4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
