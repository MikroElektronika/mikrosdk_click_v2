\mainpage Main Page
 
---
# LR 3 click

LR 3 Click is a compact add-on board that contains a long-range transceiver. This board features the 32001345, RF technology-based SRD transceiver, which operates at a frequency of 868MHz from Mipot.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lr3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lr-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the LR3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LR3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lr3_cfg_setup ( lr3_cfg_t *cfg ); 
 
- Initialization function.
> LR3_RETVAL lr3_init ( lr3_t *ctx, lr3_cfg_t *cfg );


#### Example key functions :

- Function performs the recovery of EEPROM default values.
> LR3_RETVAL lr3_factory_reset ( lr3_t *ctx );
 
- Function writes data to EEPROM.
> LR3_RETVAL lr3_write_eeprom ( lr3_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_in );

- Function performs the transmission of radio frames.
> LR3_RETVAL lr3_tx_message ( lr3_t *ctx, lr3_tx_msg_t *tx_msg );

## Examples Description

> This example reads and processes data from LR 3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, enables the click board and configures it for the selected mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lr3_cfg_t cfg;

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

    lr3_cfg_setup( &cfg );
    LR3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lr3_init( &lr3, &cfg );

    Delay_ms( 100 );
    lr3_set_ind_handler( &lr3, indication_handler );
    lr3_hard_reset( &lr3 );
    lr3_factory_reset( &lr3 );
    Delay_ms( 1000 );
    
#ifdef MASTER
    // Set device as MASTER
    tmp_msg.payload[ 0 ] = 0;

    if( lr3_write_eeprom( &lr3, 0x00, 1, &tmp_msg.payload[ 0 ] ) )
    {
        log_error( &logger, "Setting device as MASTER!\r\n" );
        for( ; ; );
    }
    
    log_printf( &logger, "Device configured as MASTER!\r\n" );
    Delay_ms( 1000 );
    
    // Delete all network table
    if( lr3_delete_all_network_table( &lr3 ) )
    {
        log_error( &logger, "Deleting all paired devices!\r\n" );
        for( ; ; );
    }
    log_printf( &logger, "All paired devices deleted!\r\n" );
    Delay_ms( 1000 );
    
    // Enable pairing
    if( lr3_enable_pairing( &lr3, 1 ) )
    {
        log_error( &logger, "Pairing not enabled!\r\n" );
        for( ; ; );
    }
    log_printf( &logger, "Pairing enabled!\r\n" );
    Delay_ms( 1000 );
#endif

#ifdef END_NODE
    // Set device as END_NODE
    tmp_msg.payload[ 0 ] = 1;
    
    if( lr3_write_eeprom( &lr3, 0x00, 1, &tmp_msg.payload[ 0 ] ) )
    {
        log_error( &logger, "Setting device as END_NODE!\r\n" );
        for( ; ; );
    }
    
    log_printf( &logger, "Device configured as END_NODE!\r\n" );
    Delay_ms( 1000 );
    
    // Send pairing request and displays MASTER ID
    uint8_t master_id[ 4 ] = { 0 };
    do
    {
        lr3_get_pairing_request( &lr3 );
        Delay_ms( 1000 );
    }
    while ( lr3_get_activation_status( &lr3, master_id ) != 1 );
    log_printf( &logger, "Paired to a network!\r\n" );
    log_printf( &logger, "Master ID: 0x%.2X%.2X%.2X%.2X\r\n", ( uint16_t ) master_id[ 3 ],
                                                              ( uint16_t ) master_id[ 2 ],
                                                              ( uint16_t ) master_id[ 1 ],
                                                              ( uint16_t ) master_id[ 0 ] );
    
#endif
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends a desired message every 3 seconds. All data is being displayed on the USB UART.

```c

void application_task ( void )
{
#ifdef END_NODE
    strcpy( tmp_msg.payload, TEXT_TO_SEND );
   
    lr3_tx_msg.data_in = &tmp_msg.payload[ 0 ];
    lr3_tx_msg.n_bytes = strlen( TEXT_TO_SEND );
    lr3_tx_msg.destination_id = LR3_BROADCAST_MESSAGE;
    lr3_tx_msg.option = LR3_UNCONFIRMED_DATA_TX;
    if ( lr3_tx_message( &lr3, &lr3_tx_msg ) == 0 )
    {
        log_printf( &logger, "Message: \"%s\" sent to MASTER...\r\n", ( uint8_t * ) TEXT_TO_SEND );
        log_printf( &logger, "------------------------\r\n" );
    }
    
    Delay_ms( 3000 );
#endif
#ifdef MASTER
    lr3_read_message_process( &lr3 );
#endif 
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LR3

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
