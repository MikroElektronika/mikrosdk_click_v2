
---
# CAN FD 6 Click

> [CAN FD 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4572) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4572&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Nikolic
- **Date**          : feb 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This application presents the capabilities of the CAN FD 6 Click board. The board can be used both as a receiver and a transmitter. Use def directive to define the receive or transmit app.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CANFD6

### Example Key Functions

- `canfd6_cfg_setup` Config Object Initialization function.
```c
void canfd6_cfg_setup ( canfd6_cfg_t *cfg );
```

- `canfd6_init` Initialization function.
```c
err_t canfd6_init ( canfd6_t *ctx, canfd6_cfg_t *cfg );
```

- `canfd6_default_cfg` Click Default Configuration function.
```c
void canfd6_default_cfg ( canfd6_t *ctx );
```

- `canfd6_mcan_write_txbuffer` This function will write a CAN message to a specified TX buffer that can be transmitted at a later time with the transmit buffer contents function.
```c
uint32_t canfd6_mcan_write_txbuffer ( canfd6_t *ctx, uint8_t buf_index, canfd6_mcan_tx_header_t *header, uint8_t data_payload[ ] );
```

- `canfd6_mcan_transmit_buffer_contents` This function writes the specified buffer index bit value into the TXBAR register to request a message to send.
```c
err_t canfd6_mcan_transmit_buffer_contents ( canfd6_t *ctx, uint8_t buf_index );
```

- `canfd6_mcan_read_nextfifo` This function will read the next MCAN FIFO element specified and return the corresponding header information and data payload.
```c
uint8_t canfd6_mcan_read_nextfifo ( canfd6_t *ctx, canfd6_mcan_fifo_enum_t fifo_def, canfd6_mcan_rx_header_t *header, uint8_t data_payload[ ] );
```

### Application Init

> The app starts by initializing the UART LOG and SPI drivers. The default cfg function performs the mandatory settings of the device. The user's default configuration can be modified ( for more information about device configuration, check the datasheet ). Additionally, the app writes two messages to the FIFO buffer and sends them if the transmit buffer content event is triggered.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    canfd6_cfg_t canfd6_cfg;  /**< Click config object. */

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
    canfd6_cfg_setup( &canfd6_cfg );
    CANFD6_MAP_MIKROBUS( canfd6_cfg, MIKROBUS_1 );
    err_t init_flag = canfd6_init( &canfd6, &canfd6_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    canfd6_default_cfg( &canfd6 );
    Delay_ms ( 100 );
#ifdef DEMO_APP_TRANSMITTER
    canfd6_mcan_tx_header_t canfd6_header = { 0 };
    uint8_t data_send_buf[ 64 ] = { 0 };
    strcpy ( data_send_buf, "MIKROE" );
    canfd6_header.DLC = CANFD6_MCAN_DLC_6B;
    canfd6_header.ID = 0x123;
    canfd6_header.FDF = 1;
    canfd6_header.BRS = 1;
    canfd6_header.EFC = 0;
    canfd6_header.MM  = 0;
    canfd6_header.RTR = 0;
    canfd6_header.XTD = 0;
    canfd6_header.ESI = 0;
    canfd6_mcan_write_txbuffer( &canfd6, CANFD6_FIRST_MSG, &canfd6_header, data_send_buf );

    strcpy ( data_send_buf, "CAN FD 6 Click board" );
    canfd6_header.DLC = CANFD6_MCAN_DLC_20B;
    canfd6_header.ID = 0x456;
    canfd6_header.FDF = 1;
    canfd6_header.BRS = 1;
    canfd6_header.EFC = 0;
    canfd6_header.MM  = 0;
    canfd6_header.RTR = 0;
    canfd6_header.XTD = 0;
    canfd6_header.ESI = 0;
    canfd6_mcan_write_txbuffer( &canfd6, CANFD6_SECOND_MSG, &canfd6_header, data_send_buf );
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending on the defined app option, the application task performs the following procedure. If the transmitter is preferred, the application task triggers the transmit buffer contents event of the first message and, later on, the second message. On the other hand, the receiver waits for the CAN FD interrupt, where the payload is read along with the header ID.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Transmit first message\r\n" );
    canfd6_mcan_transmit_buffer_contents( &canfd6, CANFD6_FIRST_MSG );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Transmit second message\r\n" );
    canfd6_mcan_transmit_buffer_contents( &canfd6, CANFD6_SECOND_MSG );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    uint8_t cnt = 0;
    if ( !canfd6_get_int_pin( &canfd6 ) ) {
        canfd6_device_interrupts_t canfd6_dev_ir = { 0 };
        canfd6_mcan_interrupts_t canfd6_mcan_ir = { 0 };
        canfd6_device_read_interrupts( &canfd6, &canfd6_dev_ir );
        canfd6_mcan_read_interrupts( &canfd6, &canfd6_mcan_ir );

        if ( canfd6_dev_ir.SPIERR ) {
            canfd6_device_clear_spierr( &canfd6 );
        }

        if ( canfd6_mcan_ir.RF0N ) {
            canfd6_mcan_rx_header_t canfd6_msg_header = { 0 };
            uint8_t num_bytes = 0;
            uint8_t data_payload[ 64 ] = { 0 };

            canfd6_mcan_clear_interrupts( &canfd6, &canfd6_mcan_ir );

            num_bytes = canfd6_mcan_read_nextfifo( &canfd6, CANFD6_RXFIFO0, &canfd6_msg_header, data_payload );
            
            log_printf( &logger, " Message received ID[ 0x%X ]: ", canfd6_msg_header.ID );

            while ( cnt < 64 ) {
                if ( data_payload[ cnt ] ) {
                    log_printf( &logger, "%c", data_payload[ cnt ] );
                    cnt++;
                } else {
                    log_printf( &logger, "\r\n" );
                    cnt = 64;
                }
            }
        }
    }
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
