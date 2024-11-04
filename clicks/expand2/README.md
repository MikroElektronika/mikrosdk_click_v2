\mainpage Main Page
 
---
# Expand 2 Click

EXPAND 2 Click is an accessory board in mikroBUS form factor. It includes a 16-bit I/O expander MCP23017 with I²C clock speeds up to 10 MHz for higher throughput applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand2_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/expand-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Expand2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void expand2_cfg_setup ( expand2_cfg_t *cfg ); 
 
- Initialization function.
> EXPAND2_RETVAL expand2_init ( expand2_t *ctx, expand2_cfg_t *cfg );

- Click Default Configuration function.
> void expand2_default_cfg ( expand2_t *ctx );


#### Example key functions :

- Function set bit to 8-bit register address from PORTA of MCP23017 chip.
> void expand2_set_bit_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask );
 
- Function toggle bit from 8-bit register address from PORTA of MCP23017 chip.
> void expand2_toggle_bit_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask );

- Function clear bit from 8-bit register address from PORTA of MCP23017 chip.
> void expand2_clear_bit_port_a ( expand2_t *ctx, uint8_t moduleAddress, uint8_t bitMask );

## Examples Description

> This application demonstrates the use of the Expand 2 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and logger, and then sets the Click default configuration: PORTA as output, PORTB as input with pull-ups on all pins.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand2_cfg_t cfg;

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

    expand2_cfg_setup( &cfg );
    EXPAND2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand2_init( &expand2, &cfg );

    expand2_default_cfg ( &expand2 );

    log_printf( &logger, "----------------\r\n" );
    log_printf( &logger, " Expand 2 Click \r\n" );
    log_printf( &logger, "----------------\r\n" );

    Delay_ms ( 100 );
}
  
```

### Application Task

> Sets other pin of PORTA every 3 seconds, then reads and displays the status of both ports on USB UART.

```c

void application_task ( void )
{
    //  Task implementation.

    uint8_t port_status;
    uint8_t pin_position;

    for ( pin_position = 0; pin_position < 8; pin_position++ )
    {
        expand2_set_port_a( &expand2, EXPAND2_I2C_MODULE_ADDRESS_0, pin_position );
        
        port_status = expand2_read_port_a( &expand2, EXPAND2_I2C_MODULE_ADDRESS_0 );

        log_printf( &logger, " Status PA (output): %d\r\n", (uint16_t) port_status );
        
        port_status = expand2_read_port_b( &expand2, EXPAND2_I2C_MODULE_ADDRESS_0 );

        log_printf( &logger, " Status PB (input) : %d  \r\n", (uint16_t) port_status );
        log_printf( &logger, "----------------\r\n" );
        
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand2

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
