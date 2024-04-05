\mainpage Main Page

---
# ADC 23 click

> ADC 23 Click is a compact add-on board that converts an analog voltage into a digital representation. This board features the ADS127L11, a wide-bandwidth 24-bit delta-sigma analog-to-digital converter from Texas Instruments. It is capable of data rates up to 400ksps using a wideband filter and up to 1067ksps using a low-latency filter. It also offers an excellent combination of AC performance and DC precision with low power consumption.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc23_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/adc-23-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the ADC 23 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADC 23 Click driver.

#### Standard key functions :

- `adc23_cfg_setup` Config Object Initialization function.
```c
void adc23_cfg_setup ( adc23_cfg_t *cfg );
```

- `adc23_init` Initialization function.
```c
err_t adc23_init ( adc23_t *ctx, adc23_cfg_t *cfg );
```

- `adc23_default_cfg` Click Default Configuration function.
```c
err_t adc23_default_cfg ( adc23_t *ctx );
```

#### Example key functions :

- `adc23_get_voltage` ADC 23 read get voltage level function.
```c
err_t adc23_get_voltage ( adc23_t *ctx, float *voltage );
```

- `adc23_read_conversion_data` ADC 23 read conversion data function.
```c
err_t adc23_read_conversion_data ( adc23_t *ctx, int32_t *adc_data );
```

- `adc23_start_conversion` ADC 23 start conversion function.
```c
err_t adc23_start_conversion ( adc23_t *ctx );
```

## Example Description

> This example demonstrates the use of the ADC 23 Click board™ 
> by reading and writing data by using SPI serial interface and reading results of AD conversion.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc23_cfg_t adc23_cfg;  /**< Click config object. */

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
    adc23_cfg_setup( &adc23_cfg );
    ADC23_MAP_MIKROBUS( adc23_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc23_init( &adc23, &adc23_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC23_ERROR == adc23_default_cfg ( &adc23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads the voltage levels from analog input and displays the results.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static float voltage = 0.0;
    if ( ADC23_OK == adc23_get_voltage( &adc23, &voltage ) )
    {
        log_printf( &logger, " Voltage : %.2f [mV]\r\n", voltage );
        Delay_ms ( 1000 );
    } 
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC23

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
