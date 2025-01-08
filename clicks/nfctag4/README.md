
---
# NFC Tag 4  Click

> [NFC Tag 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3659) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3659&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases how to configure and use the NFC Tag 4 Click. The Click is an NFC tag 
> interface which uses the I2C serial interface and an RF link interface in order to communicate.
> The example requires the ST25 NFC Tap application which can be downloaded to your phone.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NfcTag4

### Example Key Functions

- `nfctag4_cfg_setup` Config Object Initialization function. 
```c
void nfctag4_cfg_setup ( nfctag4_cfg_t *cfg );
``` 
 
- `nfctag4_init` Initialization function. 
```c
err_t nfctag4_init ( nfctag4_t *ctx, nfctag4_cfg_t *cfg );
```

- `nfctag4_default_cfg` Click Default Configuration function. 
```c
void nfctag4_default_cfg ( nfctag4_t *ctx );
```

- `nfctag4_password_present` This function presents password to device in order to open I2C security session. 
```c
uint8_t nfctag4_password_present ( nfctag4_t* ctx, uint8_t* password_bytes );
```
 
- `nfctag4_enable_mailbox` This function enables or disables mailbox functionality. 
```c
uint8_t nfctag4_enable_mailbox ( nfctag4_t* ctx, uint8_t enable_mailbox );
```

- `nfctag4_enable_rf` This function enables or disables RF functionality. 
```c
uint8_t nfctag4_enable_rf ( nfctag4_t* ctx, uint8_t enable_rf );
```

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
