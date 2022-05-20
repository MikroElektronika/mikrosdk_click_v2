---
# Analog MUX 5 click

> Analog MUX 5 Click is a compact add-on board that switches one of many inputs to one output. This board features the MAX4634, a fast, low-voltage four-channel CMOS analog multiplexer from Analog Devices. This low-voltage multiplexer operates from both mikroBUS™ power rails and features 4Ω maximum ON-resistance (RON). CMOS switch construction allows the processing of analog signals within the supply voltage range. It is also characterized by an easy way of management, only through a couple of signals from the mikroBUS™ socket. This Click board™ is suitable for various applications, from industrial and instrumentation to medical, consumer, communications, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/analogmux5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/analog-mux-5-click)

---


#### Click library

- **Author**        : Nikola Peric
- **Date**          : Apr 2022.
- **Type**          : ADC type


# Software Support

We provide a library for the Analog MUX 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Analog MUX 5 Click driver.

#### Standard key functions :

- `analogmux5_cfg_setup` Config Object Initialization function.
```c
void analogmux5_cfg_setup ( analogmux5_cfg_t *cfg );
```

- `analogmux5_init` Initialization function.
```c
err_t analogmux5_init ( analogmux5_t *ctx, analogmux5_cfg_t *cfg );
```

- `analogmux5_default_cfg` Click Default Configuration function.
```c
err_t analogmux5_default_cfg ( analogmux5_t *ctx );
```

#### Example key functions :

- `analogmux5_enable` Analog MUX 5 enable function.
```c
void analogmux5_enable ( analogmux5_t *ctx );
```

- `analogmux5_select_ch` Analog MUX 5 set channel function.
```c
err_t analogmux5_select_ch ( analogmux5_t *ctx, uint8_t ch_select );
```

- `analogmux5_read_an_pin_voltage` Analog MUX 5 read AN pin voltage level function.
```c
err_t analogmux5_read_an_pin_voltage ( analogmux5_t *ctx, float *data_out );
```

## Example Description

> This example showcases how to initialize, configure and use the Analog MUX 5 click module.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the analog inputs.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    analogmux5_cfg_t analogmux5_cfg;  /**< Click config object. */

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
    analogmux5_cfg_setup( &analogmux5_cfg );
    ANALOGMUX5_MAP_MIKROBUS( analogmux5_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == analogmux5_init( &analogmux5, &analogmux5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANALOGMUX5_ERROR == analogmux5_default_cfg ( &analogmux5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This is an example that shows the use of a Analog MUX 5 click board
> In this example, we switch from channel AN1 to channel AN4, 
> read and display the analog value and voltage on the active channel.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    float analogmux5_an_voltage = 0;

    analogmux5_select_ch( &analogmux5, ANALOGMUX5_SEL_CH_1 );
    Delay_ms( 100 );
        
    if ( ADC_ERROR != analogmux5_read_an_pin_voltage ( &analogmux5, &analogmux5_an_voltage ) ) 
    {
        log_printf( &logger, " Channel [ 1 ] ---> AN Voltage : %.3f[V]\r\n\n", analogmux5_an_voltage );
    }
    
    analogmux5_select_ch( &analogmux5, ANALOGMUX5_SEL_CH_2 );
    Delay_ms( 100 );
        
    if ( ADC_ERROR != analogmux5_read_an_pin_voltage ( &analogmux5, &analogmux5_an_voltage ) ) 
    {
        log_printf( &logger, " Channel [ 2 ] ---> AN Voltage : %.3f[V]\r\n\n", analogmux5_an_voltage );
    }
    
    analogmux5_select_ch( &analogmux5, ANALOGMUX5_SEL_CH_3 );
    Delay_ms( 100 );
        
    if ( ADC_ERROR != analogmux5_read_an_pin_voltage ( &analogmux5, &analogmux5_an_voltage ) ) 
    {
        log_printf( &logger, " Channel [ 3 ] ---> AN Voltage : %.3f[V]\r\n\n", analogmux5_an_voltage );
    }
    
    analogmux5_select_ch( &analogmux5, ANALOGMUX5_SEL_CH_4 );
    Delay_ms( 100 );
        
    if ( ADC_ERROR != analogmux5_read_an_pin_voltage ( &analogmux5, &analogmux5_an_voltage ) ) 
    {
        log_printf( &logger, " Channel [ 4 ] ---> AN Voltage : %.3f[V]\r\n\n", analogmux5_an_voltage );
    }
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AnalogMUX5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
