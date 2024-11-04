
---
# Fan 5 Click

> Fan 5 Click is a compact add-on board specially designed for fan speed management. This board features Microchip’s TC654, a PWM mode fan speed controller with FanSense™ technology suitable for brushless DC fans.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fan5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/fan-5-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Fan 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Fan 5 Click driver.

#### Standard key functions :

- `fan5_cfg_setup` Config Object Initialization function.
```c
void fan5_cfg_setup ( fan5_cfg_t *cfg );
```

- `fan5_init` Initialization function.
```c
err_t fan5_init ( fan5_t *ctx, fan5_cfg_t *cfg );
```

- `fan5_default_cfg` Click Default Configuration function.
```c
err_t fan5_default_cfg ( fan5_t *ctx );
```

#### Example key functions :

- `fan5_get_rpm1` Fan 5 get speed of FAN1.
```c
err_t fan5_get_rpm1 ( fan5_t *ctx, uint16_t *fan1_speed );
```

- `fan5_set_duty_cycle` Fan 5 set duty cycle.
```c
err_t fan5_set_duty_cycle ( fan5_t *ctx, uint8_t duty_cycle );
```

- `fan5_turn_on_fans` Fan 5 turn on fans.
```c
err_t fan5_turn_on_fans ( fan5_t *ctx );
```

## Example Description

> This example demonstrates the use of FAN 5 Click board by controlling and regulating the fan motors speed.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the Click default configuration, reads 
  manufacturer id and sets configuration in correspondence to user-selected mode.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    fan5_cfg_t fan5_cfg;  /**< Click config object. */

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
    fan5_cfg_setup( &fan5_cfg );
    FAN5_MAP_MIKROBUS( fan5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == fan5_init( &fan5, &fan5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FAN5_ERROR == fan5_default_cfg ( &fan5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    fan5_turn_on_fans( &fan5 );
    uint8_t id = 0;
    fan5_get_mfr_id( &fan5, &id );
    log_printf( &logger, " Manufacturer ID: 0x%X \r\n", ( uint16_t ) id );
    
#if defined FAN_CONTROL_MODE
    fan5_set_duty_cycle( &fan5, FAN5_100_PER_DUTY );
    fan5_set_fan_fault1( &fan5, 500 );
#else
    fan5_set_duty_cycle( &fan5, FAN5_30_PER_DUTY );
    fan5_set_fan_fault1( &fan5, 0 );
#endif
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> If Fan control is selected example will monitor FAN 1 speed and if the speed 
  falls below 500 RPM for longer then 2.4 seconds fan output will be disabled.
  In other case, example is showcasing speed control by changing duty cycle and 
  monitoring fan speed.

```c
void application_task ( void ) 
{
#if defined FAN_CONTROL_MODE
    uint16_t speed = 0;
    uint8_t flag_data = 0;
    
    fan5_get_rpm1( &fan5, &speed);
    log_printf( &logger, " SPEED: %d RPM \r\n", speed );
    
    if ( FAN5_FAULT == fan5_get_fault_state( &fan5 ) )
    {
        fan5_get_status_flags ( &fan5, &flag_data );
        log_printf( &logger, " FLAG: %d \r\n", flag_data );
        if ( FAN5_F1F_FLAG & flag_data )
        {
            log_printf( &logger, " FAN SPEED DROPED !!! \r\n" );
            log_printf( &logger, " OUTPUT IS DISABLED \r\n" );
            fan5_turn_off_fans( &fan5 );
            for( ; ; );
        }
    }
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    uint16_t speed;
    uint8_t duty_value;
    
    for ( duty_value = FAN5_30_PER_DUTY; duty_value <= FAN5_100_PER_DUTY; duty_value++ )
    {
        fan5_set_duty_cycle( &fan5, duty_value );
        log_printf( &logger, " Duty value: %d \r\n", ( uint16_t ) duty_value );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        fan5_get_rpm1( &fan5, &speed);
        log_printf( &logger, " SPEED: %d RPM \r\n", speed );
        Delay_ms ( 500 );
    }
#endif
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Fan5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
