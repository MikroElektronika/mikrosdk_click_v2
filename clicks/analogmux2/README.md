\mainpage Main Page



---
# Analog MUX 2 click

Analog MUX 2 Click is a compact add-on board that switches one of the eight inputs to one output. This board features the ADG728, a low voltage, CMOS 8-channel analog matrix switch with a serially controlled 2-wire interface from Analog Devices. The ADG728 can operate equally well as either multiplexer, demultiplexer, or switch array easily connected to a 9 pole spring action block terminal. It provides flexibility and features a low on-resistance closely matched between switches and very flat over the full signal range. This Click board™ is suitable for a wide range of applications, from industrial and instrumentation to medical, consumer, communications, and automotive systems.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/analogmux2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/analog-mux-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the AnalogMux2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for AnalogMux2 Click driver.
```

#### Standard key functions :

- Config Object Initialization function.
```
void analogmux2_cfg_setup ( analogmux2_cfg_t *cfg );
```

- Initialization function.
```
ANALOGMUX2_RETVAL analogmux2_init ( analogmux2_t *ctx, analogmux2_cfg_t *cfg );
```

- Click Default Configuration function.
```
void analogmux2_default_cfg ( analogmux2_t *ctx );
```

#### Example key functions :

- Analog MUX 2 set channel function.
```
err_t analogmux2_set_channel ( analogmux2_t *ctx, uint8_t mux_ch );
```

- Analog MUX 2 read AN pin value function.
```
err_t analogmux2_read_an_pin_value ( analogmux2_t *ctx, uint16_t *data_out );
```

- Analog MUX 2 read AN pin voltage level function.
```
err_t analogmux2_read_an_pin_voltage ( analogmux2_t *ctx, float *data_out );
```

## Examples Description

This application controls the multiplexing of a single input channel
with an eight-channel matrix switch.

**The demo application is composed of two sections :**

### Application Init

Initializes I2C and ADC driver, set Vref, STM32F407ZG - 2.048 V, PIC18F97J94 3.3 V, 
set the default configuration and start to write log.

```
void application_init ( void ) {
    log_cfg_t log_cfg;                /**< Logger config object. */
    analogmux2_cfg_t analogmux2_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    analogmux2_cfg_setup( &analogmux2_cfg );
    ANALOGMUX2_MAP_MIKROBUS( analogmux2_cfg, MIKROBUS_1 );
    
    // Vref STM32F407ZG
    analogmux2_cfg.vref = 2.048;
    
    err_t init_flag = analogmux2_init( &analogmux2, &analogmux2_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    analogmux2_default_cfg ( &analogmux2 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 100 );
}
```

### Application Task

This is an example that shows the use of a Analog MUX 2 click board.
In this example, we switch from channel AN0 to channel AN7, 
read and display the analog value and voltage on the active channel.
Results are being sent to the Usart Terminal where you can track their changes.

```
void application_task ( void ) {   
    for ( uint8_t ch_pos = ANALOGMUX2_SET_CHANNEL_0; ch_pos <= ANALOGMUX2_SET_CHANNEL_7; ch_pos++ ) {
        analogmux2_set_channel( &analogmux2, ch_pos );
        Delay_ms( 3000 );
        
        uint16_t analogmux2_an_value = 0;
    
        log_printf( &logger, "   CHANNEL    : AN%u     \r\n", ( uint16_t ) analogmux2_get_channel( &analogmux2 ) );
        log_printf( &logger, "- - - - - - - - - - - - - \r\n" );

        if ( analogmux2_read_an_pin_value ( &analogmux2, &analogmux2_an_value ) != ADC_ERROR ) {
            log_printf( &logger, "   ADC Value  : %u\r\n", analogmux2_an_value );
        }
    
        float analogmux2_an_voltage = 0;

        if ( analogmux2_read_an_pin_voltage ( &analogmux2, &analogmux2_an_voltage ) != ADC_ERROR ) {
            log_printf( &logger, "   AN Voltage : %.3f V \r\n", analogmux2_an_voltage );
        }
        
        log_printf( &logger, "-------------------------\r\n" );
    }   
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AnalogMux2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
