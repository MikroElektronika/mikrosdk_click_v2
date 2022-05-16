
---
# Current 7 click

> Current 7 Click is a compact add-on board providing a precise and accurate current sensing solution. This board features the INA282, a wide common-mode range, bidirectional, high-accuracy current shunt monitor from Texas Instruments. The INA282 represents a voltage output current shunt monitor that can sense drops across shunts at common-mode voltages from –14 V to +80 V, independent of the supply voltage, which operates in a range from 2.7V up to 18V supply. The zero-drift topology enables high-precision measurements with maximum input offset voltages as low as 70μV. Also, the user is allowed to process the output signal in analog or digital form.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/current7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/current-7-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Current 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current 7 Click driver.

#### Standard key functions :

- `current7_cfg_setup` Config Object Initialization function.
```c
void current7_cfg_setup ( current7_cfg_t *cfg );
```

- `current7_init` Initialization function.
```c
err_t current7_init ( current7_t *ctx, current7_cfg_t *cfg );
```

- `current7_default_cfg` Click Default Configuration function.
```c
err_t current7_default_cfg ( current7_t *ctx );
```

#### Example key functions :

- `current7_get_adc` Current 7 get ADC function.
```c
err_t current7_get_adc ( current7_t *ctx, uint16_t *data_out );
```

- `current7_get_adc_voltage` Current 7 get ADC voltage function.
```c
err_t current7_get_adc_voltage ( current7_t *ctx, float *adc_vtg );
```

- `current7_get_current` Current 7 get current function.
```c
err_t current7_get_current ( current7_t *ctx, float *current );
```

## Example Description

> This library contains API for Current 7 Click driver.
> The demo application reads ADC value and current ( A ).

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C or AN driver and log UART.
> After driver initialization the app set default settings.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    current7_cfg_t current7_cfg;  /**< Click config object. */

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
    current7_cfg_setup( &current7_cfg );
    CURRENT7_MAP_MIKROBUS( current7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == current7_init( &current7, &current7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENT7_ERROR == current7_default_cfg ( &current7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the Current 7 Click board™.
> In this example, we read and display the ADC values and current ( A ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    static float current;
    static uint16_t adc_val;
    
    current7_get_adc( &current7, &adc_val );
    log_printf( &logger, " ADC     : %d \r\n", adc_val );
    log_printf( &logger, "- - - - - - - - - - \r\n" );
    current7_get_current( &current7, &current );
    log_printf( &logger, " Current : %.3f A\r\n", current );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Current7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
