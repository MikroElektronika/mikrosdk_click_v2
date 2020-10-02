
 

---
# DAC click

DAC click is an accessory board in mikroBUS form factor. 
It includes a 12-bit Digital-to-Analog Converter MCP4921 that features an optional 2x buffered output and SPI interface.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/dac_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/dac-click>)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Dac Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dac Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dac_cfg_setup ( dac_cfg_t *cfg ); 
 
- Initialization function.
> DAC_RETVAL dac_init ( dac_t *ctx, dac_cfg_t *cfg );


#### Example key functions :

-  This function is used to set output voltage in percents.
> void dac_set_voltage_pct ( dac_t *ctx, uint8_t v_out_pct );
 
- This function is used to set output voltage.
> void dac_set_voltage ( dac_t *ctx, uint16_t v_out );

## Examples Description

> 
> This demo example sends digital signal to the outputs 
> and converts it to analog.
>

**The demo application is composed of two sections :**

### Application Init 

>
> Initializes driver, SPI communication and LOG.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    dac_cfg_setup( &cfg );
    DAC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac_init( &dac, &cfg );
}
  
```

### Application Task

>
> Sends different values( form 0 to 4095 with step 1000 ) to output and 
> prints expected measurement.
> 

```c

void application_task ( void )
{
    for ( dac_val = 0; dac_val <= DAC_RESOLUTION; dac_val += DAC_STEP_VALUE )
    {
        dac_set_voltage( &dac, dac_val );
        dac_val *= DAC_CALIB_VAL_1;
        dac_val /= DAC_CALIB_VAL_2;
        log_printf( &logger, " Current DAC Value: %d mV \r\n", dac_val );

        log_printf( &logger, "----------------------------------\r\n" );

        Delay_ms( 2000 );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dac

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
