\mainpage Main Page

---
# LYRA 24P Click

> LYRA 24P Click is a compact add-on board for high-performance wireless connectivity in IoT devices running on Bluetooth. This board features the LYRA 24P (453-00145R), a secure high-performance wireless module from Ezurio. It features a 32-bit ARM® Cortex®-M33 core at 39MHz, Bluetooth® Low Energy (BLE) 5.3 connectivity, and industry-leading Secure Vault® technology for enhanced security and future-proofing. The module supports 2.4GHz wireless connectivity with a built-in antenna and offers global regulatory certifications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lyra24p_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lyra-24p-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : UART type


# Software Support

We provide a library for the LYRA 24P Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LYRA 24P Click driver.

#### Standard key functions :

- `lyra24p_cfg_setup` Config Object Initialization function.
```c
void lyra24p_cfg_setup ( lyra24p_cfg_t *cfg );
```

- `lyra24p_init` Initialization function.
```c
err_t lyra24p_init ( lyra24p_t *ctx, lyra24p_cfg_t *cfg );
```

#### Example key functions :

- `lyra24p_write_command` This function writes a desired command by using UART serial interface.
```c
err_t lyra24p_write_command ( lyra24p_t *ctx, uint8_t *command );
```

- `lyra24p_write_cmd_param` This function writes a desired command, command value, prefix and parameter by using UART serial interface.
```c
err_t lyra24p_write_cmd_param ( lyra24p_t *ctx, uint8_t *command, uint8_t *cmd_val, uint8_t *prefix, uint8_t *param );
```

- `lyra24p_inquire_command` This function writes a desired inquire command, command value and enable/disable quote by using UART serial interface.
```c
err_t lyra24p_inquire_command ( lyra24p_t *ctx, uint8_t *command, uint8_t *cmd_val, uint8_t en_query );
```

## Example Description

> This example demonstrates the use of LYRA 24P Click board by processing
> the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs a factory reset. 
> In the next step, the demo app requests the LYRA module name, software version, 
> and MAC address and sets the local device name, 
> sets the module into VSP mode and start advertising.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lyra24p_cfg_t lyra24p_cfg;  /**< Click config object. */

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
    lyra24p_cfg_setup( &lyra24p_cfg );
    LYRA24P_MAP_MIKROBUS( lyra24p_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lyra24p_init( &lyra24p, &lyra24p_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    lyra24p_hw_reset( &lyra24p );
    Delay_ms ( 500 );

    lyra24p_write_command( &lyra24p, LYRA24P_CMD_AT );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_write_command( &lyra24p, LYRA24P_CMD_AT );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_inquire_command( &lyra24p, LYRA24P_CMD_ATI, 
                                       LYRA24P_ATI_ARG_DEV_NAME, 
                                       LYRA24P_QUERY_DIS );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_inquire_command( &lyra24p, LYRA24P_CMD_ATI, 
                                       LYRA24P_ATI_ARG_FW_VER, 
                                       LYRA24P_QUERY_DIS );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_inquire_command( &lyra24p, LYRA24P_CMD_ATI, 
                                       LYRA24P_ATI_ARG_BT_ADDR, 
                                       LYRA24P_QUERY_DIS );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_write_cmd_param( &lyra24p, LYRA24P_CMD_ATS, 
                                       LYRA24P_ATS_ARG_DEVNAME_FORMAT, 
                                       LYRA24P_PREFIX_SYMBOL_SET_VAL, 
                                       LYRA24P_ATS_VAL_DEVNAME );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );
    
    lyra24p_set_device_name( &lyra24p, DEVICE_NAME );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_inquire_command( &lyra24p, LYRA24P_CMD_ATPS, 
                                       LYRA24P_PREFIX_SYMBOL_ZERO, 
                                       LYRA24P_QUERY_EN );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_write_command( &lyra24p, LYRA24P_CMD_ATLADV );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_write_command( &lyra24p, LYRA24P_CMD_ATLVSP );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );
}
```

### Application Task

> Initializes the driver and performs a factory reset. 
> In the next step, the demo app are requesting the LYRA module name, 
> software version and MAC address and sets the local device name "LYRA 24P Click",  
> sets the module into VSP mode and start adverttising.

```c
void application_task ( void ) 
{
    if ( LYRA24P_OK == lyra24p_process( &lyra24p ) ) 
    {
        lyra24p_log_app_buf( );
        lyra24p_clear_app_buf( );
        Delay_ms ( 100 );
    }
}
```

## Note

> We have used the BLE Scanner smartphone application for the test.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LYRA24P

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
