\mainpage Main Page

---
# Button Power click

Button Power Click is a very interesting interactive gadget on a Click board™. It is an integrated capacitive touch sensor display in the form of a button. By utilizing an advanced capacitive touch sensing technology, the CTHS15CIC05ONOFF sensor can successfully replace the traditional mechanical button, allowing very simplified yet reliable user interfaces to be developed. Besides the touch detection, this sensor also features a green power symbol icon with backlight, which makes the Click board™ very useful for building various stylized and visually appealing interfaces.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/button_power_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/button-power-click)

---


#### Click library

- **Author**        : Nikola Peric
- **Date**          : Jan 2022.
- **Type**          : GPIO type


# Software Support

We provide a library for the ButtonPower Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ButtonPower Click driver.

#### Standard key functions :

- `buttonpower_cfg_setup` Config Object Initialization function.
```c
void buttonpower_cfg_setup ( buttonpower_cfg_t *cfg );
```

- `buttonpower_init` Initialization function.
```c
err_t buttonpower_init ( buttonpower_t *ctx, buttonpower_cfg_t *cfg );
```

#### Example key functions :

- `buttonpower_pwm_stop` This function stops the PWM moudle output.
```c
err_t buttonpower_pwm_stop ( buttonpower_t *ctx );
```

- `buttonpower_pwm_start` This function starts the PWM moudle output.
```c
err_t buttonpower_pwm_start ( buttonpower_t *ctx );
```

- `buttonpower_get_button_state` This function reads the digital signal from the INT pin which tells us whether the button has been pressed or not.
```c
uint8_t buttonpower_get_button_state ( buttonpower_t *ctx );
```

## Example Description

> This example showcases how to initialize and use the whole family of Button clicks. One library is > used for every single one of them. They are simple touch detectors which send a pressed/released 
> signal and receive a PWM output which controls the backlight on the button.

**The demo application is composed of two sections :**

### Application Init

> This function initializes and configures the logger and click modules.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;                   /**< Logger config object. */
    buttonpower_cfg_t buttonpower_cfg;   /**< Click config object. */

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

    buttonpower_cfg_setup( &buttonpower_cfg );
    BUTTONPOWER_MAP_MIKROBUS( buttonpower_cfg, MIKROBUS_1 );
    err_t init_flag  = buttonpower_init( &buttonpower, &buttonpower_cfg );
    if ( PWM_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 500 );
    
    buttonpower_pwm_start( &buttonpower );
    buttonpower_set_duty_cycle ( &buttonpower, 0.1 );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example first increases the backlight on the button and then decreases the intensity of the  > backlight. When the button is touched,
> reports the event in the console using UART communication.

```c

void application_task ( void ) 
{
    static float duty_cycle;
    static uint8_t button_state;
    static uint8_t button_state_old;

    button_state = buttonpower_get_button_state( &buttonpower );
    
    if ( button_state && ( button_state != button_state_old ) ) 
    {
        log_printf( &logger, " <-- Button pressed --> \r\n " );
        for ( uint8_t n_cnt = 1; n_cnt <= 100; n_cnt++ )
        {
            duty_cycle = ( float ) n_cnt ;
            duty_cycle /= 100;
            buttonpower_set_duty_cycle( &buttonpower, duty_cycle );
            Delay_ms( 10 );
        }
        button_state_old = button_state;
    } 
    else if ( !button_state && ( button_state != button_state_old ) ) 
    {
        for ( uint8_t n_cnt = 100; n_cnt > 0; n_cnt-- )
        {
            duty_cycle = ( float ) n_cnt ;
            duty_cycle /= 100;
            buttonpower_set_duty_cycle( &buttonpower, duty_cycle );
            Delay_ms( 10 );
        }
        button_state_old = button_state;
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ButtonPower

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
