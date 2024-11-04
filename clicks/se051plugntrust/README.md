\mainpage Main Page

---
# SE051 Plug n Trust Click

> SE051 Plug&Trust Click is a compact add-on board representing a ready-to-use IoT security solution. This board features the SE051C2, an updatable extension of the EdgeLock™ SE050 from NXP Semiconductor, which delivers proven security certified to CC EAL 6+, with AVA_VAN.5up to the OS level. Designed for the latest IoT security requirements, it allows securely storing and provisioning credentials performing cryptographic operations, giving edge-to-cloud security capability right out of the box. It also provides upgrade functionality of the IoT applet while preserving on-device credentials, alongside reconfiguration possibility.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/se051plugntrust_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/se051-plugtrust-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the SE051 Plug n Trust Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SE051 Plug n Trust Click driver.

#### Standard key functions :

- `se051plugntrust_cfg_setup` Config Object Initialization function.
```c
void se051plugntrust_cfg_setup ( se051plugntrust_cfg_t *cfg );
```

- `se051plugntrust_init` Initialization function.
```c
err_t se051plugntrust_init ( se051plugntrust_t *ctx, se051plugntrust_cfg_t *cfg );
```

#### Example key functions :

- `se051plugntrust_apdu_write` This function writes a @b frame_data to device.
```c
err_t se051plugntrust_apdu_write ( se051plugntrust_t *ctx, se051plugntrust_frame_data_t *frame_data );
```

- `se051plugntrust_apdu_read` This function reads a @b frame_data from device.
```c
err_t se051plugntrust_apdu_read ( se051plugntrust_t *ctx, se051plugntrust_frame_data_t *frame_data );
```

- `se051plugntrust_apdu_transfer` This function writes a @b frame_data and then reads return data from device and stores it in @b frame_data.
```c
err_t se051plugntrust_apdu_transfer ( se051plugntrust_t *ctx, se051plugntrust_frame_data_t *frame_data );
```

## Example Description

> This application is showcasing basic functionality of SE051 Plug&Trust Click board.
It gets identify data from device, selects card manager and applet.
Then checks free memory, reads all objects and deletes not reserved ones.
After that showcases a few of functionality:
Generating random data,
Creating, reading and deleting binary objects,
Creating AES symmetrical key and cipher with it;
In the end it is showcasing funcionality in the endless loop.

**The demo application is composed of two sections :**

### Application Init

