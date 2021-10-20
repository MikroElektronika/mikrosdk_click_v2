 

---
# Altitude click

Altitude click features a MEMS pressure sensor MPL3115A2, which provides accurate pressure/altitude (20-bit) and temperature (12-bit) data.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/altitude_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/altitude-click)

---


#### Click library 

- **Author**        : Nemanja Medakovic
- **Date**          : Oct 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Altitude Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Altitude Click driver.

#### Standard key functions :

- Configuration Object Setup function.
> void altitude_cfg_setup( altitude_cfg_t *cfg );
 
- Click Initialization function.
> altitude_err_t altitude_init( altitude_t *ctx, altitude_cfg_t *cfg );

- Click Default Configuration function.
> void altitude_default_cfg( altitude_t *ctx );


#### Example key functions :

- Generic Single Write function.
> altitude_err_t altitude_generic_single_write( altitude_t *ctx, i2c_master_data_t reg_addr, i2c_master_data_t data_in );
 
- Generic Multiple Read function.
> altitude_err_t altitude_generic_multiple_read( altitude_t *ctx, i2c_master_data_t reg_addr, i2c_master_data_t *data_out, uint8_t n_data );

- Altitude Get function.
> float altitude_get_altitude( altitude_t *ctx );

## Examples Description

>
> This is a example which demonstrates the use of Altitude Click board.
> This demo example offers the altitude [m], pressure [mbar] and temperature
> [deg C] measurements from sensor.
>

**The demo application is composed of two sections :**

### Application Init

>
> Initializes I2C driver and all used pins, performs a default configuration
> for Altitude Click board and initializes the uart console for results
> logging.
>

```c

void application_init( void )
{
    altitude_cfg_t altitude_cfg;
    log_cfg_t console_cfg;

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
    LOG_MAP_USB_UART( console_cfg );
    log_init( &console, &console_cfg );
    log_write( &console, "***  Altitude initialization done  ***", LOG_FORMAT_LINE );
    log_write( &console, "**************************************", LOG_FORMAT_LINE );
}

```

### Application Task

>
> Shows two different uses of sensor, altimeter and barometer mode.
> Reads the altitude, pressure and temperature results in standard units and
> sends this results to the console.
>

```c

void application_task( void )
{
    float altitude_result;
    float pressure_result;
    float temperature_result;

    //  Altimeter sensor mode for altitude data reading.
    altitude_set_sensor_mode( &altitude, ALTITUDE_SENSMOD_ALTIMETER );

    while (0 == altitude_get_drdy_status( &altitude, ALTITUDE_STATUS_FLAG_PDR ));

    altitude_result = altitude_get_altitude( &altitude );

    //  Barometer sensor mode for pressure data reading.
    altitude_set_sensor_mode( &altitude, ALTITUDE_SENSMOD_BAROMETER );

    while (0 == altitude_get_drdy_status( &altitude, ALTITUDE_STATUS_FLAG_PDR ));

    pressure_result = altitude_get_pressure( &altitude );
    temperature_result = altitude_get_temperature( &altitude );

    log_printf( &console, "** Altitude is %.2f m\r\n", altitude_result );
    log_printf( &console, "** Pressure is %.2f mbar\r\n", pressure_result );
    log_printf( &console, "** Temperature is %.2f %s\r\n", temperature_result, deg_cels );
    log_write( &console, "**************************************", LOG_FORMAT_LINE );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Altitude

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
