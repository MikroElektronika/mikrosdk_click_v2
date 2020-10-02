\mainpage Main Page
 
---
# BEE click

BEE click features MRF24J40MA 2.4 GHz IEEE 802.15.4 radio transceiver module from Microchip.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/bee_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/bee-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Bee Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Bee Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void bee_cfg_setup ( bee_cfg_t *cfg ); 
 
- Initialization function.
> BEE_RETVAL bee_init ( bee_t *ctx, bee_cfg_t *cfg );

#### Example key functions :

- Generic transfer function.
> void bee_generic_transfer ( bee_t *ctx, spi_master_transfer_data_t *block );
 
- Write the byte of data to the short register address function
> void bee_write_byte_short ( bee_t *ctx, uint8_t reg_address, uint8_t write_data );

- Read the byte of data from the short register address function
> uint8_t bee_read_byte_short ( bee_t *ctx, uint8_t reg_address );

## Examples Description
 
> The click is designed to run on 3.3V power supply only. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - SPI,
    sets initialization BEE Click as a receiver, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    bee_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    bee_cfg_setup( &cfg );
    BEE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bee_init( &bee, &cfg );

    rx_data_old = 255;
    rx_data[ 0 ] = 0;

    for ( cnt = 0; cnt < 2; cnt++ )
    {
        short_address1[ cnt ] = 1;
        short_address2[ cnt ] = 2;
        pan_id1[ cnt ] = 3;
        pan_id2[ cnt ] = 3;
    }

    for ( cnt = 0; cnt < 8; cnt++ )
    {
        short_address1[ cnt ] = 1;
        short_address2[ cnt ] = 2;
    }

    log_printf( &logger, "    Reset and WakeUp     \r\n"  );
    bee_hw_reset( &bee );
    bee_soft_reset( &bee );
    bee_rf_reset( &bee );
    bee_enable_immediate_wake_up( &bee );
    log_printf( &logger, "    Set address and PAN ID  \r\n" );
    bee_set_long_address( &bee, &long_address2 );
    bee_set_short_address( &bee, &short_address2 );
    bee_set_pan_id( &bee, &pan_id2 );
    log_printf( &logger, "    Init ZigBee module:    \r\n" );
    log_printf( &logger, " - Set nonbeacon-enabled \r\n" );
    bee_nonbeacon_init( &bee );
    log_printf( &logger, " - Set as PAN coordinator\r\n" );
    bee_nonbeacon_pan_coordinator_device( &bee );
    log_printf( &logger, " - Set max TX power\r\n" );
    bee_set_tx_power( &bee, 31 );
    log_printf( &logger, " - All frames 3, data frame\r\n" );
    bee_set_frame_format_filter( &bee, 1 );
    log_printf( &logger, " - Set normal mode\r\n"  );
    bee_set_reception_mode( &bee, 1 );
     log_printf( &logger, " - Device Wake Up\r\n"  );
    bee_hw_wake_up( &bee );
    log_printf( &logger, " - Received data :      \r\n" );
    Delay_1sec( );
}
  
```

### Application Task

> This is an example which demonstrates the use of BEE Click board.
    In this example, we use BEE Click to receive data. 

```c

void application_task ( void )
{
  if( bee_interrupt_activity( &bee ) == 0 )
    {
        tmp = bee_read_byte_short( &bee, BEE_INTSTAT );
        bee_read_rx_fifo( &bee, &rx_data );
        Delay_100ms( );

        if ( rx_data[ 0 ] != rx_data_old )
        {
           log_printf( &logger, "%d \r\n", rx_data[ 0 ] );
           rx_data_old = rx_data[ 0 ];
        }
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Bee

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
