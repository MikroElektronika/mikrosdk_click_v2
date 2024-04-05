\mainpage Main Page
 
---
# NFC Extend click

NFC Extend Click is NFC tag interface device with possibility of using any shape and size external antenna, offering 16 Kbit of electrically erasable programmable memory (EEPROM). This Click Board™ offer two communication interfaces.>

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nfcextend_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nfc-extend-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

We provide a library for the NfcExtend Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for NfcExtend Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void nfcextend_cfg_setup ( nfcextend_cfg_t *cfg ); 
 
- Initialization function.
> NFCEXTEND_RETVAL nfcextend_init ( nfcextend_t *ctx, nfcextend_cfg_t *cfg );

- Click Default Configuration function.
> void nfcextend_default_cfg ( nfcextend_t *ctx );

#### Example key functions :

- This function writes data to the chip.
> uint8_t nfcextend_i2c_set ( nfcextend_t *ctx, nfcextend_block_t *block );
 
- This function reads data from the chip.
> uint8_t nfcextend_i2c_get ( nfcextend_t *ctx, nfcextend_block_t *block );

- This function reads the digital signal from the INT pin.
> uint8_t nfcextend_digital_read_int ( nfcextend_t *ctx );

## Examples Description

> This example showcases how to configure and use the NFC Extend click. The click is an NFC tag 
  interface which uses the I2C serial interface and an RF link interface in order to communicate.
  The example requires the ST25 NFC Tap application which can be downloaded to your phone. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules.

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    nfcextend_cfg_t cfg;

    uint8_t init_status_flag;

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

    //  Click initialization.

    nfcextend_cfg_setup( &cfg );
    NFCEXTEND_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nfcextend_init( &nfcextend, &cfg );

    nfcextend_password_present( &nfcextend, default_password );
    Delay_ms ( 100 );

    init_status_flag = nfcextend_default_cfg( &nfcextend );
    Delay_ms ( 100 );

    if ( 1 == init_status_flag )
    {
        log_printf( &logger, " * App init failed. *\r\n" );
    }
    else if ( 0 == init_status_flag ) 
    {
        log_printf( &logger, " * App init done. *\r\n" );
    }
    log_printf( &logger, "-----------------------\r\n" );
}
  
```

### Application Task

> This function waits for the interrupt signal, after which it expects data transfers. Once
  some data has been detected it will open a communication channel with the device transmitting
  it and show the received data in the UART console. 

```c

void application_task ( )
{
    nfcextend_block_t block;

    uint8_t temp_buf[ 258 ];
    uint16_t message_len;
    uint16_t cnt;

    block.memory_area = NFCEXTEND_MEMORY_DYNAMIC;
    block.reg_addr = NFCEXTEND_DYNAMIC_REG_MB_CTRL;
    block.data_buf = temp_buf;
    block.len = 1;

    wait_for_interrupt( );
    nfcextend_i2c_get( &nfcextend, &block );

    if ( ( temp_buf[ 0 ] & 0x04 ) == 0x04 )
    {
        block.reg_addr = NFCEXTEND_DYNAMIC_REG_MB_LEN;
        block.data_buf = &temp_buf[ 0 ];

        wait_for_interrupt( );
        nfcextend_i2c_get( &nfcextend, &block );

        message_len = temp_buf[ 0 ] + 1;

        block.memory_area = NFCEXTEND_MEMORY_MAILBOX;
        block.reg_addr = NFCEXTEND_MAILBOX_REG_BYTE_0;
        block.data_buf = &temp_buf[ 0 ];
        block.len = message_len;

        wait_for_interrupt( );
        nfcextend_i2c_get( &nfcextend, &block );

        log_printf( &logger, " ** Message length:  %u Bytes**\r\n", message_len);
        
        log_printf( &logger, " ------------------------------\r\n" );
        log_printf( &logger, " ** Message START **\r\n" );

        for ( cnt = 0; cnt < message_len; cnt++ )
        {
            log_printf( &logger, " %u : 0x%x\r\n", cnt, ( uint16_t ) temp_buf[ cnt ] );
        }

        log_printf( &logger, " ** Message END **\r\n" );
        log_printf( &logger, " ------------------------------\r\n" );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.NfcExtend

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
