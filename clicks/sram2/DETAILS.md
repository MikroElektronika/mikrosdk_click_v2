
---
# SRAM 2 Click

SRAM 2 Click is based on ANV32A62A SRAM memory from Anvo-Systems Dresden. It's a 64Kb serial SRAM with a non-volatile SONOS storage element included with each memory cell, organized as 8k words of 8 bits each.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/sram2_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/sram-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Sram2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Sram2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void sram2_cfg_setup ( sram2_cfg_t *cfg ); 
 
- Initialization function.
> SRAM2_RETVAL sram2_init ( sram2_t *ctx, sram2_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void sram2_generic_write ( sram2_t *ctx, uint16_t reg, uint8_t wr_data );
 
- Generic read function.
> void sram2_generic_read ( sram2_t *ctx, uint16_t reg, uint8_t rx_data );

- Set PWM pin for write protection.
> void sram2_write_protect( sram2_t *ctx, uint8_t state );

## Examples Description

> This demo application writes and reads from memory. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    sram2_cfg_t cfg;

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

    sram2_cfg_setup( &cfg );
    SRAM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    sram2_init( &sram2, &cfg );
}
  
```

### Application Task

> Writes and then reads data from memory.

```c

void application_task ( void )
{
    uint8_t cnt;
     
    log_printf( &logger, ">> Write data [ MikroE ] to memory. \r\n" );

    sram2_write_protect( &sram2, SRAM2_WR_ENABLE );
    for ( cnt = 0; cnt < 8; cnt++ )
    {
        sram2_generic_write( &sram2, memory_addr + cnt, message_data[ cnt ] );
    }
    Delay_ms ( 1000 );
    sram2_write_protect( &sram2, SRAM2_WR_DISABLE );

    log_printf( &logger, ">> Read data from memory. Data : " );
    for ( cnt = 0; cnt < 8; cnt++ )
    {
        sram2_generic_read( &sram2, memory_addr + cnt, rx_data );
        log_printf( &logger, " %c ", rx_data );
        Delay_100ms( );
    }
    log_printf( &logger, "  \r\n" );
    log_printf( &logger, "-------------------------------- \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Sram2

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
