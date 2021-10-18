
---
# Vibro Motor 3 click

> Vibro Motor 3 Click is a compact add-on board that makes an ideal solution for adding simple haptic feedback in any design. This board features the G0832022D, a coin-sized linear resonant actuator (LRA) that generates vibration/haptic feedback in the Z plane, perpendicular to the motor's surface from Jinlong Machinery & Electronics, Inc.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vibromotor3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/vibro-motor-3-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the VibroMotor3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for VibroMotor3 Click driver.

#### Standard key functions :

- `vibromotor3_cfg_setup` Config Object Initialization function.
```c
void vibromotor3_cfg_setup ( vibromotor3_cfg_t *cfg );
```

- `vibromotor3_init` Initialization function.
```c
err_t vibromotor3_init ( vibromotor3_t *ctx, vibromotor3_cfg_t *cfg );
```

- `vibromotor3_default_cfg` Vibro Motor 3 default configuration function.
```c
err_t vibromotor3_default_cfg ( vibromotor3_t *ctx );
```

#### Example key functions :

- `vibromotor3_set_duty_cycle` Vibro Motor 3 sets PWM duty cycle.
```c
err_t vibromotor3_set_duty_cycle ( vibromotor3_t *ctx, float duty_cycle );
```

- `vibromotor3_enable` Enable the device function
```c
void vibromotor3_enable ( vibromotor3_t *ctx, uint8_t state );
```

- `vibromotor3_write_byte` Generic write the byte of data function
```c
void vibromotor3_write_byte ( vibromotor3_t *ctx, uint8_t reg, uint8_t wr_data );
```

## Example Description

> This example shows the capabilities of the Vibro Motor 3 click board 

**The demo application is composed of two sections :**

### Application Init

> Initalizes I2C driver, PWM driver and configures Vibro Motor 3 click board.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    vibromotor3_cfg_t vibromotor3_cfg;  /**< Click config object. */

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
    vibromotor3_cfg_setup( &vibromotor3_cfg );
    VIBROMOTOR3_MAP_MIKROBUS( vibromotor3_cfg, MIKROBUS_1 );
    err_t init_flag = vibromotor3_init( &vibromotor3, &vibromotor3_cfg );
    if ( I2C_MASTER_ERROR == init_flag || PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    vibromotor3_enable( &vibromotor3, VIBROMOTOR3_PROPERTY_ENABLE );
    Delay_ms( 100 );
    
    vibromotor3_soft_rst( &vibromotor3 );
    Delay_ms( 100 );
    
    vibromotor3_default_cfg( &vibromotor3 );
    Delay_ms( 100 );
    
    vibromotor3_set_duty_cycle( &vibromotor3, 0.0 );
    vibromotor3_pwm_start( &vibromotor3 );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}
```

### Application Task

> Changing duty cycle applied in order to get different vibrations.

```c

void application_task ( void ) {
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    vibromotor3_set_duty_cycle ( &vibromotor3, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms( 500 );
    
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
- Click.VibroMotor3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
