
---
# IR 2 click

> IR 2 Click is a compact add-on board representing a compact and easy solution for adding infrared (IR) remote control to your design. This board features the TSMP58138, a miniaturized sensor for receiving the modulated signal of QEE113 IR emitting diode from Vishay Semiconductors. This IR sensor module consists of a photodetector, pre-amplifier, and automatic gain control to surpass ambient noise with signals transmitted to it in the near-infrared range with a wavelength of 940nm. It also communicates with the target MCU via selectable GPIO lines.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ir2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ir-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the IR 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IR 2 Click driver.

#### Standard key functions :

- `ir2_cfg_setup` Config Object Initialization function.
```c
void ir2_cfg_setup ( ir2_cfg_t *cfg );
```

- `ir2_init` Initialization function.
```c
err_t ir2_init ( ir2_t *ctx, ir2_cfg_t *cfg );
```

#### Example key functions :

- `ir2_get_out_pin` This function returns the OUT pin logic state.
```c
uint8_t ir2_get_out_pin ( ir2_t *ctx );
```

- `ir2_nec_send_data` This function sends an address and data bytes using NEC protocol.
```c
void ir2_nec_send_data ( ir2_t *ctx, uint8_t address, uint8_t data_in );
```

- `ir2_nec_read_data` This function reads an address and data bytes by using NEC protocol.
```c
err_t ir2_nec_read_data ( ir2_t *ctx, uint8_t *address, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of an IR 2 click board by showing
the communication between the two click boards configured as a receiver and transmitter using the NEC protocol.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and displays the selected application mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ir2_cfg_t ir2_cfg;  /**< Click config object. */

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
    ir2_cfg_setup( &ir2_cfg );
    IR2_MAP_MIKROBUS( ir2_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == ir2_init( &ir2, &ir2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
#ifdef IR2_TRANSMITTER_MODE
    log_printf( &logger, "-  Transmitter mode   - \r\n" );
#else
    log_printf( &logger, "-    Receiver mode    - \r\n" );
#endif
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Depending on the selected mode, it sends a desired message using NEC protocol or
reads all the received data and displays them on the USB UART.

```c
void application_task ( void )
{
#ifdef IR2_TRANSMITTER_MODE
    log_printf( &logger, " Sending message." );
    
    for ( uint8_t cnt = 0; cnt < sizeof ( IR2_DATA ); cnt++ )
    {
        ir2_nec_send_data ( &ir2, IR2_ADDRESS, IR2_DATA[ cnt ] );
        log_printf( &logger, "." );
    }
    
    log_printf( &logger, "\r\n Message has been sent! \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    Delay_ms ( 500 );
#else
    uint8_t address;
    uint8_t rx_data;
    
    if ( IR2_OK == ir2_nec_read_data ( &ir2, &address, &rx_data ) )
    {
        log_printf( &logger, "Address: 0x%.2X, Data: %c\r\n", ( uint16_t ) address, rx_data );
    }
#endif
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IR2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
