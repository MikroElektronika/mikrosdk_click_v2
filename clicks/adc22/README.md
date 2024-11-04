\mainpage Main Page

---
# ADC 22 Click

> ADC 22 Click is a compact add-on board with a high-performance data converter. 
> This board features the ADS8665, a high-speed single-supply SAR ADC data acquisition system 
> with programmable bipolar input ranges from Texas Instruments. It features a high-speed, 
> high-precision A/D converter based on successive approximation (SAR). 
> This 12-bit resolution ADC with an integrated analog front-end (AFE) input driver circuit 
> can achieve speeds of up to 500ksps.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc22_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/adc-22-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the ADC 22 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADC 22 Click driver.

#### Standard key functions :

- `adc22_cfg_setup` Config Object Initialization function.
```c
void adc22_cfg_setup ( adc22_cfg_t *cfg );
```

- `adc22_init` Initialization function.
```c
err_t adc22_init ( adc22_t *ctx, adc22_cfg_t *cfg );
```

- `adc22_default_cfg` Click Default Configuration function.
```c
err_t adc22_default_cfg ( adc22_t *ctx );
```

#### Example key functions :

- `adc22_get_voltage` ADC 22 get voltage level function.
```c
err_t adc22_get_voltage ( adc22_t *ctx, float *voltage );
```

- `adc22_get_adc_raw_data` ADC 22 get ADC raw data function.
```c
err_t adc22_get_adc_raw_data ( adc22_t *ctx, uint16_t *raw_adc );
```

- `adc22_set_range` ADC 22 set range function.
```c
err_t adc22_set_range ( adc22_t *ctx, adc22_range_sel_t range );
```

## Example Description

> This example demonstrates the use of the ADC 22 Click board™ 
> by reading and writing data by using SPI serial interface and reading results of AD conversion.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc22_cfg_t adc22_cfg;  /**< Click config object. */

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
    adc22_cfg_setup( &adc22_cfg );
    ADC22_MAP_MIKROBUS( adc22_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc22_init( &adc22, &adc22_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( ADC22_ERROR == adc22_default_cfg ( &adc22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads the voltage levels from analog input and displays the results.
> By default, the operating input range sets from 0V to 12.288V [3×Vref;Vref=4.096V].
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{   
    static float voltage = 0.0;
    if ( ADC22_OK == adc22_get_voltage ( &adc22, &voltage ) )
    {
        log_printf( &logger, " Voltage : %.2f V\r\n", voltage );
        log_printf( &logger, " ----------------\r\n" );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC22

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
