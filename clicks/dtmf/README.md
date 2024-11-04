\mainpage Main Page

---
# DTMF Click

> DTMF Click is a compact add-on board designed for projects that demand reliable telephony interactions. This board features the CMX865A, a DTMF Codec/FSK Combo multi-standard modem from CML Micro. The CMX865A excels in encoding and decoding DTMF signals, alongside supporting FSK data transmission compatible with V.23, V.21, Bell 103, and Bell 202 standards, making it versatile for various telephony applications. It's particularly adept at enabling dual-mode operations for transmitting and receiving data, ensuring high fidelity in signal processing and resistance to voice falsing. Ideal for security systems, automated response services, and IoT devices requiring telephonic interaction, DTMF Click provides a solution for developers looking to incorporate reliable telecommunication capabilities.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dtmf_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dtmf-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the DTMF Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DTMF Click driver.

#### Standard key functions :

- `dtmf_cfg_setup` Config Object Initialization function.
```c
void dtmf_cfg_setup ( dtmf_cfg_t *cfg );
```

- `dtmf_init` Initialization function.
```c
err_t dtmf_init ( dtmf_t *ctx, dtmf_cfg_t *cfg );
```

#### Example key functions :

- `dtmf_handshake_init` This function performs a handshake init which resets the device settings to default.
```c
err_t dtmf_handshake_init ( dtmf_t *ctx );
```

- `dtmf_dial` This function dials the selected number by alternating between DTMF and No-tone.
```c
err_t dtmf_dial ( dtmf_t *ctx, uint8_t *dial_num );
```

- `dtmf_send_message` This function sends an array of bytes via V.23 FSK 1200bps modem in start-stop 8.1 mode. 
```c
err_t dtmf_send_message ( dtmf_t *ctx, uint8_t *data_in, uint8_t len );
```

## Example Description

