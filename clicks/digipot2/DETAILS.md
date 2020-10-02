
---
# DIGI POT 2 click

< DIGI POT 2 click is a mikroBUS™ add-on board with a single channel digital potentiometer TPL0501 with 256 wiper positions >

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](< https://www.mikroe.com/digipot-2-click > )

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the DigiPot2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DigiPot2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void digipot2_cfg_setup ( digipot2_cfg_t *cfg ); 
 
- Initialization function.
> DIGIPOT2_RETVAL digipot2_init ( digipot2_t *ctx, digipot2_cfg_t *cfg );


#### Example key functions :

- Generic write 8-bit data function.
> void digipot2_write_byte ( digipot2_t *ctx, uint8_t command, uint8_t write_data );
 
- Set 8-bit wiper positions.
> void digipot2_set_wiper_positions ( digipot2_t *ctx, uint8_t wiper_positions );

- Convert ADC value to volatage.
> float digipot2_convert_output ( digipot2_t *ctx, uint16_t value_adc, float v_ref );

## Examples Description

> This application change the output voltage every 5 seconds. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - SPI and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    digipot2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    digipot2_cfg_setup( &cfg );
    DIGIPOT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digipot2_init( &digipot2, &cfg );
}
  
```

### Application Task

> This is a example which demonstrates the use of DIGI POT 2 Click board. Increments the wiper position by 10 position every 5 seconds. Calculate ADC voltage and write log UART. All data logs on usb uart for aproximetly every 5 sec.

```c

void application_task ( void )
{
    uint16_t counter;
    float adc_voltage;

    for ( counter = 100; counter < 256; counter += 10 )
    {
        digipot2_set_wiper_positions( &digipot2, counter );
        
        adc_voltage = digipot2_convert_output( &digipot2, counter * 16 , DIGIPOT2_VREF_3V3 );
        
        Delay_ms( 1000 );
        Delay_ms( 1000 );
        
        log_printf( &logger, " ADC Voltage : %f V\r\n", adc_voltage );

        
        Delay_ms( 1000 );
        Delay_ms( 1000 );
        Delay_ms( 1000 );
    }

    log_printf( &logger, "--------------------------\r\n" );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DigiPot2

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
