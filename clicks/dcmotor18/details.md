
---
# DC Motor 18 Click

> DC Motor 18 Click is a compact add-on board that contains a brushed DC motor driver. This board features the TB9051FTG, an automotive PWM-type single-channel H-Bridge DC brushed motor driver from Toshiba Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dc_motor_18_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dc-motor-18-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Aug 2021.
- **Type**          : PWM type


# Software Support

We provide a library for the DCMotor18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DCMotor18 Click driver.

#### Standard key functions :

- `dcmotor18_cfg_setup` Config Object Initialization function.
```c
void dcmotor18_cfg_setup ( dcmotor18_cfg_t *cfg );
```

- `dcmotor18_init` Initialization function.
```c
err_t dcmotor18_init ( dcmotor18_t *ctx, dcmotor18_cfg_t *cfg );
```

- `dcmotor18_default_cfg` Click Default Configuration function.
```c
err_t dcmotor18_default_cfg ( dcmotor18_t *ctx );
```

#### Example key functions :

- `dcmotor18_set_speed_percentage` Set speed output percentage.
```c
err_t dcmotor18_set_speed_percentage ( dcmotor18_t *ctx, float speed_percentage );
```

- `dcmotor18_set_enable` Set enable pin state.
```c
void dcmotor18_set_enable ( dcmotor18_t *ctx, uint8_t state );
```

- `dcmotor18_read_an_pin_current` Read AN pin current.
```c
err_t dcmotor18_read_an_pin_current ( dcmotor18_t *ctx, float *data_out );
```

## Example Description

> This example application showcases ability of Click 
board to control DC motors using PWM modulation in 
both directions and different speeds.

**The demo application is composed of two sections :**

### Application Init

> Initialization of MCU communication modules (PWM, ADC, UART) 
and additioal gpio for control of the device. Then sets 
default configuration that enables device to control the DC motor.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor18_cfg_t dcmotor18_cfg;  /**< Click config object. */

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

    dcmotor18_cfg_setup( &dcmotor18_cfg );
    DCMOTOR18_MAP_MIKROBUS( dcmotor18_cfg, MIKROBUS_1 );
    err_t init_flag  = dcmotor18_init( &dcmotor18, &dcmotor18_cfg );
    if ( PWM_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    dcmotor18_default_cfg ( &dcmotor18 );

    log_info( &logger, " Application Task " );
    Delay_ms ( 500 );
}

```

### Application Task

> Drives motor in one direction from 0 to 100% of the speed using 
PWM, and then returns it back to 0. Then changes the rotation
direction and repeats the process of increasing and decreasing 
acceleration.

```c

void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float speed = duty_cnt / 10.0;
    static uint8_t direction = 1;
    
    dcmotor18_set_direction( &dcmotor18, direction );
    dcmotor18_set_speed_percentage ( &dcmotor18, speed );
    
    if ( dcmotor18.direction )
    {
        log_printf( &logger, "<<< " );
    }
    else
    {
        log_printf( &logger, ">>> " );
    }
    log_printf( &logger, "Speed: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    if ( 10 == duty_cnt )
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt )
    {
        duty_inc = 1;
        direction = !direction;
    }
    duty_cnt += duty_inc;
    
    Delay_ms ( 1000 );  
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
