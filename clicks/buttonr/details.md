
---
# Button R Click

Button R Click is the simplest solution for adding a single pushbutton to your design. The button itself is transparent, 6.8mm in diameter and has a red LED backlight. When pressed, it sends an interrupt signal to the target board microcontroller. The backlight LED is controlled separately through the mikroBUS PWM pin, so you can program all kinds of patterns (varying level of light intensity or rate of blinking on subsequent button presses). The board can use either a 3.3V or a 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/button_r_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/button-r-click)

---


#### Click library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the ButtonR Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ButtonR Click driver.

#### Standard key functions :

- `buttonr_cfg_setup` Config Object Initialization function.
```c
void buttonr_cfg_setup ( buttonr_cfg_t *cfg );
```

- `buttonr_init` Initialization function.
```c
err_t buttonr_init ( buttonr_t *ctx, buttonr_cfg_t *cfg );
```

#### Example key functions :

- `buttonr_pwm_stop` This function stops the PWM moudle output.
```c
err_t buttonr_pwm_stop ( buttonr_t *ctx );
```

- `buttonr_pwm_start` This function starts the PWM moudle output.
```c
err_t buttonr_pwm_start ( buttonr_t *ctx );
```

- `buttonr_get_button_state`  This function reads the digital signal from the INT pin which tells us whether the button has been pressed or not.
```c
uint8_t buttonr_get_button_state ( buttonr_t *ctx );
```

## Example Description

>  This library contains API for Button R Click driver. 
>  One library is used for every single one of them.
>  They are simple touch detectors that send a pressed/released 
>  signal and receive a PWM output which controls the backlight on the button.

**The demo application is composed of two sections :**

### Application Init

> This function initializes and configures the logger and Click modules.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    buttonr_cfg_t buttonr_cfg;  /**< Click config object. */

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

    buttonr_cfg_setup( &buttonr_cfg );
    BUTTONR_MAP_MIKROBUS( buttonr_cfg, MIKROBUS_1 );
    err_t init_flag  = buttonr_init( &buttonr, &buttonr_cfg );
    if ( PWM_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 500 );
    
    buttonr_set_duty_cycle ( &buttonr, 0.0 );
    buttonr_pwm_start( &buttonr );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example first increases the backlight on the button and then decreases the intensity of 
> backlight. When the button is pressed,
> reports the event in the console using UART communication.

```c

void application_task ( void ) 
{
    static float duty_cycle;
    static uint8_t button_state;
    static uint8_t button_state_old;

    button_state = buttonr_get_button_state( &buttonr );
    
    if ( button_state && ( button_state != button_state_old ) ) 
    {
        log_printf( &logger, " <-- Button pressed --> \r\n" );
        for ( uint8_t n_cnt = 1; n_cnt <= 100; n_cnt++  )
        {
            duty_cycle = ( float ) n_cnt ;
            duty_cycle /= 100;
            buttonr_set_duty_cycle( &buttonr, duty_cycle );
            Delay_ms ( 10 );
        }
        button_state_old = button_state;
    } 
    else if ( !button_state && ( button_state != button_state_old ) ) 
    {
        for ( uint8_t n_cnt = 100; n_cnt > 0; n_cnt-- )
        {
            duty_cycle = ( float ) n_cnt ;
            duty_cycle /= 100;
            buttonr_set_duty_cycle( &buttonr,  duty_cycle );
            Delay_ms ( 10 );
        }
        button_state_old = button_state;
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ButtonR

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
