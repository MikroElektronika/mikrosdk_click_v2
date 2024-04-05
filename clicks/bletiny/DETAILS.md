
---
# BLE TINY click

> BLE TINY Click is a compact add-on board that provides BLE connectivity for any embedded application. This board features the DA14531, SmartBond TINY module based on the world’s smallest and lowest power Bluetooth 5.1 System-on-Chip (SoC) from Dialog Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ble_tiny_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ble-tiny-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Apr 2021.
- **Type**          : UART type


# Software Support

We provide a library for the BLETINY Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BLETINY Click driver.

#### Standard key functions :

- `bletiny_cfg_setup` Config Object Initialization function.
```c
void bletiny_cfg_setup ( bletiny_cfg_t *cfg );
```

- `bletiny_init` Initialization function.
```c
BLETINY_RETVAL bletiny_init ( bletiny_t *ctx, bletiny_cfg_t *cfg );
```

- `bletiny_default_cfg` Click Default Configuration function.
```c
void bletiny_default_cfg ( bletiny_t *ctx );
```

#### Example key functions :

- `bletiny_send_cmd` Send command function.
```c
void bletiny_send_cmd ( bletiny_t *ctx, char *cmd );
```

- `bletiny_i2c_config` Configure Click board for I2C master communication.
```c
void bletiny_i2c_config ( bletiny_t *ctx, uint8_t speed, uint8_t reg_len );
```

- `bletiny_i2c_write` Send command to write data to reg address of slave device via I2C communication.
```c
err_t bletiny_i2c_write ( bletiny_t *ctx, uint8_t slave_address, uint16_t reg, uint8_t reg_data );
```

## Example Description

> This example reads and processes data from BLE TINY clicks. 
Application waits for connection with Click board with phone.
Then checks its Coadless FW version and checks connected device. 
Then waits for command to be stored in it's memory on 0 slot. 
After that depending on the command stored it executes that type of example.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and resets device and seds Disconnect and Reset IO commands. 
Then it waits for the connection to device. When connected it sends commands to 
check Coadless FW, connected device, its BLE address and signal quality of 
connection. In the end it waits for command from its memory. After valid 
command is stored in memory on 0 slot it contines to Application Task.

```c

void application_init ( void ) 
{   
    log_cfg_t log_cfg;  /**< Logger config object. */
    bletiny_cfg_t bletiny_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\nApplication Init\r\n" );
    Delay_ms ( 1000 );
    
    // Click initialization.
    bletiny_cfg_setup( &bletiny_cfg );
    BLETINY_MAP_MIKROBUS( bletiny_cfg, MIKROBUS_1 );
    err_t init_flag  = bletiny_init( &bletiny, &bletiny_cfg );
    
    if ( init_flag == UART_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }    
    bletiny_default_cfg ( &bletiny );
    
    bletiny_send_cmd( &bletiny, BLETINY_CMD_ATR );
    bletiny_send_cmd( &bletiny, BLETINY_CMD_ATZ );
    bletiny_send_cmd( &bletiny, BLETINY_CMD_GAPDISCONNECT );
    bletiny_process( );
    bletiny_clear_app_buf( );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    
    //wait for connection
    log_printf( &logger, " Waiting for phone to connect\r\n" );
    while ( 0 == strstr( app_buf, BLETINY_CONNECTED ) ) 
    {
        bletiny_process( );
    }
    log_printf( &logger, " Connected\r\n" );
    bletiny_clear_app_buf( );
    //send ATI command to check Codless FW
    bletiny_send_cmd( &bletiny, BLETINY_CMD_ATI );
    volatile err_t app_error_flag = bletiny_rsp_check();
    if ( BLETINY_OK == app_error_flag )
    {
        bletiny_log_app_buf();
        log_printf( &logger, "-----------------------------------\r\n" );
    }
    else
    {
        bletiny_error_check( app_error_flag );
    }
    Delay_ms ( 1000 );
    //send command to check ble address
    bletiny_send_cmd( &bletiny, BLETINY_CMD_BDADDR );    
    app_error_flag = bletiny_rsp_check();
    if ( BLETINY_OK == app_error_flag )
    {
        bletiny_log_app_buf();
        log_printf( &logger, "-----------------------------------\r\n" );
    }
    else
    {
        bletiny_error_check( app_error_flag );
    }
    Delay_ms ( 1000 );
    //send ATrI command to check remote connected device
    bletiny_send_cmd( &bletiny, BLETINY_CMD_ATRI );
    app_error_flag = bletiny_rsp_check();
    if ( BLETINY_OK == app_error_flag )
    {
        bletiny_log_app_buf();
        log_printf( &logger, "-----------------------------------\r\n" );
    }
    else
    {
        bletiny_error_check( app_error_flag );
    }
    Delay_ms ( 1000 );
    //send RSSI command to check signal quality
    bletiny_send_cmd( &bletiny, BLETINY_CMD_RSSI );
    app_error_flag = bletiny_rsp_check();
    if ( BLETINY_OK == app_error_flag )
    {
        bletiny_log_app_buf();
        log_printf( &logger, "-----------------------------------\r\n" );
    }
    else
    {
        bletiny_error_check( app_error_flag );
    }
    //select example to execute
    bletiny_example_init( );
    
    bletiny_clear_app_buf( );
    log_printf( &logger, " Application Task \r\n" );
}

```

### Application Task

> Executes one of thre application task selected in Application Init:I2C, SPI, APP.
I2C example uses EEPROM Click board to write and read data of its memory.
SPI example uses EEPROM 2 Click board to write and read data of its memory.
APP example just reads UART data and logs it to UART Terminal.

```c

void application_task ( void ) 
{
    static uint8_t info = 0;
    switch ( example_type )
    {
        case BLETINY_I2C_EXAMPLE:
        {
            if (!info)
            {
                info++;
                log_printf( &logger, " I2C example\r\n" );
                bletiny_process( );
                bletiny_clear_app_buf( );
            }
            bletiny_i2c_example( );
            break;
        }
        case BLETINY_SPI_EXAMPLE:
        {
            if (!info)
            {
                info++;
                log_printf( &logger, " SPI example\r\n" );
                bletiny_process( );
                bletiny_clear_app_buf( );
            }
            bletiny_spi_example( );
            break;
        }
        case BLETINY_APP_CTRL:
        {
            if (!info)
            {
                info++;
                log_printf( &logger, " Application example\r\n" );
                bletiny_process( );
                bletiny_clear_app_buf( );
            }
            bletiny_application_example( );
            break;
        }
        default:
        {
            break;
        }
    }
}

```

## Note

> For this application you need to install Dialog's mobile application SmartConsole.
This application I2C example is created using EEPROM Click board, and for SPI
example EEPROM 2 Click board is used.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BLETINY

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
