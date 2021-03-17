\mainpage Main Page

---

# Brushless 8  click

> Brushless 8 Click is a compact add-on board suitable for controlling BLDC motors with any MCU. This board features the TC78B042FTG, a sine-wave PWM drive three-phase full-wave brushless motor controller from Toshiba Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless8_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/brushless-8-click>)

---

#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Dec 2020.
- **Type**          : I2C type

# Software Support

We provide a library for the Brushless8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void brushless8_cfg_setup ( brushless8_cfg_t *cfg );

- Initialization function.
> BRUSHLESS8_RETVAL brushless8_init ( brushless8_t *ctx, brushless8_cfg_t *cfg );

- Click Default Configuration function.
> void brushless8_default_cfg ( brushless8_t *ctx );


#### Example key functions :

- `brushless8_cfg_setup` function initializes click configuration structure to initial values.
```c
brushless8_cfg_setup( &brushless8_cfg );
```

- `brushless8_init` function initializes all necessary pins and peripherals used for this click board.
```c
BRUSHLESS8_RETVAL init_flag = brushless8_init( &brushless8, &brushless8_cfg );
```

- `brushless8_default_cfg` function executes a default configuration of Brushless 8 click board.
```c
brushless8_default_cfg ( &brushless8 );
```

## Examples Description

> This application is a schowcase of controlling speed and direction of brushless motor with hall sesnor.

**The demo application is composed of two sections :**

### Application Init

> Initializes the click board to appropriate settings based on selected mode.
> Initialization settings are sent through I2C bus and the motor itself is
> controlled via PWM or DAC over I2C.
> * Modes:
>     - BRUSHLESS8_PWM
>     - BRUSHLESS8_DAC

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless8_cfg_t brushless8_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "Application Init" );

    // Click initialization.

    brushless8_cfg_setup( &brushless8_cfg );
    // Select desired mode.
    brushless8_cfg.ctrl_mod = BRUSHLESS8_MODE;
    BRUSHLESS8_MAP_MIKROBUS( brushless8_cfg, MIKROBUS_1 );

    BRUSHLESS8_RETVAL init_flag = brushless8_init( &brushless8, &brushless8_cfg );
    if ( BRUSHLESS8_OK != init_flag )
    {
        log_error( &logger, "Application Init Error" );
        log_info( &logger, "Please, run program again..." );

        for ( ; ; );
    }

    brushless8_default_cfg ( &brushless8 );

    if ( BRUSHLESS8_PWM == brushless8.ctrl_mod )
    {
        brushless8_set_dac_vout( &brushless8, BRUSHLESS8_DAC_REG_CHN_A_DVSP, 0 );
        brushless8_set_duty_cycle( &brushless8, 0.1 );
        brushless8_pwm_start( &brushless8 );

        Delay_ms( 3000 );
    }
    else if ( BRUSHLESS8_DAC == brushless8.ctrl_mod )
    {
        brushless8_pwm_stop( &brushless8 );
        brushless8_set_dac_vout( &brushless8, BRUSHLESS8_DAC_REG_CHN_A_DVSP, 100 );

        Delay_ms( 3000 );
    }

    log_info( &logger, "Application Task" );
    log_printf( &logger, "------------------------------\r\n" );
}

```

### Application Task

> This example demonstrates the use of Brushless 8 click board.
> Brushless 8 click communicates with the device via I2C driver in order to
> set adequate voltage level for connected motor.
> Current PWM/DAC settings being output are sent via logger.

```c

void application_task ( void )
{
    if ( BRUSHLESS8_PWM == brushless8.ctrl_mod )
    {
        for ( float duty = 0.1; duty < 1; duty += 0.1 )
        {
            Delay_ms( COMM_DELAY );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_DIS );
            brushless8_set_duty_cycle( &brushless8, duty );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_EN );
            log_info( &logger, "Duty: %u%%", ( uint16_t )ceil( duty * 100 ) );

            float adc_vout;
            brushless8_read_an_voltage( &brushless8, &adc_vout );
            log_info( &logger, "ADC [ V ]: %.2f", adc_vout );

            log_printf( &logger, "------------------------------\r\n" );
        }

        for ( float duty = 0.9; duty >= 0; duty -= 0.1 )
        {
            Delay_ms( COMM_DELAY );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_DIS );
            brushless8_set_duty_cycle( &brushless8, duty );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_EN );
            log_info( &logger, "Duty: %u%%", ( uint16_t )ceil( duty * 100 ) );

            float adc_vout;
            brushless8_read_an_voltage( &brushless8, &adc_vout );
            log_info( &logger, "ADC [ V ]: %.2f", adc_vout );

            log_printf( &logger, "------------------------------\r\n" );
        }

        Delay_ms( COMM_DELAY );
        brushless8_pwm_stop( &brushless8 );
        Delay_ms( COMM_DELAY );
        brushless8_pwm_start( &brushless8 );
    } else if ( BRUSHLESS8_DAC == brushless8.ctrl_mod ) {
        for ( int16_t dsvp = 200; dsvp <= 5000; dsvp += ( ( 5000 - 200 ) / 10 ) )
        {
            Delay_ms( COMM_DELAY );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_EN );
            brushless8_set_dac_vout( &brushless8, BRUSHLESS8_DAC_REG_CHN_A_DVSP, ( uint16_t )dsvp );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_EN );
            log_info( &logger, "DSVP [ mV ]: %d", dsvp );

            float adc_vout;
            brushless8_read_an_voltage( &brushless8, &adc_vout );
            log_info( &logger, "ADC [ V ]: %.2f", adc_vout );

            log_printf( &logger, "------------------------------\r\n" );
        }

        for ( int16_t dsvp = 5000; dsvp >= 200; dsvp -= ( ( 5000 - 200 ) / 10 ) )
        {
            Delay_ms( COMM_DELAY );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_EN );
            brushless8_set_dac_vout( &brushless8, BRUSHLESS8_DAC_REG_CHN_A_DVSP, ( uint16_t )dsvp );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_EN );
            log_info( &logger, "DSVP [ mV ]: %d", dsvp );

            float adc_vout;
            brushless8_read_an_voltage( &brushless8, &adc_vout );
            log_info( &logger, "ADC [ V ]: %.2f", adc_vout );

            log_printf( &logger, "------------------------------\r\n" );
        }
    } else {
        log_error( &logger, "Application Task Error" );
        log_info( &logger, "Please, run program again..." );

        for ( ; ; );
    }
}

```

## Note

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
