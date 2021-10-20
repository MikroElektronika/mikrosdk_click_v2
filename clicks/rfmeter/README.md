\mainpage Main Page
 
 

---
# RF Meter click

RF Meter click is a radio frequency power measurement device covering a frequency span from 1 MHz to 8 GHz over a 60 dB range (approximately).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rfmeter_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rf-meter-click-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Rfmeter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rfmeter Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rfmeter_cfg_setup ( rfmeter_cfg_t *cfg ); 
 
- Initialization function.
> RFMETER_RETVAL rfmeter_init ( rfmeter_t *ctx, rfmeter_cfg_t *cfg );


#### Example key functions :

- Function is used to calculate radio frequency signal strenght in a vicinity.
> float rfmeter_get_signal_strenght ( rfmeter_t *ctx, float slope, float intercept );

## Examples Description

> 
> Demo app measures and displays signal strenght by using RF Meter click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initalizes SPI, LOG and click drivers.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rfmeter_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "---- Application Init ----" );

    //  Click initialization.

    rfmeter_cfg_setup( &cfg );
    RFMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rfmeter_init( &rfmeter, &cfg );
    log_printf( &logger, "----------------------- \r\n" );
    log_printf( &logger, "    RF Meter Click      \r\n" );
    log_printf( &logger, "----------------------- \r\n" );
}
  
```

### Application Task

>
> This is an example that shows the capabilities of the RF Meter click by
> measuring radio frequency signal strenght.
> 

```c

void application_task ( void )
{
    signal = rfmeter_get_signal_strenght( &rfmeter, RFMETER_DEF_SLOPE, RFMETER_DEF_INTERCEPT );
    
    log_printf( &logger, "Signal strenght: %.2f dBm \r\n", signal );
    
    Delay_ms( 1000 );
    log_printf( &logger, "-----------------------\r\n" );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rfmeter

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
