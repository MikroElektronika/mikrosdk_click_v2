
---
# Thermo J Click

> [Thermo J Click](https://www.mikroe.com/?pid_product=MIKROE-2811) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2811&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This app measured temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ThermoJ

### Example Key Functions

- `thermoj_cfg_setup` Config Object Initialization function. 
```c
void thermoj_cfg_setup ( thermoj_cfg_t *cfg );
``` 
 
- `thermoj_init` Initialization function. 
```c
err_t thermoj_init ( thermoj_t *ctx, thermoj_cfg_t *cfg );
```

- `thermoj_default_cfg` Click Default Configuration function. 
```c
void thermoj_default_cfg ( thermoj_t *ctx );
```

- `thermoj_check_data_ready` Check the status of data ready function. 
```c
uint8_t thermoj_check_data_ready ( thermoj_t *ctx );
```
 
- `thermoj_set_thermocouple_type` Set thermocouple type sensor configuration function. 
```c
void thermoj_set_thermocouple_type ( thermoj_t *ctx, uint8_t thermocouple_type );
```

- `thermoj_get_temperature` Get temperature function. 
```c
float thermoj_get_temperature ( thermoj_t *ctx );
```

### Application Init

> Initialization device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermoj_cfg_t cfg;

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

    thermoj_cfg_setup( &cfg );
    THERMOJ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermoj_init( &thermoj, &cfg );

    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "      Thermo J  Click      \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    
    log_printf( &logger, " Set thermocouple type:  J \r\n" );

    thermoj_set_thermocouple_type( &thermoj, THERMOJ_THERMOCOUPLE_TYPE_J );
    Delay_ms ( 1000 );

    log_printf( &logger, "---------------------------\r\n" );
}
```

### Application Task

> This is a example which demonstrates the use of Thermo J Click board.
> Measured temperature data from the MCP9600 sensor on Thermo J Click board.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    check_data_ready =  thermoj_check_data_ready( &thermoj );

    if ( check_data_ready )
    {
        temperature = thermoj_get_temperature( &thermoj );

        log_printf( &logger, " Temperature : %.2f Celsius\r\n", temperature );
        log_printf( &logger, "---------------------------\r\n" );

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
