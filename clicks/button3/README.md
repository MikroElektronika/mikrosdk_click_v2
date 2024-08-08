\mainpage Main Page

---
# Button 3 click

> Button 3 Click is a compact add-on board for precise and reliable tactile input detection. This board features three TL3215 series tactile switches from E-Switch, known for their high reliability and consistent performance. Each switch has a 2mm actuator, 160gf actuation force, and a silver contact material for excellent conductivity and durability. The integrated LED provides clear visual feedback, and the board supports the new Click Snap feature, allowing the main sensor area to become movable by breaking the PCB for flexible implementation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/button3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/button-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Button 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Button 3 Click driver.

#### Standard key functions :

- `button3_cfg_setup` Config Object Initialization function.
```c
void button3_cfg_setup ( button3_cfg_t *cfg );
```

- `button3_init` Initialization function.
```c
err_t button3_init ( button3_t *ctx, button3_cfg_t *cfg );
```

- `button3_default_cfg` Click Default Configuration function.
```c
err_t button3_default_cfg ( button3_t *ctx );
```

#### Example key functions :

- `button3_toggle_red_led` This function toggles the red button LED by toggling the RK pin logic state.
```c
err_t button3_toggle_red_led ( button3_t *ctx );
```

- `button3_toggle_green_led` This function toggles the green button LED by toggling the GK pin logic state.
```c
err_t button3_toggle_green_led ( button3_t *ctx );
```

- `button3_toggle_blue_led` This function toggles the blue button LED by toggling the BK pin logic state.
```c
err_t button3_toggle_blue_led ( button3_t *ctx );
```

## Example Description

> This example demonstrates the use of Button 3 click board by toggling a button LED and its switch state on a button press.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    button3_cfg_t button3_cfg;  /**< Click config object. */

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
    button3_cfg_setup( &button3_cfg );
    BUTTON3_MAP_MIKROBUS( button3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == button3_init( &button3, &button3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUTTON3_ERROR == button3_default_cfg ( &button3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf ( &logger, " Press button to change switch state\r\n\n" );
    log_printf ( &logger, " RED SWITCH OFF\r\n\n" );
    log_printf ( &logger, " GREEN SWITCH OFF\r\n\n" );
    log_printf ( &logger, " BLUE SWITCH OFF\r\n\n" );
}

```

### Application Task

> Toggles a button LED and its switch state on a button press and displays the state on the USB UART.

```c
void application_task ( void )
{
    static uint8_t red_switch_state = BUTTON3_SWITCH_OFF;
    static uint8_t green_switch_state = BUTTON3_SWITCH_OFF;
    static uint8_t blue_switch_state = BUTTON3_SWITCH_OFF;
    uint8_t switch_state = BUTTON3_SWITCH_OFF;

    if ( BUTTON3_PIN_STATE_LOW == button3_get_int_pin ( &button3 ) )
    {
        if ( ( BUTTON3_OK == button3_get_red_button ( &button3, &switch_state ) ) && 
             ( BUTTON3_BUTTON_PRESSED == switch_state ) )
        {
            button3_toggle_red_led ( &button3 );
            red_switch_state ^= BUTTON3_SWITCH_ON;
            if ( BUTTON3_SWITCH_ON == red_switch_state )
            {
                log_printf ( &logger, " RED SWITCH ON\r\n\n" );
            }
            else
            {
                log_printf ( &logger, " RED SWITCH OFF\r\n\n" );
            }
        }
        if ( ( BUTTON3_OK == button3_get_green_button ( &button3, &switch_state ) ) && 
             ( BUTTON3_BUTTON_PRESSED == switch_state ) )
        {
            button3_toggle_green_led ( &button3 );
            green_switch_state ^= BUTTON3_SWITCH_ON;
            if ( BUTTON3_SWITCH_ON == green_switch_state )
            {
                log_printf ( &logger, " GREEN SWITCH ON\r\n\n" );
            }
            else
            {
                log_printf ( &logger, " GREEN SWITCH OFF\r\n\n" );
            }
        }
        if ( ( BUTTON3_OK == button3_get_blue_button ( &button3, &switch_state ) ) && 
             ( BUTTON3_BUTTON_PRESSED == switch_state ) )
        {
            button3_toggle_blue_led ( &button3 );
            blue_switch_state ^= BUTTON3_SWITCH_ON;
            if ( BUTTON3_SWITCH_ON == blue_switch_state )
            {
                log_printf ( &logger, " BLUE SWITCH ON\r\n\n" );
            }
            else
            {
                log_printf ( &logger, " BLUE SWITCH OFF\r\n\n" );
            }
        }
        Delay_ms ( 100 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Button3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
