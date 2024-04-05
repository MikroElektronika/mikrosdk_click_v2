\mainpage Main Page

---
# Buzz 3 click

> Buzz 3 Click is a compact add-on board that contains a sounder driver that produces higher volume with a lower current. This board features the PAM8904, 
a piezo-sounder driver with an integrated Multi-Mode charge pump boost converter from Diodes Incorporated. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buzz3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buzz-3-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : PWM type


# Software Support

We provide a library for the Buzz3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Buzz3 Click driver.

#### Standard key functions :

- `buzz3_cfg_setup` Config Object Initialization function.
```c
void buzz3_cfg_setup ( buzz3_cfg_t *cfg );
```

- `buzz3_init` Initialization function.
```c
err_t buzz3_init ( buzz3_t *ctx, buzz3_cfg_t *cfg );
```

- `buzz3_default_cfg` Click Default Configuration function.
```c
err_t buzz3_default_cfg ( buzz3_t *ctx );
```

#### Example key functions :

- `buzz3_pwm_start` This function starts the PWM module output.
```c
err_t buzz3_pwm_start ( buzz3_t *ctx );
```

- `buzz3_set_gain_operating_mode` The function set gain operating mode of the PAM8904 piezo sounder driver with integrated charge pump boost converter on Buzz 3 click board.
```c
err_t buzz3_set_gain_operating_mode ( buzz3_t *ctx, uint8_t op_mode );
```

- `buzz3_play_sound` This function plays sound on buzzer.
```c
void buzz3_play_sound ( buzz3_t *ctx, uint16_t freq, uint16_t duration );
```

## Example Description

> This example demonstrates the use of Buzz 3 click boards with PAM8904 for play the Imperial March.
PAM8904 is piezo-sounder driver with an integrated Multi-Mode charge pump boost converter from Diodes Incorporated. 

**The demo application is composed of two sections :**

### Application Init

> Initializes GPIO, set AN and RST pin as outputs, begins to write a log. 
> Initialization driver enables - GPIO and configures the appropriate MCU pin for 
> sound generation, also write log.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    buzz3_cfg_t buzz3_cfg;      /**< Click config object. */

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

    buzz3_cfg_setup( &buzz3_cfg );
    BUZZ3_MAP_MIKROBUS( buzz3_cfg, MIKROBUS_1 );
    err_t init_flag  = buzz3_init( &buzz3, &buzz3_cfg );
    if ( PWM_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    buzz3_default_cfg ( &buzz3 );
    buzz3_set_duty_cycle ( &buzz3, 0.0 );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, " Set the gain to x1  \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
    buzz3_pwm_start( &buzz3 );
    buzz3_set_gain_operating_mode( &buzz3, BUZZ3_OP_MODE_GAIN_x1 );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Plays the Imperial March melody. Also logs an appropriate message on the USB UART.

```c

void application_task ( void ) 
{
    log_printf( &logger, "   Play the music    \r\n" );
    buzz3_melody( );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
}

```

## Note

> The minimal PWM Clock frequency required for this example is the frequency of tone C6 - 1047 Hz. 
> So, in order to run this example and play all tones correctly, the user will need to decrease 
> the MCU's main clock frequency in MCU Settings for the certain architectures
> in order to get the required PWM clock frequency.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Buzz3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
