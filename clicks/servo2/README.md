
---
# Servo 2 Click

> [Servo 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6533) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6533&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2024.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of the Servo 2 Click board for controlling the angle of servo motors. 
The board is capable of driving multiple servos, and the example illustrates how to change the angle 
of all connected servos simultaneously within a defined range.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Servo2

### Example Key Functions

- `servo2_cfg_setup` Config Object Initialization function.
```c
void servo2_cfg_setup ( servo2_cfg_t *cfg );
```

- `servo2_init` Initialization function.
```c
err_t servo2_init ( servo2_t *ctx, servo2_cfg_t *cfg );
```

- `servo2_set_angle` This function sets the servo angle for a specific channel or all channels.
```c
err_t servo2_set_angle ( servo2_t *ctx, uint8_t ch_num, uint8_t angle );
```

- `servo2_update_output` This function updates the PWM output values for all channels by writing them to the device.
```c
void servo2_update_output ( servo2_t *ctx );
```

- `servo2_set_channel_pwm` This function sets the PWM output for a specific channel or all channels.
```c
err_t servo2_set_channel_pwm ( servo2_t *ctx, uint8_t ch_num, uint16_t pwm_out );
```

### Application Init

> Initializes the logger module and configures the Servo 2 Click board. The PWM communication is 
established, and the device is prepared for controlling the servos.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    servo2_cfg_t servo2_cfg;  /**< Click config object. */

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
    servo2_cfg_setup( &servo2_cfg );
    SERVO2_MAP_MIKROBUS( servo2_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == servo2_init( &servo2, &servo2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Gradually changes the angle of all connected servo motors from a minimum to a maximum value, and 
then back to the minimum, creating a sweeping motion. The current angle is logged during each update.

```c
void application_task ( void )
{
    static uint8_t angle = SERVO2_ANGLE_MIN;
    static int8_t step = 1;
    log_printf( &logger, "All channels angle: %u\r\n\n", angle );
    servo2_set_angle ( &servo2, SERVO2_CHANNEL_ALL, angle );
    servo2_update_output ( &servo2 );
    angle += step;
    if ( angle > SERVO2_ANGLE_MAX )
    {
        step = -step;
        angle += step;
    }
    else if ( angle < SERVO2_ANGLE_MIN )
    {
        step = -step;
        angle += step;
    }
}
```

### Note

> Ensure that the servo motors are properly connected to the Servo 2 Click board and are compatible 
with the specified angle range such as the SG90 Micro Servo motors.

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
