
---
# Altitude Click

> [Altitude Click](https://www.mikroe.com/?pid_product=MIKROE-1489) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1489&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nemanja Medakovic
- **Date**          : Oct 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This is a example which demonstrates the use of Altitude Click board.
> This demo example offers the altitude [m], pressure [mbar] and temperature
> [deg C] measurements from sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Altitude

### Example Key Functions

- `altitude_cfg_setup` Configuration Object Setup function. 
```c
void altitude_cfg_setup ( altitude_cfg_t *cfg );
```
 
- `altitude_init` Click Initialization function. 
```c
altitude_err_t altitude_init ( altitude_t *ctx, altitude_cfg_t *cfg );
```

- `altitude_default_cfg` Click Default Configuration function. 
```c
void altitude_default_cfg ( altitude_t *ctx );
```

- `altitude_generic_single_write` Generic Single Write function. 
```c
altitude_err_t altitude_generic_single_write ( altitude_t *ctx, i2c_master_data_t reg_addr, i2c_master_data_t data_in );
```
 
- `altitude_generic_multiple_read` Generic Multiple Read function. 
```c
altitude_err_t altitude_generic_multiple_read ( altitude_t *ctx, i2c_master_data_t reg_addr, i2c_master_data_t *data_out, uint8_t n_data );
```

- `altitude_get_altitude` Altitude Get function. 
```c
float altitude_get_altitude ( altitude_t *ctx );
```

### Application Init

> Initializes I2C driver and all used pins, performs a default configuration
> for Altitude Click board and initializes the uart console for results
> logging.

```c
void application_init( void )
{
    altitude_cfg_t altitude_cfg;
    log_cfg_t log_cfg;

    //  Click initialization.
    altitude_cfg_setup( &altitude_cfg );
    ALTITUDE_MAP_MIKROBUS( altitude_cfg, MIKROBUS_1 );
    altitude_init( &altitude, &altitude_cfg );
    altitude_default_cfg( &altitude );

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
    log_init( &console, &log_cfg );
    log_init( &console, &console_cfg );
    log_printf( &console, "***  Altitude initialization done  ***\r\n" );
    log_printf( &console, "**************************************\r\n" );
}
```

### Application Task

> Shows two different uses of sensor, altimeter and barometer mode.
> Reads the altitude, pressure and temperature results in standard units and
> sends this results to the console.

```c
void application_task( void )
{
    float altitude_result;
    float pressure_result;
    float temperature_result;

    //  Altimeter sensor mode for altitude data reading.
    altitude_set_sensor_mode( &altitude, ALTITUDE_SENSMOD_ALTIMETER );
    Delay_ms ( 100 );

    while ( 0 == altitude_get_drdy_status( &altitude, ALTITUDE_STATUS_FLAG_PDR ) );

    altitude_result = altitude_get_altitude( &altitude );

    //  Barometer sensor mode for pressure data reading.
    altitude_set_sensor_mode( &altitude, ALTITUDE_SENSMOD_BAROMETER );
    Delay_ms ( 100 );

    while ( 0 == altitude_get_drdy_status( &altitude, ALTITUDE_STATUS_FLAG_PDR ) );

    pressure_result = altitude_get_pressure( &altitude );
    temperature_result = altitude_get_temperature( &altitude );

    log_printf( &console, "** Altitude is %.2f m\r\n", altitude_result );
    log_printf( &console, "** Pressure is %.2f mbar\r\n", pressure_result );
    log_printf( &console, "** Temperature is %.2f Celsius\r\n", temperature_result );
    log_printf( &console, "**************************************\r\n" );
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
