
---
# STSPIN250 Click

> [STSPIN250 Click](https://www.mikroe.com/?pid_product=MIKROE-3543) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3543&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This application enables usage of brushed DC motor driver with the current limiting and current sensing.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Stspin250

### Example Key Functions

- `stspin250_cfg_setup` Config Object Initialization function. 
```c
void stspin250_cfg_setup ( stspin250_cfg_t *cfg );
``` 
 
- `stspin250_init` Initialization function. 
```c
err_t stspin250_init ( stspin250_t *ctx, stspin250_cfg_t *cfg );
```

- `stspin250_default_cfg` Click Default Configuration function. 
```c
void stspin250_default_cfg ( stspin250_t *ctx );
```

- This function regulates Direction control pin state. It controls direction
- `stspin250_set_ph` of the current. 
```c
void stspin250_set_ph ( stspin250_t *ctx, uint8_t state );
```
 
- `stspin250_enable ` This function regulates enable pin state. 
```c
void stspin250_enable  ( stspin250_t *ctx, uint8_t state );
```

- `stspin250_reset` This function regulates reset pin state. 
```c
void stspin250_reset ( stspin250_t *ctx );
```

### Application Init

> Initialization driver init, PWM init and enable device


```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    stspin250_cfg_t cfg;

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

    stspin250_cfg_setup( &cfg );
    STSPIN250_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stspin250_init( &stspin250, &cfg );

    stspin250_enable( &stspin250, STSPIN250_DEVICE_ENABLE );
    stspin250_set_duty_cycle ( &stspin250, 0.0 );

    stspin250_pwm_start( &stspin250 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 500 );
}
```

### Application Task

>  This is a example which demonstrates the use of Stspin250 Click board.
>  Stspin250 Click communicates with register via PWM interface.
>  It shows moving in the left direction from slow to fast speed
>  and from fast to slow speed.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    if ( motor_direction == 1 )
    {
        stspin250_set_ph( &stspin250, 1 );
        log_printf( &logger, "> CLOCKWISE <\r\n" );
    }
    else
    {
        stspin250_set_ph( &stspin250, 0 );
        log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
    }

    stspin250_set_duty_cycle ( &stspin250, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        if ( motor_direction == 1 )
        {
            motor_direction = 0;
        }
        else if ( motor_direction == 0 )
        {
            motor_direction = 1;
        }
    }
    duty_cnt += duty_inc;
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
