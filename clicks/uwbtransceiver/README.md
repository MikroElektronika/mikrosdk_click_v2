\mainpage Main Page
 
---
# UWB Transceiver click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the UwbTransceiver Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for UwbTransceiver Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void uwbtransceiver_cfg_setup ( uwbtransceiver_cfg_t *cfg ); 
 
- Initialization function.
> UWBTRANSCEIVER_RETVAL uwbtransceiver_init ( uwbtransceiver_t *ctx, uwbtransceiver_cfg_t *cfg );


#### Example key functions :

- This function set device working mode.
> void uwb_set_mode ( uwbtransceiver_t *ctx, uint8_t mode );
 
- This function get transmit status.
> uint8_t uwb_get_transmit_status ( uwbtransceiver_t *ctx );

- This function start communication of device.
> void uwb_start_transceiver ( uwbtransceiver_t *ctx );

## Examples Description

> UWB Transceiver Click send and recieve data, depending on the selected device mode.
> Click is communicating via standard SPI protocol.

**The demo application is composed of two sections :**

### Application Init 

> Mapping GPIO and SPI module, setting device working mode
> setting device ID and default configuration for selected mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uwbtransceiver_cfg_t cfg;

    uint16_t tag_data;
    uint8_t id_raw[ 4 ];

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    uwbtransceiver_cfg_setup( &cfg );
    UWBTRANSCEIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uwbtransceiver_init( &uwbtransceiver, &cfg );

    Delay_ms( 100 );
    uwb_dev_reset( &uwbtransceiver );

    uwbtransceiver.offset = UWB_SUB_NO;                               
    uwb_generic_read( &uwbtransceiver, UWB_REG_DEV_ID, &id_raw[ 0 ], 4 );
                                 
    tag_data = ( id_raw[ 3 ] << 8 ) | id_raw[ 2 ];
    
    if ( UWB_TAG != tag_data )
    {
        log_printf( &logger, " ***** ERROR ***** \r\n" );
        for ( ; ; );
    }
    
    uwb_set_mode( &uwbtransceiver, UWB_MODE_IDLE );
    
    // Chose module working mode RX(receiver)/TX(transmiter)
    dev_mode = UWB_MODE_TX;
    //-----------------------------------------------------
    
    // Setting device mode and interrupt for that mode as well as clearing dev_status reg.
    uwb_set_mode( &uwbtransceiver, dev_mode );
    uwb_int_mask_set( &uwbtransceiver );
    uwb_clear_status( &uwbtransceiver );

    // Setting device address and network ID
    log_printf( &logger, " ******************** \r\n" );
    if ( UWB_MODE_RX == dev_mode )
    {
        uwb_set_dev_adr_n_network_id( &uwbtransceiver, 6, 10 );
        log_printf( &logger, " ***** RECEIVER ***** \r\n" );
    }
    else if ( UWB_MODE_TX == dev_mode )
    {
        uwb_set_dev_adr_n_network_id( &uwbtransceiver, 5, 10 );
        log_printf( &logger, " **** TRANSMITER **** \r\n" );
    }
    log_printf( &logger, " ******************** \r\n" );
    
    Delay_ms( 100 );

    // Setting default configuartion and tuning device for that configuration
    uwb_use_smart_power( &uwbtransceiver, UWB_LOW );
    uwb_frame_check( UWB_LOW );
    uwb_frame_filter( &uwbtransceiver, UWB_LOW );
    uwb_set_transmit_type( &uwbtransceiver, &UWB_TMODE_LONGDATA_RANGE_LOWPOWER[ 0 ] );
    uwb_set_channel( &uwbtransceiver, UWB_CHANNEL_5 );
    uwb_tune_config( &uwbtransceiver );

    Delay_ms( 100 );
    
    if ( UWB_MODE_RX == dev_mode )
    {
        // Setup for first receive
        uwb_set_mode( &uwbtransceiver, UWB_MODE_IDLE );
        uwb_set_bit ( &uwbtransceiver, UWB_REG_SYS_CFG, 29, UWB_HIGH );
        uwb_set_bit ( &uwbtransceiver, UWB_REG_SYS_CFG, 30, UWB_HIGH );
        uwb_set_bit ( &uwbtransceiver, UWB_REG_SYS_CFG, 31, UWB_HIGH );
        uwb_set_mode( &uwbtransceiver, UWB_MODE_RX );
        uwb_clear_status( &uwbtransceiver );
        uwb_start_transceiver( &uwbtransceiver );
    }
    else if ( UWB_MODE_TX == dev_mode )
    {
        // Setup for first transmit
        uwb_set_mode( &uwbtransceiver, UWB_MODE_IDLE );
        uwb_clear_status( &uwbtransceiver );
        uwb_set_transmit( &uwbtransceiver, &data_tx[ 0 ], 6 );
        uwb_set_mode( &uwbtransceiver, UWB_MODE_TX );
        uwb_start_transceiver( &uwbtransceiver );
    }

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
    Delay_ms( 500 );
}

  
```

### Application Task

> Checks if interrupt occured for previous set mode.
>      TX mode: Transmit data and then set delay for 2 seconds.
>      RX mode: Receive data and logs it.

```c

void application_task ( void )
{
    dev_status = uwb_get_qint_pin_status( &uwbtransceiver );

    if ( UWB_MODE_RX == dev_mode )
    {
        if ( dev_status )
        {
            // Reading transtimed data logs it and reseting to receive mode
            uwb_set_mode( &uwbtransceiver, UWB_MODE_IDLE );
            uwb_clear_status( &uwbtransceiver );
            temp_len = uwb_get_transmit_len( &uwbtransceiver );
            uwb_get_transmit( &uwbtransceiver, &transmit_data[ 0 ], temp_len );
            log_printf( &logger, "Received data: %s\r\n", transmit_data );
            log_printf( &logger, " - Receive done - \r\n" );
            uwb_set_mode( &uwbtransceiver, UWB_MODE_RX );
            uwb_start_transceiver( &uwbtransceiver );
        }
    }
    else if ( UWB_MODE_TX == dev_mode )
    {
        if ( dev_status )
        {
            // Transmits data reseting to transmit mode and setts 2sec delay
            log_printf( &logger, " - Transmit done - \r\n" );
            uwb_set_mode( &uwbtransceiver, UWB_MODE_IDLE );
            uwb_clear_status( &uwbtransceiver );
            uwb_set_transmit( &uwbtransceiver, &data_tx[ 0 ], 6 );
            uwb_set_mode( &uwbtransceiver, UWB_MODE_TX );
            uwb_start_transceiver( &uwbtransceiver );
            Delay_ms( 2000 );
        }
    }
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.UwbTransceiver

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
