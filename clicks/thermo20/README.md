\mainpage Main Page

---
# Thermo 20 click

> Thermo 20 Click is a compact add-on board that provides an accurate temperature measurement. This board features the TSYS03, a miniature digital temperature sensor that comes up with factory calibrated, highly accurate temperature data from TE Connectivity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo20_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-20-click)

---


#### Click library

- **Author**        : Mikroe Team
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo20 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo20 Click driver.

#### Standard key functions :

- `thermo20_cfg_setup` Config Object Initialization function.
```c
void thermo20_cfg_setup ( thermo20_cfg_t *cfg );
```

- `thermo20_init` Initialization function.
```c
err_t thermo20_init ( thermo20_t *ctx, thermo20_cfg_t *cfg );
```

- `thermo20_default_cfg` Click Default Configuration function.
```c
err_t thermo20_default_cfg ( thermo20_t *ctx );
```

#### Example key functions :

- `thermo20_set_cmd` Send command function.
```c
err_t thermo20_set_cmd ( thermo20_t *ctx, uint8_t cmd );
```

- `thermo20_start_conversion` Start conversion function.
```c
void thermo20_start_conversion ( thermo20_t *ctx );
```

- `thermo20_get_temperature` Get temperature data function.
```c
float thermo20_get_temperature ( thermo20_t *ctx );
```

## Example Description

> This example showcases the ability of Thermo 20 Click board to
 read it's serial number. It can read themperature and measure from -40degC to 120degC.

**The demo application is composed of two sections :**

### Application Init

> Initialization communication modules(I2C, UART). Resets device and read Serial Number.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo20_cfg_t thermo20_cfg;  /**< Click config object. */

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
    thermo20_cfg_setup( &thermo20_cfg );
    THERMO20_MAP_MIKROBUS( thermo20_cfg, MIKROBUS_1 );
    err_t init_flag = thermo20_init( &thermo20, &thermo20_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    thermo20_default_cfg ( &thermo20 );
    
    uint32_t ser_numb = thermo20_get_serial_number( &thermo20 );
    log_printf( &logger, " > Serial Number: %lu\r\n", ser_numb );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> In span of ~ 1000ms it sends command for adc conversion of temperature, reads ADC value,
 and calculates temperature in degrees C.

```c

void application_task ( void ) 
{
    thermo20_start_conversion( &thermo20 );
    float temperature = thermo20_get_temperature( &thermo20 );
    log_printf( &logger, " > Temperature[deg C]: %.2f\r\n", temperature );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo20

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
