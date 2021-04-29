
---
# ADAC click

The click is designed to run on either 3.3V or 5V power supply. ADAC click communicates with the target microcontroller over I2C interface, with additional functionality provided by the RST pin on the mikroBUS™ line. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adac_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/adac-click-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the ADAC Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ADAC Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void adac_cfg_setup ( adac_cfg_t *cfg ); 
 
- Initialization function.
> ADAC_RETVAL adac_init ( adac_t *ctx, adac_cfg_t *cfg );

- Click Default Configuration function.
> void adac_default_cfg ( adac_t *ctx );


#### Example key functions :

- This function writes DAC using the I2C serial interface.
> void adac_write_dac ( adac_t *ctx, uint8_t chan, uint8_t msb, uint8_t lsb );
 
- This function reads ADC data using the I2C serial interface.
> uint16_t adac_read_adc( adac_t *ctx, uint8_t *chan );

- This function sets the configuration for the click module.
> void adac_set_configuration ( adac_t *ctx, uint8_t ptr, uint8_t msb, uint8_t lsb );

## Examples Description

> This example showcases how to initialize, configure and use the ADAC click module. The click
  has an ADC and a DAC. An external power supply sets the maximum voltage of the input analog
  signal, which is bound to 2.5 V by default. For the input any external analog signal will
  suffice and a multimeter is needed to read the output on one of the channels.
  
**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the click and logger modules. It does a hardware 
  reset first and after that configures the click module using default settings. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    adac_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adac_cfg_setup( &cfg );
    ADAC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adac_init( &adac, &cfg );
    Delay_100ms( );
    adac_hardware_reset( &adac );
    Delay_100ms( );
    adac_set_configuration( &adac, ADAC_POWER_REF_CTRL, ADAC_VREF_ON, ADAC_NO_OP );
    Delay_100ms( );
    log_printf( &logger, "\r\n Click module initialized \r\n" );
    Delay_ms( 500 );
}
  
```

### Application Task

> This function first writes digital values ranging from 0 to 256 to output channel 3 with a 
  10 millisecond delay between iterations and after that reads analog values from channel 4 
  10 times and displays results in the UART console. 

```c

void application_task ( void )
{
    uint16_t adc_val;
    uint16_t cnt;
    uint8_t chan;

    log_printf( &logger, "\r\n *** DAC : write ***\r\n" );
    adac_set_configuration( &adac, ADAC_DAC_CONFIG, ADAC_NO_OP, ADAC_IO3 );
    Delay_100ms( );

    for ( cnt = 0; cnt < 0xFF; cnt +=4 )
    {
        adac_write_dac( &adac, ADAC_PB_PIN3, cnt / 0x100, cnt % 0x100 );
        Delay_ms( 10 );
        log_printf( &logger, " > write... \r\n" );
    }
    
    log_printf( &logger, "-------------------\r\n" );
    Delay_ms( 1000 );

    log_printf( &logger, "\r\n *** ADC : read ***\r\n" );
    adac_set_configuration( &adac, ADAC_ADC_CONFIG, ADAC_NO_OP, ADAC_IO4 );
    Delay_100ms( );
    adac_set_configuration( &adac, ADAC_ADC_SEQUENCE, ADAC_SEQUENCE_ON, ADAC_IO4 );

    for( cnt = 0; cnt < 10; cnt++ )
    {
        adc_val = adac_read_adc( &adac, &chan );
        log_printf( &logger, "   channel : %d\r\n", chan );
        log_printf( &logger, "       val : %d\r\n", adc_val ); 
        Delay_ms( 2000 );
    }

    log_printf( &logger, "-------------------\r\n" );
    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ADAC

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
