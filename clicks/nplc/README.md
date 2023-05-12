\mainpage Main Page

---
# N-PLC click

> N-PLC Click is a compact add-on board that uses existing electrical power lines to transmit data signals. This board features the SM2400, an advanced multi-standard Narrow-band Power Line Communication (N-PLC) modem from Semitech. The SM2400 features a dual-core architecture, a DSP core for N-PLC modulations, and a 32-bit core for running protocols for superior communication performance and flexibility for various open standards and customized implementations. It includes firmware options for IEEE 1901.2 compliant PHY and MAC layers, a 6LoWPAN data link layer, and special modes for industrial IoT applications. In addition to the ability to accept signals from another PLC modem or the power line communication AC coupling circuit, this board also has a handful of other features, such as a selectable interface and power supply, firmware update capabilities, LED indicators, and many others.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nplc_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/n-plc-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : UART type


# Software Support

We provide a library for the N-PLC Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for N-PLC Click driver.

#### Standard key functions :

- `nplc_cfg_setup` Config Object Initialization function.
```c
void nplc_cfg_setup ( nplc_cfg_t *cfg );
```

- `nplc_init` Initialization function.
```c
err_t nplc_init ( nplc_t *ctx, nplc_cfg_t *cfg );
```

- `nplc_default_cfg` Click Default Configuration function.
```c
err_t nplc_default_cfg ( nplc_t *ctx );
```

#### Example key functions :

- `nplc_set_mode` This function sets operation mode to command or data.
```c
void nplc_set_mode ( nplc_t *ctx, uint8_t mode );
```

- `nplc_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t nplc_generic_write ( nplc_t *ctx, char *data_in, uint16_t len );
```

- `nplc_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t nplc_generic_read ( nplc_t *ctx, char *data_out, uint16_t len );
```

## Example Description

> This example demonstrates the use of an N-PLC click boards by showing the communication between the two click boards configured as a receiver and transmitter.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, resets the click board to default config, displays the firmware version and switches to data operation mode.
After that displays the selected application mode and sends an initial message in case of transmitter mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nplc_cfg_t nplc_cfg;  /**< Click config object. */

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
    nplc_cfg_setup( &nplc_cfg );
    NPLC_MAP_MIKROBUS( nplc_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nplc_init( &nplc, &nplc_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    } 
    nplc_process( );
    nplc_clear_app_buf( );

    log_printf( &logger, " - HW reset -\r\n" );
    nplc_hw_reset ( &nplc );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Go to command mode -\r\n" );
    nplc_set_mode ( &nplc, NPLC_MODE_COMMAND );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Factory reset -\r\n" );
    nplc_factory_reset ( &nplc );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Reboot -\r\n" );
    nplc_sw_reset ( &nplc );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Go to command mode -\r\n" );
    nplc_set_mode ( &nplc, NPLC_MODE_COMMAND );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Show firmware version -\r\n" );
    nplc_firmware_version ( &nplc );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Go to data mode -\r\n" );
    nplc_set_mode ( &nplc, NPLC_MODE_DATA );

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
    
    log_printf( &logger, " Sending initial message: %s", ( char * ) DEMO_TEXT_MESSAGE );
    nplc_generic_write( &nplc, DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "\r\n--------------------------------\r\n" );
    Delay_ms( 1000 ); 
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif   
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads all the received data and echoes them back to the transmitter. The received and echoed messages will be displayed on the USB UART.

```c
void application_task ( void )
{
    nplc_process ( );
    if ( app_buf_len > 0 ) 
    {
        Delay_ms( 500 );
        nplc_process( );
        log_printf( &logger, " Received message: %s", app_buf );
        log_printf( &logger, "\r\n--------------------------------\r\n" );
        Delay_ms( 500 );
        log_printf( &logger, " Sending echo response: %s", app_buf );
        nplc_generic_write( &nplc, app_buf, app_buf_len );
        log_printf( &logger, "\r\n--------------------------------\r\n\n" );
        nplc_clear_app_buf( );
        Delay_ms( 1000 ); 
    }
}
```

## Note

> Once both devices are programmed, one as a receiver and the other as a transmitter, you will need to reset the transmitter board in order
to start the communication by sending an initial message.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NPLC

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
