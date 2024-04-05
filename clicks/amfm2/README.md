\mainpage Main Page

---
# AM/FM 2 click

> AM/FM 2 Click is a compact add-on board that can be used to listen to music from the AM and FM radio bands. 
> This board features the Si4732, a broadcast AM/FM/SE/LW/RDS radio receiver from Skyworks. 
> This radio receiver integrates the complete broadcast tuner and receiver function from antenna input 
> to digital audio output. In addition to the radio receiver, this Click board™ is equipped with the LM4910, 
> a Boomer output capacitor-less stereo 35mW headphone amplifier from Texas Instruments. 
> This amplifier can deliver 35mW of continuous average power to a 32Ω load with less than 1% distortion.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/amfm2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/amfm-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the AM/FM 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AM/FM 2 Click driver.

#### Standard key functions :

- `amfm2_cfg_setup` Config Object Initialization function.
```c
void amfm2_cfg_setup ( amfm2_cfg_t *cfg );
```

- `amfm2_init` Initialization function.
```c
err_t amfm2_init ( amfm2_t *ctx, amfm2_cfg_t *cfg );
```

- `amfm2_default_cfg` Click Default Configuration function.
```c
err_t amfm2_default_cfg ( amfm2_t *ctx );
```

#### Example key functions :

- `amfm2_seek_station` AM/FM 2 seek station function.
```c
err_t amfm2_seek_station ( amfm2_t *ctx, uint8_t *rsp );
```

- `amfm2_tuning_freq` AM/FM 2 tuning frequency function.
```c
err_t amfm2_tuning_freq ( amfm2_t *ctx, float frequency, uint8_t *rsp );
```

- `amfm2_get_tuning_freq` AM/FM 2 get tuning frequency function.
```c
err_t amfm2_get_tuning_freq ( amfm2_t *ctx, float *frequency );
```

## Example Description

> This example demonstrates the use of the AM/FM 2 Click board™.
> The app represents a radio tuner that supports worldwide AM/FM bands 
> and has features such as automatic frequency control, seek station, and volume control.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C module and log UART.
> After driver initialization, the app sets the default configuration 
> and searches and memorizes for a valid frequency of the 5 radio stations.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    amfm2_cfg_t amfm2_cfg;  /**< Click config object. */

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
    amfm2_cfg_setup( &amfm2_cfg );
    AMFM2_MAP_MIKROBUS( amfm2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == amfm2_init( &amfm2, &amfm2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMFM2_ERROR == amfm2_default_cfg ( &amfm2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_printf( &logger, " Begins searching for a valid frequency...\r\n" );
    log_printf( &logger, "--------------------\r\n" );
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ )
    {
        if ( AMFM2_OK == amfm2_seek_station( &amfm2, &rsp_status ) )
        {
            if ( AMFM2_RSP_STATUS_CTS & rsp_status )
            {
                log_printf( &logger, " The search is done.\r\n" );
                if ( AMFM2_OK == amfm2_get_tuning_freq( &amfm2, &mem_station_freq[ n_cnt ] ) )
                {
                    log_printf( &logger, " Frequency: %.2f MHz \r\n", mem_station_freq[ n_cnt ] );
                    log_printf( &logger, "- - - - - - - - - - \r\n" );
                    Delay_ms ( 100 );
                }
            }
        }
    }
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 100 );
    
    if ( AMFM2_OK == amfm2_set_volume( &amfm2, AMFM2_SET_VOLUME_MAX, &rsp_status ) )
    {
        log_printf( &logger, " Set max volume \r\n" );
        Delay_ms ( 100 );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the AM/FM 2 Click board™.
> The application switches all 5 previously memorized radio frequencies every 10 seconds.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ )
    {
        if ( AMFM2_OK == amfm2_tuning_freq( &amfm2, mem_station_freq[ n_cnt ], &rsp_status ) )
        {
            log_printf( &logger, " FM Station %d \r\nFrequency: %.2f MHz\r\n", 
                       ( uint16_t ) ( n_cnt + 1 ), mem_station_freq[ n_cnt ] );
            log_printf( &logger, "--------------------\r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AMFM2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
