\mainpage Main Page

---
# SpeakUp 3 click

> SpeakUP 3 Click is a compact add-on board providing an offline speech recognition solution. This board features the VC-02, a low-cost pure offline speech recognition module developed by Ai-Thinker Technology. The VC-02 module uses an integrated voice chip US516P6 based on a 32-bit RSIC architecture core, a DSP instruction set for signal processing and speech recognition, an FPU arithmetic unit, and an FFT accelerator. The VC-02 supports offline identification of 150 local instructions, RTOS lightweight system, firmware update feature, as well as the selection of the communication method with the module.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/speakup3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/speakup-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2022.
- **Type**          : UART type


# Software Support

We provide a library for the SpeakUp 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SpeakUp 3 Click driver.

#### Standard key functions :

- `speakup3_cfg_setup` Config Object Initialization function.
```c
void speakup3_cfg_setup ( speakup3_cfg_t *cfg );
```

- `speakup3_init` Initialization function.
```c
err_t speakup3_init ( speakup3_t *ctx, speakup3_cfg_t *cfg );
```

#### Example key functions :

- `speakup3_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t speakup3_generic_read ( speakup3_t *ctx, char *data_out, uint16_t len );
```

- `speakup3_wait_for_reply` This function waits up to @b wait_ms for a reply to the voice command.
```c
err_t speakup3_wait_for_reply ( speakup3_t *ctx, uint8_t *reply_ins, uint32_t wait_ms );
```

## Example Description

> This example demonstrates the use of the SpeakUp 3 click board by reading and displaying the voice commands reply messages.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    speakup3_cfg_t speakup3_cfg;  /**< Click config object. */

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
    speakup3_cfg_setup( &speakup3_cfg );
    SPEAKUP3_MAP_MIKROBUS( speakup3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == speakup3_init( &speakup3, &speakup3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the reply message to a voice command and displays it on the USB UART.

```c
void application_task ( void )
{
    uint8_t reply_ins;
    if ( SPEAKUP3_OK == speakup3_wait_for_reply ( &speakup3, &reply_ins, 1000 ) )
    {
        speakup3_display_reply ( reply_ins );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SpeakUp3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
