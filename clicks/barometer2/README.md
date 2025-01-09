
---
# Barometer 2 Click

> [Barometer 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3603) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3603&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> The example starts off with the initialization and configuration of the Click and logger modules, tests the communication channel and reads and displays temperature and pressure values every second.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer2

### Example Key Functions

- `barometer2_cfg_setup` Config Object Initialization function. 
```c
void barometer2_cfg_setup ( barometer2_cfg_t *cfg );
``` 
 
- `barometer2_init` Initialization function. 
```c
err_t barometer2_init ( barometer2_t *ctx, barometer2_cfg_t *cfg );
```

- `barometer2_default_cfg` Click Default Configuration function. 
```c
void barometer2_default_cfg ( barometer2_t *ctx );
```

- `barometer2_get_pressure` Gets the pressure value. 
```c
float barometer2_get_pressure ( barometer2_t *ctx, uint8_t press_format );
```
 
- `barometer2_get_temperature` Gets the temperature value. 
```c
float barometer2_get_temperature ( barometer2_t *ctx, uint8_t temp_format );
```

- `barometer2_software_reset` Resets the device. 
```c
void barometer2_software_reset ( barometer2_t *ctx );
```

### Application Init

> Initializes and configures the Click and logger modules and tests the communication for errors.

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    barometer2_cfg_t cfg;
    
    uint8_t test;

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

    barometer2_cfg_setup( &cfg );
    BAROMETER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barometer2_init( &barometer2, &cfg );
    barometer2_default_cfg( &barometer2 );

    // Test communication

    test = barometer2_read_byte( &barometer2, BAROMETER2_REG_WHO_AM_I ); 

    if ( test == BAROMETER2_WHO_AM_I )
    {
        log_printf( &logger, "---- Communication OK!!! ----\r\n" );
    }
    else
    {
        log_printf( &logger, "---- Communication ERROR!!! ----\r\n" );
        for ( ; ; );
    } 

    // Software reset 

    barometer2_software_reset( &barometer2 );
    Delay_1sec();

    Delay_1sec( );
    log_printf( &logger, "---- Start Measurement ---- \r\n" );
}
```

### Application Task

> Reads and displays temperature and pressure values every second.

```c
void application_task ( )
{
    float temperature;
    float pressure;
     
    temperature = barometer2_get_temperature( &barometer2, BAROMETER2_TEMPERATURE_IN_CELSIUS );
    log_printf( &logger, " Temperature : %f ", temperature );

    pressure = barometer2_get_pressure( &barometer2, BAROMETER2_PRESSURE_DATA_IN_mBar );
    log_printf( &logger, " Pressure : %f \n", pressure );

    log_printf( &logger, "--------------------------\n" );
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
