

---
# NFC Tag 4  Click

NFC Tag 4 Click is NFC tag device, offering 16 Kbit of electrically erasable
programmable memory (EEPROM). 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nfctag4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/nfc-tag-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the NfcTag4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for NfcTag4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void nfctag4_cfg_setup ( nfctag4_cfg_t *cfg ); 
 
- Initialization function.
> NFCTAG4_RETVAL nfctag4_init ( nfctag4_t *ctx, nfctag4_cfg_t *cfg );

- Click Default Configuration function.
> void nfctag4_default_cfg ( nfctag4_t *ctx );


#### Example key functions :

- This function presents password to device in order to open I2C security session
> uint8_t nfctag4_password_present ( nfctag4_t* ctx, uint8_t* password_bytes );
 
- This function enables or disables mailbox functionality
> uint8_t nfctag4_enable_mailbox ( nfctag4_t* ctx, uint8_t enable_mailbox );

- This function enables or disables RF functionality
> uint8_t nfctag4_enable_rf ( nfctag4_t* ctx, uint8_t enable_rf );

## Examples Description

> This example showcases how to configure and use the NFC Tag 4 Click. The Click is an NFC tag 
> interface which uses the I2C serial interface and an RF link interface in order to communicate.
> The example requires the ST25 NFC Tap application which can be downloaded to your phone.


**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and Click modules.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    nfctag4_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    nfctag4_cfg_setup( &cfg );
    NFCTAG4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nfctag4_init( &nfctag4, &cfg );

    nfctag4_default_cfg( &nfctag4 );
}
  
```

### Application Task

> This function waits for the interrupt signal, after which it expects data transfers. Once
> some data has been detected it will open a communication channel with the device transmitting
> it and show the received data in the UART console.

```c

void application_task ( void )
{
    nfctag4_wait_for_int( );

    info.memory_area = NFCTAG4_MEMORY_DYNAMIC;
    info.register_address = NFCTAG4_DYNAMIC_REG_MB_CTRL;
    info.n_registers = 1;
    nfctag4_i2c_get( &nfctag4, &info, aux_buffer );

    if ( ( aux_buffer[ 0 ] & 0x04 ) == ( 0x04 ) )
    {
        nfctag4_wait_for_int( );
        info.memory_area = NFCTAG4_MEMORY_DYNAMIC;
        info.register_address = NFCTAG4_DYNAMIC_REG_MB_LEN;
        info.n_registers = 1;
        nfctag4_i2c_get( &nfctag4, &info, aux_buffer );
        message_length = aux_buffer[ 0 ];
        message_length++;
        nfctag4_wait_for_int( );
        info.memory_area = NFCTAG4_MEMORY_MAILBOX;
        info.register_address = NFCTAG4_MAILBOX_REG_BYTE_0;
        info.n_registers = message_length;
        nfctag4_i2c_get( &nfctag4, &info, aux_buffer );

        log_printf( &logger, "************* MESSAGE ***************\r\n" );
        log_printf( &logger, " ** Message length:  %u Bytes**\r\n", message_length );

        for ( i = 0; i < message_length; i++ )
        {
            log_printf( &logger, " %u : 0x%x\r\n", i, ( uint16_t ) aux_buffer[ i ] );
        }

        log_printf( &logger, "************** END ****************\r\n" );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.NfcTag4

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
