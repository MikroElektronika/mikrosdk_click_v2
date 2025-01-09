
---
# Fan Click

> [Fan Click](https://www.mikroe.com/?pid_product=MIKROE-2004) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2004&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is controller for powering and regulating.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Fan

### Example Key Functions

- `fan_cfg_setup` Config Object Initialization function. 
```c
void fan_cfg_setup ( fan_cfg_t *cfg );
``` 
 
- `fan_init` Initialization function. 
```c
err_t fan_init ( fan_t *ctx, fan_cfg_t *cfg );
```

- `fan_generic_write` Generic write function. 
```c
void fan_generic_write ( fan_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```
 
- `fan_generic_read` Generic read function. 
```c
void fan_generic_read ( fan_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```
- `fan_lock_registers` Fan Click lock registers. 
```c
void fan_lock_registers ( fan_t *ctx, uint8_t lock );
```

### Application Init

> Initialization driver init and init chip. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    fan_cfg_t fan_cfg;

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

    fan_cfg_setup( &fan_cfg );
    FAN_MAP_MIKROBUS( fan_cfg, MIKROBUS_1 );
    if ( fan_init( &fan, &fan_cfg ) == I2C_MASTER_ERROR )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );

        for ( ; ; );
    }
    log_info( &logger, "---- Application Init Done ----" );
    fan_default_cfg( &fan );
    fan_pwm_base( &fan, FAN_PWM_BASE_FREQ_HALF_SCALE );
    log_info( &logger, "---- Application Program Running... ----\n" );
}
```

### Application Task

> Performs a control of the fan and reads rotation per minute (RPM).
> Results will be sent to the usb uart terminal.

```c
void application_task ( void )
{
    for ( uint8_t duty = FAN_DUTY_RATIO_0_PER; duty <= FAN_DUTY_RATIO_100_PER;
          duty += FAN_DUTY_RATIO_10_PER )
    {
        fan_setting( &fan, duty );
        log_printf( &logger, " Duty Ratio : %u%%\r\n", (uint16_t)duty );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );

        uint16_t tacho = 0;

        fan_get_tach( &fan, &tacho );
        log_printf( &logger, " Rotation per minute : %urpm\r\n\n", tacho );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
