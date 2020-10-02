 \mainpage Main Page
 
---
# Analog MUX click

Analog MUX Click is a Click board™ that switches one of the sixteen inputs to one output. It employs the CD74HC4067, a High-Speed CMOS Logic 16-Channel Analog Multiplexer/Demultiplexer, produced by Texas Instruments.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](https://www.mikroe.com/analog-mux-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : ADC type


# Software Support

We provide a library for the AnalogMUX Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AnalogMUX Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void analogmux_cfg_setup ( analogmux_cfg_t *cfg ); 
 
- Initialization function.
> ANALOGMUX_RETVAL analogmux_init ( analogmux_t *ctx, analogmux_cfg_t *cfg );

- Click Default Configuration function.
> void analogmux_default_cfg ( analogmux_t *ctx );


#### Example key functions :

- This function calculates voltage based on the read ADC, vref and rez values.
> float analogmux_get_voltage ( float adc_val, uint16_t vref, uint16_t rez );
 
- This function sets the active channel on the MUX.
> void analogmux_set_channel ( analogmux_t *ctx, uint8_t cfg );

## Examples Description

> This example showcases how to initialize, configure and use the Analog MUX click module. The
  click switches one of the 16 inputs to 1 output and the adc values can be read on the COM (AN)
  pin. RST, PWM, CS and INT are used as control output pins. An external power supply is requ-
  ired in order to make this demo work. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    analogmux_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    Delay_100ms( );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    analogmux_cfg_setup( &cfg );
    ANALOGMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    analogmux_init( &analogmux, &cfg );

    analogmux_set_channel( &analogmux, ANALOGMUX_CHANNEL_0 );
    log_printf( &logger, " ** ADC configured **\r\n" );
}
  
```

### Application Task

> This function first provides the arithmetic mean of 10 measurements on channel 0 (AN0) and 
  then calculates the voltage value using that result. It shows both values in the UART console
  and does so every 2 seconds. 

```c

void application_task ( void )
{
    analogmux_data_t tmp;
    uint8_t cnt;
    float val;

    tmp = 0;
    
    for ( cnt = 0; cnt < 10; cnt++ )
    {
        tmp += analogmux_generic_read( &analogmux );
    }

    val = tmp / 10.0;
    
    log_printf( &logger, " ** ADC value : %.2f\r\n", val );

    val = analogmux_get_voltage( val, ANALOGMUX_DEF_VREF, ANALOGMUX_DEF_REZ );

    log_printf( &logger, " ** Voltage: %.2f\r\n", val );
    log_printf( &logger, " ----------\r\n" );

    Delay_ms( 2000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AnalogMUX

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
