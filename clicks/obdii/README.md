\mainpage Main Page

---
# OBDII click

> OBDII click offers a unique opportunity to tap into the car diagnostic systems. It features the STN1110 Multiprotocol OBD to UART Interface, developed by the ScanTool technologies. This click can be used for the communication with the Electronic Control Unit (ECU) of a vehicle, via several different OBD II diagnostic protocols such as CAN, K LINE, L LINE and J1850. The STN1110 IC is used to process requests sent by the MCU via the UART interface and return back the responses from the ECU network nodes.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/obdii_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/obdii-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2023.
- **Type**          : UART type


# Software Support

We provide a library for the OBDII Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for OBDII Click driver.

#### Standard key functions :

- `obdii_cfg_setup` Config Object Initialization function.
```c
void obdii_cfg_setup ( obdii_cfg_t *cfg );
```

- `obdii_init` Initialization function.
```c
err_t obdii_init ( obdii_t *ctx, obdii_cfg_t *cfg );
```

#### Example key functions :

- `obdii_send_command` This function sends command string by using UART serial interface.
```c
void obdii_send_command ( obdii_t *ctx, uint8_t *cmd );
```

- `obdii_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t obdii_generic_read ( obdii_t *ctx, uint8_t *data_out, uint16_t len );
```

- `obdii_reset_device` This function resets the device by toggling the RST pin.
```c
void obdii_reset_device ( obdii_t *ctx );
```

## Example Description

> This example demonstrates the use of OBDII click board by reading the engine RPM and vehicle speed and displaying results on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    obdii_cfg_t obdii_cfg;  /**< Click config object. */

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
    obdii_cfg_setup( &obdii_cfg );
    OBDII_MAP_MIKROBUS( obdii_cfg, MIKROBUS_1 );
    if ( UART_ERROR == obdii_init( &obdii, &obdii_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    obdii_reset_device ( &obdii );
    
    obdii_process ( &obdii );
    obdii_clear_app_buf ( );
    
    log_printf( &logger, "> Reset device\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_RESET_DEVICE );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    obdii_log_app_buf ( );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Disable echo\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_DISABLE_ECHO );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    obdii_log_app_buf ( );
    
    log_printf( &logger, " Remove spaces\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_SPACES_OFF );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    obdii_log_app_buf ( );
}

```

### Application Task

> Reads and processes the engine RPM and vehicle speed and displays the results on the USB UART once per second.

```c
void application_task ( void )
{
    uint8_t * __generic_ptr start_ptr = NULL;
    uint8_t data_buf[ 5 ] = { 0 };
    uint16_t rpm = 0;
    uint8_t speed = 0;
    
    log_printf( &logger, " Get current RPM\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_GET_CURRENT_RPM );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    start_ptr = strstr( app_buf, OBDII_RSP_CURRENT_RPM );
    if ( start_ptr )
    {
        memcpy ( data_buf, ( start_ptr + 4 ), 4 );
        data_buf[ 4 ] = 0;
        rpm = hex_to_uint16( data_buf ) / 4;
        log_printf( &logger, "RPM: %u\r\n\n>", rpm );
    }
    else
    {
        obdii_log_app_buf ( );
    }
    
    log_printf( &logger, " Get current speed\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_GET_CURRENT_SPEED );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    start_ptr = strstr( app_buf, OBDII_RSP_CURRENT_SPEED );
    if ( start_ptr )
    {
        memcpy ( data_buf, ( start_ptr + 4 ), 2 );
        data_buf[ 2 ] = 0;
        speed = hex_to_uint8( data_buf );
        log_printf( &logger, "Speed: %u km/h\r\n\n>", ( uint16_t ) speed );
    }
    else
    {
        obdii_log_app_buf ( );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.OBDII

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
