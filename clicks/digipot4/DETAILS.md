
# Digi Pot 4 click

DIGI POT 4 click is a digitally controlled dual potentiometer, with the resistance of 10KΩ. It has a 10bit resolution which allows for a very smooth linear wiper positioning through 1024 steps.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digipot4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/digi-pot-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the DigiPot4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DigiPot4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void digipot4_cfg_setup ( digipot4_cfg_t *cfg ); 
 
- Initialization function.
> DIGIPOT4_RETVAL digipot4_init ( digipot4_t *ctx, digipot4_cfg_t *cfg );

- Click Default Configuration function.
> void digipot4_default_cfg ( digipot4_t *ctx );


#### Example key functions :

- This function writes data in wiper register and NV register.
> void digipot4_write_reg ( digipot4_t *ctx, uint8_t reg,          uint16_t value );
 
- This function is used to copy the data from the wipers to the    NV memory and from the NV memory it wipers.
> void digipot4_copy_reg ( digipot4_t *ctx, uint8_t reg );

## Examples Description

> This application is a digitally controlled dual potentiometer.

**The demo application is composed of two sections :**

### Application Init 

> Driver intialization

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    digipot4_cfg_t cfg;

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

    digipot4_cfg_setup( &cfg );
    DIGIPOT4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digipot4_init( &digipot4, &cfg );
}
  
```

### Application Task

> Set the wiper position. 

```c

void application_task ( void )
{

    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_1, 0 );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_2, 0 );
    Delay_1sec( );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_1, 512 );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_2, 512 );
    Delay_1sec( );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_1, 1023 );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_2, 1023 );
    Delay_1sec( );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DigiPot4

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
