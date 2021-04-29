
---
# ADC 6 click

ADC 6 click is an advanced 24bit multichannel analog to digital converter (ADC),
with 8 fully differential or 15 single ended/pseudo differential sampling inputs,
and very flexible routing capabilities. The click board� has two 2x10 pin headers,
used both to configure the device and connect the input channels.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/adc-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the ADC6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ADC6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void adc6_cfg_setup ( adc6_cfg_t *cfg ); 
 
- Initialization function.
> ADC6_RETVAL adc6_init ( adc6_t *ctx, adc6_cfg_t *cfg );


#### Example key functions :

- This function writes data to determined register.
> void adc6_write_reg( adc6_t* ctx, const uint8_t register_address, const uint32_t transfer_data );
 
- This function reads data from determined register.
> uint32_t adc6_read_reg(adc6_t* ctx, const uint8_t register_address);

- This function continuously reads data from Data register without
  writing anything on SPI.
> uint32_t adc6_continuous_read_data(adc6_t* ctx);

## Examples Description

> This example collects data from the sensor, calculates the voltage to a digital value and then logs it.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and sets configuration witch enables apointed channel.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc6_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adc6_cfg_setup( &cfg );
    ADC6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc6_init( &adc6, &cfg );
    adc6_default_cfg( &adc6 );

}
  
```

### Application Task

>  Gets 24-bit converted data in single read mode and logs data on terminal every 500 ms.


```c

void application_task ( void )
{
    uint32_t adc_value = 0;

    adc_value = adc6_get_adc_data( &adc6, ADC6_SINGLE_GET_DATA_MODE );

    log_printf( &logger, "The ADC value is: %lu\r\n", adc_value );

    Delay_ms( 500 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC6

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
