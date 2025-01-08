
---
# DC MOTOR 7 Click

> [DC MOTOR 7 Click](https://www.mikroe.com/?pid_product=MIKROE-3289) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3289&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is a dual brushed DC motor driving.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor7

### Example Key Functions

- `dcmotor7_cfg_setup` Config Object Initialization function. 
```c
void dcmotor7_cfg_setup ( dcmotor7_cfg_t *cfg );
``` 
 
- `dcmotor7_init` Initialization function. 
```c
err_t dcmotor7_init ( dcmotor7_t *ctx, dcmotor7_cfg_t *cfg );
```

- `dcmotor7_default_cfg` Default Configuration . 
```c
void dcmotor7_default_cfg( dcmotor7_t *ctx );
```

- `dcmotor7_set_port` Functions for set port. 
```c
void dcmotor7_set_port( dcmotor7_t *ctx, uint8_t port, uint8_t value );
```
 
- `dcmotor7_go_to_stand_by_mode` Function for setting the motor in stand mode. 
```c
void dcmotor7_go_to_stand_by_mode( dcmotor7_t *ctx, uint8_t motor );
```

- `dcmotor7_set_pwm_motor_b` Function for set PWM value for motor B. 
```c
void dcmotor7_set_pwm_motor_b( dcmotor7_t *ctx, uint8_t state );
```

### Application Init

> Initialization driver init, enabled all output port, sets H-Bridge operation mode and Motor Digital tblk

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor7_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dcmotor7_cfg_setup( &cfg );
    DCMOTOR7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor7_init( &dcmotor7, &cfg );

    dcmotor7_default_cfg( &dcmotor7 );
}
```

### Application Task

> Set the motor A and the motor B to rotate clockwise and in the Counte clockwise direction, 
> and between the change of direction, the motor stops the motor. 

```c
void application_task ( void )
{
    dcmotor7_set_motor( &dcmotor7, DCMOTOR7_MOTOR_A, 0, 1 );
    dcmotor7_set_motor( &dcmotor7, DCMOTOR7_MOTOR_B, 0, 1 );
    Delay_ms ( 500 );
    
    dcmotor7_motor_stop( &dcmotor7, DCMOTOR7_MOTOR_A );
    dcmotor7_motor_stop( &dcmotor7, DCMOTOR7_MOTOR_B );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    dcmotor7_set_motor( &dcmotor7, DCMOTOR7_MOTOR_A, 1, 0 );
    dcmotor7_set_motor( &dcmotor7, DCMOTOR7_MOTOR_B, 1, 0 );
    Delay_ms ( 500 );
    
    dcmotor7_motor_stop( &dcmotor7, DCMOTOR7_MOTOR_A );
    dcmotor7_motor_stop( &dcmotor7, DCMOTOR7_MOTOR_B );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> VM input - 10 V (min) to 47 V (max)

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
