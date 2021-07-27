\mainpage Main Page
 
---
# Noise click

Noise click is a mikroBUS add-on board with noise detecting circuitry. It enables you to set a noise detection threshold for alarm systems, environmental monitoring or data logging.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/noise_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/noise-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the noise Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for noise Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void noise_cfg_setup ( noise_cfg_t *cfg ); 
 
- Initialization function.
> NOISE_RETVAL noise_init ( noise_t *ctx, noise_cfg_t *cfg );

- Click Default Configuration function.
> void noise_default_cfg ( noise_t *ctx );


#### Example key functions :

- This function sets command register.
> uint8_t noise_set_command_register ( noise_t *ctx, uint8_t configuration,
>                                      uint16_t threshold );
 
- This function switches click on or off.
> void noise_set_state ( noise_t *ctx, uint8_t state );

- This function reads value from adc.
> noise_data_t noise_read_adc ( noise_t *ctx );

## Examples Description

This example performs noise monitoring and 2D graph 
plotting based on measured ambient noise using Noise Click.  

**The demo application is composed of two sections :**

### Application Init 

Device initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    noise_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    noise_cfg_setup( &cfg );
    NOISE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    noise_init( &noise, &cfg );

    noise_default_cfg( &noise );
}
  
```

### Application Task

Every 5 ms measure ambient noise and if it's above threshold
alarm message is being shown.
Monitoring results are being plotted on serial plotter. 

```c

void application_task ( void )
{
    uint8_t interrupt_status;
    interrupt_status = noise_check_int_pin( &noise );

    adc_value = noise_read_adc( &noise );
    plot_data( adc_value );
    Delay_ms( 5 );

    if (interrupt_status == 1)
    {
        log_printf( &logger, " Sound threshold exceeded \r\n" );
    }
}

```

## Note

When ambient noise is above specified threshold, an interrupt
is triggered. Default threshold value is set to 0x64 = 52.

Additional functions:

- void plot_data ( uint16_t data_plot ) - plots 2D graph
based on provided ADC value.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.noise

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
