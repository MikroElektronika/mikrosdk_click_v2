
---
# Air Quality 7 click

Air quality 7 Click is a compact add-on board that combines state-of-the-art MOS sensor technology with intelligent detection algorithms to monitor VOCs and CO2 equivalent variations in confined spaces.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/airquality7_click.png" height=300px>
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
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

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
> airquality7_err_t airquality7_get_status( airquality7_t *ctx, uint16_t *tvoc_ppb, uint16_t *co2_ppm, uint32_t *res_val_ohm, uint8_t *err_byte );
 
- Get Revision function.
> airquality7_err_t airquality7_get_revision( airquality7_t *ctx, uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *ascii_code );

- Get R0 Calibration function.
> airquality7_err_t airquality7_get_r0_calib( airquality7_t *ctx, uint16_t *r0_kohm );

## Examples Description

> This demo application measures air quality.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver and reads revision date of the module. 
> If CRC check is OK allows the program to go on, otherwise, it displays a message that
> the program needs to be restarted.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality7_cfg_t cfg;
    
    uint8_t airquality7_rev_year       = AIRQUALITY7_DUMMY;
    uint8_t airquality7_rev_month      = AIRQUALITY7_DUMMY;
    uint8_t airquality7_rev_day        = AIRQUALITY7_DUMMY;
    uint8_t airquality7_rev_ascii_code = AIRQUALITY7_DUMMY;

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

    airquality7_cfg_setup( &cfg );
    AIRQUALITY7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality7_init( &airquality7, &cfg );

    
    airquality7_tvoc_ppb    = AIRQUALITY7_DUMMY;
    airquality7_co2_ppm     = AIRQUALITY7_DUMMY;
    airquality7_res_val_ohm = AIRQUALITY7_DUMMY;

    airquality7_err_code = airquality7_get_revision( &airquality7, 
                                                     &airquality7_rev_year,
                                                     &airquality7_rev_month,
                                                     &airquality7_rev_day,
                                                     &airquality7_rev_ascii_code );
    
    if ( airquality7_err_code == AIRQUALITY7_ERR_OK )
    {
        log_printf( &logger, " Revision date: %.2u.%.2u.%.2u\r\n", ( uint16_t ) airquality7_rev_day, 
                                                                   ( uint16_t ) airquality7_rev_month,
                                                                   ( uint16_t ) airquality7_rev_year );
        log_printf( &logger, " ASCII code for a charter: %u \r\n", ( uint16_t ) airquality7_rev_ascii_code );
    }
    else
    {
        log_printf( &logger, "CRC ERROR READING REVISION. \r\n" );
        Delay_ms ( 1000 );
        
        for ( ; ; )
        {
            log_printf( &logger, "PLEASE, RESTART YOUR SYSTEM...\r\n" );
            Delay_ms ( 1000 );
            log_printf( &logger, " \r\n \r\n " );
            Delay_ms ( 1000 );
        }
    }
    
    log_printf( &logger, "----------------------------------------- \r\n" );
    Delay_ms ( 500 );
}
  
```

### Application Task

> Reads air quality status every 1500ms and shows the results on the USB UART.

```c

void application_task ( void )
{
    airquality7_err_code = airquality7_get_status( &airquality7, 
                                                   &airquality7_tvoc_ppb, 
                                                   &airquality7_co2_ppm,
                                                   &airquality7_res_val_ohm, 
                                                   AIRQUALITY7_NULL );
        
    if ( airquality7_err_code == AIRQUALITY7_ERR_OK )
    {
        uint8_t cnt;

        log_printf( &logger, " tVOC [ppb] = %u \r\n", airquality7_tvoc_ppb );

        log_printf( &logger, " CO2 [ppm] = %u \r\n", airquality7_co2_ppm );

        log_printf( &logger, " Resistor value [ohm] = %lu \r\n", airquality7_res_val_ohm );
        log_printf( &logger, "----------------------------------------- \r\n" );
    }
    
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality7

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
