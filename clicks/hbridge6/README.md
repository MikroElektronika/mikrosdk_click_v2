
---
# H-Bridge 6 Click

> [H-Bridge 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4289) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4289&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrates the use of H-Bridge 6 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge6

### Example Key Functions

- `hbridge6_cfg_setup` Config Object Initialization function.
```c
void hbridge6_cfg_setup ( hbridge6_cfg_t *cfg );
```

- `hbridge6_init` Initialization function.
```c
err_t hbridge6_init ( hbridge6_t *ctx, hbridge6_cfg_t *cfg );
```

- `hbridge6_default_cfg` Click Default Configuration function.
```c
err_t hbridge6_default_cfg ( hbridge6_t *ctx );
```

- `hbridge6_reset` HW reset function.
```c
void hbridge6_reset ( hbridge6_t *ctx );
```

- `hbridge6_enable_diagnostic` Enable the diagnostic function.
```c
void hbridge6_enable_diagnostic ( hbridge6_t *ctx, uint8_t en_state );
```

- `hbridge6_set_direction` Adjust the direction function.
```c
void hbridge6_set_direction ( hbridge6_t *ctx, uint8_t direction );
```

### Application Init

> Initialization driver enables - I2C, reset the device and set default configuration, initialization and configure the PWM, also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge6_cfg_t hbridge6_cfg;  /**< Click config object. */

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
    hbridge6_cfg_setup( &hbridge6_cfg );
    HBRIDGE6_MAP_MIKROBUS( hbridge6_cfg, MIKROBUS_1 );
    err_t init_flag = hbridge6_init( &hbridge6, &hbridge6_cfg );
    if ( I2C_MASTER_ERROR == init_flag || PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "  Set default config.  \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_default_cfg( &hbridge6 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> It shows moving in the clockwise direction of rotation and moving in the counterclockwise direction of rotation from slow to fast speed. All data logs write on USB uart changes.

```c
void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = 0;
    
    log_printf( &logger, "       Clockwise       \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_set_direction( &hbridge6, HBRIDGE6_DIRECTION_CLOCKWISE );
    
    while ( duty_cnt < 10 ) {
        duty = duty_cnt / 10.0;
        hbridge6_set_duty_cycle ( &hbridge6, duty );
        Delay_ms ( 500 );
        duty_cnt += duty_inc;
    }
    
    log_printf( &logger, "         Brake         \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_set_direction( &hbridge6, HBRIDGE6_DIRECTION_BRAKE );
    duty_cnt = 1;
    Delay_ms ( 1000 );
    
    log_printf( &logger, "    Counterclockwise   \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_set_direction( &hbridge6, HBRIDGE6_DIRECTION_COUNTERCLOCKWISE );
    
    while ( duty_cnt < 10 ) {
        duty = duty_cnt / 10.0;
        hbridge6_set_duty_cycle ( &hbridge6, duty );
        Delay_ms ( 500 );
        duty_cnt += duty_inc;
    }
    
    log_printf( &logger, "         Brake         \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_set_direction( &hbridge6, HBRIDGE6_DIRECTION_BRAKE );
    duty_cnt = 1;
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge6_pwm_stop( &hbridge6 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge6_pwm_start( &hbridge6 );
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
