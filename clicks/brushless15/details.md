
---
# Brushless 15 Click

> Brushless 15 Click is a compact add-on board suitable for controlling BLDC motors with any MCU. This board features the TB9061AFNG, an automotive pre-driver that incorporates a sensorless controller for driving a 3-phase full-wave brushless DC motor from Toshiba Semiconductor. The TB9061AFNG achieves 120° rectangular wave motor control by using an input signal line that measures the induced voltage of the motors and three-phase motor output without using Hall sensors, rated for an operating voltage range of 6 to 18V. Motor rotation can be controlled by either the DC or the PWM input signal. Besides, it features several diagnostic circuits and drive-control functions such as motor lock detection, step-out detection, over-current/over-temperature detection, and many more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless15_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/brushless-15-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless 15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 15 Click driver.

#### Standard key functions :

- `brushless15_cfg_setup` Config Object Initialization function.
```c
void brushless15_cfg_setup ( brushless15_cfg_t *cfg );
```

- `brushless15_init` Initialization function.
```c
err_t brushless15_init ( brushless15_t *ctx, brushless15_cfg_t *cfg );
```

- `brushless15_default_cfg` Click Default Configuration function.
```c
err_t brushless15_default_cfg ( brushless15_t *ctx );
```

#### Example key functions :

- `brushless15_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless15_set_duty_cycle ( brushless15_t *ctx, float duty_cycle );
```

- `brushless15_enable_device` This function enables the device by setting the EN pin to low logic state.
```c
void brushless15_enable_device ( brushless15_t *ctx );
```

- `brushless15_switch_direction` This function switches the direction by toggling the DIR pin state.
```c
void brushless15_switch_direction ( brushless15_t *ctx );
```

## Example Description

> This example demonstrates the use of the Brushless 15 Click board by driving the motor in both directions at different speeds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless15_cfg_t brushless15_cfg;  /**< Click config object. */

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
    brushless15_cfg_setup( &brushless15_cfg );
    BRUSHLESS15_MAP_MIKROBUS( brushless15_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless15_init( &brushless15, &brushless15_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS15_ERROR == brushless15_default_cfg ( &brushless15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Controls the motor speed by changing the PWM duty cycle once per second.
> The duty cycle ranges from 20% to 80%. At the minimal speed, the motor switches direction.
> Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 2;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless15_set_duty_cycle ( &brushless15, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 1000 );
    duty_cnt += duty_inc;
    if ( 8 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 1 == duty_cnt ) 
    {
        duty_inc = 1;
        duty_cnt = 2;
        log_printf( &logger, " Switch direction\r\n\n" );
        brushless15_switch_direction ( &brushless15 );
    }
}
```

## Note

> The maximal PWM Clock frequency for this Click board is 1 kHz. 
> So, depending on the selected setup the user will need to lower the MCU's main clock frequency 
> in the setup in order to get the PWM clock frequency down to 1 kHz.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
