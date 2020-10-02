 
---
# MP3 click

MP3 Click is an accessory board in mikroBus™ form factor. It includes a stereo MP3 decoder chip VS1053 which can decode multiple formats (Ogg vorbis, MP3, MP1, MP2, MPEG4, WMA, FLAC, WAV, MIDI).

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](<https://www.mikroe.com/mp3-click> )

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

- Config Object Initialization function.
> void mp3_cfg_setup ( mp3_cfg_t *cfg ); 
 
- Initialization function.
> MP3_RETVAL mp3_init ( mp3_t *ctx, mp3_cfg_t *cfg );

- Click Default Configuration function.
> void mp3_default_cfg ( mp3_t *ctx );


#### Example key functions :

- Function writes one byte (command) to MP3
> void mp3_cmd_write( mp3_t *ctx, uint8_t address, uint16_t input );
 
- Function writes one byte ( data ) to MP3
> uint8_t mp3_data_write( mp3_t *ctx, uint8_t input );

- Function Write 32 bytes ( data ) to MP3
> uint8_t mp3_data_write_32( mp3_t *ctx, uint8_t *input32 );

## Examples Description

> This app demonstrates the use of MP3 click for playing .mp3 file from SD.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init, MP3 init and reset procedure. 
> Standard configuration chip and set volume on the left and right channel.
> Then initializes SD card and searching for songs on the SD card.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mp3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mp3_cfg_setup( &cfg );
    MP3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mp3_init( &mp3, &cfg );

    mp3_reset( &mp3 );

    mp3_cmd_write( &mp3, MP3_MODE_ADDR, 0x0800 );
    mp3_cmd_write( &mp3, MP3_BASS_ADDR, 0x7A00 );
    mp3_cmd_write( &mp3, MP3_CLOCKF_ADDR, 0x2000 );

    mp3_set_volume( &mp3, 0x2F, 0x2F );

    log_printf( &logger, "App init done\r\n" );
}
  
```

### Application Task

> Play audio, every 100 ms.

```c

void application_task ( void )
{
    uint32_t file_size = 32778;
    uint8_t cnt;
    uint8_t file_pos = 0;

    log_printf( &logger, "--Play audio\r\n" );

    while( file_size > buff_size )
    {
        for (cnt = 0; cnt < buff_size / 32 ; cnt++)
        {
            while( mp3_data_write_32( &mp3, MP3_LAKI + file_pos * 32 ) );
            file_pos += 32;
        }
        file_size -= buff_size;
    }

    for( cnt = 0; cnt < file_size; cnt++ )
    {
        while( mp3_data_write( &mp3, MP3_LAKI[ file_pos ] ) );
        file_pos++;
    }
    log_printf( &logger, "--Finish\r\n" );
    Delay_ms( 100 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mp3

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
