
---
# Air Quality 7 click

Air quality 7 Click is a compact add-on board that combines state-of-the-art MOS sensor technology with intelligent detection algorithms to monitor VOCs and CO2 equivalent variations in confined spaces.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](https://www.mikroe.com/air-quality-7-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Aug 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the AirQuality7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AirQuality7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void airquality7_cfg_setup ( airquality7_cfg_t *cfg ); 
 
- Initialization function.
> AIRQUALITY7_RETVAL airquality7_init ( airquality7_t *ctx, airquality7_cfg_t *cfg );

#### Example key functions :

- Get Status function.
> airquality7_err_t
> airquality7_get_status( airquality7_t *ctx, uint16_t *tvoc_ppb, uint16_t *co2_ppm, 
                        uint32_t *res_val_ohm, uint8_t *err_byte );
 
- Get Revision function.
> airquality7_err_t 
> airquality7_get_revision( airquality7_t *ctx, uint8_t *year, uint8_t *month, uint8_t *day,
                            uint8_t *ascii_code );

- Get R0 Calibration function.
> airquality7_err_t airquality7_get_r0_calib( airquality7_t *ctx, uint16_t *r0_kohm );

## Examples Description

> This demo application measures air quality.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver and reads revision of the 
> module. If CRC check is OK allows the program to go on, and if it's not OK,
> needs to restart the program.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality7_cfg_t cfg;
    
    uint8_t airquality7_rev_year       = AIRQUALITY7_DUMMY;
    uint8_t airquality7_rev_month      = AIRQUALITY7_DUMMY;
    uint8_t airquality7_rev_day        = AIRQUALITY7_DUMMY;
    uint8_t airquality7_rev_ascii_code = AIRQUALITY7_DUMMY;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    airquality7_cfg_setup( &cfg );
    AIRQUALITY7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality7_init( &airquality7, &cfg );

    
    airquality7_tvoc_ppb    = AIRQUALITY7_DUMMY;
    airquality7_co2_ppm     = AIRQUALITY7_DUMMY;
    airquality7_res_val_ohm = AIRQUALITY7_DUMMY;

    airquality7_err_code = airquality7_get_revision( &airquality7, &airquality7_rev_year,
                                                     &airquality7_rev_month,
                                                     &airquality7_rev_day,
                                                     &airquality7_rev_ascii_code
                                                     );
    
    if ( airquality7_err_code == AIRQUALITY7_ERR_OK )
    {
        log_printf( &logger, "REVISION: \r\n" );
        log_printf( &logger, " Year: %d \r\n", airquality7_rev_year );
        Delay_ms( 500 );
    
        log_printf( &logger, " Month: %d \r\n", airquality7_rev_month );
        Delay_ms( 500 );
    
        log_printf( &logger, " Day: %d \r\n", airquality7_rev_day );
        Delay_ms( 500 );
    
        log_printf( &logger, " ASCII code for a charter: %d \r\n", airquality7_rev_ascii_code );
    }
    else
    {
        log_printf( &logger, "CRC ERROR READING REVISION. \r\n" );
        Delay_ms( 1000 );
        
        for ( ; ; )
        {
            log_printf( &logger, "PLEASE, RESTART YOUR SYSTEM...\r\n" );
            Delay_ms( 1000 );
            log_printf( &logger, " \r\n \r\n " );
            Delay_ms( 1000 );
        }
    }
    
    log_printf( &logger, "----------------------------------------- \r\n" );
    Delay_ms( 500 );
}
  
```

### Application Task

> Reads air quality status every 1500ms and shows the results on serial terminal.

```c

void application_task ( void )
{
    airquality7_err_code = airquality7_get_status( &airquality7, &airquality7_tvoc_ppb, 
                                                   &airquality7_co2_ppm,
                                                   &airquality7_res_val_ohm, 
                                                   AIRQUALITY7_NULL );
        
    
    if ( airquality7_err_code == AIRQUALITY7_ERR_OK )
    {
        uint8_t cnt;

        log_printf( &logger, "\r\n" );

        for ( cnt = 0; cnt < 70; cnt++ )
        {
            log_printf( &logger, " " );
            Delay_ms( 5 );
        }

        log_printf( &logger, "\r\n" );

        log_printf( &logger, " tVOC [ppb] = %d ", airquality7_tvoc_ppb );
        log_printf( &logger, ";  " );

        log_printf( &logger, "CO2 [ppm] = %d ", airquality7_co2_ppm );
        log_printf( &logger, ";  " );

        log_printf( &logger, "Resistor value [ohm] = %ld ", airquality7_res_val_ohm );
    }
    
    Delay_ms( 1500 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality7

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
