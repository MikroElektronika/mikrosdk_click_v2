
---

# CO2 Click

CO2 Click is a compact add-on board that contains Sensirion’s miniature CO2 sensor. This board features the STC31, a gas concentration sensor designed for high-volume applications. The STC31 utilizes a revolutionized thermal conductivity measurement principle, which results in superior repeatability and long-term stability. The outstanding performance of these sensors is based on Sensirion’s patented CMOSens® sensor technology, which combines the sensor element, signal processing, and digital calibration on a small CMOS chip. It features a digital I2C interface, which makes it easy to connect directly to MCU. This Click board™ represents an ideal choice for health, environmental, industrial, residential monitoring of high CO2 concentrations and applications where reliability is crucial.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/CO2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/co2-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the CO2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for CO2 Click driver.

#### Standard key functions :

- `co2_cfg_setup` Config Object Initialization function.
```c
void co2_cfg_setup ( co2_cfg_t *cfg );
```

- `co2_init` Initialization function.
```c
err_t co2_init ( co2_t *ctx, co2_cfg_t *cfg );
```

- `co2_default_cfg` Click Default Configuration function.
```c
err_t co2_default_cfg ( co2_t *ctx );
```

#### Example key functions :

- `co2_get_id` Read device and serial ID's.
```c
err_t co2_get_id ( co2_t *ctx );
```

- `co2_set_reference` Set device refrence values for gas calculation.
```c
err_t co2_set_reference ( co2_t *ctx, uint16_t humidity, uint16_t pressure );
```

- `co2_read_gas` Read CO2 concentration and temperature value.
```c
err_t co2_read_gas ( co2_t *ctx, float *gas_concentration, float *temperature );
```

## Example Description

> This example showcases ability of Click board. It reads ID's 
configures device for operation work and reads CO2 gas 
concentration in air and temperature of IC every second.

**The demo application is composed of two sections :**

### Application Init

> Initialization of host communication modules (UART, I2C). 
Checks device and serial ID's from device. Then calls default 
configuration function that resets device, self tests it selft 
and configures for measuring CO2 concentration from air.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */

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
    co2_cfg_setup( &co2_cfg );
    CO2_MAP_MIKROBUS( co2_cfg, MIKROBUS_1 );
    err_t init_flag = co2_init( &co2, &co2_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    init_flag = co2_get_id( &co2 );
    
    if ( ( init_flag < 0 ) && ( co2.device_id != CO2_DEVICE_ID ) )
    {
        log_error( &logger, "ID" );
    }
    else
    {
        log_printf( &logger, " > Device ID: 0x%.8lX\r\n", co2.device_id );
        log_printf( &logger, " > Serial ID: 0x%.8lX%.8lX\r\n", co2.serial_id[ 0 ], co2.serial_id[ 1 ] );
    }
    
    init_flag = co2_default_cfg ( &co2 );
    
    if ( init_flag < 0 )
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    //Set reference values for device to calculate gas concentartion.
    if ( CO2_OK != co2_set_reference( &co2, CO2_AIR_HUMIDITY, CO2_AIR_PRESSURE ) )
    {
        log_error( &logger, " Reference values." );
    }
    
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads air CO2 gas concentration in precentage and IC's 
temperature in deg Celzius in span of 1 second and logs 
data to UART Terminal.

```c

void application_task ( void )
{
    float gas_data = 0;
    float temp_data = 0;
    
    if ( CO2_OK == co2_read_gas( &co2, &gas_data, &temp_data ) )
    {
        log_printf( &logger, " > CO2[%%]: %.2f\r\n", gas_data );
        log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temp_data );
        Delay_ms ( 1000 );
    }
    
    Delay_ms ( 1 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CO2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
