
---
# Brushless 17 Click

> Brushless 17 Click is a compact add-on board suitable for controlling brushless DC (BLDC) motors with any MCU. This board features the L6229Q, DMOS fully integrated three-phase BLDC motor driver with overcurrent protection from STMicroelectronics. This motor driver combines isolated DMOS power transistors with CMOS and bipolar circuits on the same chip, realized in BCD (Bipolar-CMOS-DMOS) multipower technology. It includes all the circuitry for a three-phase BLDC motor drive, including a three-phase DMOS bridge, a constant off-time PWM current controller, and the decoding logic for single-ended hall sensors that generate the required sequence for the power stage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless17_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/brushless-17-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 17 Click driver.

#### Standard key functions :

- `brushless17_cfg_setup` Config Object Initialization function.
```c
void brushless17_cfg_setup ( brushless17_cfg_t *cfg );
```

- `brushless17_init` Initialization function.
```c
err_t brushless17_init ( brushless17_t *ctx, brushless17_cfg_t *cfg );
```

- `brushless17_default_cfg` Click Default Configuration function.
```c
err_t brushless17_default_cfg ( brushless17_t *ctx );
```

#### Example key functions :

- `brushless17_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless17_set_duty_cycle ( brushless17_t *ctx, float duty_cycle );
```

- `brushless17_switch_direction` This function switches the direction by toggling the DIR pin state.
```c
void brushless17_switch_direction ( brushless17_t *ctx );
```

- `brushless17_get_diagnostic_pin` This function returns the DIAG pin logic state.
```c
uint8_t brushless17_get_diagnostic_pin ( brushless17_t *ctx );
```

## Example Description

> This example demonstrates the use of the Brushless 17 Click board by driving the motor in both directions at different speeds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless17_cfg_t brushless17_cfg;  /**< Click config object. */

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
    brushless17_cfg_setup( &brushless17_cfg );
    BRUSHLESS17_MAP_MIKROBUS( brushless17_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless17_init( &brushless17, &brushless17_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS17_ERROR == brushless17_default_cfg ( &brushless17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every 500ms.
The duty cycle ranges from 40% to 80%. At the minimal speed, the motor switches direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 4;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless17_set_duty_cycle ( &brushless17, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    duty_cnt += duty_inc;
    if ( 8 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 3 == duty_cnt ) 
    {
        duty_inc = 1;
        duty_cnt = 4;
        log_printf( &logger, " Switch direction\r\n\n" );
        brushless17_switch_direction ( &brushless17 );
    }
    
    if ( !brushless17_get_diagnostic_pin ( &brushless17 ) )
    {
        log_info ( &logger, " An overcurrent or overtemperature event has occured " );
    }

    Delay_ms ( 500 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
