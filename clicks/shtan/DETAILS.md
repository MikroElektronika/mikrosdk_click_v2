 
---
# SHT AN click

SHT AN Click is a sensorics based add on board which can be used for measuring humidity and temperature. It features fully calibrated, linearized and temperature compensated SHT31-ARP-B sensor with analog output.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/shtan_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/sht-an-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : ADC type


# Software Support

We provide a library for the ShtAn Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ShtAn Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void shtan_cfg_setup ( shtan_cfg_t *cfg ); 
 
- Initialization function.
> SHTAN_RETVAL shtan_init ( shtan_t *ctx, shtan_cfg_t *cfg );

- Click Default Configuration function.
> void shtan_default_cfg ( shtan_t *ctx );


#### Example key functions :

- Function sets signal output ADC mode 
- of the SHT3x-ARP Humidity and Temperature Sensor IC on SHT
- ANClick.
> void shtan_set_mode ( shtan_t *ctx, uint8_t adc_mode );
 
- Function hardware reset the SHT3x-ARP Humidity and Temperature Sensor IC
- on SHT AN click by cleared to '0' state of the RST pin,
- wait the 100 ms, sets to '1' state of the RST pin.
> void shtan_reset ( shtan_t *ctx );


## Examples Description

> This example demonstrates the use of SHT AN click to measure temperature and humidity.


**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - GPIO, sw reset,
> initializes ADC, set ADC channel and sets ADC read mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    shtan_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    shtan_cfg_setup( &cfg );
    SHTAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    shtan_init( &shtan, &cfg );

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "   SHT AN click   \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 100 );

    deg_cel[ 0 ] = 32;
    deg_cel[ 1 ] = 176;
    deg_cel[ 2 ] = 67;
    deg_cel[ 3 ] = 0;

    shtan_reset( &shtan );
    Delay_ms ( 1000 );
    shtan_set_mode( &shtan, SHTAN_SET_ADC_MODE_TEMP );
    adc_mode = SHTAN_SET_ADC_MODE_TEMP;
    log_printf( &logger, "  Temp. & Hum.   \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

> This is a example which demonstrates the use of SHT AN Click board.
> Measured temperature and humidity ADC data and calculate temperature data to degrees Celsius [ �C ] and
> humidity data to percentarg [ % ].
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 1 sec.

```c

void application_task ( void )
{
   shtan_calculate_temperature( void );
   log_printf( &logger, "  Temp. : %.2f\r\n", temperature );
   shtan_calculate_humidity( void );
   log_printf( &logger, "  Hum.  : %.2f\r\n", humidity );
   log_printf( &logger, "--------------------------" );
   Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ShtAn

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
