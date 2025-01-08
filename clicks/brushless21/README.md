
---
# Brushless 21 Click

> [Brushless 21 Click](https://www.mikroe.com/?pid_product=MIKROE-5055) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5055&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : PWM/I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Brushless 21 Click board by driving the motor at different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless21

### Example Key Functions

- `brushless21_cfg_setup` Config Object Initialization function.
```c
void brushless21_cfg_setup ( brushless21_cfg_t *cfg );
```

- `brushless21_init` Initialization function.
```c
err_t brushless21_init ( brushless21_t *ctx, brushless21_cfg_t *cfg );
```

- `brushless21_default_cfg` Click Default Configuration function.
```c
err_t brushless21_default_cfg ( brushless21_t *ctx );
```

- `brushless21_set_duty_cycle` This function sets the duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless21_set_duty_cycle ( brushless21_t *ctx, float duty_cycle );
```

- `brushless21_get_motor_speed` This function reads the motor speed in Hz.
```c
err_t brushless21_get_motor_speed ( brushless21_t *ctx, float *motor_speed_hz );
```

- `brushless21_switch_direction` This function switches the motor direction by toggling the DIR bit.
```c
err_t brushless21_switch_direction ( brushless21_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the GPIO as a default communication and enables the PWM.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless21_cfg_t brushless21_cfg;  /**< Click config object. */

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
    brushless21_cfg_setup( &brushless21_cfg );
    BRUSHLESS21_MAP_MIKROBUS( brushless21_cfg, MIKROBUS_1 );
    err_t init_flag = brushless21_init( &brushless21, &brushless21_cfg );
    if ( ( PWM_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS21_ERROR == brushless21_default_cfg ( &brushless21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controls the motor speed by changing the PWM duty cycle once per second. The duty cycle ranges from 0% to 100%. 
When the Click board is configured in I2C mode the motor switches the direction at a minimal speed.
Also, the chip internal temperature, VBB voltage and the motor speed readings are supported in I2C mode.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    if ( BRUSHLESS21_OK == brushless21_set_duty_cycle ( &brushless21, duty ) )
    {
        log_printf( &logger, "\r\n Duty Cycle : %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    }
    
    if ( BRUSHLESS21_DRV_SEL_I2C == brushless21.drv_sel ) 
    {
        int8_t temperature = 0;
        float motor_speed = 0;
        float vbb_voltage = 0;
        if ( BRUSHLESS21_OK == brushless21_get_temperature ( &brushless21, &temperature ) )
        {
            log_printf( &logger, " Temperature: %d C\r\n", ( int16_t ) temperature );
        }
        if ( BRUSHLESS21_OK == brushless21_get_motor_speed ( &brushless21, &motor_speed ) )
        {
            log_printf( &logger, " Motor Speed: %.2f Hz\r\n", motor_speed );
        }
        if ( BRUSHLESS21_OK == brushless21_get_vbb_voltage ( &brushless21, &vbb_voltage ) )
        {
            log_printf( &logger, " VBB Voltage: %.2f V\r\n", vbb_voltage );
        }
        if ( 0 == duty_cnt ) 
        {
            duty_inc = 1;
            if ( BRUSHLESS21_OK == brushless21_switch_direction ( &brushless21 ) )
            {
                log_printf( &logger, " Switch direction\r\n" );
            }
        }
    }
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
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
