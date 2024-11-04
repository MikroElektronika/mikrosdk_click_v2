\mainpage Main Page
 
 

---
# Single Cell Click

The Single Cell Click is a Click board™ which features MCP16251 synchronous boost regulator with true load disconnect and MCP1811A low-dropout (LDO) linear regulator that provide an ultra low quiescent current during device operation of about 250nA and can be shut down for 5nA (typical) supply current draw. Given the potential applications of these features, the Single Cell Click can be used for one, two and three-cell Alkaline and NiMH/NiCd portable products, solar cell applications, personal care and medical products, smartphones, MP3 players, wireless sensors and many more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/singlecell_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/single-cell-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the SingleCell Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for SingleCell Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void singlecell_cfg_setup ( singlecell_cfg_t *cfg ); 
 
- Initialization function.
> SINGLECELL_RETVAL singlecell_init ( singlecell_t *ctx, singlecell_cfg_t *cfg );

- Click Default Configuration function.
> void singlecell_default_cfg ( singlecell_t *ctx );


#### Example key functions :

- Set power mode function.
> void singlecell_set_power_mode ( singlecell_t *ctx, uint8_t en_mode );

## Examples Description

> 
> Demo application is used to shows basic controls Single Cell Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initializes GPIO and LOG structures,
> set CS pin as output and start write log.
> Initialization driver enable's - GPIO, also write log.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    singlecell_cfg_t cfg;

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
    log_printf(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    singlecell_cfg_setup( &cfg );
    SINGLECELL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    singlecell_init( &singlecell, &cfg );
    singlecell_default_cfg ( &singlecell );
   
    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "    Single Cell Click    \r\n");
    log_printf(&logger, "-------------------------\r\n");

    Delay_ms ( 100 );
}
  
```

### Application Task

>
> This is a example which demonstrates the use of Single Cell board.
> This example shows the automatic control of the Single Cell Click,
> enable and disable power the regulator output on 10 sec. 
> 

```c

void application_task ( void )
{
    log_printf(&logger, "         Enable\r\n");
    singlecell_set_power_mode ( &singlecell, SINGLECELL_ENABLE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf(&logger, "         Disable\r\n");
    singlecell_set_power_mode ( &singlecell, SINGLECELL_DISABLE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
 

```

## Note

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.SingleCell

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