> At the start it sets comunication interface to I2C and resets the chip, 
reads identifying data from device, and then selects card manager and applet.
After that it reads free persistent memory, reads all objects and deletes
objects that are not reserved by the Applet. Then it generates 2 byte of
random data, and gets the version information from the Applet. That's
followed up with creating binary object with 'MikroE' data inside. Then it checks
if object is created and reads data back. After that, the object is deleted and
it's checked if it still exists. Finally it creates 128AES key (16bytes), encrypts it
and then decrypts data with that key, and in the end it deletes that key object.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    se051plugntrust_cfg_t se051plugntrust_cfg;  /**< Click config object. */

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
    se051plugntrust_cfg_setup( &se051plugntrust_cfg );
    SE051PLUGNTRUST_MAP_MIKROBUS( se051plugntrust_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == se051plugntrust_init( &se051plugntrust, &se051plugntrust_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    frame_data.apdu = &apdu_data;

    se051plugntrust.interface = SE051PLUGNTRUST_INTERFACE_I2C;
    se051plugntrust_reset( &se051plugntrust );
    if ( SE051PLUGNTRUST_INTERFACE_ISO14443 == se051plugntrust.interface )
    {
        log_info( &logger, " ISO14443 Interface active..." );
        for ( ; ; );
    }
    
    soft_reset( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    get_data_identify( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    select_card_manger( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    select_applet( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    check_free_memory( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    list_and_delete_objects( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    get_random( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    read_uid_object( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    get_version(  );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    create_check_delete( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    aes_cipher( );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

### Application Task

> It generates 16bytes of data, writes it in binary object and then reads it back and displays
on the USB UART. Then creates AES key and encrypts that generated data with it, and then decrypts it.
In the end it deletes both AES key object and binary object that's created at the start of the task.

```c
void application_task ( void )
{
    #define DATA_LEN 16
    static uint8_t aes_value[ DATA_LEN ]    = { 0x40, 0x41, 0x42, 0x43,0x44, 0x45, 0x46, 0x47,
                                                0x48, 0x49, 0x4A, 0x4B,0x4C, 0x4D, 0x4E, 0x4F };
    static uint32_t binary_id               = 0xBBBBBBBB;
    static uint32_t aes_id                  = 0xCCCCCCCC;
    uint8_t random_data[ DATA_LEN ]         = { 0 };
    uint8_t read_data[ DATA_LEN ]           = { 0 };
    uint8_t encrypted_data[ DATA_LEN ]      = { 0 };
    uint32_t read_len = DATA_LEN;
    
    if ( SE051PLUGNTRUST_OK == se051plugntrust_get_random_numbers( &se051plugntrust, random_data, DATA_LEN ) )
    {
        log_printf( &logger, " > Generated random data: 0x" );
        log_buf_hex( random_data, DATA_LEN );
        log_printf( &logger, "\r\n" );
    }
    else
    {
        log_error( &logger, " Random" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( SE051PLUGNTRUST_OBJECT_DOESNT_EXIST == se051plugntrust_check_object_exist( &se051plugntrust, binary_id ) )
    {
        log_printf( &logger, " Write random data to binary object...\r\n" );
        if ( SE051PLUGNTRUST_OK != se051plugntrust_write_binary_object( &se051plugntrust, binary_id, 
                                                                        0, DATA_LEN, random_data ) )
        {
            log_error( &logger, " Write Binary" );
        }
        else
        {
            log_info( &logger, " Status OK" );
        }
    }
    else
    {
        log_error( &logger, " Binary object already exist" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( SE051PLUGNTRUST_OBJECT_DOES_EXISTS == se051plugntrust_check_object_exist( &se051plugntrust, binary_id ) )
    {
        if ( SE051PLUGNTRUST_OK == se051plugntrust_read_object( &se051plugntrust, binary_id, 0, 0, 
                                                                read_data, &read_len ) )
        {
            log_printf( &logger, " > Read data from binary object: 0x" );
            log_buf_hex( read_data, read_len );
            log_printf( &logger, "\r\n" );
        }
        else
        {
            log_error( &logger, " Read binray object" );
        } 
    }
    else
    {
        log_error( &logger, " Binary object doesn't exist" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Create AES key...\r\n" );
    create_128_aes_key( aes_id, aes_value );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( SE051PLUGNTRUST_OK == cipher_data_with_aes_key( aes_id, SE051PLUGNTRUST_P2_ENCRYPT_ONESHOT, 
                                                         read_data, encrypted_data ) )
    {
        log_printf( &logger, " > Encrypted data: 0x" );
        log_buf_hex( encrypted_data, DATA_LEN );
        log_printf( &logger, "\r\n" );
    }
    else
    {
        log_error( &logger, " Encrypting data" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( SE051PLUGNTRUST_OK == cipher_data_with_aes_key( aes_id, SE051PLUGNTRUST_P2_DECRYPT_ONESHOT, 
                                                         encrypted_data, read_data ) )
    {
        log_printf( &logger, " > Decrypted data: 0x" );
        log_buf_hex( read_data, DATA_LEN );
        log_printf( &logger, "\r\n" );
    }
    else
    {
        log_error( &logger, " Decrypting data" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Delete Binary and AES object...\r\n" );
    if ( ( SE051PLUGNTRUST_OK != se051plugntrust_delete_object( &se051plugntrust, binary_id ) ) || 
         ( SE051PLUGNTRUST_OK != se051plugntrust_delete_object( &se051plugntrust, aes_id ) ) )
    {
        log_error( &logger, " Deleting objects" );
    }
    log_printf( &logger, "*****************************************************************************\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Note

> For more information refer to documents from NXP: AN12413 and UM11225.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SE051PlugnTrust

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
