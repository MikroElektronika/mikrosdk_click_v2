
---
# BUZZ 2 click

BUZZ 2 click carries the CMT-8540S-SMT magnetic buzzer transducer. The buzzer’s resonant frequency is 4kHz. The click is designed to run on either 3.3V or 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buzz2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buzz-2-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : PWM type


# Software Support

We provide a library for the Buzz2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Buzz2 Click driver.

#### Standard key functions :

- `buzz2_cfg_setup` Config Object Initialization function.
```c
void buzz2_cfg_setup ( buzz2_cfg_t *cfg );
```

- `buzz2_init` Initialization function.
```c
BUZZ2_RETVAL buzz2_init ( buzz2_t *ctx, buzz2_cfg_t *cfg );
```

#### Example key functions :

- `buzz2_set_duty_cycle` BUZZ 2 sets PWM duty cycle.
```c
 err_t buzz2_set_duty_cycle ( buzz2_t *ctx, float duty_cycle );
```

- `buzz2_play_sound` Play sound function.
```c
void buzz2_play_sound ( buzz2_t *ctx, uint16_t freq, uint16_t level, uint16_t duration );
```

- `buzz2_pwm_start` BUZZ 2 start PWM module.
```c
err_t buzz2_pwm_start ( buzz2_t *ctx );
```

## Example Description

> This example demonstrates the use of Buzz 2 click boards.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buzz2_cfg_t buzz2_cfg;  /**< Click config object. */

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

    buzz2_cfg_setup( &buzz2_cfg );
    BUZZ2_MAP_MIKROBUS( buzz2_cfg, MIKROBUS_1 );
    err_t init_flag  = buzz2_init( &buzz2, &buzz2_cfg );
    if ( init_flag == PWM_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    buzz2_default_cfg ( &buzz2 );

    buzz2_set_duty_cycle ( &buzz2, 0.0 );
    buzz2_pwm_start( &buzz2 );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Plays the Imperial March melody. Also logs an appropriate message on the USB UART.

```c

void application_task ( void )
{
    log_printf( &logger, "Playing the Imperial March melody ...\r\n" );
    imperial_march( ); 
    Delay_ms( 10000 );
}

```

## Note

> The minimal PWM Clock frequency required for this example is the frequency of tone C6 - 1047 Hz. 
  So, in order to run this example and play all tones correctly, the user will need to decrease 
  the MCU's main clock frequency in MCU Settings for the certain architectures
  in order to get the required PWM clock frequency.
  

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Buzz2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
