
---
# Thermostat Click

> [Thermostat Click](https://www.mikroe.com/?pid_product=MIKROE-2273) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2273&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application regulates value of temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermostat

### Example Key Functions

- `thermostat_cfg_setup` Config Object Initialization function. 
```c
void thermostat_cfg_setup ( thermostat_cfg_t *cfg );
``` 
 
- `thermostat_init` Initialization function. 
```c
err_t thermostat_init ( thermostat_t *ctx, thermostat_cfg_t *cfg );
```

- `thermostat_default_cfg` Click Default Configuration function. 
```c
void thermostat_default_cfg ( thermostat_t *ctx );
```

- `uint16_t thermostat_read_data` Generic read 16-bit data function. 
```c
 uint16_t thermostat_read_data ( thermostat_t *ctx, uint8_t reg_address );
```
 
- `thermostat_get_temperature` Get temperature in degrees Celsius. 
```c
float thermostat_get_temperature ( thermostat_t *ctx );
```

- `thermostat_convert_fahrenheit` Convert temperature in degrees Celsius to Fahrenheit. 
```c
float thermostat_convert_fahrenheit ( thermostat_t *ctx, float temp_celsius );
```

- `thermostat_set_configuration` Set configuration function. 
```c
void thermostat_set_configuration ( thermostat_t *ctx, uint16_t config_value );
```

- `thermostat_set_temp_hyst` Set temperature hysterezis function. 
```c
void thermostat_set_temp_hyst ( thermostat_t *ctx, int8_t temp_hyst );
```

- `thermostat_set_temp_ref` Set referent temperature function. 
```c
void thermostat_set_temp_ref ( thermostat_t *ctx, int8_t temp_ref );
```

- `thermostat_soft_reset` Soft reset function. 
```c
void thermostat_soft_reset ( thermostat_t *ctx );
```

- `thermostat_switch_on` Set on thermal switch function. 
```c
void thermostat_switch_on ( thermostat_t *ctx );
```

- `thermostat_switch_off` Set off thermal switch function. 
```c
void thermostat_switch_off ( thermostat_t *ctx );
```

- `thermostat_enable` Thermostat enabled function. 
```c
void thermostat_enable ( thermostat_t *ctx );
```

- `thermostat_disable` Thermostat disabled function. 
```c
void thermostat_disable ( thermostat_t *ctx );
```

### Application Init

> Initialization driver enable's - I2C, soft reset sesnor, set default configuration and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermostat_cfg_t cfg;

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

    thermostat_cfg_setup( &cfg );
    THERMOSTAT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermostat_init( &thermostat, &cfg );

    thermostat_soft_reset( &thermostat );
    Delay_ms ( 100 );
    log_printf( &logger, "     Configuration    \r\n");

    thermostat_set_configuration( &thermostat, THERMOSTAT_DEFAULT_CONFIG );
    Delay_ms ( 100 );
    log_printf( &logger, "----------------------\r\n" );
}
```

### Application Task

> This is a example which demonstrates the use of Thermostat Click board.

```c
void application_task ( void )
{
    float temperature;
    float limit_max = 25.0;
    float limit_min = 15.0;

    temperature = thermostat_get_temperature( &thermostat );

    log_printf( &logger, " Temperature : %.2f \r\n", temperature );

    if ( ( temperature < limit_max ) && ( temperature > limit_min ) )
    { 
        thermostat_switch_on(  &thermostat  );
    }
    else
    {   
        thermostat_switch_off(  &thermostat  );
        log_printf( &logger, "----------------------\r\n" );
    }
    Delay_ms ( 1000 );
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
