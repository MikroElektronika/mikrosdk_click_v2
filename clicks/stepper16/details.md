
---
# Stepper 16 click

Stepper 16 Click is a compact add-on board that contains a micro-stepping stepper motor driver. This board features the NCV70517, an SPI and I/O configurable motor driver for bipolar stepper motors from ON Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper_16_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/stepper-16-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : May 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Stepper16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper16 Click driver.

#### Standard key functions :

- `stepper16_cfg_setup` Config Object Initialization function.
```c
void stepper16_cfg_setup ( stepper16_cfg_t *cfg );
```

- `stepper16_init` Initialization function.
```c
err_t stepper16_init ( stepper16_t *ctx, stepper16_cfg_t *cfg );
```

- `stepper16_default_cfg` Click Default Configuration function.
```c
err_t stepper16_default_cfg ( stepper16_t *ctx );
```

#### Example key functions :

- `stepper16_hard_reset` Resets device.
```c
void stepper16_hard_reset ( stepper16_t *ctx );
```

- `stepper16_set_step_resolution` Set step resolution.
```c
void stepper16_set_step_resolution ( stepper16_t *ctx, uint8_t step_res );
```

- `stepper16_move_motor_angle` Move motor in angle value.
```c
void stepper16_move_motor_angle ( stepper16_t *ctx, float degree, uint8_t speed );
```

## Example Description

> This example showcases the device's ability to control the motor.
It initializes the device for control and moves the motor in two 
directions in a variety of speeds and step resolutions for 360 degrees.

**The demo application is composed of two sections :**

### Application Init

> Initializes UART and SPI communication modules, and additional  
pins for motor control, resets device, set's default configuration,
and reads its ID and sets

```c

void application_init ( void ) 
{
    uint16_t read_data = 0;
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper16_cfg_t stepper16_cfg;  /**< Click config object. */

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
    stepper16_cfg_setup( &stepper16_cfg );
    STEPPER16_MAP_MIKROBUS( stepper16_cfg, MIKROBUS_1 );
    err_t init_flag  = stepper16_init( &stepper16, &stepper16_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    stepper16_default_cfg ( &stepper16 );
    check_error( &stepper16 );
    stepper16_generic_read( &stepper16, STEPPER16_REG_SR4, &read_data );
    check_error( &stepper16 );
    log_info( &logger, "DEV ID: %d ", ( read_data >> 3 ) );
    log_info( &logger, "REV ID: %d ", ( read_data & 3 ) );

    log_info( &logger, " Application Task " );
    stepper16_set_dir( &stepper16, 1 );
}

```

### Application Task

> First it move motor clockwise for 360 degrees in medium speed and 
full step resolution. Then changes direction and moves motor for 
180 degrees in slow speed and quarter step, and additional 180 degrees
in fast speed and 1/16 step resolution.

```c

void application_task ( void ) 
{
    static uint8_t direction = 1;
    log_printf( &logger, "> Move 360deg in CW direction.\r\n" );
    stepper16_set_step_resolution( &stepper16, STEPPER16_STEP_RES_FULL );
    check_error( &stepper16 );
    stepper16_move_motor_angle( &stepper16, 360, STEPPER16_SPEED_MEDIUM );
    direction = !direction;
    stepper16_set_dir( &stepper16, direction );
    Delay_ms ( 500 );
    log_printf( &logger, "> Move 180deg in CCW direction.\r\n" );
    stepper16_set_step_resolution( &stepper16, STEPPER16_STEP_RES_QUARTER );
    check_error( &stepper16 );
    stepper16_move_motor_angle( &stepper16, 180, STEPPER16_SPEED_SLOW );
    Delay_ms ( 1000 );
    log_printf( &logger, "> Move 180deg in CCW direcion.\r\n" );
    stepper16_set_step_resolution( &stepper16, STEPPER16_STEP_RES_1div16 );
    check_error( &stepper16 );
    stepper16_move_motor_angle( &stepper16, 180, STEPPER16_SPEED_FAST );
    direction = !direction;
    stepper16_set_dir( &stepper16, direction );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

## Note

> Device is powered by externam VM so for communication to work Click 
board should be connected on power supply from 6V to 29V. At the start of
application user should reset device and read it's Status register 1 to clear it.
After that it can communicate with device and control it noramaly.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper16

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
