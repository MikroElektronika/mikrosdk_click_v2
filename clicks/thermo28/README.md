\mainpage Main Page

---
# Thermo 28 click

> Thermo 28 Click is a compact add-on board that accurately measures temperature. 
> This board features the ams AG’s AS6221, a high-accuracy digital temperature sensor. 
> The AS6221 consists of a Si bandgap temperature factory-calibrated sensor, 16-bit ADC, 
> and a digital signal processor, offering a high accuracy of ±0.9°C. 
> It provides temperature data to the host controller through a compatible I2C interface, 
> reliability, user-selectable I2C addresses, and alert functionality, 
> which triggers an interrupt to protect the device from excessive temperatures.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo28_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-28-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo 28 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo 28 Click driver.

#### Standard key functions :

- `thermo28_cfg_setup` Config Object Initialization function.
```c
void thermo28_cfg_setup ( thermo28_cfg_t *cfg );
```

- `thermo28_init` Initialization function.
```c
err_t thermo28_init ( thermo28_t *ctx, thermo28_cfg_t *cfg );
```

- `thermo28_default_cfg` Click Default Configuration function.
```c
err_t thermo28_default_cfg ( thermo28_t *ctx );
```

#### Example key functions :

- `thermo28_get_temperature` Thermo 28 get temperature function.
```c
err_t thermo28_get_temperature ( thermo28_t *ctx, float *temperature );
```

- `thermo28_set_config` Thermo 28 set configuration function.
```c
err_t thermo28_set_config ( thermo28_t *ctx, thermo28_config_t config );
```

- `thermo28_set_continuous_conversion` Thermo 28 set continuous conversion function.
```c
err_t thermo28_set_continuous_conversion ( thermo28_t *ctx );
```

## Example Description

> This example demonstrates the use of Thermo 28 click board™ 
> by reading and displaying the temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo28_cfg_t thermo28_cfg;  /**< Click config object. */

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
    thermo28_cfg_setup( &thermo28_cfg );
    THERMO28_MAP_MIKROBUS( thermo28_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo28_init( &thermo28, &thermo28_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( THERMO28_ERROR == thermo28_default_cfg ( &thermo28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of a Thermo 28 click board™.
> Reads the temperature measurement in degree Celsius and displays the results.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    float temperature;
   
    if ( THERMO28_OK == thermo28_get_temperature( &thermo28, &temperature ) )
    {
        log_printf( &logger, " Temperature [degC]: %.2f \r\n", temperature );
        Delay_ms ( 1000 );
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo28

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
