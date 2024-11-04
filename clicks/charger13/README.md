\mainpage Main Page
 
 

---
# Charger 13 Click

Charger 13 Click is a single lithium-ion (Li+) cell battery charger. This Click can be used for Low-Cost Li-Ion battery chargers, or Power Tools, toys, backup energy storage solutions, etc.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger13_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/charger-13-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Charger13 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https:///shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https:///shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Charger13 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void charger13_cfg_setup ( charger13_cfg_t *cfg ); 
 
- Initialization function.
> CHARGER13_RETVAL charger13_init ( charger13_t *ctx, charger13_cfg_t *cfg );

- Click Default Configuration function.
> void charger13_default_cfg ( charger13_t *ctx );


#### Example key functions :

- This function enable battery charging by cleared to LOW state of the EN ( PWM ) pin of the Charger 13 Click board.
> void charger13_enable ( charger13_t *ctx );
 
- This function disable battery charging by sets to HIGH state of the EN ( PWM ) pin of the Charger 13 Click board.
> charger13_disable ( charger13_t *ctx );

- This function check if the battery is charging of the Charger 13 Click board.
> uint8_t charger13_check ( charger13_t *ctx );

## Examples Description

> This demo application charges the battery.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    charger13_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    charger13_cfg_setup( &cfg );
    CHARGER13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger13_init( &charger13, &cfg );

    Delay_100ms( );

    charger_flag = 2;
    enable_flag = 0;

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "      'E' : Enable       \r\n" );
    log_printf( &logger, "      'D' : Disable      \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "Charging Status : Disable\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_100ms( );
}
  
```

### Application Task

> This is an example which demonstrates the use of Charger 13 Click board.
> This example shows the automatic control of the Charger 13 Click,
> waits for valid user input and executes functions based on a set of valid commands
> and check the battery charge status.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for approximately every 1 sec when the data value changes.

```c
void application_task ( void )
{
    if ( enable_flag == 0 )
    {
        enable_flag = 1;
        charger13_enable( &charger13 );
        log_printf( &logger, "Charging Status : Enabled\r\n" );
        log_printf( &logger, "-------------------------\r\n" );
    }
    else if ( enable_flag == 1 )
    {
        enable_flag = 0;
        charger13_disable( &charger13 );
        log_printf( &logger, "Charging Status : Disable\r\n" );
        log_printf( &logger, "-------------------------\r\n" );
    }
    status_flag = charger13_check( &charger13 );

    if ( status_flag != charger_flag )
    {   
        charger_flag = charger13_check( &charger13 );

        if ( charger_flag == 0 )
        {
            log_printf( &logger, "   Battery is charging   \r\n" );
            log_printf( &logger, "-------------------------\r\n" );
        }
        else
        {
            log_printf( &logger, " Battery does not charge \r\n" );
            log_printf( &logger, "-------------------------\r\n" );
        }
    }    
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger13

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
