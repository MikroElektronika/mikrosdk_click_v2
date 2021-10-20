

---
# Current click

Current click is an add-on board used for measurement of electric current. It features INA196 current shunt monitor, MCP3201 12-bit ADC, MAX6106 voltage reference as well as two screw terminals. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/current_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/current-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Current Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Current Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void current_cfg_setup ( current_cfg_t *cfg ); 
 
- Initialization function.
> CURRENT_RETVAL current_init ( current_t *ctx, current_cfg_t *cfg );


#### Example key functions :

- Function is used to calculate current in mA.
> float current_get_current_data ( current_t *ctx, float r_hunt );

## Examples Description

> This is an example that shows the capabilities of the Current click board 
> by measuring current in miliampers. Current click board can be used to safely
> measure DC current in the range of 2-2048mA depending on shunt resistor.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes SPI, LOG and click drivers.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    current_cfg_t cfg;

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

    current_cfg_setup( &cfg );
    CURRENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    current_init( &current, &cfg );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    Current  Click     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}
  
```

### Application Task

> Measures DC current and displays the results on USB UART each second.

```c

void application_task ( void )
{
    curr = current_get_current_data( &current, CURRENT_RSHUNT_0_05 );
    
    if ( curr == CURRENT_OUT_OF_RANGE )
    {
        log_printf( &logger, "Out of range!\r\n" );
    }
    else
    {
       log_printf( &logger, " Current: %.2f mA\r\n", curr );
    }
    
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Current

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
