
# PIR click

PIR Click is a pyroelectric sensor which generates a voltage when exposed to infrared radiation emitted by live bodies. It is equipped with the PL-N823-01, an infrared sensor from KEMET that uses the pyrolectric effect of ceramic by absorbing infrared rays emitted from the human body, while the the white plastic Fresnel lens covering the sensor filters visible light.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pir_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/pir-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Pir Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pir Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pir_cfg_setup ( pir_cfg_t *cfg ); 
 
- Initialization function.
> PIR_RETVAL pir_init ( pir_t *ctx, pir_cfg_t *cfg );

#### Example key functions :

- Reading 12bit ADC value.
> uint16_t pir_get_adc ( pir_t *ctx )
 
- Reading register.
> uint16_t pir_reg_read ( pir_t *ctx );

- Reading ADC data in mili Volts
> float pir_get_mili_volt ( pir_t *ctx, uint16_t ref_voltage );

## Examples Description
 
> This application which generates a voltage when exposed to infrared radiation.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pir_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pir_cfg_setup( &cfg );
    PIR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pir_init( &pir, &cfg );
}
  
```

### Application Task

> Reads ADC data, converts it to miliVolts and logs scaled value in miliVolts. 

```c

void application_task ( void )
{
    uint16_t adc_val;
    float map_out;

    adc_val = pir_get_adc( &pir );
    map_out = pir_scale_results( &pir, adc_val, 0, 3303 );
    
    log_printf( &logger, " Voltage: %.2f\r\n", map_out);
   
    log_printf( &logger, " miliVolts \r\n" );
    Delay_ms( 100 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pir

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
