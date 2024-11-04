
---
# DTMF Generator Click

> DTMF Generator Click is a compact add-on board that generates DTMF (Dual-Tone Multi-Frequency) signals designed for MCU interfaces. This board features the HT9200A, a dual-tone multi-frequency decoder mostly used in mobile communications systems from Holtek Semiconductor Inc.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dtmfgenerator_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dtmf-generator-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the DTMFGenerator Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DTMFGenerator Click driver.

#### Standard key functions :

- `dtmfgenerator_cfg_setup` Config Object Initialization function.
```c
void dtmfgenerator_cfg_setup ( dtmfgenerator_cfg_t *cfg );
```

- `dtmfgenerator_init` Initialization function.
```c
err_t dtmfgenerator_init ( dtmfgenerator_t *ctx, dtmfgenerator_cfg_t *cfg );
```

#### Example key functions :

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

## Example Description

> This is an example which demonstrates the use of DTMF Generator Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - GPIO, run the power-on sequence, also write log.

```c

void application_init ( void ) {
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

void application_task ( void ) {
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


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DTMFGenerator

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
