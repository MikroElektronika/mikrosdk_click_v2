
---
# LLC SPI click

The LLC SPI click is a very useful Click board™ which can be utilized as the level converter for logic signals.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/llcspi_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/llc-spi-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the LlcSpi Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LlcSpi Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void llcspi_cfg_setup ( llcspi_cfg_t *cfg ); 
 
- Initialization function.
> LLCSPI_RETVAL llcspi_init ( llcspi_t *ctx, llcspi_cfg_t *cfg );

#### Example key functions :

- LLC SPI write
> void spillc_generic_write ( llcspi_t *ctx, uint8_t *p_buf, uint16_t n_bytes );
 
- LLC SPI read
> void spillc_generic_read ( llcspi_t *ctx, uint8_t *p_buf, uint16_t n_bytes );

- LLC SPI transfer
> void spillc_generic_transfer ( llcspi_t *ctx, uint8_t *p_in, uint8_t *p_out, uint16_t n_bytes );

## Examples Description

> This application is converter for logic signals.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device init

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    llcspi_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    llcspi_cfg_setup( &cfg );
    LLCSPI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    llcspi_init( &llcspi, &cfg );
}
  
```

### Application Task

> Counter passes through the loop and logs the value of the counter on the bargraph display

```c

void application_task ( void )
{
    spi_master_transfer_data_t block;
    uint16_t convert;
    uint8_t tmp[ 2 ];
    uint8_t cnt;

    // Bar_graph display
    for ( cnt = 0; cnt <= 10; cnt++ )
    {
        convert  = ( uint16_t ) ( ( 1 << cnt ) - 1 );
        tmp[ 1 ] = ( convert & 0x00FF );
        tmp[ 0 ] = ( convert & 0xFF00 ) >> 8;

        block.tx_buffer = &tmp[ 0 ];
        block.tx_length = 2;
        block.rx_buffer = NULL;
        block.rx_length = 0;
    
        llcspi_generic_transfer( &llcspi, &block );
        
        Delay_ms( 1000 );
    }
}  

```

## Note
 
> Connection between BarGraph and SPI-LLC is made through SPI interface.
> You can connect a BarGraph click and SPI-LLC click with the wires to make connection between click boards.
> We use the BarGraph click to demonstrate the functions of the SPI-LLC click.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LlcSpi

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
