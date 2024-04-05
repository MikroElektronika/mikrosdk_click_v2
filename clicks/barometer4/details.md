
---
# Barometer 4 click

> Barometer 4 Click is a compact add-on board used to measure air pressure in a specific environment. This board features the ICP-10111, a high accuracy low power barometric and temperature sensor from TDK InvenSense. The ICP-10111 is based on MEMS capacitive technology providing ultra-low noise at the lowest power, enabling industry-leading relative accuracy, sensor throughput, and temperature stability. It comes with a configurable host interface that supports I2C serial communication and measures pressure in a range from 30kPa up to 110kPa with an accuracy of ±1Pa over a wide operating temperature range.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barometer4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/barometer-4-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Barometer4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Barometer4 Click driver.

#### Standard key functions :

- `barometer4_cfg_setup` Config Object Initialization function.
```c
void barometer4_cfg_setup ( barometer4_cfg_t *cfg );
```

- `barometer4_init` Initialization function.
```c
err_t barometer4_init ( barometer4_t *ctx, barometer4_cfg_t *cfg );
```

- `barometer4_default_cfg` Click Default Configuration function.
```c
err_t barometer4_default_cfg ( barometer4_t *ctx );
```

#### Example key functions :

- `barometer4_get_pressure_and_temperature` Barometer 4 get pressure and temperature function.
```c
err_t barometer4_get_pressure_and_temperature ( barometer4_t *ctx,  float *pressure, float *temperature );
```

- `barometer4_get_raw_data` Barometer 4 get RAW data function.
```c
err_t barometer4_get_raw_data ( barometer4_t *ctx, uint16_t measurement_comd, uint32_t *pressure, uint16_t *temperature );
```

- `barometer4_soft_reset` Barometer 4 software reset function.
```c
err_t barometer4_soft_reset ( barometer4_t *ctx );
```

## Example Description

> This library contains API for the Barometer 4 Click driver.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers.
> This demo application shows an example of 
> atmospheric pressure and temperature measurement.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the I2C module and log UART.
> After driver initialization and default settings, 
> the app display device ID.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    barometer4_cfg_t barometer4_cfg;  /**< Click config object. */

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
    barometer4_cfg_setup( &barometer4_cfg );
    BAROMETER4_MAP_MIKROBUS( barometer4_cfg, MIKROBUS_1 );
    err_t init_flag = barometer4_init( &barometer4, &barometer4_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    barometer4_default_cfg ( &barometer4 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 100 );
    
    static uint16_t device_id;
    err_t err_flag = barometer4_get_device_id( &barometer4, &device_id );
    if ( BAROMETER4_ERROR == err_flag ) 
    {
        log_error( &logger, " Communication Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, " Device ID   : 0x%.4X \r\n", device_id );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 1000 );
}

```

### Application Task

> This is an example that shows the use of a Barometer 4 Click board™.
> Logs the atmospheric pressure [ Pa ] and temperature [ degree Celsius ] data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{  
    static float pressure;
    static float temperature;
    
    barometer4_get_pressure_and_temperature( &barometer4, &pressure, &temperature );
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
- Click.Barometer4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
