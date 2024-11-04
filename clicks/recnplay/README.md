\mainpage Main Page
 
---
# Rec & Play Click 

Rec&Play Click is a digital voice recorder on a Click board. It is based on the
ISD3900, a multi-message record and playback device. It features the ChipCorder
technology, offering digital sound compression, smart message management, 
digitally configurable signal path, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/recnplay_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/recplay-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the RecNPlay Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for RecNPlay Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void recnplay_cfg_setup ( recnplay_cfg_t *cfg ); 
 
- Initialization function.
> RECNPLAY_RETVAL recnplay_init ( recnplay_t *ctx, recnplay_cfg_t *cfg );

#### Example key functions :

- Function queries the ISD3900 device status.
> RECNPLAY_RETVAL recplay_read_status ( recnplay_t* ctx, uint8_t* interr_status );
 
- Function erases the message starting at the specified address.
> RECNPLAY_RETVAL recplay_erase_msg ( recnplay_t* ctx, uint32_t mem_addr );

- Function initiates a managed record at first available location in memory.
> RECNPLAY_RETVAL recplay_record_msg ( recnplay_t* ctx );

## Examples Description

> This application demonstrates the process of recording a message and playing it back.

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI interface in proper mode and performs all the necessary commands to
> put the device in proper working mode (chip reset, chip power up, chip erasing, clock configuration).

```c

void application_init ( void )
{
  	log_cfg_t log_cfg;
    recnplay_cfg_t cfg;

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

    recnplay_cfg_setup( &cfg );
    RECNPLAY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    recnplay_init( &recnplay, &cfg );

    log_printf( &logger, "Chip reset...\r\n" );
    recplay_reset( &recnplay );
    log_printf( &logger, "Power up...\r\n" );
    recplay_pwr_up( &recnplay );
    wait_power_up( );
    log_printf( &logger, "Chip Erasing...\r\n" );
    recplay_erase_chip( &recnplay );
    wait_cmd_fin( );
    log_printf( &logger, "Clock Configuration...\r\n" );
    status_byte = recplay_set_clk_cnfg( &recnplay, 0x34 );
    log_printf( &logger, "----------------------------\r\n" );
    volume = 0;
    Delay_ms ( 1000 );
}
  
```

### Application Task

> Performs the chip configuration for recording message via microphone, then records a message
> for 8 seconds to specified memory location. After that, it reads the recorded message address with message length and then plays the
> recorded message. When playback is done it erases the recorded message from memory. Afterwards, it repeats all the operations every 10 seconds.

```c

void application_task ( void )
{
  	uint8_t cnt;
    log_printf( &logger, "Preparing to record a message\r\n" );
    for ( cnt = 0; cnt < 32; cnt++ )
    {
        if ( ( cnt != RECPLAY_CFG0A_REG ) && ( cnt != RECPLAY_CFG1C_REG ) && ( cnt != RECPLAY_CFG1E_REG ) )
        {
            wait_ready( );
            temp_var = config_rec_mic[ cnt ];
            status_byte = recplay_write_cnfg_reg( &recnplay, cnt, &temp_var, 1 );
        }
    }
    wait_ready( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "Message recording" );
    status_byte = recplay_record_msg_addr( &recnplay, 0x12000 );
    time_record( 8 );
    status_byte = recplay_stop( &recnplay );
    wait_cmd_fin( );
    log_printf( &logger, "End of recording\r\n" );

    status_byte = recplay_read_msg_addr( &recnplay, &msg_addr, &msg_len );
    log_printf( &logger, "Message Address: 0x%lx\r\n", msg_addr );
    log_printf( &logger, "Message Length: %u\r\n", msg_len );
    Delay_ms ( 1000 );

    log_printf( &logger, "Preparing to play a message\r\n" );
    set_volume( 100 );
    for ( cnt = 0; cnt < 32; cnt++ )
    {
        if ( ( cnt != RECPLAY_CFG0A_REG ) && ( cnt != RECPLAY_CFG1C_REG ) && ( cnt != RECPLAY_CFG1E_REG ) )
        {
            wait_ready( );

            if ( cnt == RECPLAY_CFG03_REG )
            {
                temp_var = volume;
            }
            else
            {
                temp_var = config_play_pwm_spk[ cnt ];
            }
            status_byte = recplay_write_cnfg_reg( &recnplay, cnt, &temp_var, 1 );
        }
    }

    wait_ready( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "Message is playing...\r\n" );
    status_byte = recplay_play_msg( &recnplay, 0x12000, 0 );
    wait_cmd_fin( );
    log_printf( &logger, "End of playing...\r\n" );


    log_printf( &logger, "Status Byte: 0x%x\r\n", ( uint16_t ) status_byte );
    log_printf( &logger, "Interrupt byte: 0x%x\r\n", ( uint16_t ) interr_byte );
    Delay_ms ( 1000 );

    log_printf( &logger, "Message erasing...\r\n" );
    status_byte = recplay_erase_msg( &recnplay, 0x12000 );
    wait_cmd_fin( );
    log_printf( &logger, "End of erasing\r\n" );

    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 1000 );
}  

```

## Note

> The ISD3900 must be properly configured to work in record mode every time when user wants to record a message.
> When user wants to play a recorded message, then ISD3900 must be properly configured, but now to work in play mode.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.RecNPlay

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
