
---
# MP3 Click

> [MP3 Click](https://www.mikroe.com/?pid_product=MIKROE-946) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-946&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This app demonstrates the use of MP3 Click by playing the specified sound from the mp3_resources.h file.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mp3

### Example Key Functions

- `mp3_cfg_setup` Config Object Initialization function.
```c
void mp3_cfg_setup ( mp3_cfg_t *cfg ); 
```

- `mp3_init` Initialization function.
```c
err_t mp3_init ( mp3_t *ctx, mp3_cfg_t *cfg );
```

- `mp3_cmd_write` Function writes one byte (command) to MP3
```c
void mp3_cmd_write( mp3_t *ctx, uint8_t address, uint16_t input );
```

- `mp3_data_write` Function writes one byte ( data ) to MP3
```c
err_t mp3_data_write( mp3_t *ctx, uint8_t input );
```

- `mp3_data_write_32` Function Write 32 bytes ( data ) to MP3
```c
err_t mp3_data_write_32( mp3_t *ctx, uint8_t *input32 );
```

### Application Init

> Initializes the driver and performs the default Click configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mp3_cfg_t cfg;

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
    mp3_cfg_setup( &cfg );
    MP3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mp3_init( &mp3, &cfg );

    mp3_reset( &mp3 );

    mp3_cmd_write( &mp3, MP3_MODE_ADDR, 0x0800 );
    mp3_cmd_write( &mp3, MP3_BASS_ADDR, 0x7A00 );
    mp3_cmd_write( &mp3, MP3_CLOCKF_ADDR, 0x2000 );

    // MP3 set volume, maximum volume is 0x00 and total silence is 0xFE.
    mp3_set_volume( &mp3, 0x2F, 0x2F );
    Delay_ms ( 1000 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Playing the specified sound form the mp3_resources.h file.

```c
void application_task ( void )
{
    uint32_t file_size = sizeof ( gandalf_sax_mp3_compressed );
    uint32_t file_pos = 0;
    uint8_t data_buf[ 32 ] = { 0 };

    log_printf( &logger, " Playing audio..." );
    for ( file_pos = 0; ( file_pos + 32 ) <= file_size; file_pos += 32 )
    {
        memcpy ( data_buf, &gandalf_sax_mp3_compressed[ file_pos ], 32 );
        while ( MP3_OK != mp3_data_write_32( &mp3, data_buf ) );
    }

    for ( ; file_pos < file_size; file_pos++ )
    {
        while ( MP3_OK != mp3_data_write( &mp3, gandalf_sax_mp3_compressed[ file_pos ] ) );
    }
    log_printf( &logger, "Done\r\n\n" );
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
