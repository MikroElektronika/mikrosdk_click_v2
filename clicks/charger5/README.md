\mainpage Main Page

 

---
# Charger 5 Click

Charger 5 Click is designed to charge Lithium-Ion and Lithium-Polymer batteries.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/charger-5-click)

---


#### Click library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Charger5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https:///shop.mikroe.com/compilers).
The demo can run on all the main MikroElektronika [development boards](https:///shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account.

## Library Description

> This library contains API for Charger 5 Click driver.

#### Standard key functions :

- Configuration Object Setup function.
> void charger5_cfg_setup( charger5_cfg_t *cfg );
 
- Click Initialization function.
> charger5_err_t charger5_init( charger5_t *ctx, charger5_cfg_t *cfg );

- Click Default Configuration function.
> void charger5_default_cfg( charger5_t *ctx );

#### Example key functions :

- Generic Write function.
> charger5_err_t charger5_generic_write( charger5_t *ctx, uint8_t reg_addr, uint16_t transfer_data );
 
- Generic Read function.
> uint16_t charger5_generic_read( charger5_t *ctx, uint8_t reg_addr );

- Increment Wiper function.
> charger5_err_t charger5_increment_wiper( charger5_t *ctx, uint8_t reg_addr, uint8_t n_steps );

## Examples Description

>
> This example demonstrates the use of the Charger 5 Click board.
>

**The demo application is composed of two sections :**

### Application Init

>
> Initializes peripherals and pins used for the Charger 5 Click and prepares the Charger 5 Click for properly working.
>

```c

void application_init( void )
{
    charger5_cfg_t charger5_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    charger5_cfg_setup( &charger5_cfg );
    CHARGER5_MAP_MIKROBUS( charger5_cfg, MIKROBUS_1 );
    charger5_init( &charger5, &charger5_cfg );
    charger5_default_cfg( &charger5 );

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( console_cfg );
    log_init( &console, &console_cfg );
    log_write( &console, "***  Charger 5 initialization done  ***",
               LOG_FORMAT_LINE );
    log_write( &console, "***************************************",
               LOG_FORMAT_LINE );
}

```

### Application Task

>
> Demonstrates the use of driver functions. It will set charging current to 500 mA,
> then will increment that value by 10 steps, and after that will decrement it by 5 steps.
>

```c

void application_task( void )
{
    charger5_generic_write( &charger5, CHARGER5_REG_WIPER0_VOL,
                            CHARGER5_CURRENT_500MA );
    log_write( &console, "Output current is set to 500 mA.",
               LOG_FORMAT_LINE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    charger5_increment_wiper( &charger5, CHARGER5_REG_WIPER0_VOL,
                              CHARGER5_STEPS_10 );
    log_write( &console, "Output current value is incremented by 10 steps.",
               LOG_FORMAT_LINE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    charger5_decrement_wiper( &charger5, CHARGER5_REG_WIPER0_VOL,
                              CHARGER5_STEPS_5 );
    log_write( &console, "Output current value is decremented by 5 steps.",
               LOG_FORMAT_LINE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

## Note

>
> Increment/decrement command can only be issued to volatile memory locations.
>

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger5

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https:///shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https:///shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https:///shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https:///shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
