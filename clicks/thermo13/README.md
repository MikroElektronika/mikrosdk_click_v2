
---
# Thermo 13 Click

> [Thermo 13 Click](https://www.mikroe.com/?pid_product=MIKROE-3688) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3688&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> The application measures temperature 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo13

### Example Key Functions

- `thermo13_cfg_setup` Config Object Initialization function. 
```c
void thermo13_cfg_setup ( thermo13_cfg_t *cfg );
``` 
 
- `thermo13_init` Initialization function. 
```c
err_t thermo13_init ( thermo13_t *ctx, thermo13_cfg_t *cfg );
```

- `thermo13_default_cfg` Click Default Configuration function. 
```c
void thermo13_default_cfg ( thermo13_t *ctx );
```

- `thermo13_set_temp_limit` Set temperature limit register. 
```c
void thermo13_set_temp_limit ( thermo13_t *ctx, uint8_t temp_reg, float temp );
```
 
- `thermo13_get_temp_limit` Get temperature register. 
```c
float thermo13_get_temp_limit ( thermo13_t *ctx, uint8_t temp_reg );
```

- `thermo13_get_ambient_temperature_data` Ambient temperature data. 
```c
float thermo13_get_ambient_temperature_data ( thermo13_t *ctx, uint8_t temp_in );
```

### Application Init

> Initializes the driver init, configures the module and reads the temperature Limit LOW/HIGH values that are set.


```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo13_cfg_t cfg;
    
    float temp_limit_low;
    float temp_limit_high;

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

    //  Click initialization

    thermo13_cfg_setup( &cfg );
    THERMO13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo13_init( &thermo13, &cfg );

    // Configuration 
   
    thermo13_configuration( &thermo13, THERMO13_CFG_CONTINUOUS_MEASUREMENT |
                            THERMO13_CFG_FAULT_QUEUE_1 |
                            THERMO13_CFG_ALERT_ACTIVE_HIGH |
                            THERMO13_CFG_INTERRUPT_IS_ACTIVE |
                            THERMO13_CFG_WAIT_TIME_X16 );

        
    // Temperature Register
    log_printf( &logger, " --- Temperature register data --- \r\n \r\n" );

    temp_limit_low = thermo13_get_temp_limit ( &thermo13, THERMO13_REG_TEMPERATURE_LIMIT_LOW );
    log_printf( &logger, " --- Temp - Limit LOW : %.2f C \r\n ", temp_limit_low );

    temp_limit_high = thermo13_get_temp_limit ( &thermo13, THERMO13_REG_TEMPERATURE_LIMIT_HIGH );
    log_printf( &logger, " --- Temp - Limit HIGH :  %.2f C \r\n \r\n  ", temp_limit_high );
    
    log_printf( &logger, " --- Ambient temperature measurement --- \r\n " );

}
```

### Application Task

> Reads ambient temperature data and this data logs to USBUART every 1500ms.

```c
void application_task ( void )
{
    float temperature;

    temperature = thermo13_get_ambient_temperature_data ( &thermo13,  THERMO13_TEMP_IN_CELSIUS );

    log_printf( &logger, "** temperature %.2f ** \r\n" );

    log_printf( &logger, " ----------------------------\r\n" );

    Delay_ms ( 1000 );
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
