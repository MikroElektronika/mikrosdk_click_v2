
---
# Button ALARM Click

Button ALARM Click is a very interesting interactive gadget on a Click board™. It is an integrated capacitive touch sensor display in the form of a button. By utilizing an advanced capacitive touch sensing technology, the CTHS15CIC05ALARM sensor can successfully replace the traditional mechanical button, allowing very simplified yet reliable user interfaces to be developed. Besides the touch detection, this sensor also features a green power symbol icon with backlight, which makes the Click board™ very useful for building various stylized and visually appealing interfaces.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/button_alarm_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/button-alarm-click)

---


#### Click library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : GPIO type


# Software Support

We provide a library for the ButtonAlarm Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ButtonAlarm Click driver.

#### Standard key functions :

- `buttonalarm_cfg_setup` Config Object Initialization function.
```c
void buttonalarm_cfg_setup ( buttonalarm_cfg_t *cfg );
```

- `buttonalarm_init` Initialization function.
```c
err_t buttonalarm_init ( buttonalarm_t *ctx, buttonalarm_cfg_t *cfg );
```

#### Example key functions :

- `buttonalarm_pwm_stop` This function stops the PWM moudle output.
```c
err_t buttonalarm_pwm_stop ( buttonalarm_t *ctx );
```

- `buttonalarm_pwm_start` This function starts the PWM moudle output.
```c
err_t buttonalarm_pwm_start ( buttonalarm_t *ctx );
```

- `buttonalarm_get_button_state` This function reads the digital signal from the INT pin which tells us whether the button has been pressed or not.
```c
uint8_t buttonalarm_get_button_state ( buttonalarm_t *ctx );
```

## Example Description

> This example showcases how to initialize and use the whole family of Button clicks. 
> One library is used for every single one of them. They are simple touch detectors that send 
> a pressed/released signal and receive a PWM output which controls the backlight on the button.

**The demo application is composed of two sections :**

### Application Init

> This function initializes and configures the logger and Click modules.

```c

void application_init ( void )  
{
    log_cfg_t log_cfg;                 /**< Logger config object. */
    buttonalarm_cfg_t buttonalarm_cfg;   /**< Click config object. */

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

    buttonalarm_cfg_setup( &buttonalarm_cfg );
    BUTTONALARM_MAP_MIKROBUS( buttonalarm_cfg, MIKROBUS_1 );
    err_t init_flag  = buttonalarm_init( &buttonalarm, &buttonalarm_cfg );
    if ( PWM_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 500 );
    
    buttonalarm_set_duty_cycle ( &buttonalarm, 0.1 );
    buttonalarm_pwm_start( &buttonalarm );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example first increases the backlight on the button and then decreases the intensity of the
> backlight. When the button is touched,  
> reports the event in the console using UART communication.

```c

void application_task ( void ) 
{
    static float duty_cycle;
    static uint8_t button_state;
    static uint8_t button_state_old;

    button_state = buttonalarm_get_button_state( &buttonalarm );
    
    if ( button_state && ( button_state != button_state_old ) ) 
    {
        log_printf( &logger, " <-- Button pressed --> \r\n" );
        for ( uint8_t n_cnt = 1; n_cnt <= 100; n_cnt++  )
        {
            duty_cycle = ( float ) n_cnt ;
            duty_cycle /= 100;
            buttonalarm_set_duty_cycle( &buttonalarm, duty_cycle );
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
            buttonalarm_set_duty_cycle( &buttonalarm,  duty_cycle );
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
- Click.ButtonAlarm

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
