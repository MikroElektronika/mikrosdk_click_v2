
---
# UWB Click

> [UWB Click](https://www.mikroe.com/?pid_product=MIKROE-4199) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4199&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> UWB Click sends and receive data, depending on the selected device mode.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Uwb

### Example Key Functions

- `uwb_cfg_setup` Config Object Initialization function.
```c
void uwb_cfg_setup ( uwb_cfg_t *cfg ); 
```

- `uwb_init` Initialization function.
```c
err_t uwb_init ( uwb_t *ctx, uwb_cfg_t *cfg );
```

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

### Application Init

> Initializes the driver and configures the Click board for the selected mode.

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
    Delay_ms ( 100 );
    
    uwb_enable ( &uwb );
    Delay_ms ( 100 );
    
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
    
    Delay_ms ( 100 );

    // Setting default configuartion and tuning device for that configuration
    uwb_use_smart_power( &uwb, UWB_LOW );
    uwb_frame_check( UWB_LOW );
    uwb_frame_filter( &uwb, UWB_LOW );
    uwb_set_transmit_type( &uwb, &UWB_TMODE_LONGDATA_RANGE_LOWPOWER[ 0 ] );
    uwb_set_channel( &uwb, UWB_CHANNEL_5 );
    uwb_tune_config( &uwb );

    Delay_ms ( 100 );
    
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
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            uwb_set_mode( &uwb, UWB_MODE_IDLE );
            uwb_clear_status( &uwb );
            uwb_set_transmit( &uwb, &data_tx_1[ 0 ], 6 );
            uwb_set_mode( &uwb, UWB_MODE_TX );
            uwb_start_transceiver( &uwb );
            log_printf( &logger, " - Transmit 1 done - \r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
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
