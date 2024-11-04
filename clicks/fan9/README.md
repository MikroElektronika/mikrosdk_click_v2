\mainpage Main Page

---
# Fan 9 Click

> Fan 9 Click is a compact add-on board designed for high-power fan applications requiring low noise and minimal vibration. This board features the A5932, an automotive-grade three-phase sinusoidal sensorless fan controller from Allegro Microsystems. This board operates with a power supply range of 12V to 42V, using a sinusoidal drive to reduce audible noise and vibration. It features I2C communication, PWM speed control, and a red FLT LED indicator for fault conditions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fan9_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/fan-9-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Fan 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Fan 9 Click driver.

#### Standard key functions :

- `fan9_cfg_setup` Config Object Initialization function.
```c
void fan9_cfg_setup ( fan9_cfg_t *cfg );
```

- `fan9_init` Initialization function.
```c
err_t fan9_init ( fan9_t *ctx, fan9_cfg_t *cfg );
```

- `fan9_default_cfg` Click Default Configuration function.
```c
err_t fan9_default_cfg ( fan9_t *ctx );
```

#### Example key functions :

- `fan9_set_direction` This function is used to set direction of Fan 9 Click board.
```c
void fan9_set_direction ( fan9_t *ctx, uint8_t dir );
```

- `fan9_write_reg` This function reads a data bytes from the selected register by using I2C serial interface.
```c
err_t fan9_write_reg ( fan9_t *ctx, uint8_t reg, uint16_t data_in );
```

- `fan9_set_pwm` This function is used to get PWM value of Fan 9 Click board.
```c
err_t fan9_set_pwm ( fan9_t *ctx, uint8_t pwm_val );
```

## Example Description

> This example demonstrates the use of FAN 9 Click board, by changing speed of the fan from 0 to 100 percent, then decreasing it back to 0.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    fan9_cfg_t fan9_cfg;  /**< Click config object. */

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
    fan9_cfg_setup( &fan9_cfg );
    FAN9_MAP_MIKROBUS( fan9_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == fan9_init( &fan9, &fan9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FAN9_ERROR == fan9_default_cfg ( &fan9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    fan9_set_pwm( &fan9, 10 );
    // Waiting for motor to start.
    while ( 0 == fan9_get_rd_pin( &fan9 ) );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the speed of fans by changing the PWM duty cycle.
  The results are being displayed via USB UART where you can track their changes.

```c
void application_task ( void ) 
{
    static int8_t duty_cnt = 10;
    static int8_t duty_inc = 10;
    uint8_t direction = FAN9_DIRECTION_CW;

    fan9_set_pwm( &fan9, duty_cnt );
    log_printf( &logger, " Set PWM: %d%% \r\n", ( uint16_t ) duty_cnt );
    
    if ( 100 == duty_cnt ) 
    {
        duty_inc = -10;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 10;
    }
    duty_cnt += duty_inc;
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Fan9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
