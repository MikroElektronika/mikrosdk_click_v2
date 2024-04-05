
---
# Barometer 12 click

> Barometer 12 Click is a compact add-on board that measures air pressure in a specific environment. This board features the ICP-10125, a high-accuracy, low-power, 10-atm waterproof barometric pressure and temperature sensor from TDK InvenSense. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barometer12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/barometer-12-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Barometer 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Barometer 12 Click driver.

#### Standard key functions :

- `barometer12_cfg_setup` Config Object Initialization function.
```c
void barometer12_cfg_setup ( barometer12_cfg_t *cfg );
```

- `barometer12_init` Initialization function.
```c
err_t barometer12_init ( barometer12_t *ctx, barometer12_cfg_t *cfg );
```

- `barometer12_default_cfg` Click Default Configuration function.
```c
err_t barometer12_default_cfg ( barometer12_t *ctx );
```

#### Example key functions :

- `barometer12_inv_invpres_calib` Barometer 12 inverse process data function.
```c
err_t barometer12_inv_invpres_calib ( barometer12_t *ctx, barometer12_invpres_t *cfg_data );
```

- `barometer12_get_raw_data` Barometer 12 get RAW data function.
```c
err_t barometer12_get_raw_data ( barometer12_t *ctx, uint16_t measurement_comd, uint32_t *pressure, uint16_t *temperature );
```

- `barometer12_get_press_and_temp` Barometer 12 get pressure and temperature function.
```c
err_t barometer12_get_press_and_temp ( barometer12_t *ctx,  float *pressure, float *temperature );
```

## Example Description

> This library contains API for the Barometer 12 Click driver.
  The library initializes and defines the I2C bus drivers 
  to write and read data from registers.
  This demo application shows an example of 
  atmospheric pressure and temperature measurement.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the I2C module and log UART.
  After driver initialization and default settings, 
  the app display device ID.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer12_cfg_t barometer12_cfg;  /**< Click config object. */

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
    barometer12_cfg_setup( &barometer12_cfg );
    BAROMETER12_MAP_MIKROBUS( barometer12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == barometer12_init( &barometer12, &barometer12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER12_ERROR == barometer12_default_cfg ( &barometer12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    static uint16_t device_id;
    err_t err_flag = barometer12_get_device_id( &barometer12, &device_id );
    if ( BAROMETER12_ERROR == err_flag ) 
    {
        log_error( &logger, " Communication Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, " Device ID   : 0x%.4X \r\n", device_id );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This is an example that shows the use of a Barometer 12 Click board™.
  Logs the atmospheric pressure [ Pa ] and temperature [ degree Celsius ] data.
  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    float pressure;
    float temperature;
    
    barometer12_get_press_and_temp( &barometer12, &pressure, &temperature );
    log_printf( &logger, " Pressure    : %.2f Pa\r\n", pressure );
    log_printf( &logger, " Temperature : %.2f C\r\n", temperature );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
