
---
# Stepper 11 Click

> [Stepper 11 Click](https://www.mikroe.com/?pid_product=MIKROE-4578) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4578&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases the device's ability to control the motor.
It initializes the device for control and moves the motor in two 
directions in a variety of resolutions for 360 degrees.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper11

### Example Key Functions

- `stepper11_cfg_setup` Config Object Initialization function.
```c
void stepper11_cfg_setup ( stepper11_cfg_t *cfg );
```

- `stepper11_init` Initialization function.
```c
err_t stepper11_init ( stepper11_t *ctx, stepper11_cfg_t *cfg );
```

- `stepper11_default_cfg` Click Default Configuration function.
```c
err_t stepper11_default_cfg ( stepper11_t *ctx );
```

- `stepper11_set_step_resolution` Set step resolution.
```c
err_t stepper11_set_step_resolution ( stepper11_t *ctx, uint8_t step_res );
```

- `stepper11_move_motor_angle` Move motor in angle value.
```c
void stepper11_move_motor_angle ( stepper11_t *ctx, float degree, uint8_t speed );
```

- `stepper11_move_motor_step` Move motor in step value.
```c
void stepper11_move_motor_step ( stepper11_t *ctx, uint16_t steps, uint8_t speed );
```

### Application Init

> Initialization of communication modules(I2C, UART) and additional pins
for control of device. Then sets default configuration that enables
device for motor control.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper11_cfg_t stepper11_cfg;  /**< Click config object. */

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
    stepper11_cfg_setup( &stepper11_cfg );
    STEPPER11_MAP_MIKROBUS( stepper11_cfg, MIKROBUS_1 );
    err_t init_flag = stepper11_init( &stepper11, &stepper11_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    stepper11_default_cfg ( &stepper11 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Firstly it rotates motor in CW direction for 360 degrees in FULL step 
resolution. Then changes direction in CCW and rotates backwards 360 degrees
in 2 different step resolutions (Quarter and 1/16) in 180 degrees each.

```c
void application_task ( void ) 
{
    stepper11_set_step_resolution( &stepper11, STEPPER11_RESOLUTION_FULL );
    stepper11_set_direction( &stepper11, 1 );
    log_info( &logger, " Rotate motor CW for 360 degrees in full step" );
    stepper11_move_motor_angle( &stepper11, 360, STEPPER11_SPEED_FAST );
    Delay_ms ( 1000 );
    stepper11_set_direction( &stepper11, 0 );
    stepper11_set_step_resolution( &stepper11, STEPPER11_RESOLUTION_QUARTER );
    log_info( &logger, " Rotate motor CCW for 180 degrees in half step" );
    stepper11_move_motor_angle( &stepper11, 180, STEPPER11_SPEED_FAST );
    Delay_ms ( 1000 );
    stepper11_set_step_resolution( &stepper11, STEPPER11_RESOLUTION_1div16 );
    log_info( &logger, " Rotate motor CCW for 180 degrees in 1/8 step" );
    stepper11_move_motor_angle( &stepper11, 180, STEPPER11_SPEED_FAST );
    Delay_ms ( 1000 );
}
```


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
