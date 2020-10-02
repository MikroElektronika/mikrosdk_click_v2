
---
# HZ to V 2 click

HZ to V 2 click is a device that can convert input frequency of the signal with virtually any wave shape to a DC voltage output, with a level proportional to the input frequency.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hztov2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/hz-to-v-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : ADC type


# Software Support

We provide a library for the HzToV2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HzToV2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hztov2_cfg_setup ( hztov2_cfg_t *cfg ); 
 
- Initialization function.
> HZTOV2_RETVAL hztov2_init ( hztov2_t *ctx, hztov2_cfg_t *cfg );

- Click Default Configuration function.
> void hztov2_default_cfg ( hztov2_t *ctx );


#### Example key functions :

- This function enable the click board.
> void hztov2_en_pin ( hztov2_t *ctx, uint8_t pin_state );
 
- This function setting and clearing of the FIN pin.
> void hztov2_fin_pin ( hztov2_t *ctx, uint8_t pin_state );

## Examples Description

> This app converts input frequency to a DC voltage output.

**The demo application is composed of two sections :**

### Application Init 

> Power on the click board and initilaize device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hztov2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hztov2_cfg_setup( &cfg );
    HZTOV2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hztov2_init( &hztov2, &cfg );
    hztov2_en_pin( &hztov2, 1 );
    Delay_ms( 100 );
}
  
```

### Application Task

> Voltage reading is done from the analog pin and the conversion
> result is sent to UART terminal.

```c

void application_task ( void )
{
    hztov2_data_t tmp;
    float voltage;
    
    tmp = hztov2_generic_read ( &hztov2 );
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    Delay_ms( 1000 );

    voltage = hztov2_adc_read( &hztov2 );
    if( voltage < 0.99 )
    {
      voltage = voltage * 1000.0;
      log_printf( &logger, "Voltage: %f mV \r\n", voltage );
    }
    else
    {
        log_printf( &logger, "Voltage: %f V \r\n", voltage );
    }

    Delay_ms(100);
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HzToV2

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
