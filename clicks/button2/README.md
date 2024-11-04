\mainpage Main Page

---
# Button 2 Click

> Button 2 Click is a compact add-on board designed for simple and efficient tactile input detection. This board features the TL3215AF160BQ, a TL3215 series of tactile switches from E-Switch, featuring high reliability and precise operation. The switch has a 2mm actuator, 160gf actuation force, silver contact material, and a lifespan of 1,000,000 cycles, while the integrated blue LED provides visual feedback. The board supports the new Click Snap feature, allowing easy detachment of the sensor area for flexible use.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/button2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/button-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the Button 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Button 2 Click driver.

#### Standard key functions :

- `button2_cfg_setup` Config Object Initialization function.
```c
void button2_cfg_setup ( button2_cfg_t *cfg );
```

- `button2_init` Initialization function.
```c
err_t button2_init ( button2_t *ctx, button2_cfg_t *cfg );
```

#### Example key functions :

- `button2_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t button2_get_int_pin ( button2_t *ctx );
```

- `button2_toggle_led` This function toggles the button LED state by toggling the LED pin logic state.
```c
void button2_toggle_led ( button2_t *ctx );
```

- `button2_enable_led` This function enables button LED by setting the LED pin to the high logic state.
```c
void button2_enable_led ( button2_t *ctx );
```

## Example Description

> This example demonstrates the use of Button 2 Click board by toggling the button LED and switch state on button press.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    button2_cfg_t button2_cfg;  /**< Click config object. */

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
    button2_cfg_setup( &button2_cfg );
    BUTTON2_MAP_MIKROBUS( button2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == button2_init( &button2, &button2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf ( &logger, " Press button to change switch state\r\n\n" );
    log_printf ( &logger, " SWITCH OFF\r\n\n" );
}

```

### Application Task

> Toggles the button LED and switch state on button press and displays the state on the USB UART.

```c
void application_task ( void )
{
    static uint8_t switch_state = BUTTON2_SWITCH_OFF;
    
    if ( BUTTON2_BUTTON_PRESSED == button2_get_int_pin ( &button2 ) )
    {
        button2_toggle_led ( &button2 );
        switch_state ^= BUTTON2_SWITCH_ON;
        if ( BUTTON2_SWITCH_ON == switch_state )
        {
            log_printf ( &logger, " SWITCH ON\r\n\n" );
        }
        else
        {
            log_printf ( &logger, " SWITCH OFF\r\n\n" );
        }
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Button2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
