
# ATA6570 Click

ATA6570 Click is a CAN Partial Networking interface board. The Click carries the ATA6570, a high-speed CAN transceiver that interfaces a Controller Area Network (CAN) protocol controller and the physical two-wire CAN bus. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ata6570_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ata6570-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Ata6570 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ata6570 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ata6570_cfg_setup ( ata6570_cfg_t *cfg ); 
 
- Initialization function.
> ATA6570_RETVAL ata6570_init ( ata6570_t *ctx, ata6570_cfg_t *cfg );

#### Example key functions :

- Write Register
> void ata6570_write_reg ( ata6570_t *ctx, const uint8_t address, uint8_t input );
 
- Read Register
> uint8_t ata6570_read_reg ( ata6570_t *ctx, const uint8_t address );

## Examples Description
 
> This application is interfaces a Controller Area Network (CAN) protocol controller and the physical two-wire CAN bus.

**The demo application is composed of two sections :**

### Application Init 

> In addition to this module is palced inside normal working mode cappable of tranmission and reception of data.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ata6570_cfg_t cfg;

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

    ata6570_cfg_setup( &cfg );
    ATA6570_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ata6570_init( &ata6570, &cfg );
    ata6570_write_reg( &ata6570, ATA6570_DMCR, ATA6570_OPMODE_NORMAL );
    Delay_ms ( 500 );
}
  
```

### Application Task

> Tranismiter/Receiver task depend on uncommented code
  Receiver logging each received byte to the UART for data logging, while transmiter send message each
  2 seconds.

```c

void application_task ( void )
{
     //  Task implementation.
    
#ifdef DEMO_APP_RECEIVER
       // RECEIVER - UART polling
      rsp_size = ata6570_generic_read( &ata6570, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

      if ( rsp_size > 0 )
        {  
            log_printf( &logger, "%s", uart_rx_buffer );
            memset( uart_rx_buffer, 0, rsp_size );
        }  
#endif
       
#ifdef DEMO_APP_TRANSMITER
       // TRANSMITER - TX each 2 sec
       for( uint8_t i = 0; i < 8; i++ )
       {
           ata6570_generic_write( &ata6570, &demo_message[ i ], 1 );
       }
       Delay_ms ( 1000 );
       Delay_ms ( 1000 );
#endif
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ata6570

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
