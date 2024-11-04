\mainpage Main Page

---
# LED Driver 13 Click

> LED Driver 13 Click is a compact add-on board that simplifies the control of multiple LEDs. This board features the A80604-1, a 4-channel LED driver designed at a switching frequency of 400kHz that provides 150mA per channel from Allegro Microsystems. It is powered by an external power supply in the range of 6V to 18V, providing an output voltage of approximately 26V, which is used to power LEDs connected to LED channels. On the logical side, this board uses both 3V3 and 5V with mikroBUS™ power rails and communicates with the MCU via GPIO pins. In addition, the user is given the option of analog or digital LED dimming selection, using a PWM pin from the mikroBUS™ socket or via an onboard potentiometer/external PWM signal.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver13_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/led-driver-13-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2021.
- **Type**          : PWM type


# Software Support

We provide a library for the LED Driver 13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LED Driver 13 Click driver.

#### Standard key functions :

- `leddriver13_cfg_setup` Config Object Initialization function.
```c
void leddriver13_cfg_setup ( leddriver13_cfg_t *cfg );
```

- `leddriver13_init` Initialization function.
```c
err_t leddriver13_init ( leddriver13_t *ctx, leddriver13_cfg_t *cfg );
```

- `leddriver13_default_cfg` Click Default Configuration function.
```c
err_t leddriver13_default_cfg ( leddriver13_t *ctx );
```

#### Example key functions :

- `leddriver13_set_enable` LED Driver 13 set enable function.
```c
err_t leddriver13_set_enable ( leddriver13_t *ctx );
```

- `leddriver13_pwm_start` LED Driver 13 start PWM module.
```c
err_t leddriver13_pwm_start ( leddriver13_t *ctx );
```

- `leddriver13_set_duty_cycle` LED Driver 13 sets PWM duty cycle.
```c
err_t leddriver13_set_duty_cycle ( leddriver13_t *ctx, float duty_cycle );
```

## Example Description

> This library contains API for LED Driver 13 Click driver.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and executes the Click default configuration which
> starts the PWM module and sets the LEDs current to minimum.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver13_cfg_t leddriver13_cfg;  /**< Click config object. */

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
    leddriver13_cfg_setup( &leddriver13_cfg );
    LEDDRIVER13_MAP_MIKROBUS( leddriver13_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == leddriver13_init( &leddriver13, &leddriver13_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER13_ERROR == leddriver13_default_cfg ( &leddriver13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    
    leddriver13_set_duty_cycle ( &leddriver13, 0.01 );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the LED Driver 13 Click board™.
> The app controls the LEDs brightness by changing the PWM duty cycle.
> The PWM duty cycle percentage will be logged on the USB UART.

```c

 void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 1000.0;
    
    leddriver13_set_duty_cycle ( &leddriver13, duty );
    log_printf( &logger, "> Duty: %.1f%%\r\n", duty * 100 );
    Delay_ms ( 100 );
    
    if ( 30 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
} 

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
