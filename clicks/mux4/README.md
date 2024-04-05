\mainpage Main Page

---
# MUX 4 click

MUX 4 Click is a compact add-on board that contains a precise analog multiplexing IC. This board features the 74HC4851, 8-channel analog multiplexer/demultiplexer with injection-current effect control from Nexperia USA Inc.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mux_4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mux-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the MUX4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MUX4 Click driver.

#### Standard key functions :

- `mux4_cfg_setup` Config Object Initialization function.
```c
void mux4_cfg_setup ( mux4_cfg_t *cfg );
```

- `mux4_init` Initialization function.
```c
err_t mux4_init ( mux4_t *ctx, mux4_cfg_t *cfg );
```

#### Example key functions :

- `mux4_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t mux4_read_an_pin_voltage ( mux4_t *ctx, float *data_out );
```

- `mux4_enable_input` This function enable or disables analog inputs.
```c
void mux4_enable_input ( mux4_t *ctx, uint8_t en_state );
```

- `mux4_select_input` This function selects which input channel signal is being forwarded to the AN/EXT pin.
```c
void mux4_select_input ( mux4_t *ctx, uint8_t input );
```

## Example Description

> This example demonstrates the use of MUX 4 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables analog inputs.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;    /**< Logger config object. */
    mux4_cfg_t mux4_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    mux4_cfg_setup( &mux4_cfg );
    MUX4_MAP_MIKROBUS( mux4_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == mux4_init( &mux4, &mux4_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    mux4_enable_input( &mux4, MUX4_ENABLE_INPUT );
}

```

### Application Task

> Reads the voltage from all input channels and displays the values of each channel on the USB UART approximately every second.

```c

void application_task ( void )
{
    float mux4_an_voltage = 0;

    for ( uint8_t cnt = MUX4_SELECT_INPUT_1; cnt <= MUX4_SELECT_INPUT_8; cnt++ )
    {
        mux4_select_input( &mux4, cnt );
        Delay_ms ( 10 );
        if ( ADC_ERROR != mux4_read_an_pin_voltage ( &mux4, &mux4_an_voltage ) ) 
        {
            log_printf( &logger, " CH%u Voltage : %.3f V\r\n", ( uint16_t ) cnt, mux4_an_voltage );
        }
    }
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MUX4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
