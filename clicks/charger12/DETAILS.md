
---
# CHARGER 12 Click

Charger 12 Click is a single lithium-ion (Li+) cell or three-cell NiMH/NiCd battery charger. This Click can be used for Low-Cost Li-Ion battery chargers, or Power Tools, toys, backup energy storage solutions, etc. Charger 12 Click is based on MAX1501 controller which has some extra features enabling charging without too much hassle.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger12_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/charger-12-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Charger12 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Charger12 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void charger12_cfg_setup ( charger12_cfg_t *cfg ); 
 
- Initialization function.
> CHARGER12_RETVAL charger12_init ( charger12_t *ctx, charger12_cfg_t *cfg );


#### Example key functions :

- Generic transfer.
> void charger12_generic_transfer ( charger12_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t tx_len, uint8_t rx_len );
 
- Charger mode selection.
> uint8_t charger12_mode_select ( charger12_t *ctx, uint8_t mode_select );

- This function set spi register.
> void charger12_spi_set_register( charger12_t *ctx, uint8_t register_address, uint16_t register_value )

## Examples Description

> This application charges the batery.

**The demo application is composed of two sections :**

### Application Init 

> Iniztializes SPI driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    charger12_cfg_t cfg;

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

    charger12_cfg_setup( &cfg );
    CHARGER12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger12_init( &charger12, &cfg );

    Delay_ms ( 100 );
    charger12_mode_select( &charger12, CHARGER12_MODE_DISABLE );
    Delay_ms ( 100 );
    log_printf( &logger, "> App init done" );
}
  
```

### Application Task

> Executes additional functions based on user input.

```c

void application_task ( void )
{
    charger12_case_plus( );
    Delay_ms ( 1 );

    charger12_case_minus( );
    Delay_ms ( 1 );

    charger12_case_one( );
    Delay_ms ( 1 );     

    charger12_case_two( );
    Delay_ms ( 1 );   

    charger12_case_three( );
    Delay_ms ( 1 );

    charger12_case_four( );
    Delay_ms ( 1 );
}  

```

## Note

> Additional Functions :

  - charger12_case_Plus()  - Increments Wiper position.
  - charger12_case_Minus() - Decrements Wiper position.
  - charger12_case_One()   - Selects 1st mode of operation.
  - charger12_case_Two()   - Selects 2nd mode of operation.
  - charger12_case_Three() - Selects 3rd mode of operation.
  - charger12_case_Four()  - Selects 4th mode of operation.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger12

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
