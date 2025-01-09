
---
# Light Temp Click

> [Light Temp Click](https://www.mikroe.com/?pid_product=MIKROE-3399) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3399&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This application controls light intensity of LEDs.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightTemp

### Example Key Functions

- `lighttemp_cfg_setup` Config Object Initialization function. 
```c
void lighttemp_cfg_setup ( lighttemp_cfg_t *cfg );
``` 
 
- `lighttemp_init` Initialization function. 
```c
err_t lighttemp_init ( lighttemp_t *ctx, lighttemp_cfg_t *cfg );
```

- `lighttemp_get_interrupt_state` Get INT pin state. 
```c
uint8_t lighttemp_get_interrupt_state ( lighttemp_t *ctx );
```
 
- `lighttemp_get_pg_voltage` Get voltage. 
```c
uint16_t lighttemp_get_pg_voltage ( lighttemp_t *ctx );
```

- `lighttemp_cs_set_state` Start PW2 module. 
```c
void lighttemp_cs_set_state ( lighttemp_t *ctx, uint8_t state );
```

### Application Init

> Initialization driver init and pwm init for all LED's

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lighttemp_cfg_t cfg;

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
    Delay_ms ( 100 );
    
    //  Click initialization.

    lighttemp_cfg_setup( &cfg );
    LIGHTTEMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lighttemp_init( &lighttemp, &cfg );
    
    lighttemp_led1_set_duty_cycle ( &lighttemp, 0.0 );
    lighttemp_led2_set_duty_cycle ( &lighttemp, 0.0 );
    
    log_info( &logger, "---- Application Task ----" );

    Delay_ms ( 500 );
}
```

### Application Task

>  This is an example that demonstrates the use of the Light Temp Click board.
>  This example shows the automatic control of the LED light intensity,
>  the first intensity of light is rising and then the intensity of light is falling.
>  Results are being sent to the Usart Terminal where you can track their changes. 

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    lighttemp_led1_set_duty_cycle ( &lighttemp, duty );
    lighttemp_led2_set_duty_cycle ( &lighttemp, duty );
    
    lighttemp_led1_pwm_start( &lighttemp );
    lighttemp_led2_pwm_start( &lighttemp );

    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
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
