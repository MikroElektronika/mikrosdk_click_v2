
---
# Heater  Click

> [Heater Click](https://www.mikroe.com/?pid_product=MIKROE-3996) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3996&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> 
>  The devices resolution depends on settings applied.
>  User should consult the datasheet and choose resolution value 
>  that corresponds to the settings applied.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Heater

### Example Key Functions

- `heater_cfg_setup` Config Object Initialization function. 
```c
void heater_cfg_setup ( heater_cfg_t *cfg );
``` 
 
- `heater_init` Initialization function. 
```c
err_t heater_init ( heater_t *ctx, heater_cfg_t *cfg );
```

- `heater_default_cfg` Click Default Configuration function. 
```c
void heater_default_cfg ( heater_t *ctx );
```

- `heater_read_data` This function writes data to the desired register. 
```c
uint16_t heater_read_data ( heater_t *ctx );
```

- `heater_read_mv` Read data in mV. 
```c
float heater_read_mv (  heater_t *ctx  );
```

- `heater_read_temp` Read data in C. 
```c
float heater_read_temp (  heater_t *ctx  );
```

### Application Init

>
> Initialization of PWM module and start heating up
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    heater_cfg_t cfg;
    heater_config_t cfg1;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    heater_cfg_setup( &cfg, &cfg1 );
    HEATER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heater_init( &heater, &cfg, &cfg1 );
    
    frequency = 500;
    
    heater_set_duty_cycle( &heater, heater.pwm_period );
    status_dev = HEATER_HEATING;
    
    log_printf( &logger, " ***** APP INIT ***** \r\n" );
    Delay_ms ( 500 );

}
```

### Application Task

>
> Durning the task device is heating up to 50 degree C and then
> cooling down to 40 degree C
 

```c
void application_task ( void )
{
    temp_read = heater_read_temp( &heater );
    
    if ( ( temp_read > HOT_TEMP ) && ( status_dev == HEATER_WAITING ) )
    {
    status_dev = HEATER_COOLING;
    }
    else if ( ( temp_read < COOL_TEMP ) && ( status_dev == HEATER_WAITING ) )
    {
    status_dev = HEATER_HEATING;
    }

    if ( status_dev == HEATER_HEATING )
    {
    heater_pwm_start ( &heater );
    heater_set_led1_status( &heater, HEATER_LED_ON );
    heater_set_led2_status( &heater, HEATER_LED_OFF );
    status_dev = HEATER_WAITING;
    }
    else if ( status_dev == HEATER_COOLING )
    {
    heater_pwm_stop ( &heater );
    heater_set_led1_status( &heater,HEATER_LED_OFF );
    heater_set_led2_status( &heater,HEATER_LED_ON );
    status_dev = HEATER_WAITING;
    }

    log_printf( &logger,  " - Temperature: %.2f %s\r\n", temp_read, log_degree );
    
    log_printf( &logger, "***************\r\n" );

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
