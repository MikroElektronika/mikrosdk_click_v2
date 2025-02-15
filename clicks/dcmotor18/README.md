
---
# DC Motor 18 Click

> [DC Motor 18 Click](https://www.mikroe.com/?pid_product=MIKROE-4786) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4786&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Aug 2021.
- **Type**          : PWM type

# Software Support

## Example Description

> This example application showcases ability of Click 
board to control DC motors using PWM modulation in 
both directions and different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor18

### Example Key Functions

- `dcmotor18_cfg_setup` Config Object Initialization function.
```c
void dcmotor18_cfg_setup ( dcmotor18_cfg_t *cfg );
```

- `dcmotor18_init` Initialization function.
```c
err_t dcmotor18_init ( dcmotor18_t *ctx, dcmotor18_cfg_t *cfg );
```

- `dcmotor18_default_cfg` Click Default Configuration function.
```c
err_t dcmotor18_default_cfg ( dcmotor18_t *ctx );
```

- `dcmotor18_set_speed_percentage` Set speed output percentage.
```c
err_t dcmotor18_set_speed_percentage ( dcmotor18_t *ctx, float speed_percentage );
```

- `dcmotor18_set_enable` Set enable pin state.
```c
void dcmotor18_set_enable ( dcmotor18_t *ctx, uint8_t state );
```

- `dcmotor18_read_an_pin_current` Read AN pin current.
```c
err_t dcmotor18_read_an_pin_current ( dcmotor18_t *ctx, float *data_out );
```

### Application Init

> Initialization of MCU communication modules (PWM, ADC, UART) 
and additioal gpio for control of the device. Then sets 
default configuration that enables device to control the DC motor.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor18_cfg_t dcmotor18_cfg;  /**< Click config object. */

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

    dcmotor18_cfg_setup( &dcmotor18_cfg );
    DCMOTOR18_MAP_MIKROBUS( dcmotor18_cfg, MIKROBUS_1 );
    err_t init_flag  = dcmotor18_init( &dcmotor18, &dcmotor18_cfg );
    if ( PWM_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    dcmotor18_default_cfg ( &dcmotor18 );

    log_info( &logger, " Application Task " );
    Delay_ms ( 500 );
}
```

### Application Task

> Drives motor in one direction from 0 to 100% of the speed using 
PWM, and then returns it back to 0. Then changes the rotation
direction and repeats the process of increasing and decreasing 
acceleration.

```c
void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float speed = duty_cnt / 10.0;
    static uint8_t direction = 1;
    
    dcmotor18_set_direction( &dcmotor18, direction );
    dcmotor18_set_speed_percentage ( &dcmotor18, speed );
    
    if ( dcmotor18.direction )
    {
        log_printf( &logger, "<<< " );
    }
    else
    {
        log_printf( &logger, ">>> " );
    }
    log_printf( &logger, "Speed: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    if ( 10 == duty_cnt )
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt )
    {
        duty_inc = 1;
        direction = !direction;
    }
    duty_cnt += duty_inc;
    
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
