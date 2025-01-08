
---
# Vibro Motor 3 Click

> [Vibro Motor 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4356) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4356&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example shows the capabilities of the Vibro Motor 3 Click board 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VibroMotor3

### Example Key Functions

- `vibromotor3_cfg_setup` Config Object Initialization function.
```c
void vibromotor3_cfg_setup ( vibromotor3_cfg_t *cfg );
```

- `vibromotor3_init` Initialization function.
```c
err_t vibromotor3_init ( vibromotor3_t *ctx, vibromotor3_cfg_t *cfg );
```

- `vibromotor3_default_cfg` Vibro Motor 3 default configuration function.
```c
err_t vibromotor3_default_cfg ( vibromotor3_t *ctx );
```

- `vibromotor3_set_duty_cycle` Vibro Motor 3 sets PWM duty cycle.
```c
err_t vibromotor3_set_duty_cycle ( vibromotor3_t *ctx, float duty_cycle );
```

- `vibromotor3_enable` Enable the device function
```c
void vibromotor3_enable ( vibromotor3_t *ctx, uint8_t state );
```

- `vibromotor3_write_byte` Generic write the byte of data function
```c
void vibromotor3_write_byte ( vibromotor3_t *ctx, uint8_t reg, uint8_t wr_data );
```

### Application Init

> Initalizes I2C driver, PWM driver and configures Vibro Motor 3 Click board.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vibromotor3_cfg_t vibromotor3_cfg;  /**< Click config object. */

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
    vibromotor3_cfg_setup( &vibromotor3_cfg );
    VIBROMOTOR3_MAP_MIKROBUS( vibromotor3_cfg, MIKROBUS_1 );
    err_t init_flag = vibromotor3_init( &vibromotor3, &vibromotor3_cfg );
    if ( I2C_MASTER_ERROR == init_flag || PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    vibromotor3_enable( &vibromotor3, VIBROMOTOR3_PROPERTY_ENABLE );
    Delay_ms ( 100 );
    
    vibromotor3_soft_rst( &vibromotor3 );
    Delay_ms ( 100 );
    
    vibromotor3_default_cfg( &vibromotor3 );
    Delay_ms ( 100 );
    
    vibromotor3_set_duty_cycle( &vibromotor3, 0.0 );
    vibromotor3_pwm_start( &vibromotor3 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> Changing duty cycle applied in order to get different vibrations.

```c
void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    vibromotor3_set_duty_cycle ( &vibromotor3, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) {
        duty_inc = -1;
    } else if ( 0 == duty_cnt ) {
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
