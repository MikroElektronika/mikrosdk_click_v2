
---
# Servo Click

> [Servo Click](https://www.mikroe.com/?pid_product=MIKROE-3133) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3133&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This app shows how the servo motor can be controled by the Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Servo

### Example Key Functions

- `servo_cfg_setup` Config Object Initialization function. 
```c
void servo_cfg_setup ( servo_cfg_t *cfg );
``` 
 
- `servo_init` Initialization function. 
```c
err_t servo_init ( servo_t *ctx, servo_cfg_t *cfg );
```

- `servo_default_cfg` Click Default Configuration function. 
```c
void servo_default_cfg ( servo_t *ctx );
```

- `servo_set_vref` This function settings Vref of Servo Clicks. 
```c
void servo_set_vref ( servo_t *ctx, uint16_t v_ref );
```
 
- `servo_set_position` This function sets position. 
```c
void servo_set_position ( servo_t *ctx, uint8_t motor, uint8_t position );
```

- `setvo_get_current` This function reads the current value of Servo Click witch motor spends. 
```c
uint16_t setvo_get_current ( servo_t *ctx, uint8_t channel );
```

### Application Init

> Initializes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    servo_cfg_t cfg;

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

    servo_cfg_setup( &cfg );
    SERVO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    servo_init( &servo, &cfg );
    
    servo_default_cfg( &servo );
}
```

### Application Task

> The servo motor at CH1 rotate in clockwise and counter clockwise directions.

```c
void application_task ( void )
{
    log_printf( &logger, "<<< Counter clockwise >>>\r\n" );
    Delay_1sec( );
    
    for ( cnt = servo.min_pos; cnt <= servo.max_pos; cnt++ )
    {
        servo_set_position( &servo, SERVO_MOTOR_1, cnt );
        log_printf( &logger, "Position : %u \r\n", ( uint16_t ) cnt );
        Delay_10ms( );
    }
    
    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, "<<< Clockwise >>>\r\n" );
    Delay_1sec( );
    
    for ( cnt = servo.max_pos; cnt >= servo.min_pos; cnt-- )
    {
        servo_set_position( &servo, SERVO_MOTOR_1, cnt );
        log_printf( &logger, "Position : %u \r\n", ( uint16_t ) cnt );
        Delay_10ms( );
    }
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
