
---
# Driver 2 Click

> Driver 2 Click is a compact add-on board that contains a gate driver with a level-shift technology with an additional Shutdown function. This board features the IR2104S, a high voltage, high-speed power MOSFET and IGBT driver with typical 0.21 A source and 0.36 A sink currents and independent high and low side referenced output channels from Infineon Technologies.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/driver2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/driver-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : PWM type


# Software Support

We provide a library for the Driver2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Driver2 Click driver.

#### Standard key functions :

- `driver2_cfg_setup` Config Object Initialization function.
```c
void driver2_cfg_setup ( driver2_cfg_t *cfg );
```

- `driver2_init` Initialization function.
```c
err_t driver2_init ( driver2_t *ctx, driver2_cfg_t *cfg );
```

- `driver2_default_cfg` Click Default Configuration function.
```c
err_t driver2_default_cfg ( driver2_t *ctx );
```

#### Example key functions :

- `driver2_set_sd_pin` Set SD pin.
```c
void driver2_set_sd_pin ( driver2_t *ctx, uint8_t state );
```

- `driver2_set_pwm_pin` Set PWM pin.
```c
void driver2_set_pwm_pin ( driver2_t *ctx, uint8_t state );
```

- `driver2_get_fb_pin` Get FB pin
```c
uint8_t driver2_get_fb_pin ( driver2_t *ctx );
```

## Example Description

> This is an example that demonstrates the use of the Driver 2 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver module and sets PWM.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    driver2_cfg_t driver2_cfg;  /**< Click config object. */

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

    driver2_cfg_setup( &driver2_cfg );
    DRIVER2_MAP_MIKROBUS( driver2_cfg, MIKROBUS_1 );
    err_t init_flag  = driver2_init( &driver2, &driver2_cfg );
    if ( PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    driver2_default_cfg ( &driver2 );

    driver2_set_duty_cycle ( &driver2, 0.0 );
    driver2_pwm_start( &driver2 );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Start motor example with change in motor speed using changes in PWM duty cycle.

```c

void application_task ( void ) {
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    driver2_set_duty_cycle ( &driver2, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) {
        duty_inc = -1;
    } else if ( 0 == duty_cnt ) {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Driver2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
