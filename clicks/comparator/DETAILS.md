

---
# Comparator click

Comparator Click represents board equipped with two independent precise voltage comparators.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/comparator_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/comparator-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Comparator Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Comparator Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void comparator_cfg_setup ( comparator_cfg_t *cfg ); 
 
- Initialization function.
> COMPARATOR_RETVAL comparator_init ( comparator_t *ctx, comparator_cfg_t *cfg );

- Click Default Configuration function.
> void comparator_default_cfg ( comparator_t *ctx );

#### Example key functions :

- This function check and return state of the o1 ( AN ) pin of Comparator Click Board.
> uint8_t comparator_check_output_one ( comparator_t *ctx );
 
- This function check and return state of the o2 ( INT ) pin of Comparator Click Board.
> uint8_t comparator_check_output_two ( comparator_t *ctx );

## Examples Description

> 
> This is an example which demonstrates the usage of Comparator Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Application Init performs Logger and Click initialization.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    comparator_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 500 );

    //  Click initialization.

    comparator_cfg_setup( &cfg );
    COMPARATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    comparator_init( &comparator, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " --- Comparator Click --- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> Comparator click checks state of the O1 and O2 pins. Results are being sent to the UART Terminal where you can track their changes. 
> All data logs write on USB UART and changes for every 1 sec.
> 

```c

void application_task ( void )
{
    out_state_one = comparator_check_output_one( &comparator );
    out_state_two = comparator_check_output_two( &comparator );
    
    log_printf( &logger, "   Output One: \r\n" );
    
    if ( out_state_one )
    {
        log_printf( &logger, "   High \r\n" );
    }
    else
    {
        log_printf( &logger, "   Low \r\n" );
    }
    
    Delay_ms ( 500 );
    
    log_printf( &logger, "   Output Two: \r\n" );
    
    if ( out_state_two )
    {
        log_printf( &logger, "   High \r\n" );
    }
    else
    {
        log_printf( &logger, "   Low \r\n" );
    }
    
    Delay_ms ( 500 );
    
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Comparator

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
