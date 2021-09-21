\mainpage Main Page

---
# Compass 6 click

> Compass 6 Click is a compact add-on board perfect for implementation in applications such as an electronic compass. This board features the HSCDTD008A, a high-sensitivity geomagnetic sensor from ALPS Alpine. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/compass_6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/compass-6-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Compass6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Compass6 Click driver.

#### Standard key functions :

- `compass6_cfg_setup` Config Object Initialization function.
```c
void compass6_cfg_setup ( compass6_cfg_t *cfg );
```

- `compass6_init` Initialization function.
```c
err_t compass6_init ( compass6_t *ctx, compass6_cfg_t *cfg );
```

- `compass6_default_cfg` Click Default Configuration function.
```c
err_t compass6_default_cfg ( compass6_t *ctx );
```

#### Example key functions :

- `compass6_get_axes_data` Magnetic axes data reading.
```c
err_t compass6_get_axes_data ( compass6_t *ctx, compass6_axes_t *axes_data );
```

- `compass6_data_ready` Get data ready pin state.
```c
uint8_t compass6_data_ready ( compass6_t *ctx );
```

- `compass6_generic_read` Reading function.
```c
err_t compass6_generic_read ( compass6_t *ctx, uint8_t reg, uint8_t *rx_data );
```

## Example Description

> This example is a showcase the ability of the device
to read 3 axis data of magnetic raw value when data is ready.

**The demo application is composed of two sections :**

### Application Init

> Initialization of communication modules (I2C, UART) and data 
ready pin as input. Then reads identification data and checks 
if some of them have wrong value, and configures device for reading.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    compass6_cfg_t compass6_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    compass6_cfg_setup( &compass6_cfg );
    COMPASS6_MAP_MIKROBUS( compass6_cfg, MIKROBUS_1 );
    err_t init_flag = compass6_init( &compass6, &compass6_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint8_t temp_data = 0;
    compass6_generic_read( &compass6, COMPASS6_REG_WHO_I_AM, &temp_data );
    log_printf( &logger, " > Who am I: 0x%.2X\r\n", ( uint16_t )temp_data );
    if ( COMPASS6_WHO_AM_I != temp_data )
    {
        log_error( &logger, " Who am I. " );
    }
    
    compass6_generic_read( &compass6, COMPASS6_REG_INFO_VERSION, &temp_data );
    log_printf( &logger, " > Version: 0x%.2X\r\n", ( uint16_t )temp_data );
    if ( COMPASS6_VERSION != temp_data )
    {
        log_error( &logger, " Version. " );
    }
    
    compass6_generic_read( &compass6, COMPASS6_REG_INFO_ALPS, &temp_data );
    log_printf( &logger, " > ALPS: 0x%.2X\r\n", ( uint16_t )temp_data );
    if ( COMPASS6_ALPS != temp_data )
    {
        log_error( &logger, " ALPS. " );
    }

    compass6_default_cfg ( &compass6 );
    
    log_info( &logger, " Application Task " );
    Delay_ms( 2000 );
}

```

### Application Task

> Checks Data ready pin and if asserted high it will read data of all
3 axes(x, y, z) and log data to Terminal and set delay of 500ms.

```c

void application_task ( void ) 
{
    if ( compass6_data_ready( &compass6 ) )
    {      
        compass6_axes_t axes_data;
        compass6_get_axes_data( &compass6, &axes_data );
        log_printf( &logger, " > X: %d\r\n", axes_data.x );
        log_printf( &logger, " > Y: %d\r\n", axes_data.y );
        log_printf( &logger, " > Z: %d\r\n", axes_data.z );
        log_printf( &logger, "*********************\r\n" );
        Delay_ms( 500 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
