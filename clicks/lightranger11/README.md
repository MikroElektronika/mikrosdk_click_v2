\mainpage Main Page

---
# LightRanger 11 click

> LightRanger 11 Click is a compact add-on board suitable for range-finding and distance-sensing applications. This board features the VL53L7CX, a time-of-flight 8x8 multizone ranging sensor from STMicroelectronics. It is a fast and accurate multizone distance-ranging sensor width of 90° wide FoV. The multizone-ranging output with either 4x4 or 8x8 separate zones, width multitarget detection, and distance measurement in each zone. As a multizone-ranging device, its range is only up to 350cm.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lightranger11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lightranger-11-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the LightRanger 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LightRanger 11 Click driver.

#### Standard key functions :

- `lightranger11_cfg_setup` Config Object Initialization function.
```c
void lightranger11_cfg_setup ( lightranger11_cfg_t *cfg );
```

- `lightranger11_init` Initialization function.
```c
err_t lightranger11_init ( lightranger11_t *ctx, lightranger11_cfg_t *cfg );
```

- `lightranger11_default_cfg` Click Default Configuration function.
```c
err_t lightranger11_default_cfg ( lightranger11_t *ctx );
```

#### Example key functions :

- `lightranger11_get_ranging_data` LightRanger 11 get ranging data function.
```c
err_t lightranger11_get_ranging_data ( lightranger11_t *ctx, lightranger11_results_data_t *results );
```

- `lightranger11_get_resolution` LightRanger 11 get resolution function.
```c
err_t lightranger11_get_resolution ( lightranger11_t *ctx, uint8_t *resolution );
```

- `lightranger11_get_int_pin` LightRanger 11 get int pin function.
```c
uint8_t lightranger11_get_int_pin ( lightranger11_t *ctx );
```

## Example Description

> This example demonstrates the use of LightRanger 11 click board by reading and displaying
> 8x8 zones measurements on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger11_cfg_t lightranger11_cfg;  /**< Click config object. */

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
    lightranger11_cfg_setup( &lightranger11_cfg );
    LIGHTRANGER11_MAP_MIKROBUS( lightranger11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == lightranger11_init( &lightranger11, &lightranger11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHTRANGER11_ERROR == lightranger11_default_cfg ( &lightranger11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads all zone measurements approximately every 500ms and logs them to the USB UART as an 8x8 map. 
> The silicon temperature measurement in degrees Celsius is also displayed.

```c
void application_task ( void ) 
{
    if ( !lightranger11_get_int_pin ( &lightranger11 ) )
    {
        lightranger11_results_data_t results;
        uint8_t resolution, map_side;
        err_t error_flag = lightranger11_get_resolution ( &lightranger11, &resolution );
        error_flag |= lightranger11_get_ranging_data ( &lightranger11, &results );
        if ( LIGHTRANGER11_OK == error_flag )
        {
            map_side = ( LIGHTRANGER11_RESOLUTION_4X4 == resolution ) ? 4 : 8;
            log_printf ( &logger, "\r\n %ux%u MAP (mm):\r\n", ( uint16_t ) map_side, ( uint16_t ) map_side );
            for ( uint16_t cnt = 1; cnt <= resolution; cnt++ )
            {
                log_printf ( &logger, " %u\t", results.distance_mm[ cnt - 1 ] );
                if ( 0 == ( cnt % map_side ) )
                {
                    log_printf ( &logger, "\r\n" );
                }
            }
            log_printf ( &logger, " Silicon temperature : %d degC\r\n", ( int16_t ) results.silicon_temp_degc );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
