
---
# UWB click

> UWB Click is an Ultra-Wideband transceiver Click board™ that can be used in 2-way ranging or TDOA location systems to locate assets to a precision of 10 cm and supports data rates of up to 6.8 Mbps. This Click board™ features the DWM1000 module based on Decawave's DW1000 Ultra-Wideband (UWB) transceiver from Decawave Limited.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uwb_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uwb-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Uwb Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Uwb Click driver.

#### Standard key functions :

- `uwb_cfg_setup` Config Object Initialization function.
```c
void uwb_cfg_setup ( uwb_cfg_t *cfg ); 
```

- `uwb_init` Initialization function.
```c
err_t uwb_init ( uwb_t *ctx, uwb_cfg_t *cfg );
```

#### Example key functions :

- `uwb_set_mode` This function set device working mode.
```c
void uwb_set_mode ( uwb_t *ctx, uint8_t mode );
```

- `uwb_get_transmit_status` This function get transmit status.
```c
uint8_t uwb_get_transmit_status ( uwb_t *ctx );
```

- `uwb_start_transceiver` This function start communication of device.
```c
void uwb_start_transceiver ( uwb_t *ctx );
```

## Examples Description

> UWB Click sends and receive data, depending on the selected device mode.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the click board for the selected mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uwb_cfg_t cfg;

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

    // Click initialization.
    uwb_cfg_setup( &cfg );
    UWB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uwb_init( &uwb, &cfg );
    Delay_ms( 100 );
    
    uwb_enable ( &uwb );
    Delay_ms( 100 );
    
    uint8_t id_raw[ 4 ] = { 0 };
    uwb.offset = UWB_SUB_NO;                               
    uwb_generic_read( &uwb, UWB_REG_DEV_ID, &id_raw[ 0 ], 4 );
                                 
    uint16_t tag_data = ( ( uint16_t ) id_raw[ 3 ] << 8 ) | id_raw[ 2 ];
    
    if ( UWB_TAG != tag_data )
    {
        log_printf( &logger, " ***** ERROR ***** \r\n" );
        for ( ; ; );
    }
    
    uwb_set_mode( &uwb, UWB_MODE_IDLE );
    
    //-----------------------------------------------------
    
    // Setting device mode and interrupt for that mode as well as clearing dev_status reg.
    uwb_set_mode( &uwb, dev_mode );
    uwb_int_mask_set( &uwb );
    uwb_clear_status( &uwb );

    // Setting device address and network ID
    log_printf( &logger, " ******************** \r\n" );
    if ( UWB_MODE_RX == dev_mode )
    {
        uwb_set_dev_adr_n_network_id( &uwb, 6, 10 );
        log_printf( &logger, " ***** RECEIVER ***** \r\n" );
    }
    else if ( UWB_MODE_TX == dev_mode )
    {
        uwb_set_dev_adr_n_network_id( &uwb, 5, 10 );
        log_printf( &logger, " **** TRANSMITER **** \r\n" );
    }
    log_printf( &logger, " ******************** \r\n" );
    
    Delay_ms( 100 );

    // Setting default configuartion and tuning device for that configuration
    uwb_use_smart_power( &uwb, UWB_LOW );
    uwb_frame_check( UWB_LOW );
    uwb_frame_filter( &uwb, UWB_LOW );
    uwb_set_transmit_type( &uwb, &UWB_TMODE_LONGDATA_RANGE_LOWPOWER[ 0 ] );
    uwb_set_channel( &uwb, UWB_CHANNEL_5 );
    uwb_tune_config( &uwb );

    Delay_ms( 100 );
    
    if ( UWB_MODE_RX == dev_mode )
    {
        // Setup for first receive
        uwb_set_mode( &uwb, UWB_MODE_IDLE );
        uwb_set_bit ( &uwb, UWB_REG_SYS_CFG, 29, UWB_HIGH );
        uwb_set_bit ( &uwb, UWB_REG_SYS_CFG, 30, UWB_HIGH );
        uwb_set_bit ( &uwb, UWB_REG_SYS_CFG, 31, UWB_HIGH );
        uwb_set_mode( &uwb, UWB_MODE_RX );
        uwb_clear_status( &uwb );
        uwb_start_transceiver( &uwb );
    }
    else if ( UWB_MODE_TX == dev_mode )
    {
        // Setup for first transmit
        uwb_set_mode( &uwb, UWB_MODE_IDLE );
        uwb_clear_status( &uwb );
        uwb_set_transmit( &uwb, &data_tx_1[ 0 ], 6 );
        uwb_set_mode( &uwb, UWB_MODE_TX );
        uwb_start_transceiver( &uwb );
        log_printf( &logger, " - Transmit 1 done - \r\n" );
    }

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
    Delay_ms( 2000 );
}

  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void )
{
    dev_status = uwb_get_qint_pin_status( &uwb );

    if ( UWB_MODE_RX == dev_mode )
    {
        if ( dev_status )
        {
            // Reading transmitted data, logs it and resetting to receive mode
            uwb_set_mode( &uwb, UWB_MODE_IDLE );
            uwb_clear_status( &uwb );
            temp_len = uwb_get_transmit_len( &uwb );
            uwb_get_transmit( &uwb, &transmit_data[ 0 ], temp_len );
            log_printf( &logger, "Received data: %s\r\n", transmit_data );
            log_printf( &logger, " - Receive done - \r\n" );
            uwb_set_mode( &uwb, UWB_MODE_RX );
            uwb_start_transceiver( &uwb );
        }
    }
    else if ( UWB_MODE_TX == dev_mode )
    {
        if ( dev_status )
        {
            // Transmits data, resetting to transmit mode and sets 2sec delay
            uwb_set_mode( &uwb, UWB_MODE_IDLE );
            uwb_clear_status( &uwb );
            uwb_set_transmit( &uwb, &data_tx_2[ 0 ], 9 );
            uwb_set_mode( &uwb, UWB_MODE_TX );
            uwb_start_transceiver( &uwb );
            log_printf( &logger, " - Transmit 2 done - \r\n" );
            Delay_ms( 2000 );
            uwb_set_mode( &uwb, UWB_MODE_IDLE );
            uwb_clear_status( &uwb );
            uwb_set_transmit( &uwb, &data_tx_1[ 0 ], 6 );
            uwb_set_mode( &uwb, UWB_MODE_TX );
            uwb_start_transceiver( &uwb );
            log_printf( &logger, " - Transmit 1 done - \r\n" );
            Delay_ms( 2000 );
        }
    }
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Uwb

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
