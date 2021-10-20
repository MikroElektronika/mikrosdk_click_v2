
---
# POWER BANK click

PowerBank Click is a USB charging expansion board which can be used for creating power bank devices or adding charging option to your device. For battery charging management this board uses MP2632B a highly integrated 3A Lu-ion and Li-polymer battery charger from Microchip. In addition to battery charger PowerBank Click also has a MCP3221 analog to digital converter, which is serving for monitoring battery voltage over I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/powerbank_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/power-bank-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the PowerBank Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for PowerBank Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void powerbank_cfg_setup ( powerbank_cfg_t *cfg ); 
 
- Initialization function.
> POWERBANK_RETVAL powerbank_init ( powerbank_t *ctx, powerbank_cfg_t *cfg );



#### Example key functions :

- Read data function
> uint16_t powerbank_read_data ( powerbank_t *ctx );
 
- Read voltage function
> uint16_t powerbank_read_voltage ( powerbank_t *ctx, uint16_t v_ref );


## Examples Description

> 
> This is an example which demonstrates the usage of Power Bank Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    powerbank_cfg_t cfg;

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

    powerbank_cfg_setup( &cfg );
    POWERBANK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    powerbank_init( &powerbank, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "     PowerBank click    \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}
  
```

### Application Task

> This example shows the capabilities of the PowerBank click by measuring voltage of the connected battery. In order to get correct calculations user should change "v_ref" value to his own power supply voltage.

```c

void application_task ( void )
{
    uint16_t voltage;
    uint16_t v_ref = 5075;

    voltage = powerbank_read_voltage( &powerbank, v_ref );
    log_printf( &logger, "Battery voltage: %d mV\r\n", voltage );
    
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 2000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerBank

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
