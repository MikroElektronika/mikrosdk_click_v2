
---
# Fan 6  Click

> [Fan 6 Click](https://www.mikroe.com/?pid_product=MIKROE-3867) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3867&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo application reads tachometer value which is calculated as rpm value, and reads
> temperature of external diode in celsius value.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Fan6

### Example Key Functions

- `fan6_cfg_setup` Config Object Initialization function. 
```c
void fan6_cfg_setup ( fan6_cfg_t *cfg );
``` 
 
- `fan6_init` Initialization function. 
```c
err_t fan6_init ( fan6_t *ctx, fan6_cfg_t *cfg );
```

- `fan6_default_cfg` Click Default Configuration function. 
```c
void fan6_default_cfg ( fan6_t *ctx );
```

- `fan6_read_eeprom` This function reads 256 bytes from EEPROM. 
```c
void fan6_read_eeprom ( fan6_t *ctx, uint8_t *data_out );
```
 
- `fan6_set_pwm_mode` This function sets Fan on PWM mode and determines Fan speed (PWM duty). 
```c
void fan6_set_pwm_mode ( fan6_t *ctx, const uint8_t pwm_duty );
```

- `fan6_read_tachometer` This function reads current tachometer value and calculates that value in rpm. 
```c
uint32_t fan6_read_tachometer ( fan6_t *ctx );
```

### Application Init

> Initializes device configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    fan6_cfg_t cfg;

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

    fan6_cfg_setup( &cfg );
    FAN6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fan6_init( &fan6, &cfg );
    
    fan6_enable_device( &fan6, 1 );
    Delay_ms ( 500 );
    
    fan6_default_cfg( &fan6 );
    tachometer = 0;
}
```

### Application Task

> Reads tachometer value which is calculated as rpm value, and reads
> temperature of external diode in celsius value. All this results logs on USB UART.
> Repeats operation every 500 ms.>
 

```c
void application_task ( void )
{
    float temp_diode;

    temp_diode = fan6_get_temperature( &fan6, FAN6_INTERNAL_TEMP_READ_REG );
    log_printf( &logger, "Temperature of DIODE is: %f - Cels \r\n", temp_diode );
    
    fan6_set_pwm_mode( &fan6, duty_cycle );
    
    duty_cycle += 5;
    
    tachometer = fan6_read_tachometer( &fan6 );
    log_printf( &logger, "Tachometer value is: %lu rpm \r\n", tachometer );
    log_printf( &logger, "---------------------------------------- \r\n", tachometer );
    
    Delay_ms ( 500 );
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
