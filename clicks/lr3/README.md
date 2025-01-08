
---
# LR 3 Click

> [LR 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4616) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4616&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from LR 3 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LR3

### Example Key Functions

- `lr3_cfg_setup` Config Object Initialization function. 
```c
void lr3_cfg_setup ( lr3_cfg_t *cfg );
``` 
 
- `lr3_init` Initialization function. 
```c
err_t lr3_init ( lr3_t *ctx, lr3_cfg_t *cfg );
```

- `lr3_factory_reset` Function performs the recovery of EEPROM default values. 
```c
err_t lr3_factory_reset ( lr3_t *ctx );
```
 
- `lr3_write_eeprom` Function writes data to EEPROM. 
```c
err_t lr3_write_eeprom ( lr3_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_in );
```

- `lr3_tx_message` Function performs the transmission of radio frames. 
```c
err_t lr3_tx_message ( lr3_t *ctx, lr3_tx_msg_t *tx_msg );
```

### Application Init

> Initializes the driver, enables the Click board and configures it for the selected mode.

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

    Delay_ms ( 100 );
    lr3_set_ind_handler( &lr3, indication_handler );
    lr3_hard_reset( &lr3 );
    lr3_factory_reset( &lr3 );
    Delay_ms ( 1000 );
    
#ifdef MASTER
    // Set device as MASTER
    tmp_msg.payload[ 0 ] = 0;

    if( lr3_write_eeprom( &lr3, 0x00, 1, &tmp_msg.payload[ 0 ] ) )
    {
        log_error( &logger, "Setting device as MASTER!\r\n" );
        for( ; ; );
    }
    
    log_printf( &logger, "Device configured as MASTER!\r\n" );
    Delay_ms ( 1000 );
    
    // Delete all network table
    if( lr3_delete_all_network_table( &lr3 ) )
    {
        log_error( &logger, "Deleting all paired devices!\r\n" );
        for( ; ; );
    }
    log_printf( &logger, "All paired devices deleted!\r\n" );
    Delay_ms ( 1000 );
    
    // Enable pairing
    if( lr3_enable_pairing( &lr3, 1 ) )
    {
        log_error( &logger, "Pairing not enabled!\r\n" );
        for( ; ; );
    }
    log_printf( &logger, "Pairing enabled!\r\n" );
    Delay_ms ( 1000 );
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
    Delay_ms ( 1000 );
    
    // Send pairing request and displays MASTER ID
    uint8_t master_id[ 4 ] = { 0 };
    do
    {
        lr3_get_pairing_request( &lr3 );
        Delay_ms ( 1000 );
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
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
#ifdef MASTER
    lr3_read_message_process( &lr3 );
#endif 
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