> This example demonstrates the use of DTMF Click board by showing the communication between the two Click boards connected to PBX system.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger, and displays the selected application mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dtmf_cfg_t dtmf_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    dtmf_cfg_setup( &dtmf_cfg );
    DTMF_MAP_MIKROBUS( dtmf_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dtmf_init( &dtmf, &dtmf_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

#if ( DEMO_APP == APP_DIALING )
    log_printf( &logger, " Application Mode: Dialing\r\n" );
#elif ( DEMO_APP == APP_ANSWERING )
    log_printf( &logger, " Application Mode: Answering\r\n" );
#else
    #error "Selected application mode is not supported!"
#endif
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Dialing application mode:
- Resets the device settings and dials the selected number. If a call is answered
it starts sending desired messages every couple of seconds with constantly checking
if a call is still in progress or it's terminated from the other side.

> Answering application mode:
- Resets the device settings and waits for an incoming call indication, answers the call,
and waits for a desired number of messages. The call is terminated after all messages
are received successfully.

```c
void application_task ( void )
{
    uint8_t state = DTMF_STATE_IDLE;
    uint32_t time_cnt = 0;
    uint8_t msg_cnt = 0;

    dtmf_handshake_init ( &dtmf );

#if ( DEMO_APP == APP_DIALING )
    log_printf( &logger, "\r\n Hook OFF\r\n" );
    dtmf_hook_off ( &dtmf );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Dial: %s\r\n", ( char * ) DIAL_NUMBER );
    dtmf_dial ( &dtmf, DIAL_NUMBER );
    dtmf.rx_mode &= DTMF_RX_LEVEL_MASK; // No change in rx level setting
    dtmf.rx_mode |= ( DTMF_RX_MODE_DTMF_TONES | DTMF_RX_TONE_DETECT_CALL_PROG );
    dtmf_set_receive_mode ( &dtmf, dtmf.rx_mode );
    for ( ; ; )
    {
        Delay_ms ( 1 );
        if ( !dtmf_get_irq_pin ( &dtmf ) )
        {
            time_cnt = 0;
            state = DTMF_STATE_IRQ_SET;
        }
        if ( ( DTMF_STATE_IRQ_SET == state ) && !dtmf_call_progress ( &dtmf ) )
        {
            if ( time_cnt < DTMF_TIMING_BUSY )
            {
                log_printf( &logger, " Busy\r\n" );
                break;
            }
            else if ( time_cnt < DTMF_TIMING_DISCONNECTED )
            {
                log_printf( &logger, " Disconnected\r\n" );
                break;
            }
            else if ( time_cnt < DTMF_TIMING_RINGING )
            {
                log_printf( &logger, " Ringing\r\n" );
                state = DTMF_STATE_RINGING;
            }
        }
        if ( ( DTMF_STATE_RINGING == state ) && ( time_cnt > DTMF_TIMING_CALL_PROGRESS ) )
        {
            log_printf( &logger, " Call in progress\r\n" );
            state = DTMF_STATE_CALL_IN_PROGRESS;
            time_cnt = 0;
        }
        if ( ( DTMF_STATE_CALL_IN_PROGRESS == state ) && !( time_cnt % DTMF_TIMING_SEND_MESSAGE ) )
        {
            log_printf( &logger, " Send message %u\r\n", ( uint16_t ) msg_cnt++ );
            dtmf_send_message ( &dtmf, TEXT_TO_SEND, strlen ( TEXT_TO_SEND ) );
        }
        if ( time_cnt++ > DTMF_TIMEOUT_CALL_PROGRESS )
        {
            log_printf( &logger, " Timeout\r\n" );
            break;
        }
    }
    log_printf( &logger, " Hook ON\r\n" );
    dtmf_hook_on ( &dtmf );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_APP == APP_ANSWERING )
    uint8_t rx_data = 0;
    uint8_t msg_end_buff[ 2 ] = { 0 };

    log_printf( &logger, "\r\n Waiting for a call...\r\n" );

    while ( dtmf_get_rdn_pin ( &dtmf ) );

    Delay_ms ( 1000 );
    log_printf( &logger, " Hook OFF\r\n" );
    dtmf_hook_off ( &dtmf );
    Delay_ms ( 1000 );
    log_printf( &logger, " Waiting for %u messages...\r\n", ( uint16_t ) NUM_MESSAGES );
    dtmf.rx_mode &= DTMF_RX_LEVEL_MASK; // No change in rx level setting
    dtmf.rx_mode |= ( DTMF_RX_MODE_V23_FSK_1200 | DTMF_RX_USART_START_STOP | DTMF_RX_DATA_PARITY_8_NO_PAR );
    dtmf_set_receive_mode ( &dtmf, dtmf.rx_mode );

    for ( ; ; )
    {
        Delay_ms ( 1 );
        if ( !dtmf_get_irq_pin ( &dtmf ) )
        {
            if ( DTMF_STATE_IDLE != state )
            {
                log_printf( &logger, "\r\n Disconnected\r\n" );
                break;
            }
            log_printf( &logger, " Message %u: ", ( uint16_t ) msg_cnt );
            state = DTMF_STATE_IRQ_SET;
            time_cnt = 0;
        }
        if ( ( DTMF_STATE_IRQ_SET == state ) && !( time_cnt % DTMF_TIMING_RX_READY ) )
        {
            if ( dtmf_unscram_1s_det ( &dtmf ) && dtmf_rx_ready ( &dtmf ) )
            {
                dtmf_receive_data ( &dtmf, &rx_data );
                log_printf( &logger, "%c", ( uint16_t ) rx_data );
                if ( '\r' == rx_data )
                {
                    msg_end_buff[ 0 ] = rx_data;
                }
                else if ( '\n' == rx_data )
                {
                    msg_end_buff[ 1 ] = rx_data;
                }
                else
                {
                    msg_end_buff[ 0 ] = 0;
                    msg_end_buff[ 1 ] = 0;
                }
            }
            if ( ( '\r' == msg_end_buff[ 0 ] ) && ( '\n' == msg_end_buff[ 1 ] ) )
            {
                msg_end_buff[ 0 ] = 0;
                msg_end_buff[ 1 ] = 0;
                state = DTMF_STATE_IDLE;
                if ( NUM_MESSAGES == ++msg_cnt )
                {
                    Delay_ms ( 100 );
                    log_printf( &logger, " Terminate call\r\n" );
                    Delay_ms ( 100 );
                    break;
                }
            }
        }
        if ( time_cnt++ > DTMF_TIMING_WAIT_FOR_MESSAGE )
        {
            log_printf( &logger, "\r\n Timeout\r\n" );
            break;
        }
    }
    log_printf( &logger, " Hook ON\r\n" );
    dtmf_hook_on ( &dtmf );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
}
```

## Note

> We have used a Yeastar S20 VoIP PBX system for the test, where the Click boards are
connected to ports 1 and 2 configured as FXS extension with numbers 1000 and 1001 (dialer).

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DTMF

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
