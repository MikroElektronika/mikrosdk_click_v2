
---
# DTMF Generator Click

> [DTMF Generator Click](https://www.mikroe.com/?pid_product=MIKROE-4298) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4298&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This is an example which demonstrates the use of DTMF Generator Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DTMFGenerator

### Example Key Functions

- `dtmfgenerator_cfg_setup` Config Object Initialization function.
```c
void dtmfgenerator_cfg_setup ( dtmfgenerator_cfg_t *cfg );
```

- `dtmfgenerator_init` Initialization function.
```c
err_t dtmfgenerator_init ( dtmfgenerator_t *ctx, dtmfgenerator_cfg_t *cfg );
```

- `dtmfgenerator_set_dat` Set DATA ( RST ) pin state function.
```c
void dtmfgenerator_set_dat ( dtmfgenerator_t *ctx, uint8_t pin_state );
```

- `dtmfgenerator_power_on` Power ON function.
```c
void dtmfgenerator_power_on ( dtmfgenerator_t *ctx );
```

- `dtmfgenerator_transmit_out_tone` The function transmit duration time of the desired tone.
```c
void dtmfgenerator_transmit_out_tone ( dtmfgenerator_t *ctx, uint8_t out_tone, uint16_t delay_m_s );
```

### Application Init

> Initialization driver enables - GPIO, run the power-on sequence, also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dtmfgenerator_cfg_t dtmfgenerator_cfg;  /**< Click config object. */

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
    dtmfgenerator_cfg_setup( &dtmfgenerator_cfg );
    DTMFGENERATOR_MAP_MIKROBUS( dtmfgenerator_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == dtmfgenerator_init( &dtmfgenerator, &dtmfgenerator_cfg ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, " Powering on device \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    dtmfgenerator_power_on( &dtmfgenerator );
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> DTMF Generator Click board DTMF generator transmits the signal for generating tone for digits :
> "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
> "A", "B", "C", "D", "*" and "#".
> All data logs write on USB uart changes.

```c
void application_task ( void ) 
{
    log_printf( &logger, " TONE      '0' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_0, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '1' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_1, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '2' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_2, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '3' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_3, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '4' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_4, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '5' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_5, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '6' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_6, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '7' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_7, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '8' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_8, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '9' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_9, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      'A' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_A, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      'B' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_B, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      'C' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_C, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      'D' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_D, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '*' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_ASTERISK, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '#' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_HASH, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
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
