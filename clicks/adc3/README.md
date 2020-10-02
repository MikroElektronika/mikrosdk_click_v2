\mainpage Main Page
 
 

---
# ADC 3 click

ADC 3 Click represent 16-bit multichannel analog-to-digital converter. 
The click has four pairs of screw terminals onboard, letting you access the chip’s four differential input channels.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/adc3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/adc-3-click>)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Adc3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Adc3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void adc3_cfg_setup ( adc3_cfg_t *cfg ); 
 
- Initialization function.
> ADC3_RETVAL adc3_init ( adc3_t *ctx, adc3_cfg_t *cfg );

- Click Default Configuration function.
> void adc3_default_cfg ( adc3_t *ctx );


#### Example key functions :

- This function is used to initiate general call reset.
> void adc3_default_cfg ( adc3_t *ctx );
 
- This function is used to read ADC value and calculate voltage.
> float adc3_read_voltage ( adc3_t *ctx, uint8_t channel, uint8_t resolution, uint8_t gain );

## Examples Description

> 
> ADC 3 example code shows usage of analog-to-digital converter.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Application Init performs Logger and Click initialization.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 100 );

    //  Click initialization.

    adc3_cfg_setup( &cfg );
    ADC3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc3_init( &adc3, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ------ ADC 3 Click ----- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    adc3_default_cfg( &adc3 );
    Delay_ms ( 100 );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> This is an example that shows the capabilities of the ADC 3 Click 
> by taking voltage measurements from all four channel. Results are being sent to the UART Terminal 
> where you can track their changes. All data logs write on USB UART and changes for every 1 sec.
> 

```c

void application_task ( void )
{
    read_volt = adc3_read_voltage( &adc3, ADC3_SELECT_CHANNEL_1, ADC3_SAMPLE_RATE_12, ADC3_PGA_GAIN_X1 );
    Delay_ms( 100 );
    log_printf( &logger, "Channel 1 : %0.2f  V \r\n", read_volt );

    read_volt = adc3_read_voltage( &adc3, ADC3_SELECT_CHANNEL_2, ADC3_SAMPLE_RATE_12, ADC3_PGA_GAIN_X1 );
    Delay_ms( 100 );
    log_printf( &logger, "Channel 2 : %0.2f  V \r\n", read_volt );
    
    read_volt = adc3_read_voltage( &adc3, ADC3_SELECT_CHANNEL_3, ADC3_SAMPLE_RATE_12, ADC3_PGA_GAIN_X1 );
    Delay_ms( 100 );
    log_printf( &logger, "Channel 3 : %0.2f  V \r\n", read_volt );
    
    read_volt = adc3_read_voltage( &adc3, ADC3_SELECT_CHANNEL_4, ADC3_SAMPLE_RATE_12, ADC3_PGA_GAIN_X1 );
    Delay_ms( 100 );
    log_printf( &logger, "Channel 4 : %0.2f  V \r\n", read_volt );
    
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc3

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
