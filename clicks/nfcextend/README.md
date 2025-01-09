
---
# NFC Extend Click

> [NFC Extend Click](https://www.mikroe.com/?pid_product=MIKROE-3971) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3971&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases how to configure and use the NFC Extend Click. The Click is an NFC tag 
  interface which uses the I2C serial interface and an RF link interface in order to communicate.
  The example requires the ST25 NFC Tap application which can be downloaded to your phone. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NfcExtend

### Example Key Functions

- `nfcextend_cfg_setup` Config Object Initialization function. 
```c
void nfcextend_cfg_setup ( nfcextend_cfg_t *cfg );
``` 
 
- `nfcextend_init` Initialization function. 
```c
err_t nfcextend_init ( nfcextend_t *ctx, nfcextend_cfg_t *cfg );
```

- `nfcextend_default_cfg` Click Default Configuration function. 
```c
void nfcextend_default_cfg ( nfcextend_t *ctx );
```

- `nfcextend_i2c_set` This function writes data to the chip. 
```c
uint8_t nfcextend_i2c_set ( nfcextend_t *ctx, nfcextend_block_t *block );
```
 
- `nfcextend_i2c_get` This function reads data from the chip. 
```c
uint8_t nfcextend_i2c_get ( nfcextend_t *ctx, nfcextend_block_t *block );
```

- `nfcextend_digital_read_int` This function reads the digital signal from the INT pin. 
```c
uint8_t nfcextend_digital_read_int ( nfcextend_t *ctx );
```

### Application Init

> This function initializes and configures the logger and Click modules.

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
