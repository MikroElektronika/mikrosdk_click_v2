\mainpage Main Page

---

# IRNSS click

> IRNSS Click is a compact add-on board that provides fast positioning capability. This board features the L89H, a high-performance IRNSS-enabled GNSS module capable of acquiring and tracking GPS, IRNSS, GLONASS, BeiDou, Galileo, and QZSS signals from Quectel Wireless Solutions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irnss_click.png">
</p>

[click Product page](https://www.mikroe.com/irnss-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Dec 2020.
- **Type**          : UART type


# Software Support

We provide a library for the IRNSS Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for IRNSS Click driver.
```

#### Standard key functions :

- Config Object Initialization function.
```
void irnss_cfg_setup ( irnss_cfg_t *cfg );
```

- Initialization function.
```
err_t irnss_init ( irnss_t *ctx, irnss_cfg_t *cfg );
```

#### Example key functions :

> IRNSS data writing function.
```
err_t irnss_generic_write ( irnss_t *ctx, char *data_buf, uint16_t len );
```

> IRNSS data reading function.
```
err_t irnss_generic_read ( irnss_t *ctx, char *data_buf, uint16_t max_len );
```

> Sets state of the rst pin setting.
```
void irnss_set_rst_pin_state ( irnss_t *ctx, uint8_t state );
```

## Examples Description

> This example application reads data, checks for specific command. If command is found checks for data validation and if it's found logs that data to UART terminal.

**The demo application is composed of two sections :**

### Application Init

> Initializes log and device communication modules

```
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irnss_cfg_t irnss_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );
    Delay_ms( 500 );

    // Click initialization.
    irnss_cfg_setup( &irnss_cfg );
    IRNSS_MAP_MIKROBUS( irnss_cfg, MIKROBUS_1 );
    err_t init_flag  = irnss_init( &irnss, &irnss_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    app_buf_cnt = 0;
    last_error_flag = 0;
    log_info( &logger, " Application Task " );
    Delay_ms( 500 );
    irnss_process();
    irnss_clear_app_buf(  );
}
```

### Application Task

>Collects data and waits for Latitude, longitude, and altitude data from the device.\
When it's received logs data, and while waiting it will log '.' until data is received.

```
void application_task ( void ) 
{
    irnss_process();
    
    
    err_t error_flag = irnss_element_parser( RSP_GNGGA, RSP_GNGGA_LATITUDE_ELEMENT, 
                                             latitude_data );
    
    error_flag |= irnss_element_parser(  RSP_GNGGA, RSP_GNGGA_LONGITUDE_ELEMENT, 
                                         longitude_data );
    
    error_flag |= irnss_element_parser(  RSP_GNGGA, RSP_GNGGA_ALTITUDE_ELEMENT, 
                                         altitude_data );
    
    
    if ( error_flag == 0 )
    {
        if ( last_error_flag != 0)
        {
            log_printf( &logger, "\r\n" );
        }
        log_printf( &logger, ">Latitude:\r\n - deg: %.2s \r\n - min: %s\r\n", 
                    latitude_data, &latitude_data[ 2 ] );
        
        log_printf( &logger, ">Longitude:\r\n - deg: %.3s \r\n - min: %s\r\n", 
                    longitude_data, &longitude_data[ 3 ] );
        
        log_printf( &logger, ">Altitude:\r\n - %sm\r\n", 
                    altitude_data );
        
        log_printf( &logger, "----------------------------------------\r\n" );
    }
    else if ( error_flag < -1 )
    {
        if ( last_error_flag == 0 )
        {
            log_printf( &logger, "Waiting for data" );
        }
        log_printf( &logger, "." );
    }
    
    if ( error_flag != -1 )
    {
        last_error_flag = error_flag;
        irnss_clear_app_buf(  );
    }
}
```

## Note

> For the device to connect it can take it from 1 to 8 minutes to get useful data from satellites.\
Time to connect is depending on weather, do you have an external antenna, etc.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IRNSS

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
