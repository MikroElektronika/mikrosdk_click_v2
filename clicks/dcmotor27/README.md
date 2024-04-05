\mainpage Main Page

---
# DC Motor 27 click

> DC Motor 27 Click is a compact add-on board that contains a high-performance brushed DC motor driver. This board features the DRV8143, an automotive half-bridge driver with integrated current sense and diagnostic from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor27_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dc-motor-27-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : PWM type


# Software Support

We provide a library for the DC Motor 27 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DC Motor 27 Click driver.

#### Standard key functions :

- `dcmotor27_cfg_setup` Config Object Initialization function.
```c
void dcmotor27_cfg_setup ( dcmotor27_cfg_t *cfg );
```

- `dcmotor27_init` Initialization function.
```c
err_t dcmotor27_init ( dcmotor27_t *ctx, dcmotor27_cfg_t *cfg );
```

- `dcmotor27_default_cfg` Click Default Configuration function.
```c
err_t dcmotor27_default_cfg ( dcmotor27_t *ctx );
```

#### Example key functions :

- `dcmotor27_set_duty_cycle` DC Motor 27 sets PWM duty cycle.
```c
err_t dcmotor27_set_duty_cycle ( dcmotor27_t *ctx, float duty_cycle );
```

- `dcmotor27_get_flt_pin` DC Motor 27 get flt pin state.
```c
uint8_t dcmotor27_get_flt_pin ( dcmotor27_t *ctx );
```

- `dcmotor27_set_coast` DC Motor 27 set coast mode funtion.
```c
void dcmotor27_set_coast ( dcmotor27_t *ctx, uint8_t coast_state );
```

## Example Description

> This example demonstrates the use of the DC Motor 27 Click board by driving 
  the motor at different speeds, enabling brake and coast modes.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor27_cfg_t dcmotor27_cfg;  /**< Click config object. */

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
    dcmotor27_cfg_setup( &dcmotor27_cfg );
    DCMOTOR27_MAP_MIKROBUS( dcmotor27_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == dcmotor27_init( &dcmotor27, &dcmotor27_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    if ( DCMOTOR27_ERROR == dcmotor27_default_cfg ( &dcmotor27 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every second, 
  places the motor into coast or braking mode.

```c
void application_task ( void ) 
{
    for ( uint8_t speed_cnt = 10; speed_cnt <= 100; speed_cnt += 10 )
    {
        float speed = ( float ) speed_cnt / 100;
        dcmotor27_set_duty_cycle( &dcmotor27, speed );
        log_printf( &logger, " Motor speed %d%% \r\n", ( uint16_t ) speed_cnt );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Motor coasting \r\n" );
    dcmotor27_set_coast( &dcmotor27, DCMOTOR27_SET_COAST_ON );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor27_set_coast( &dcmotor27, DCMOTOR27_SET_COAST_OFF );
    
    for ( uint8_t speed_cnt = 10; speed_cnt <= 100; speed_cnt += 10 )
    {
        float speed = ( float ) speed_cnt / 100;
        dcmotor27_set_duty_cycle( &dcmotor27, speed );
        log_printf( &logger, " Motor speed %d%% \r\n", ( uint16_t ) speed_cnt );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Motor brake is on \r\n" );
    dcmotor27_pwm_stop( &dcmotor27 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor27_pwm_start( &dcmotor27 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor27

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
