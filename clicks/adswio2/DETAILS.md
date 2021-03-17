
---
# AD SWIO 2 click

AD-SWIO 2 Click is a quad-channel software configurable input/output solution based on AD74413R, for building and process control application. The AD74413R is a quad-channel software configurable input/output solution for building and process control applications. The device provides a fully integrated single chip solution for input and output operation. The AD-SWIO 2 Click contains four 13-bit DACs, one per chanal, and 16-bit Σ-∆ ADC. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adswio2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ad-swio-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the AdSwio2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AdSwio2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void adswio2_cfg_setup ( adswio2_cfg_t *cfg ); 
 
- Initialization function.
> ADSWIO2_RETVAL adswio2_init ( adswio2_t *ctx, adswio2_cfg_t *cfg );

- Click Default Configuration function.
> void adswio2_default_cfg ( adswio2_t *ctx );


#### Example key functions :

- This function allows user to get the converted results of the selected channel.
> adswio2_err_t adswio2_get_conv_results ( adswio2_t *ctx, uint8_t channel, uint16_t *data_out );
 
- This function checks the status of the ready pin.
> uint8_t adswio2_status_pin_ready ( adswio2_t *ctx );


## Examples Description

> This Click is a quad-channel software configurable input/output solution for building 
> and process control application. The AD-SWIO 2 Click contains four 13-bit DACs, one 
> per chanal, and 16-bit Σ-∆ ADC. These options give a lot of flexibility in choosing 
> functionality for analog output, analog input, digital input, resistance temperature 
> detector (RTD), and thermocouple measurements integrated into a single chip solution 
> with a serial peripheral interface (SPI). 

**The demo application is composed of two sections :**

### Application Init 

> Performs a hardware reset of the click board and
> executes a default configuration that enables channel A and sets it to measure voltage
> input in the range from 0V to 10V, with 4800 SPS.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    adswio2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adswio2_cfg_setup( &cfg );
    ADSWIO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adswio2_init( &adswio2, &cfg );
    Delay_ms( 100 );
    
    adswio2_default_cfg( &adswio2 );
    Delay_ms( 1000 );

    adswio2_rdy  = DUMMY;
    adswio2_ch_a = DUMMY;
    adswio2_res  = DUMMY;
    adswio2_err  = ADSWIO2_ERR_STATUS_OK;
    log_printf( &logger, " AD-SWIO 2 click initialization done \r\n");
    log_printf( &logger, "************************************\r\n");
}
  
```

### Application Task

> Waits for the data ready and then reads the results of ADC conversion from channel A
> and if response is ok, then prints the results on the uart console.

```c

void application_task ( void )
{
    timeout = 0;
    do
    {
        Delay_1ms( );
        timeout++;
        adswio2_rdy = adswio2_status_pin_ready( &adswio2 );
        if ( timeout > 3000 ) 
        {
            timeout = 0;
            log_printf( &logger, " Reinitializing...");
            adswio2_default_cfg( &adswio2 );
            log_printf( &logger, "Done\r\n");
        }
    }
    while ( adswio2_rdy != 0 );
    
    adswio2_err = adswio2_get_conv_results( &adswio2, ADSWIO2_SETUP_CONV_EN_CHA, &adswio2_ch_a );
    
    if ( adswio2_err == ADSWIO2_ERR_STATUS_OK )
    {
        adswio2_res = adswio2_ch_a;
        adswio2_res /= ADSWIO2_RANGE_RESOLUTION;
        adswio2_res *= ADSWIO2_RANGE_VOLT_MV;
        adswio2_ch_a = adswio2_res;

        log_printf( &logger, " Voltage from channel A: %d mV\r\n", adswio2_ch_a );
        
        log_printf( &logger, "-----------------------------------\r\n\r\n" );
        Delay_ms( 200 );
    }
}
 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AdSwio2

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
