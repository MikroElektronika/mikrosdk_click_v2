\mainpage Main Page

---
# 3D Hall 8 click

3D Hall 8 Click is a compact add-on board containing an ultra-small 3D-magnetic sensor for industrial and consumer applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3d_hall_8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/3d-hall-8-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jan 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the 3DHall8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 3DHall8 Click driver.

#### Standard key functions :

- `c3dhall8_cfg_setup` Config Object Initialization function.
```c
void c3dhall8_cfg_setup ( c3dhall8_cfg_t *cfg );
```

- `c3dhall8_init` Initialization function.
```c
C3DHALL8_RETVAL c3dhall8_init ( c3dhall8_t *ctx, c3dhall8_cfg_t *cfg );
```

- `c3dhall8_default_cfg` Click Default Configuration function.
```c
void c3dhall8_default_cfg ( c3dhall8_t *ctx );
```

#### Example key functions :

- `c3dhall8_generic_write` 3D Hall 8 I2C writing function.
```c
err_t c3dhall8_generic_write ( c3dhall8_t *ctx, uint8_t reg, uint8_t tx_buf )
```

- `c3dhall8_read_sensor_data` Reading sensor data function.
```c
void c3dhall8_read_sensor_data ( c3dhall8_t *ctx, c3dhall8_data_t *sensor_data );
```

- `c3dhall8_get_xyz_magnetic_matching` Calculating magnetic matching.
```c
float c3dhall8_get_xyz_magnetic_matching ( c3dhall8_t *ctx, c3dhall8_data_t sensor_data );
```

## Example Description

> This application shows capability of 3D Hall 8 Click board. 
It configures device and reads sensor data. Sensor is capeable 
of reading magnetic flux density from 3 axes and temperature.

**The demo application is composed of two sections :**

### Application Init

> Initialization of device communication and application log and configures device.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall8_cfg_t c3dhall8_cfg;  /**< Click config object. */
    uint8_t rx_data;

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    c3dhall8_cfg_setup( &c3dhall8_cfg );
    C3DHALL8_MAP_MIKROBUS( c3dhall8_cfg, MIKROBUS_1 );
    err_t init_flag = c3dhall8_init( &c3dhall8, &c3dhall8_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger," > Setting configuration...\r\n" );
    c3dhall8_default_cfg ( &c3dhall8 ); 

    log_info( &logger, " Application Task " );
    log_printf( &logger, "**************************************\r\n" );
    Delay_ms( 1000 );
}

```

### Application Task

> Reads data from the device and logs it in span of 500ms.

```c

void application_task ( void ) 
{
    c3dhall8_data_t sens_data;
    c3dhall8_read_sensor_data( &c3dhall8, &sens_data );
    
    log_printf( &logger, "> X[mT]: %.2f\r\n> Y[mT]: %.2f\r\n> Z[mT]: %.2f \r\n> Temperature[C]: %.2f\r\n", 
                sens_data.x_axis, sens_data.y_axis, sens_data.z_axis, sens_data.temperature );
    float magnetic_match = c3dhall8_get_xyz_magnetic_matching( &c3dhall8, sens_data );
    log_printf( &logger, "> XYZ magnetic matching: %.2f\r\n", magnetic_match );
    log_printf( &logger, "**************************************\r\n" );

    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
