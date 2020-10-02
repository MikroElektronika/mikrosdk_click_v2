\mainpage Main Page
 
 

---
# Qi Receiver click

Qi Receiver click is based on the P9025AC 5W Qi wireless power receiver integrated circuit, with the advanced Foreign Object Detection (FOD) feature, from IDT. The click utilizes the principles of the inductive coupling for the purpose of wireless power transfer.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/qireceiver_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/qi-receiver-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the QiReceiver Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for QiReceiver Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void qireceiver_cfg_setup ( qireceiver_cfg_t *cfg ); 
 
- Initialization function.
> QIRECEIVER_RETVAL qireceiver_init ( qireceiver_t *ctx, qireceiver_cfg_t *cfg );

- Click Default Configuration function.
> void qireceiver_default_cfg ( qireceiver_t *ctx );


#### Example key functions :

- Function is used to measure current voltage in volt.
> float qireceiver_read_voltage( qireceiver_t *ctx );
 
- Function is used to measure current amperage in ampere.
> qireceiver_read_current( qireceiver_t *ctx );

- Function is used to measure current frequency in hertz.
> qireceiver_read_freq( qireceiver_t *ctx );

- Function is used to enable the device.
> void qireceiver_dev_enable( qireceiver_t *ctx );

## Examples Description

> This application reads voltage, current and frequency.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver, enables the device and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    qireceiver_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    qireceiver_cfg_setup( &cfg );
    QIRECEIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    qireceiver_init( &qireceiver, &cfg );
    
    Delay_ms( 100 );
    qireceiver_dev_enable( &qireceiver );
    log_printf( &logger, "-----------------" );
    log_printf( &logger, "Qi Receiver Click" );
    log_printf( &logger, "-----------------" );
    Delay_ms( 100 );
}
  
```

### Application Task

> This is an example that shows the most important
        functions that Qi Receiver click has, it mesures current voltage, amperage and frequency.

```c

void application_task ( void )
{
    char logTxt[ 50 ];
    float voltage;
    float current;
    float freq;
    
    voltage = qireceiver_readVoltage();
    FloatToStr( voltage, logTxt );
    log_printf( &logger, "Voltage : \r\n", LOG_TEXT );
    log_printf( &logger, logTxt, LOG_TEXT );
    log_printf( &logger, " V\r\n", LOG_LINE );

    current = qireceiver_readCurrent();
    FloatToStr( current, logTxt );
    log_printf( &logger, "Current : \r\n", LOG_TEXT );
    log_printf( &logger, logTxt, LOG_TEXT );
    log_printf( &logger, " A\r\n", LOG_LINE );

    freq = qireceiver_readFreq();
    FloatToStr( freq, logTxt );
    log_printf( &logger, "Frequency : \r\n", LOG_TEXT );
    log_printf( &logger, logTxt, LOG_TEXT );
    log_printf( &logger, " Hz\r\n", LOG_LINE );
    
    log_printf( &logger, "-----------------\r\n", LOG_LINE );
    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.QiReceiver

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
