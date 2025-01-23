
---
# NFC 7 SPI Click

> [NFC 7 SPI Click](https://www.mikroe.com/?pid_product=MIKROE-6452) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2024.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of NFC 7 SPI Click board by handling the detection
and processing of various NFC technologies and protocols, and ensuring the application
can respond to different NFC card types (A,B,F,V).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NFC7SPI

### Example Key Functions

- `nfc7spi_cfg_setup` Config Object Initialization function.
```c
void nfc7spi_cfg_setup ( nfc7spi_cfg_t *cfg );
```

- `nfc7spi_init` Initialization function.
```c
err_t nfc7spi_init ( nfc7spi_t *ctx, nfc7spi_cfg_t *cfg );
```

- `nfc7spi_default_cfg` Click Default Configuration function.
```c
err_t nfc7spi_default_cfg ( nfc7spi_t *ctx );
```

- `nfc7spi_wait_discovery` This function waits until remote NFC device is discovered.
```c
err_t nfc7spi_wait_discovery ( nfc7spi_t *ctx, nfc7spi_rf_intf_t *rf_intf );
```

- `nfc7spi_presence_check` This function waits until the discovered target device is removed.
```c
err_t nfc7spi_presence_check ( nfc7spi_t *ctx, nfc7spi_rf_intf_t *rf_intf );
```

- `nfc7spi_stop_discovery` This function stops the RF discovery process.
```c
err_t nfc7spi_stop_discovery ( nfc7spi_t *ctx );
```

### Application Init

> Initializes the driver and logger, performs the Click default configuration and reads the device firmware version.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc7spi_cfg_t nfc7spi_cfg;  /**< Click config object. */

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
    nfc7spi_cfg_setup( &nfc7spi_cfg );
    NFC7SPI_MAP_MIKROBUS( nfc7spi_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == nfc7spi_init( &nfc7spi, &nfc7spi_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NFC7SPI_ERROR == nfc7spi_default_cfg ( &nfc7spi ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_printf( &logger, " FW version: %.2X.%.2X.%.2X\r\n", 
                ( uint16_t ) nfc7spi.fw_version[ 0 ], 
                ( uint16_t ) nfc7spi.fw_version[ 1 ], 
                ( uint16_t ) nfc7spi.fw_version[ 2 ] );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for an NFC device to be discovered, checks if it supports a known NFC technology, 
and then handles the device based on its protocol. The application continues processing
the device (reading and writing information) and waits until the card is removed.
Once the card is removed, the discovery process is restarted to detect a new NFC device.

```c
void application_task ( void )
{
    nfc7spi_rf_intf_t rf_intf;
    log_printf( &logger, " WAITING FOR DEVICE DISCOVERY\r\n\n" );
    if ( NFC7SPI_OK == nfc7spi_wait_discovery ( &nfc7spi, &rf_intf ) )
    {
        if ( ( NFC7SPI_NCI_RF_TECH_PASSIVE_POLL_NFC_A == rf_intf.mode_tech ) || 
             ( NFC7SPI_NCI_RF_TECH_PASSIVE_POLL_NFC_B == rf_intf.mode_tech ) || 
             ( NFC7SPI_NCI_RF_TECH_PASSIVE_POLL_NFC_F == rf_intf.mode_tech ) || 
             ( NFC7SPI_NCI_RF_TECH_PASSIVE_POLL_15693 == rf_intf.mode_tech ) )
        {
            for ( ; ; )
            {
                nfc7spi_display_card_info ( rf_intf );

                switch ( rf_intf.protocol )
                {
                    case NFC7SPI_NCI_RF_PROT_T2T:
                    {
                        nfc7spi_handle_iso14443_3a ( &nfc7spi );
                        break;
                    }
                    case NFC7SPI_NCI_RF_PROT_ISODEP:
                    {
                        nfc7spi_handle_iso14443_4 ( &nfc7spi );
                        break;
                    }
                    case NFC7SPI_NCI_RF_PROT_T5T:
                    {
                        nfc7spi_handle_iso15693 ( &nfc7spi );
                        break;
                    }
                    case NFC7SPI_NCI_RF_PROT_MIFARE:
                    {
                        nfc7spi_handle_mifare ( &nfc7spi );
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                if ( !rf_intf.more_tags )
                {
                    break;
                }
                nfc7spi_reader_act_next ( &nfc7spi, &rf_intf );
            }
            
            nfc7spi_presence_check ( &nfc7spi, &rf_intf );
            log_printf ( &logger, " - CARD REMOVED\r\n\n" );

            nfc7spi_stop_discovery ( &nfc7spi );
            while ( NFC7SPI_OK != nfc7spi_start_discovery ( &nfc7spi ) );
        }
        else
        {
            log_printf ( &logger, " - WRONG DISCOVERY\r\n\n" );
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
