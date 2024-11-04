\mainpage Main Page

---
# Barometer 9 Click

> Barometer 9 Click is a compact add-on board ideal for precision activity tracking and indoor navigation/localization. This board features the ENS220, a barometric pressure and temperature sensor from ScioSense

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barometer9_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/barometer-9-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Barometer 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Barometer 9 Click driver.

#### Standard key functions :

- `barometer9_cfg_setup` Config Object Initialization function.
```c
void barometer9_cfg_setup ( barometer9_cfg_t *cfg );
```

- `barometer9_init` Initialization function.
```c
err_t barometer9_init ( barometer9_t *ctx, barometer9_cfg_t *cfg );
```

- `barometer9_default_cfg` Click Default Configuration function.
```c
err_t barometer9_default_cfg ( barometer9_t *ctx );
```

#### Example key functions :

- `barometer9_read_part_id` This function is used to read a Device ID of Barometer 9 Click board.
```c
err_t barometer9_read_part_id ( barometer9_t *ctx, uint16_t *part_id );
```

- `barometer9_get_temperature` This function is used to read a temperature of Barometer 9 Click board in degree of Celsius.
```c
err_t barometer9_get_temperature ( barometer9_t *ctx, float *temperature );
```

- `barometer9_get_pressure` This function is used to read a pressure of Barometer 9 Click board in Pascals.
```c
err_t barometer9_get_pressure ( barometer9_t *ctx, float *pressure );
```

## Example Description

> This example demonstrates the use of  Barometer 9  Click board 
 by reading and displaying the pressure and temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or SPI module and log UART.
  After driver initialization, the app sets the default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer9_cfg_t barometer9_cfg;  /**< Click config object. */

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
    barometer9_cfg_setup( &barometer9_cfg );
    BAROMETER9_MAP_MIKROBUS( barometer9_cfg, MIKROBUS_1 );
    err_t init_flag = barometer9_init( &barometer9, &barometer9_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( BAROMETER9_ERROR == barometer9_default_cfg ( &barometer9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint16_t device_id = 0;
    barometer9_read_part_id ( &barometer9, &device_id );
    if ( BAROMETER9_DEVICE_ID != device_id )
    {
        log_error( &logger, " Read error " );
        for ( ; ; );
    }
    else
    {
        log_printf( &logger, " Device ID: 0x%.4X \r\n", device_id );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> The demo application reads and displays the Pressure [Pa] and Temperature [degree Celsius] data.
  Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    float temperature = 0;
    float pressure = 0;

    barometer9_get_temperature( &barometer9, &temperature );
    barometer9_get_pressure( &barometer9, &pressure );
    log_printf( &logger, " Temperature: %.2f C \r\n Pressure %.3f Pa \r\n", temperature, pressure );
    log_printf( &logger, " - - - - - - - - - - \r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
