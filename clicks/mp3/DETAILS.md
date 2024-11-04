 
---
# MP3 Click

> MP3 Click is an accessory board in mikroBus™ form factor. It includes a stereo MP3 decoder chip VS1053 which can decode multiple formats (Ogg vorbis, MP3, MP1, MP2, MPEG4, WMA, FLAC, WAV, MIDI).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mp3_click.png">
</p>

[Click Product page](https://www.mikroe.com/mp3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Mp3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mp3 Click driver.

#### Standard key functions :

- `mp3_cfg_setup` Config Object Initialization function.
```c
void mp3_cfg_setup ( mp3_cfg_t *cfg ); 
```

- `mp3_init` Initialization function.
```c
err_t mp3_init ( mp3_t *ctx, mp3_cfg_t *cfg );
```

#### Example key functions :

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

## Example Description

> This app demonstrates the use of MP3 Click by playing the specified sound from the mp3_resources.h file.

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mp3

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
