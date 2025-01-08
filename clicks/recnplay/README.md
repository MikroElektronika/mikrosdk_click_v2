
---
# Rec & Play Click

> [Rec N Play Click](https://www.mikroe.com/?pid_product=MIKROE-3345) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3345&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application demonstrates the process of recording a message and playing it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RecNPlay

### Example Key Functions

- `recnplay_cfg_setup` Config Object Initialization function. 
```c
void recnplay_cfg_setup ( recnplay_cfg_t *cfg );
``` 
 
- `recnplay_init` Initialization function. 
```c
err_t recnplay_init ( recnplay_t *ctx, recnplay_cfg_t *cfg );
```

- `recplay_read_status` Function queries the ISD3900 device status. 
```c
err_t recplay_read_status ( recnplay_t* ctx, uint8_t* interr_status );
```
 
- `recplay_erase_msg` Function erases the message starting at the specified address. 
```c
err_t recplay_erase_msg ( recnplay_t* ctx, uint32_t mem_addr );
```

- `recplay_record_msg` Function initiates a managed record at first available location in memory. 
```c
err_t recplay_record_msg ( recnplay_t* ctx );
```

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

### Note

> The ISD3900 must be properly configured to work in record mode every time when user wants to record a message.
> When user wants to play a recorded message, then ISD3900 must be properly configured, but now to work in play mode.

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
