 
---
# AD SWIO click

AD-SWIO Click is a quad-channel software configurable input/output solution based on AD74412R. The AD74412R is a quad-channel software configurable input/output integrated circuit for building and process control applications. 

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
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
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

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
> executes a default configuration which includes that channel A will be
> enabled to measure voltage input in the range from 0V to 10V, with 4k8 SPS
> sample rating. In this function also Silicon Revision ID will be checked.

```c

void application_init ( void )
{
    uint16_t id = DUMMY;
    log_cfg_t log_cfg;
    adswio_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud =  57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adswio_cfg_setup( &cfg );
    ADSWIO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adswio_init( &adswio, &cfg );

    adswio_set_handler( &adswio, &application_default_handler );
    Delay_ms( 200 );

    adswio_default_cfg( &adswio );

    adswio_rdy  = DUMMY;
    adswio_ch_a = DUMMY;
    adswio_res  = DUMMY;
    adswio_err  = ADSWIO_ERR_STATUS_OK;

    log_printf( &logger, "***  AD-SDIO click initialization done  ***\r\n");
    log_printf( &logger, "*******************************************\r\n");
    Delay_ms( 100 );

    while ( id != ADSWIO_ID_SILICON_REV )
    {
        adswio_generic_read( &adswio, ADSWIO_REG_SILICON_REV, &id, ADSWIO_NULL );
    }
}
  
```

### Application Task

> Waits until data from the enabled channel
> is ready and then reads results of conversion for channel A and if response
> is ok, prints the results on the uart console.

```c

void application_task ( void )
{
    adswio_rdy = adswio_status_pin_ready( &adswio );

    while ( adswio_rdy == 0 )
    {
        adswio_rdy = adswio_status_pin_ready( &adswio );
    }

    adswio_err = adswio_get_conv_results( &adswio, ADSWIO_SETUP_CONV_EN_CHA, &adswio_ch_a );

    if ( adswio_err == ADSWIO_ERR_STATUS_OK )
    {
        adswio_res = adswio_ch_a;
        adswio_res /= ADSWIO_RANGE_RESOLUTION;
        adswio_res *= ADSWIO_RANGE_VOLT_MV;
        adswio_ch_a = adswio_res;

        log_printf( &logger, "* CH A converted result is %s mV\r\n", adswio_ch_a );
        Delay_ms( 100 );
    }
}  

```

## Note

>  <pre> 
>  Additional Functions :
> 
>  Application Default Handler - Used to send error report messages from click
>  driver to initialized console module.
>  </pre>

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AdSwio

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
