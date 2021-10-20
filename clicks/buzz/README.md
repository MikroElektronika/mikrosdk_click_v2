\mainpage Main Page

---
# BUZZ click

BUZZ Click is an accessory board in mikroBus™ form factor. Board features a piezo speaker capable of emitting audio signals.Buzzer’s resonant frequency is 3.8kHz (where you can expect it’s best performance).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buzz_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buzz-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : PWM type


# Software Support

We provide a library for the BUZZ Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BUZZ Click driver.

#### Standard key functions :

- `buzz_cfg_setup` Config Object Initialization function.
```c
void buzz_cfg_setup ( buzz_cfg_t *cfg );
```

- `buzz_init` Initialization function.
```c
BUZZ_RETVAL buzz_init ( buzz_t *ctx, buzz_cfg_t *cfg );
```

- `buzz_default_cfg` Click Default Configuration function.
```c
void buzz_default_cfg ( buzz_t *ctx );
```

#### Example key functions :

- `buzz_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ]).
```c
err_t buzz_set_duty_cycle ( buzz_t *ctx, float duty_cycle );
```

- `buzz_pwm_stop` This function stops the PWM moudle output.
```c
err_t buzz_pwm_stop ( buzz_t *ctx );
```

- `buzz_pwm_start` This function starts the PWM moudle output.
```c
err_t buzz_pwm_start ( buzz_t *ctx );
```

- `buzz_play_sound` This function plays sound on buzzer.
```c
void buzz_play_sound ( buzz_t *ctx, uint16_t freq, uint16_t level, uint16_t duration );
```

## Example Description

> This example demonstrates the use of Buzz click boards.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    buzz_cfg_t buzz_cfg;  /**< Click config object. */

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

    buzz_cfg_setup( &buzz_cfg );
    BUZZ_MAP_MIKROBUS( buzz_cfg, MIKROBUS_1 );
    err_t init_flag  = buzz_init( &buzz, &buzz_cfg );
    if ( init_flag == PWM_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    buzz_set_duty_cycle ( &buzz, 0.0 );
    buzz_pwm_start( &buzz );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Plays the Imperial March melody. Also logs an appropriate message on the USB UART.

```c

void application_task ( void ) {
    log_printf( &logger, "Playing the Imperial March melody ...\r\n" );
    imperial_march( ); 
    Delay_ms( 10000 );
}

```

## Note

> The minimal PWM Clock frequency required for this example is the frequency of tone C6 - 1047 Hz. So, in order to run this example and play all tones correctly, the user will need to decrease the MCU's main clock frequency in MCU Settings for the certain architectures in order to get the required PWM clock frequency.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BUZZ

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
