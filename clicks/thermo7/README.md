
---
# Thermo 7 Click

> [Thermo 7 Click](https://www.mikroe.com/?pid_product=MIKROE-2979) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2979&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application reads ambient temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo7

### Example Key Functions

- `thermo7_cfg_setup` Config Object Initialization function. 
```c
void thermo7_cfg_setup ( thermo7_cfg_t *cfg );
``` 
 
- `thermo7_init` Initialization function. 
```c
err_t thermo7_init ( thermo7_t *ctx, thermo7_cfg_t *cfg );
```

- `thermo7_default_cfg` Click Default Configuration function. 
```c
void thermo7_default_cfg ( thermo7_t *ctx );
```

- `thermo7_get_hysteresis_temperature` This fuction gets Hysteresis Temperature. 
```c
int16_t thermo7_get_hysteresis_temperature ( thermo7_t *ctx );
```
 
- `thermo7_set_limit_temperature` This fuction sets limit temperature. 
```c
void thermo7_set_limit_temperature ( thermo7_t *ctx, int16_t temperature );
```

- `thermo7_get_interrupt` This fuction reads state of interrupt pins. 
```c
uint8_t thermo7_get_interrupt ( thermo7_t *ctx );
```

### Application Init

> Initializes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo7_cfg_t cfg;

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

    thermo7_cfg_setup( &cfg );
    THERMO7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo7_init( &thermo7, &cfg );

    thermo7_set_configuration( &thermo7, THERMO7_CONFIG_COMPARATOR_MODE | THERMO7_CONFIG_ALERT_POLARITY_ACTIVE_HIGH );
    thermo7_set_resolution( &thermo7, THERMO7_CONFIG_ADC_RESOLUTION_12bit );
}
```

### Application Task

> Reads ambient temperature and logs to USBUART every 1 seconds.

```c
void application_task ( void )
{
    float ambient_temperature;

    ambient_temperature = thermo7_read_ambient_temperature( &thermo7 );
    log_printf( &logger, " Ambient temperature : %f �C\r\n", ambient_temperature );

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
