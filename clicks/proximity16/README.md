\mainpage Main Page

---
# Proximity 16 click

> Proximity 16 Click is a compact add-on board that contains a close-range proximity sensing solution. This board features the VL53L5CX, a Time-of-Flight (ToF) multizone ranging sensor from STMicroelectronics. The VL53L5CX integrates a SPAD array, physical infrared filters, and diffractive optical elements (DOE) to achieve the best-ranging performance in various ambient lighting conditions with different cover glass materials. It allows absolute distance measurement, whatever the target color and reflectance, provides accurate ranging up to 400cm, and can work at fast speeds (60Hz). Also, multizone distance measurements are possible with either 4x4 or 8x8 separate zones with broad 63° diagonal software-configurable Field-of-View (FoV).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity16_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/proximity-16-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity 16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Proximity 16 Click driver.

#### Standard key functions :

- `proximity16_cfg_setup` Config Object Initialization function.
```c
void proximity16_cfg_setup ( proximity16_cfg_t *cfg );
```

- `proximity16_init` Initialization function.
```c
err_t proximity16_init ( proximity16_t *ctx, proximity16_cfg_t *cfg );
```

- `proximity16_default_cfg` Click Default Configuration function.
```c
err_t proximity16_default_cfg ( proximity16_t *ctx );
```

#### Example key functions :

- `proximity16_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t proximity16_get_int_pin ( proximity16_t *ctx );
```

- `proximity16_get_resolution` This function gets the current resolution (4x4 or 8x8).
```c
err_t proximity16_get_resolution ( proximity16_t *ctx, uint8_t *resolution );
```

- `proximity16_get_ranging_data` This function gets the ranging data, using the selected output and the resolution.
```c
err_t proximity16_get_ranging_data ( proximity16_t *ctx, proximity16_results_data_t *results );
```

## Example Description

> This example demonstrates the use of Proximity 16 click board by reading and displaying 8x8 zones measurements on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity16_cfg_t proximity16_cfg;  /**< Click config object. */

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
    proximity16_cfg_setup( &proximity16_cfg );
    PROXIMITY16_MAP_MIKROBUS( proximity16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity16_init( &proximity16, &proximity16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY16_ERROR == proximity16_default_cfg ( &proximity16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads all zone measurements approximately every 500ms and logs them to the USB UART as an 8x8 map. The silicon temperature measurement in degrees Celsius is also displayed.

```c
void application_task ( void )
{
    if ( !proximity16_get_int_pin ( &proximity16 ) )
    {
        proximity16_results_data_t results;
        uint8_t resolution, map_side;
        err_t error_flag = proximity16_get_resolution ( &proximity16, &resolution );
        error_flag |= proximity16_get_ranging_data ( &proximity16, &results );
        if ( PROXIMITY16_OK == error_flag )
        {
            map_side = ( PROXIMITY16_RESOLUTION_4X4 == resolution ) ? 4 : 8;
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
- Click.Proximity16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
