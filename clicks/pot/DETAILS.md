
# POT click

Click board with the accurate selectable reference voltage output.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pot_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pot-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : nov 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Pot Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pot Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pot_cfg_setup ( pot_cfg_t *cfg ); 
 
- Initialization function.
> POT_RETVAL pot_init ( pot_t *ctx, pot_cfg_t *cfg );


#### Example key functions :
 
- This function read ADC data.
> pot_data_t pot_generic_read ( pot_t *ctx );

## Examples Description

> AD conversion where results will be calculated to millivolts [mV]. 

**The demo application is composed of two sections :**

### Application Init 

> Performs logger and Click initialization.


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pot_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pot_cfg_setup( &cfg );
    POT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pot_init( &pot, &cfg );
}
  
```

### Application Task

> Makes the averaged results by using the desired number of samples of AD conversion.
> The averaged results will be calculated to millivolts [mV] and sent to the uart terminal.


```c

void application_task ( void )
{
    pot_data_t tmp;
    uint16_t adc_read;
    uint16_t n_samples;
    uint16_t adc_max;
    uint16_t adc_min;
    float adc_avrg;

    #define N_SAMPLES         = 100;
    #define ADC_V_REF_MV      = 1790;
    #define ADC_12BIT_RESOL   = 4096;
    #define ADC_10BIT_RESOL   = 1024;
    
    //  Task implementation.

    for ( n_samples = 0; n_samples < N_SAMPLES; n_samples++ )
    {
        adc_read = ADC1_Get_Sample( 4 );
        
        if ( n_samples == 0 )
        {
            adc_max = adc_read;
            adc_min = adc_read;
        }

        if ( adc_read > adc_max )
        {
            adc_max = adc_read;
        }

        else if ( adc_read < adc_min )
        {
            adc_min = adc_read;
        }
        
        Delay_ms( 1 );
    }

    adc_avrg = adc_max;
    adc_avrg += adc_min;
    adc_avrg /= 2;
    adc_avrg /= ADC_12BIT_RESOL;
    adc_avrg *= ADC_V_REF_MV;
    adc_aead = adc_avrg;
    
    tmp = pot_generic_read ( &pot );
    log_printf( &logger, "** AN : [DEC]- %d, [HEX]- 0x%x mV\r\n", tmp, tmp );
    Delay_ms( 1000 );

}  

```

## Note

> The AD conversion will be performed on the analog (AN) pin on the mikrobus 1.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pot

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
