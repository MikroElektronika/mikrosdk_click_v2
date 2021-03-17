\mainpage Main Page
 
---
# AD SWIO click

AD-SWIO Click is a quad-channel software configurable input/output solution based on AD74412R. The AD74412R is a quad-channel software configurable input/output integrated circuit for building and process control applications. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adswio_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ad-swio-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the AdSwio Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AdSwio Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void adswio_cfg_setup ( adswio_cfg_t *cfg ); 
 
- Initialization function.
> ADSWIO_RETVAL adswio_init ( adswio_t *ctx, adswio_cfg_t *cfg );

- Click Default Configuration function.
> void adswio_default_cfg ( adswio_t *ctx );


#### Example key functions :

- This function checks the status of the ready pin.
> uint8_t adswio_status_pin_ready ( adswio_t *ctx );
 
- This function allows user to get the converted results of the selected channel.
> adswio_err_t adswio_get_conv_results ( adswio_t *ctx, uint8_t channel, uint16_t *data_out );


## Examples Description

> This click provides a fully integrated single chip solution for input and output operation. 
> The AD-SWIO Click contains four 13-bit DACs, one per chanal, and 16-bit Σ-∆ ADC. 
> These options give a lot of flexibility in choosing functionality for analog output, 
> analog input, digital input, resistance temperature detector (RTD), and thermocouple 
> measurements integrated into a single chip solution with a serial peripheral interface (SPI)

**The demo application is composed of two sections :**

### Application Init 

> Performs a hardware reset of the click board and
> executes a default configuration that enables channel A and sets it to measure voltage
> input in the range from 0V to 10V, with 4800 SPS.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    adswio_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adswio_cfg_setup( &cfg );
    ADSWIO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adswio_init( &adswio, &cfg );
    Delay_ms( 100 );

    adswio_default_cfg( &adswio );
    Delay_ms( 1000 );

    adswio_rdy  = DUMMY;
    adswio_ch_a = DUMMY;
    adswio_res  = DUMMY;
    adswio_err  = ADSWIO_ERR_STATUS_OK;

    log_printf( &logger, " AD-SDIO click initialization done \r\n");
    log_printf( &logger, "************************************\r\n");
}
  
```

### Application Task

> Waits for the data ready and then reads the results of ADC conversion from channel A
> and if response is ok, then prints the results on the uart console.

```c

void application_task ( void )
{
    uint16_t timeout = 0;
    do
    {
        Delay_1ms( );
        timeout++;
        adswio_rdy = adswio_status_pin_ready( &adswio );
        if ( timeout > 3000 ) 
        {
            timeout = 0;
            log_printf( &logger, " Reinitializing...");
            adswio_default_cfg( &adswio );
            log_printf( &logger, "Done\r\n");
        }
    }
    while ( adswio_rdy != 0 );

    adswio_err = adswio_get_conv_results( &adswio, ADSWIO_SETUP_CONV_EN_CHA, &adswio_ch_a );

    if ( adswio_err == ADSWIO_ERR_STATUS_OK )
    {
        adswio_res = adswio_ch_a;
        adswio_res /= ADSWIO_RANGE_RESOLUTION;
        adswio_res *= ADSWIO_RANGE_VOLT_MV;
        adswio_ch_a = adswio_res;

        log_printf( &logger, " Voltage from channel A: %d mV\r\n", adswio_ch_a );
        
        log_printf( &logger, "-----------------------------------\r\n\r\n" );
        Delay_ms( 200 );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AdSwio

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
