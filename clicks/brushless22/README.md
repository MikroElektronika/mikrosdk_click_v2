\mainpage Main Page

---
# Brushless 22 Click

> Brushless 22 Click is a compact add-on board suitable for controlling brushless DC (BLDC) motors with any MCU. This board features the MTD6508, a 3-phase full-wave sensorless driver for BLDC motors from Microchip Technology. It features 180° sinusoidal drive, high torque output, and silent drive, rated for an operating voltage range including both mikroBUS™ power rails, and comes with speed control achieved through pulse-width modulation (PWM). Besides, it features several diagnostic circuits and drive-control functions such as motor lock protection, overcurrent limitation, and thermal shutdown protection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless22_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/brushless-22-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless 22 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 22 Click driver.

#### Standard key functions :

- `brushless22_cfg_setup` Config Object Initialization function.
```c
void brushless22_cfg_setup ( brushless22_cfg_t *cfg );
```

- `brushless22_init` Initialization function.
```c
err_t brushless22_init ( brushless22_t *ctx, brushless22_cfg_t *cfg );
```

- `brushless22_default_cfg` Click Default Configuration function.
```c
err_t brushless22_default_cfg ( brushless22_t *ctx );
```

#### Example key functions :

- `brushless22_set_slew_rate_resistance` This function sets the slew rate resistance by configuring the onboard digital potentiometer.
```c
err_t brushless22_set_slew_rate_resistance ( brushless22_t *ctx, uint16_t res_ohm );
```

- `brushless22_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless22_set_duty_cycle ( brushless22_t *ctx, float duty_cycle );
```

- `brushless22_switch_direction` This function switches the direction by toggling the DIR pin state.
```c
void brushless22_switch_direction ( brushless22_t *ctx );
```

## Example Description

> This example demonstrates the use of the Brushless 22 Click board by driving the motor in both directions at different speeds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless22_cfg_t brushless22_cfg;  /**< Click config object. */

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
    brushless22_cfg_setup( &brushless22_cfg );
    BRUSHLESS22_MAP_MIKROBUS( brushless22_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless22_init( &brushless22, &brushless22_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS22_ERROR == brushless22_default_cfg ( &brushless22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every 500ms.
The duty cycle ranges from 0% to 100%. At the minimal speed, the motor switches direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless22_set_duty_cycle ( &brushless22, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        log_printf( &logger, " Switch direction\r\n\n" );
        brushless22_switch_direction ( &brushless22 );
    }
    duty_cnt += duty_inc;

    Delay_ms ( 500 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless22

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
