\mainpage Main Page
 
---
# RTD 2 click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Rtd 2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rtd 2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rtd2_cfg_setup ( rtd2_cfg_t *cfg ); 
 
- Initialization function.
> RTD2_RETVAL rtd2_init ( rtd2_t *ctx, rtd2_cfg_t *cfg );

- Click Default Configuration function.
> void rtd2_default_cfg ( rtd2_t *ctx );


#### Example key functions :

- The function check new data ready of the 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters
- With Programmable Gain Amplifier (PGA) For Sensor Measurement on the RTD 2 click board.
> uint8_t rtd2_check_new_data_ready ( rtd2_t *ctx );
 
- The function read output data and return ambient temperature from the PT100 3-wire temperature 
- probe wired to the 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With Programmable 
- Gain Amplifier (PGA) For Sensor Measurement on the RTD 2 click board.
> float rtd2_get_temperature ( rtd2_t *ctx );

- The function enables ADC conversion of the 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital 
- Converters With Programmable Gain Amplifier (PGA) For Sensor Measurement on the RTD 2 click.
> void rtd2_enable_start ( rtd2_t *ctx, uint8_t en_start );

## Examples Description

> RTD 2 Click board is commonly used for measure ambient temperature
> from the PT100 3-wire temperature probe.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - SPI,
> hardware reset the device and set default configuration 
> and start the measurement, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtd2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtd2_cfg_setup( &cfg );
    RTD2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtd2_init( &rtd2, &cfg );

    Delay_ms( 200 );

    log_printf( &logger, "----- Hardware Reset ------\r\n" );
    rtd2_hw_reset( &rtd2 );
    Delay_ms( 100 );
    
    log_printf( &logger, "-- Default configuration --\r\n" );

    rtd2_default_cfg( &rtd2 );
    Delay_ms( 1000 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Start Measurement    \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

> This is an example that demonstrates the use of RTD 2 Click board.
> RTD 2 Click board can be used to measure ambient temperature
> from the PT100 3-wire temperature probe
> wired to the 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
> Programmable Gain Amplifier (PGA) For Sensor Measurement
> on the RTD 2 click board
> All data logs write on USB uart changes for every 1 sec.

```c

void application_task ( void )
{
    if ( rtd2_check_new_data_ready( &rtd2 ) == RTD2_NEW_DATA_IS_READY )
    {
        temperature = rtd2_get_temperature( &rtd2 );
        log_printf( &logger, " Temperature : %f C\r\n", temperature );
        log_printf( &logger, "--------------------------\r\n");
        Delay_ms( 1000 );
    }
    else
    {
        rtd2_enable_start( &rtd2, RTD2_START_CONVERSION_DISABLE );
        Delay_ms( 1000 );
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtd 2

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
