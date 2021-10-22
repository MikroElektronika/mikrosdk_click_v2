
---
# GainAMP 3 click

> GainAMP 3 Click is a compact add-on board that contains a 4-channel programmable gain amplifier. This board features the ADA4254, a zero drift, high voltage, programmable gain instrumentation amplifier from Analog Devices. It features 12 binary weighted gains and three scaling gain options resulting in 36 possible gain settings. It comes with an input multiplexer providing ±60V protection to the high impedance inputs of the amplifier and an excitation current source output available to bias sensors such as resistance temperature detectors (RTDs).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gainamp3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gainamp-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the GainAMP3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GainAMP3 Click driver.

#### Standard key functions :

- `gainamp3_cfg_setup` Config Object Initialization function.
```c
void gainamp3_cfg_setup ( gainamp3_cfg_t *cfg );
```

- `gainamp3_init` Initialization function.
```c
err_t gainamp3_init ( gainamp3_t *ctx, gainamp3_cfg_t *cfg );
```

- `gainamp3_default_cfg` Click Default Configuration function.
```c
err_t gainamp3_default_cfg ( gainamp3_t *ctx );
```

#### Example key functions :

- `gainamp3_write_register` This function writes a data byte to the selected register by using SPI serial interface.
```c
err_t gainamp3_write_register ( gainamp3_t *ctx, uint8_t reg, uint8_t data_in );
```

- `gainamp3_set_amplifier_gain` This function sets the amplifier gain level.
```c
err_t gainamp3_set_amplifier_gain ( gainamp3_t *ctx, uint8_t gain );
```

- `gainamp3_set_input_channel` This function sets the input channel.
```c
err_t gainamp3_set_input_channel ( gainamp3_t *ctx, uint8_t channel );
```

## Example Description

> This example demonstrates the use of GainAMP 3 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which verifies the communication and sets active the input channel 1.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    gainamp3_cfg_t gainamp3_cfg;  /**< Click config object. */

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

    gainamp3_cfg_setup( &gainamp3_cfg );
    GAINAMP3_MAP_MIKROBUS( gainamp3_cfg, MIKROBUS_1 );
    err_t init_flag = gainamp3_init( &gainamp3, &gainamp3_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    init_flag = gainamp3_default_cfg ( &gainamp3 );
    if ( GAINAMP3_ERROR == init_flag )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the amplifier gain level every 3 seconds and displays the gain value on the USB UART.

```c

void application_task ( void )
{
    for ( uint8_t cnt = GAINAMP3_GAIN_1_OVER_16; cnt <= GAINAMP3_GAIN_128; cnt++ )
    {
        gainamp3_set_amplifier_gain ( &gainamp3, cnt );
        log_printf( &logger, " Amplifier gain set to " );
        float gain = ( 1 << cnt ) / 16.0;
        
        if ( gain < 1.0 )
        {
            log_printf( &logger, "1/%u\r\n", ( uint16_t ) ( 1.0 / gain ) );
        }
        else
        {
            log_printf( &logger, "%u\r\n", ( uint16_t ) gain );
        }
        Delay_ms( 3000 );
    }
}

```

## Note

> VDDH should be within the range from +5V to +30V.
VSSH should be within the range from -5V to -30V.
Input channels should be within the range from GND to VCC selected by the VCC_SEL SMD jumpers.
Gain * Input voltage must not exceed VCC voltage.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GainAMP3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
