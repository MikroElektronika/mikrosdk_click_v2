
---
# LED Driver 10 click

LED Driver 10 Click is a compact add-on board that simplifies the control of multiple LEDs. This board features the TLC59283, a 16-channel, constant-current sink light-emitting diode (LED) driver with pre-charge FET from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-driver-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the LEDDriver10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LEDDriver10 Click driver.

#### Standard key functions :

- `leddriver10_cfg_setup` This function initializes click configuration structure to initial values.
```c
void leddriver10_cfg_setup ( leddriver10_cfg_t *cfg );
```

- `leddriver10_init` This function initializes all necessary pins and peripherals used for this click board.
```c
err_t leddriver10_init ( leddriver10_t *ctx, leddriver10_cfg_t *cfg );
```

- `leddriver10_pwm_start` This function starts the PWM module output.
```c
err_t leddriver10_pwm_start ( leddriver10_t *ctx );
```

#### Example key functions :

- `leddriver10_set_channels` This function sets all channels to desired value by using SPI serial interface.
```c
err_t leddriver10_set_channels ( leddriver10_t *ctx, uint16_t ch_mask );
```

- `leddriver10_read_channels` This function reads the current state of all channels by using SPI serial interface.
```c
err_t leddriver10_read_channels ( leddriver10_t *ctx, uint16_t *ch_mask );
```

- `leddriver10_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t leddriver10_set_duty_cycle ( leddriver10_t *ctx, float duty_cycle );
```

## Example Description

> This example demonstrates the use of LED Driver 10 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, starts the PWM module and enables all channels.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    leddriver10_cfg_t leddriver10_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    leddriver10_cfg_setup( &leddriver10_cfg );
    LEDDRIVER10_MAP_MIKROBUS( leddriver10_cfg, MIKROBUS_1 );
    err_t init_flag  = leddriver10_init( &leddriver10, &leddriver10_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    leddriver10_pwm_start( &leddriver10 );    
    leddriver10_set_channels ( &leddriver10, LEDDRIVER10_ENABLE_ALL_CH );
    log_printf( &logger, " All channels enabled!\r\n" );
    log_printf( &logger, " Dimming the LEDs light...\r\n" );
}

```

### Application Task

> Controls the LEDs brightness by changing the PWM duty cycle.
> The PWM duty cycle percentage will be logged on the USB UART.

```c

void application_task ( void )
{
    static int16_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    leddriver10_set_duty_cycle ( &leddriver10, duty );
    log_printf( &logger, "> Duty: %u%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms( 500 );
    
    if ( 10 == duty_cnt ) 
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
- Click.LEDDriver10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
