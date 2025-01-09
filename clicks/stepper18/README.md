
---
# Stepper 18 Click

> [Stepper 18 Click](https://www.mikroe.com/?pid_product=MIKROE-4689) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4689&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : May 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases the device's ability to control the motor.
It initializes the device for control and moves the motor in two 
directions in a variety of speeds for 360 degrees.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper18

### Example Key Functions

- `stepper18_cfg_setup` Config Object Initialization function.
```c
void stepper18_cfg_setup ( stepper18_cfg_t *cfg );
```

- `stepper18_init` Initialization function.
```c
err_t stepper18_init ( stepper18_t *ctx, stepper18_cfg_t *cfg );
```

- `stepper18_default_cfg` Click Default Configuration function.
```c
void stepper18_default_cfg ( stepper18_t *ctx );
```

- `stepper18_set_out_voltage` Set voltage reference.
```c
err_t stepper18_set_out_voltage ( stepper18_t *ctx, uint16_t voltage );
```

- `stepper18_set_dir` Set direction.
```c
void stepper18_set_dir ( stepper18_t *ctx, uint8_t value );
```

- `stepper18_move_motor_angle` Move motor in angle value.
```c
void stepper18_move_motor_angle ( stepper18_t *ctx, float degree, uint8_t step_res, uint8_t speed );
```

### Application Init

> Initializes UART and I2C communication modules, and additional  
pins for motor control, and set's default configuration

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper18_cfg_t stepper18_cfg;  /**< Click config object. */

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
    stepper18_cfg_setup( &stepper18_cfg );
    STEPPER18_MAP_MIKROBUS( stepper18_cfg, MIKROBUS_1 );
    err_t init_flag = stepper18_init( &stepper18, &stepper18_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    stepper18_default_cfg ( &stepper18 );
    log_info( &logger, " Application Task " );
    stepper18_set_dir( &stepper18, 0 );
}
```

### Application Task

> First it move motor clockwise for 360 degrees in medium speed. 
Then changes direction and moves motor for 180 degrees in slow speed,
and additional 180 degrees in fast speed.

```c
void application_task ( void ) 
{
    static uint8_t direction = 0;
    log_printf( &logger, "> Move 360deg in CW direction.\r\n" );
    stepper18_move_motor_angle( &stepper18, 360, STEPPER18_STEP_RES_FULL, STEPPER18_SPEED_MEDIUM );
    direction = !direction;
    stepper18_set_dir( &stepper18, direction );
    Delay_ms ( 500 );
    log_printf( &logger, "> Move 180deg in CCW direction.\r\n" );
    stepper18_move_motor_angle( &stepper18, 180, STEPPER18_STEP_RES_FULL, STEPPER18_SPEED_SLOW );
    Delay_ms ( 1000 );
    log_printf( &logger, "> Move 180deg in CCW direcion.\r\n" );
    stepper18_move_motor_angle( &stepper18, 180, STEPPER18_STEP_RES_FULL, STEPPER18_SPEED_FAST );
    direction = !direction;
    stepper18_set_dir( &stepper18, direction );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Step resolution is changed by the switches[ M0, M1 ] on device.
Full step    :   M0=>0 ,     M1=>0;
Half step    :   M0=>1 ,     M1=>0;
Quarter step :   M0=>0 ,     M1=>1;
1/8 step     :   M0=>1 ,     M1=>1;
1/16 step    :   M0=>Hi-Z ,  M1=>1;
1/32 step    :   M0=>0 ,     M1=>Hi-Z;
1/64 step    :   M0=>Hi-Z ,  M1=>0;
1/128 step   :   M0=>Hi-Z ,  M1=>Hi-Z;
1/256 step   :   M0=>1 ,     M1=>0;

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
