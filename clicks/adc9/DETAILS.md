
---
# ADC 9 click

ADC 9 Click is 8th channel analog to digital converter expansion board, for projects where you have demand for multi channel ADC conversion such as microcontrollers with small number or none analog inputs. This Click board is based on MCP3564 a 24-bit Delta-Sigma Analog-to-Digital Converter with programmable data rate of up to 153.6 ksps from Microchip. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/adc-9-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Adc9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Adc9 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void adc9_cfg_setup ( adc9_cfg_t *cfg ); 
 
- Initialization function.
> ADC9_RETVAL adc9_init ( adc9_t *ctx, adc9_cfg_t *cfg );

- Click Default Configuration function.
> void adc9_default_cfg ( adc9_t *ctx, adc9_rw_t *rw );


#### Example key functions :

- Function is used to check if an interrupt has occured.
> uint8_t adc9_irq_pin_state ( adc9_t *ctx );
 
- Function is used to read ADC value when the default fata format is applied.
> uint8_t adc9_read_def_adc ( adc9_t *ctx, adc9_rw_t *rw, int32_t *rd_data );

- Function is used to calculate voltage based on ADC values.
> float adc9_volt_calc ( adc9_t *ctx, int32_t adc_val, uint16_t v_ref, uint8_t gain );

## Examples Description

> This click is 8th channel analog to digital converter expansion board, usefull for projects 
> where we have demand for multi channel ADC conversion such as microcontrollers with small 
> number or none analog inputs. It offers integrated features, such as internal oscillator, 
> temperature sensor and burnout sensor detection, in order to reduce system component count 
> and total solution cost. 

**The demo application is composed of two sections :**

### Application Init 

> Initalizes SPI driver, resets and starts the device, and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc9_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adc9_cfg_setup( &cfg );
    ADC9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uint8_t err_flag = adc9_init( &adc9, &cfg );
    if ( ADC9_INIT_ERROR == err_flag )
    {
        log_info( &logger, "---- Error Init ----" );
        for ( ; ; );
    }

    adc9_default_cfg( &adc9, &adc9_rw );
    
    Delay_ms( 1000 );
}
  
```

### Application Task

> This is an example that shows the capabilities of the ADC 9 click by calculating voltage level 
> based on ADC from channels 0(positive) and 1(negative), and logs the result. 

```c

void application_task ( void )
{
    measurement_init( &adc9, &adc9_rw );
    
    while ( adc9_irq_pin_state( &adc9 ) );
    
    adc9_rw.reg = ADC9_DEVICE_ADR;
    adc9_read_def_adc ( &adc9, &adc9_rw, &adc_value );

    log_printf( &logger, "ADC Value : %ld\r\n" , adc_value );
    
    m_volts = adc9_volt_calc ( &adc9, adc_value, VREF, 1 );
    log_printf( &logger, "Voltage in milivolts : %.2f\r\n", m_volts );

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 1000 );
}

```

## Note

> Depending on the VOLT SEL jumper position on the click board the user needs to set VREF macro value (mV) in the code.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc9

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
