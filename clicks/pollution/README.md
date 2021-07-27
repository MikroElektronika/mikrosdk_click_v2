\mainpage Main Page
 
 

---
# Pollution click

Pollution click carries the VOC gas sensor and has high sensitivity to organic gases 
such as methanal (also known as formaldehyde), benzene, alcohol, toluene, etc.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pollution_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pollution-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Pollution Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pollution Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pollution_cfg_setup ( pollution_cfg_t *cfg ); 
 
- Initialization function.
> POLLUTION_RETVAL pollution_init ( pollution_t *ctx, pollution_cfg_t *cfg );

- Click Default Configuration function.
> void pollution_default_cfg ( pollution_t *ctx );

#### Example key functions :

- This function read ADC data.
> pollution_data_t pollution_generic_read ( pollution_t *ctx );
 
- This function gets load voltage from read ADC value.
> float pollution_measure_load_voltage ( pollution_t *ctx, uint16_t adc_value );

- This function gets the corrected resistance of the sensor.
> float pollution_get_corrected_resistance ( pollution_t *ctx, uint16_t adc_value );

## Examples Description

> 
> Example code reads ADC value and measures quantity of organic gases in the air.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Application Init performs Logger and Click initialization.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pollution_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "---------------------------------------------\r\n" );
    log_printf( &logger, "------------  Application  Init ------------\r\n" );
    Delay_ms ( 1000 );

    //  Click initialization.

    pollution_cfg_setup( &cfg );
    POLLUTION_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pollution_init( &pollution, &cfg );
    
    log_printf( &logger, "---------------------------------------------\r\n" );
    log_printf( &logger, "-------------- Pollution Click --------------\r\n" );
    log_printf( &logger, "---------------------------------------------\r\n" );
    Delay_ms ( 1000 );
    
    pollution_default_cfg( &pollution );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "------------ ADC Initializated ------------\r\n" );
    log_printf( &logger, "---------------------------------------------\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> This is an example which demonstrates the usage of Pollution Click board.
> Pollution Click reads ADC value, load voltage from ADC value, and reads  
> corrected resistance of the sensor where results are being sent to 
> the UART terminal where you can track changes.
> 

```c

void application_task ( void )
{
    pollution_data_t tmp;
    
    tmp = pollution_generic_read( &pollution );
    log_printf( &logger, " ADC value : %d ppm\r\n\n", tmp );
    Delay_ms( 1000 );
    
    value_volt = pollution_measure_load_voltage( &pollution, tmp );
    log_printf( &logger, " Load voltage : %0.2f V\r\n\n", value_volt );
    Delay_ms( 1000 );
    
    value_res = pollution_get_corrected_resistance( &pollution, tmp );
    log_printf( &logger, " Corrected resistance : %0.2f kOhm\r\n\n", value_res );
    log_printf( &logger, "---------------------------------------------\r\n\n" );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pollution

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
