\mainpage Main Page

---
# AudioAmp 8 click

> AudioAmp 8 Click is a compact add-on board that reproduces input audio signal at sound-producing output elements, with desired volume and power levels. This board features the MA12070, a super-efficient audio power amplifier from Infineon Technologies. This I2C configurable audio amplifier is based on proprietary multi-level switching technology, enabling low power loss during operation. It supports a supply voltage range from 4 to 26V, allowing it to be used in many applications. Besides, it is equipped with protection features, allowing a reliable operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/audioamp8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/audioamp-8-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the AudioAmp8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AudioAmp8 Click driver.

#### Standard key functions :

- `audioamp8_cfg_setup` Config Object Initialization function.
```c
void audioamp8_cfg_setup ( audioamp8_cfg_t *cfg );
```

- `audioamp8_init` Initialization function.
```c
err_t audioamp8_init ( audioamp8_t *ctx, audioamp8_cfg_t *cfg );
```

- `audioamp8_default_cfg` Click Default Configuration function.
```c
err_t audioamp8_default_cfg ( audioamp8_t *ctx );
```

#### Example key functions :

- `audioamp8_set_config_power_mode` AudioAmp 8 set power mode configuration function.
```c
err_t audioamp8_set_config_power_mode ( audioamp8_t *ctx, audioamp8_pwr_mon_cfg_t pwr_mode );
```

- `audioamp8_set_config_power_mode_profile` AudioAmp 8 set power mode profile configuration function.
```c
err_t audioamp8_set_config_power_mode_profile ( audioamp8_t *ctx, audioamp8_pwr_mod_profile_cfg_t pm_profile );
```

- `audioamp8_channel_monitoring` AudioAmp 8 monitors the status of the channel's function.
```c
err_t audioamp8_channel_monitoring ( audioamp8_t *ctx, uint8_t mon_ch, audioamp8_monitor_channel_t *ch_mon );
```

## Example Description

> This library contains API for AudioAmp 8 Click driver.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers. 

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C  module, log UART, and additional pins. 
> After the driver init and then executes a default configuration, 
> the app performs a BTL signal configuration, configure power mode
> and configure power mode profile.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    audioamp8_cfg_t audioamp8_cfg;  /**< Click config object. */

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
    audioamp8_cfg_setup( &audioamp8_cfg );
    AUDIOAMP8_MAP_MIKROBUS( audioamp8_cfg, MIKROBUS_1 );
    err_t init_flag = audioamp8_init( &audioamp8, &audioamp8_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( AUDIOAMP8_ERROR == audioamp8_default_cfg ( &audioamp8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 1000 );
}

```

### Application Task

> This is an example that shows the use of a AudioAmp 8 Click board™.
> Display status monitoring for the channel 0 or channel 1.
> This task repeats every 2 seconds.

```c

void application_task ( void ) 
{
    channel_status_monitoring( AUDIOAMP8_SET_MON_CH_0 );
    Delay_ms( 1000 );
}

```

## Additional Function
- `channel_status_monitoring` The function displays the status monitoring channel.
```c
static void channel_status_monitoring ( uint8_t ch_sel );
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
