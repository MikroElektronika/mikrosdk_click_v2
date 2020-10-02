
---
# ADC 9 click

ADC 9 Click is 8th channel analog to digital converter expansion board, for projects where you have demand for multi channel ADC conversion such as microcontrollers with small number or none analog inputs. This Click board is based on MCP3564 a 24-bit Delta-Sigma Analog-to-Digital Converter with programmable data rate of up to 153.6 ksps from Microchip. 

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/adc9_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/adc-9-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Adc9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

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

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adc9_cfg_setup( &cfg );
    ADC9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc9_init( &adc9, &cfg );
}
  
```

### Application Task

> This is an example that shows the capabilities of the ADC 9 click
> by calculating voltage level based on ADC from channels 0(positive) and 1(negative), 
> and logs the result. 

```c

void application_task ( void )
{
    log_printf( &logger, "Setup... \r\n" );
    adc9_meas_init( &adc9, &adc9_rw );
    log_printf( &logger, "Done! \r\n" );
    
    while ( adc9_irq_pin_state( &adc9 ) )
    {

    }
    adc9_rw.reg = ADC9_DEVICE_ADR;
    adc9_read_def_adc ( &adc9, &adc9_rw, &adc_value );

    log_printf( &logger, "ADC Value : %ld\r\n" , adc_value );
    
    m_volts = adc9_volt_calc ( &adc9, adc_value, v_ref, 1 );
    log_printf( &logger, "Voltage in milivolts : %.4f mV\r\n", m_volts );

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 1000 );
}

```

## Note

> <pre>
> Additional Functions :
>      void adc9_meas_init ( adc9_t *ctx, adc9_rw_t *rw ) 
>
> Measurement Initialization function is used to easily apply desired settings, 
> in this case device is set to read ADC value from channels 0(positive) and 1(negative)
> with default data format, gain, boost and internal clock.
> </pre>

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc9

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
