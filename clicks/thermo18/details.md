
---
# Thermo 18 Click

> Thermo 18 Click is a compact add-on board that provides an accurate temperature measurement. This board features the WSEN-TIDS, a silicon-based, high-precision digital temperature sensor with embedded analog and digital signal processing unit from Würth Elektronik.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo_18_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/thermo-18-click)

---


#### Click library

- **Author**        : Luka FIlipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo18 Click driver.

#### Standard key functions :

- `thermo18_cfg_setup` Config Object Initialization function.
```c
void thermo18_cfg_setup ( thermo18_cfg_t *cfg );
```

- `thermo18_init` Initialization function.
```c
err_t thermo18_init ( thermo18_t *ctx, thermo18_cfg_t *cfg );
```

- `thermo18_default_cfg` Click Default Configuration function.
```c
err_t thermo18_default_cfg ( thermo18_t *ctx );
```

#### Example key functions :

- `thermo18_read_temperature` Reads and calculates temperature value.
```c
err_t thermo18_read_temperature ( thermo18_t *ctx, float *temperature )
```

- `thermo18_set_temperature_threshold` Sets temperature threshold.
```c
err_t thermo18_set_temperature_threshold ( thermo18_t *ctx, uint8_t threshold_reg, float threshold_limit );
```

- `thermo18_reset` Resets device.
```c
err_t thermo18_reset ( thermo18_t *ctx );
```

## Example Description

> The example application showcases ability of device
to read temperature and detect and assert interrupt
on undertemperature or overtemperature thresholds.

**The demo application is composed of two sections :**

### Application Init

> Initialization of communication modules and interrupt pin.
Reads device ID to check comunication. Then resets device,
and sets undertemperature and overtemperature thresholds
on 24 and 30 degrees Celsius. In the end enables OneShot 
temperature conversion.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo18_cfg_t thermo18_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    thermo18_cfg_setup( &thermo18_cfg );
    THERMO18_MAP_MIKROBUS( thermo18_cfg, MIKROBUS_1 );
    err_t init_flag = thermo18_init( &thermo18, &thermo18_cfg );
    if ( I2C_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    uint8_t temp_data = 0;
    thermo18_generic_read( &thermo18, THERMO18_REG_DEVICE_ID, &temp_data );
    log_printf( &logger, " > ID: 0x%.2X\r\n", ( uint16_t )temp_data );

    if ( THERMO18_DEVICE_ID != temp_data )
    {
        log_error( &logger, " Device ID. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( thermo18_default_cfg ( &thermo18 ) )
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    //One shot reading
    thermo18_generic_write( &thermo18, THERMO18_REG_CTRL, THERMO18_CONTROL_ONESHOT_ENABLED );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Checks status to see if the temperature conversion is finished.
When it's finished reads and logs calculated temperature data.
Then checks if status is asserted for threshold detection, and
logs if detected. In the end re-enables OneShot conversion.

```c

void application_task ( void ) 
{
    uint8_t status;
    thermo18_generic_read( &thermo18, THERMO18_REG_STATUS, &status );
    //Check if data is ready
    if ( THERMO18_STATUS_DATA_READY == ( status & THERMO18_STATUS_DATA_BUSY ) )
    {
        //Temperature reading
        float temp = 0.0;
        thermo18_read_temperature( &thermo18, &temp );
        log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temp );
        //Check threshold
        if ( 0 != status )
        {
            if ( THERMO18_STATUS_OVERTEMPERATURE == status )
            {
                log_info( &logger, " Overtemperature Threshold detected." );
            }
            else if ( THERMO18_STATUS_UNDERTEMPERATURE == status )
            {
                log_info( &logger, " Undertemperature Threshold detected." );
            }
        }
        //Re-Enable One shot reading
        thermo18_generic_write( &thermo18, THERMO18_REG_CTRL, THERMO18_CONTROL_ONESHOT_ENABLED );
    }

    Delay_ms ( 300 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
