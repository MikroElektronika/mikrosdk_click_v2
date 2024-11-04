\mainpage Main Page
 
 

---
# MCP73213 Click

MCP73213 Click carries the MCP73213 dual-cell Li-Ion/Li-Polymer battery charge management controller with input overvoltage protection from Microchip.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mcp73213_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/mcp73213-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Mcp73213 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mcp73213 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mcp73213_cfg_setup ( mcp73213_cfg_t *cfg ); 
 
- Initialization function.
> MCP73213_RETVAL mcp73213_init ( mcp73213_t *ctx, mcp73213_cfg_t *cfg );

#### Example key functions :

- Set values for output current function
> void mcp73213_set_current_output ( mcp73213_t *ctx, uint8_t out_data );
 
- Get the status register data function
> uint8_t mcp73213_get_status ( mcp73213_t *ctx );

- Convert ADC value to volatage
> float mcp73213_convert_output ( uint8_t value_adc, float v_ref );

## Examples Description

> This application is polymer battery charge management controller.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - SPI, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp73213_cfg_t cfg;

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

    mcp73213_cfg_setup( &cfg );
    MCP73213_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp73213_init( &mcp73213, &cfg );

    log_printf( &logger, "   SPI Driver Init     \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "  Set Current Output   \r\n" );
}
  
```

### Application Task

> This is a example which demonstrates the use of MCP73213 Click board.
> This example sets the resistance to a given value, thus affecting the output current.
> Controls output current using internal digital potentiometer.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on usb uart changes for every 3 sec.

```c

void application_task ( void )
{
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "   10 kOhm - 130 mA    \r\n" );
    mcp73213_set_current_output( &mcp73213, MCP73213_OUTPUT_130_mA );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "    5 kOhm - 250 mA    \r\n" );
    mcp73213_set_current_output( &mcp73213, MCP73213_OUTPUT_250_mA );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mcp73213

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
