\mainpage Main Page

---
# GNSS MAX click

GNSS MAX Click is a compact add-on board that provides fast positioning capability. This board features the MAX-M10S, an ultra-low-power GNSS receiver for high-performance asset-tracking from u-blox. The MAX-M10S supports the concurrent reception of four GNSS (GPS, GLONASS, Galileo, and BeiDou), which maximizes the position availability, particularly under challenging conditions such as in deep urban canyons. It is built on the u-blox M10 GNSS platform, which provides exceptional sensitivity and acquisition times for all L1 GNSS systems. It also comes with a configurable host interface, and advanced jamming and spoofing detection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnssmax_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gnss-max-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the GNSSMAX Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSSMAX Click driver.

#### Standard key functions :

- `gnssmax_cfg_setup` Config Object Initialization function.
```c
void gnssmax_cfg_setup ( gnssmax_cfg_t *cfg );
```

- `gnssmax_init` Initialization function.
```c
err_t gnssmax_init ( gnssmax_t *ctx, gnssmax_cfg_t *cfg );
```

- `gnssmax_default_cfg` Click Default Configuration function.
```c
err_t gnssmax_default_cfg ( gnssmax_t *ctx );
```

#### Example key functions :

- `gnssmax_generic_read` GNSS MAX data reading function.
```c
err_t gnssmax_generic_read ( gnssmax_t *ctx, char *data_buf, uint16_t max_len );
```

- `gnssmax_reset` GNSS MAX reset function.
```c
void gnssmax_reset ( gnssmax_t *ctx );
```

- `gnssmax_get_pps` GNSS MAX reads timestamp pin state.
```c
uint8_t gnssmax_get_pps ( gnssmax_t *ctx );
```

## Example Description

> This example showcases device abillity to read data outputed 
from device and show it's coordinates and altitude when connected.

**The demo application is composed of two sections :**

### Application Init

> Initializes host communication modules, additioaln GPIO's used 
for control of device and resets device.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnssmax_cfg_t gnssmax_cfg;  /**< Click config object. */

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
    Delay_ms ( 500 );

    // Click initialization.
    gnssmax_cfg_setup( &gnssmax_cfg );
    GNSSMAX_MAP_MIKROBUS( gnssmax_cfg, MIKROBUS_1 );
    err_t init_flag  = gnssmax_init( &gnssmax, &gnssmax_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    gnssmax_default_cfg( &gnssmax );
    
    last_error_flag = GNSSMAX_OK;
    log_info( &logger, " Application Task " );
    Delay_ms ( 500 );
}

```

### Application Task

> Reads data from device and wait's untill device is connected. 
While not connected it will log '.'. When conneceted and received 
data for latitude, longitude, and altitude it will log that data 
parsed from "GNGGA" command.

```c

void application_task ( void ) 
{
    gnssmax_process();
    
    err_t error_flag = gnssmax_element_parser( RSP_GNGGA, RSP_GNGGA_LATITUDE_ELEMENT, 
                                             latitude_data );
    
    error_flag |= gnssmax_element_parser(  RSP_GNGGA, RSP_GNGGA_LONGITUDE_ELEMENT, 
                                         longitude_data );
    
    error_flag |= gnssmax_element_parser(  RSP_GNGGA, RSP_GNGGA_ALTITUDE_ELEMENT, 
                                         altitude_data );
    
    
    if ( error_flag == GNSSMAX_OK )
    {
        if ( last_error_flag != GNSSMAX_OK )
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
    else if ( error_flag < GNSSMAX_ERROR )
    {
        if ( last_error_flag == GNSSMAX_OK )
        {
            log_printf( &logger, "Waiting for data " );
        }
        log_printf( &logger, "." );
    }
    
    if ( error_flag != GNSSMAX_ERROR )
    {
        last_error_flag = error_flag;
        gnssmax_clear_app_buf(  );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSSMAX

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
