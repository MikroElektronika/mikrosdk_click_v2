
---
# Servo 3 Click

> [Servo 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6837) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6837&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2025.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of the Servo 3 Click board for controlling the angle of servo motors. 
The board is capable of driving multiple servos, and the example illustrates how to change the angle 
of all connected servos simultaneously within a defined range.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Servo3

### Example Key Functions

- `servo3_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void servo3_cfg_setup ( servo3_cfg_t *cfg );
```

- `servo3_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t servo3_init ( servo3_t *ctx, servo3_cfg_t *cfg );
```

- `servo3_set_angle` This function sets the servo angle for a specific channel or all channels.
```c
err_t servo3_set_angle ( servo3_t *ctx, uint8_t ch_num, uint8_t angle );
```

- `servo3_update_output` This function updates the PWM output values for all channels by writing them to the device.
```c
void servo3_update_output ( servo3_t *ctx );
```

### Application Init

> Initializes the logger module and configures the Servo 3 Click board. The PWM communication is 
established, and the device is prepared for controlling the servos.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    servo3_cfg_t servo3_cfg;  /**< Click config object. */

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
    servo3_cfg_setup( &servo3_cfg );
    SERVO3_MAP_MIKROBUS( servo3_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == servo3_init( &servo3, &servo3_cfg ) )
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
    static uint8_t angle = SERVO3_ANGLE_MIN;
    static int8_t step = 1;
    log_printf( &logger, "All channels angle: %u\r\n\n", ( uint16_t ) angle );
    servo3_set_angle ( &servo3, SERVO3_CHANNEL_ALL, angle );
    servo3_update_output ( &servo3 );
    angle += step;
    if ( angle > SERVO3_ANGLE_MAX )
    {
        step = -step;
        angle += step;
    }
    else if ( angle < SERVO3_ANGLE_MIN )
    {
        step = -step;
        angle += step;
    }
}
```

### Note

> Ensure that the servo motors are properly connected to the Servo 3 Click board and are compatible 
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
