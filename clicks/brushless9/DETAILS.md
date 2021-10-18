---

# Brushless 9 click

Brushless 9 Click is a compact add-on board suitable for controlling BLDC motors with any MCU. This board features the TC78B027FTG, a 1-Hall sine-wave PWM controller for three-phase brushless DC motors from Toshiba Semiconductor. It simplifies the motor selection by using only one Hall sensor input that can be used with either a single Hall sensor motor or the more conventional 3 Hall sensor motors.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless-9-click-necto.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-9-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Dec 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushlesss9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushlesss9 Click driver.

#### Standard key functions :

- `brushless9_cfg_setup` Config Object Initialization function.
```c
void brushless9_cfg_setup ( brushless9_cfg_t *cfg );
```

- `brushless9_init` Initialization function.
```c
err_t brushless9_init ( brushless9_t *ctx, brushless9_cfg_t *cfg );
```

#### Example key functions :

- `brushless9_cfg_setup` function initializes click configuration structure to initial values.
```c
void brushless9_cfg_setup ( brushless9_cfg_t *cfg );
```

- `brushless9_init` function initializes all necessary peripherals.
```c
BRUSHLESS9_RETVAL brushless9_init ( brushless9_t *ctx, brushless9_cfg_t *cfg );
```

- `brushless9_default_cfg` function sets default configuration.
```c
void brushless9_default_cfg ( brushless9_t *ctx );
```

## Examples Description

> This example works with motors using adequate PWM pin.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and sets up adequate module
> configuration.
> Once in this state, the module is ready to
> operate.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless9_cfg_t brushless9_cfg;  /**< Click config object. */

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
    brushless9_cfg_setup( &brushless9_cfg );
    BRUSHLESS9_MAP_MIKROBUS( brushless9_cfg, MIKROBUS_1 );
    err_t init_flag  = brushless9_init( &brushless9, &brushless9_cfg );
    if ( init_flag == PWM_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    brushless9_set_dir( &brushless9, direction );
    brushless9_set_brk( &brushless9, 1 );

    brushless9_set_duty_cycle ( &brushless9, 0 );
    brushless9_pwm_start( &brushless9 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of Brushless 9 click board.
> Brushless 9 click communicates with the device via PWM driver in order to
> set adequate voltage level for connected motor.
> Current PWM settings being output are sent via logger.

```c

void application_task ( void )
{
    log_info( &logger, " Starting... " );
    brushless9_set_brk( &brushless9, 0 );
    for ( float duty = 0.1; duty < 1; duty += 0.1 )
    {
        Delay_ms( DUTY_CHANGE_DELAY );
        brushless9_set_duty_cycle ( &brushless9, duty );
        log_printf( &logger, "Duty: %u%%\r\n", ( uint16_t )ceil( duty * 100 ) );
    }

    for ( float duty = 0.9; duty >= 0; duty -= 0.1 )
    {
        Delay_ms( DUTY_CHANGE_DELAY );
        brushless9_set_duty_cycle ( &brushless9, duty );
        log_printf( &logger, "Duty: %u%%\r\n", ( uint16_t )ceil( duty * 100 ) );
    }

    Delay_ms( DUTY_CHANGE_DELAY );
    log_info( &logger, " Stopping... " );
    brushless9_set_duty_cycle ( &brushless9, 0 );
    brushless9_set_brk( &brushless9, 1 );
    Delay_ms( BREAK_DELAY );
    log_info( &logger, " Changing direction... " );
    direction = !direction;
    brushless9_set_dir( &brushless9, direction );
}

```

## Note

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless9

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
