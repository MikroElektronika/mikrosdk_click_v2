\mainpage Main Page

---
# BLE 10 click

> BLE 10 Click is a compact add-on board that provides BT/BLE connectivity for any embedded application. This board features the PAN1780-AT, a Bluetooth® 5 Low Energy Module based on Nordic's nRF52840 single-chip controller from Panasonic. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ble10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ble-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : UART type


# Software Support

We provide a library for the BLE10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BLE10 Click driver.

#### Standard key functions :

- `ble10_cfg_setup` Config Object Initialization function.
```c
void ble10_cfg_setup ( ble10_cfg_t *cfg );
```

- `ble10_init` Initialization function.
```c
err_t ble10_init ( ble10_t *ctx, ble10_cfg_t *cfg );
```

- `ble10_default_cfg` Click Default Configuration function.
```c
void ble10_default_cfg ( ble10_t *ctx );
```

#### Example key functions :

- `ble10_set_device_name` This function sets the local device name.
```c
err_t ble10_set_device_name ( ble10_t *ctx, char *dev_name );
```

- `ble10_factory_reset` This function factory resets the device.
```c
err_t ble10_factory_reset ( ble10_t *ctx );
```

- `ble10_get_temperature` This function executes get temperature command which returns the current temperature of the module's internal temperature sensor.
```c
err_t ble10_get_temperature ( ble10_t *ctx );
```

## Example Description

> This example reads and processes data from BLE 10 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, then performs a factory reset and sets the local device name.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    ble10_cfg_t ble10_cfg;  /**< Click config object. */

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

    ble10_cfg_setup( &ble10_cfg );
    BLE10_MAP_MIKROBUS( ble10_cfg, MIKROBUS_1 );
    err_t init_flag  = ble10_init( &ble10, &ble10_cfg );
    if ( UART_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    ble10_default_cfg ( &ble10 );
    ble10_process( );
    ble10_clear_app_buf( );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    log_printf( &logger, " - Factory Reset -\r\n" );
    ble10_factory_reset ( &ble10 );
    ble10_display_rsp ( EVT_RESET );
    
    log_printf( &logger, " - Set Device Name -\r\n" );
    ble10_set_device_name ( &ble10, DEVICE_NAME );
    ble10_display_rsp ( RSP_OK );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Logs all the received events/responses on the USB UART. 
> Then checks if there's a specific command string (defined by the GET_TEMP_COMMAND macro) 
> received from the GATT Server, and if so, it executes temperature reading command and logs the results.

```c

void application_task ( void )
{
    ble10_process( );
    if ( app_buf_len > 0 ) 
    {
        Delay_ms ( 100 );
        ble10_process( );
        for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
        {
            log_printf( &logger, "%c", app_buf[ buf_cnt ] );
        }
        if ( strstr( app_buf, EVT_GATT_VAL ) )
        {
            char get_temp_cmd[ ] = GET_TEMP_COMMAND;
            const char * __generic msg_ptr = strrchr ( app_buf, ',' ) + 1;
            uint8_t msg_len = *( msg_ptr - 2 ) - 48;
            
            if ( msg_len == strlen ( get_temp_cmd ) )
            {
                char get_temp_hex[ 64 ] = { 0 };
                uint8_t get_temp_hex_chr[ 3 ] = { 0 };
                uint8_t cnt = 0;
                for ( cnt = 0; cnt < strlen ( get_temp_cmd ); cnt++ )
                {
                    uint8_to_hex ( get_temp_cmd[ cnt ], get_temp_hex_chr );
                    strcat ( get_temp_hex, get_temp_hex_chr );
                }
            
                if ( 0 == memcmp ( get_temp_hex, msg_ptr, strlen ( get_temp_hex ) ) )
                {
                    ble10_clear_app_buf( );
                    log_printf( &logger, " - Get Temperature -\r\n" );
                    ble10_get_temperature ( &ble10 );
                    ble10_display_rsp ( RSP_OK );
                }
            }
        }
        ble10_clear_app_buf( );
    }
    Delay_ms ( 1 );
}

```

## Note

> We have used the nRF Connect smartphone application for the test. 
> Make sure to configure the GATT Server properly in the nRF Connect application, then you 
> will be able to send a desired command from it, once you connect to the click board.
> You can use the Sample configuration for GATT Server which comes with the application installation
> and then send a command via Test Service from the Server.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BLE10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
