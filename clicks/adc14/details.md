
---
# ADC 14 click

> ADC 14 Click is a compact add-on board with a high-performance data converter. This board features the MAX11108A, a low-power serial ADC from Analog Devices. It includes a high-dynamic range sample-and-hold and a high-speed serial interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/adc-14-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the ADC 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADC 14 Click driver.

#### Standard key functions :

- `adc14_cfg_setup` Config Object Initialization function.
```c
void adc14_cfg_setup ( adc14_cfg_t *cfg );
```

- `adc14_init` Initialization function.
```c
err_t adc14_init ( adc14_t *ctx, adc14_cfg_t *cfg );
```

#### Example key functions :

- `adc14_get_voltage`  ADC 14 get voltage function.
```c
err_t adc14_get_voltage ( adc14_t *ctx, float *voltage );
```

- `adc14_read_conversion_data` ADC 14 read conversion data function.
```c
err_t adc14_read_conversion_data ( adc14_t *ctx, uint16_t *adc_data );
```

- `adc14_set_vref` ADC 14 set voltage reference function.
```c
err_t adc14_set_vref ( adc14_t *ctx, float vref );
```

## Example Description

> This example demonstrates the use of the ADC 14 Click board™ 
> by reading results of AD conversion by using SPI serial interface.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART and enabled internal voltage reference.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc14_cfg_t adc14_cfg;  /**< Click config object. */

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
    adc14_cfg_setup( &adc14_cfg );
    ADC14_MAP_MIKROBUS( adc14_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc14_init( &adc14, &adc14_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}
```

### Application Task

> The demo application gets the voltage levels from analog input and displays the results.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    float voltage = 0.0;
    if ( ADC14_OK == adc14_get_voltage( &adc14, &voltage ) )
    {
        log_printf( &logger, " Voltage : %.2f [mV]\r\n", voltage );
        Delay_ms( 1000 );
    } 
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
