\mainpage Main Page

---
# A5000 Plug n Trust click

> A5000 Plug&Trust Click is a compact add-on board representing a ready-to-use secure IoT authenticator. This board features the A5000, an Edge Lock® Secure Authenticator from NXP Semiconductors. The A5000 provides a root of trust at the IC level, giving an IoT authentication system state-of-the-art security capability. It allows for securely storing and provisioning credentials and performing cryptographic operations for security-critical communication and authentication functions. It has an independent Common Criteria EAL 6+ security certification up to OS level and supports ECC asymmetric cryptographic and AES/3DES symmetric algorithms.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/a5000plugntrust_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/a5000-plugtrust-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the A5000 Plug n Trust Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for A5000 Plug n Trust Click driver.

#### Standard key functions :

- `a5000plugntrust_cfg_setup` Config Object Initialization function.
```c
void a5000plugntrust_cfg_setup ( a5000plugntrust_cfg_t *cfg );
```

- `a5000plugntrust_init` Initialization function.
```c
err_t a5000plugntrust_init ( a5000plugntrust_t *ctx, a5000plugntrust_cfg_t *cfg );
```

#### Example key functions :

- `a5000plugntrust_apdu_write` This function writes a @b frame_data to device.
```c
err_t a5000plugntrust_apdu_write ( a5000plugntrust_t *ctx, a5000plugntrust_frame_data_t *frame_data );
```

- `a5000plugntrust_apdu_read` This function reads a @b frame_data from device.
```c
err_t a5000plugntrust_apdu_read ( a5000plugntrust_t *ctx, a5000plugntrust_frame_data_t *frame_data );
```

- `a5000plugntrust_apdu_transfer` This function writes a @b frame_data and then reads return data from device and stores it in @b frame_data.
```c
err_t a5000plugntrust_apdu_transfer ( a5000plugntrust_t *ctx, a5000plugntrust_frame_data_t *frame_data );
```

## Example Description

> This application is showcasing basic functionality of A5000 Plug&Trust click board.
It gets identify data from device, selects card manager and applet.
Then checks free memory, reads all objects and deletes not reserved ones.
After that showcases a few of functionality:
Generating random data,
Creating, reading and deleting binary objects,
Creating AES symmetrical key and cipher with it;
In the end it is showcasing funcionality in the endless loop.

**The demo application is composed of two sections :**

### Application Init

> Reads indetifing data from device, and then selects card manager and applet.
After that it reads free presistant memory, reads all objects and deletes
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
    a5000plugntrust_cfg_t a5000plugntrust_cfg;  /**< Click config object. */

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
    a5000plugntrust_cfg_setup( &a5000plugntrust_cfg );
    A5000PLUGNTRUST_MAP_MIKROBUS( a5000plugntrust_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == a5000plugntrust_init( &a5000plugntrust, &a5000plugntrust_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    frame_data.apdu = &apdu_data;
    
    soft_reset( );
    Delay_ms( 2000 );
    get_data_identify( );
    Delay_ms( 2000 );
    select_card_manger( );
    Delay_ms( 2000 );
    select_applet( );
    Delay_ms( 2000 );
    check_free_memory( );
    Delay_ms( 2000 );
    list_and_delete_objects( );
    Delay_ms( 2000 );
    get_random( );
    Delay_ms( 2000 );
    read_uid_object( );
    Delay_ms( 2000 );
    get_version(  );
    Delay_ms( 2000 );
    create_check_delete( );
    Delay_ms( 2000 );
    aes_cipher( );
    
    log_info( &logger, " Application Task " );
    Delay_ms( 5000 );
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
    
    if ( A5000PLUGNTRUST_OK == a5000plugntrust_get_random_numbers( &a5000plugntrust, random_data, DATA_LEN ) )
    {
        log_printf( &logger, " > Generated random data: 0x" );
        log_buf_hex( random_data, DATA_LEN );
        log_printf( &logger, "\r\n" );
    }
    else
    {
        log_error( &logger, " Random" );
    }
    Delay_ms( 2000 );
    if ( A5000PLUGNTRUST_OBJECT_DOESNT_EXIST == a5000plugntrust_check_object_exist( &a5000plugntrust, binary_id ) )
    {
        log_printf( &logger, " Write random data to binary object...\r\n" );
        if ( A5000PLUGNTRUST_OK != a5000plugntrust_write_binary_object( &a5000plugntrust, binary_id, 
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
    Delay_ms( 2000 );
    if ( A5000PLUGNTRUST_OBJECT_DOES_EXISTS == a5000plugntrust_check_object_exist( &a5000plugntrust, binary_id ) )
    {
        if ( A5000PLUGNTRUST_OK == a5000plugntrust_read_object( &a5000plugntrust, binary_id, 0, 0, 
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
    Delay_ms( 2000 );
    log_printf( &logger, " Create AES key...\r\n" );
    create_128_aes_key( aes_id, aes_value );
    Delay_ms( 2000 );
    if ( A5000PLUGNTRUST_OK == cipher_data_with_aes_key( aes_id, A5000PLUGNTRUST_P2_ENCRYPT_ONESHOT, 
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
    Delay_ms( 2000 );
    if ( A5000PLUGNTRUST_OK == cipher_data_with_aes_key( aes_id, A5000PLUGNTRUST_P2_DECRYPT_ONESHOT, 
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
    Delay_ms( 2000 );
    log_printf( &logger, " Delete Binary and AES object...\r\n" );
    if ( ( A5000PLUGNTRUST_OK != a5000plugntrust_delete_object( &a5000plugntrust, binary_id ) ) || 
         ( A5000PLUGNTRUST_OK != a5000plugntrust_delete_object( &a5000plugntrust, aes_id ) ) )
    {
        log_error( &logger, " Deleting objects" );
    }
    log_printf( &logger, "*****************************************************************************\r\n" );
    Delay_ms( 5000 );
}
```

## Note

> For more information refer to documents from NXP: AN13187 and AN13266.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.A5000PlugnTrust

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
