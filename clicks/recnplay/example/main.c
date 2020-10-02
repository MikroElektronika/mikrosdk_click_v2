/*!
 * \file 
 * \brief RecNPlay Click example
 * 
 * # Description
 * This application demonstrates the processof recording a message and playing it back.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI interface in proper mode and performs all the necessary commands to
 * put the device in proper working mode (chip reset, chip power up, chip erasing, clock configuration).
 * 
 * ## Application Task  
 * Performs the chip configuration for recording message via microphone, then records a message
 * for 8 seconds to specified memory location. After that, it reads the recorded message address with message length and then plays the
 * recorded message. When playback is done it erases the recorded message from memory. Afterwards, it repeats all the operations every 10 seconds.
 * 
 * *note:* 
 * The ISD3900 must be properly configured to work in record mode every time when user wants to record a message.
 * When user wants to play a recorded message, then ISD3900 must be properly configured, but now to work in play mode.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "recnplay.h"

// ------------------------------------------------------------------ VARIABLES

static recnplay_t recnplay;
static log_t logger;
static uint32_t msg_addr;
static uint16_t msg_len;
static uint8_t temp_var;
static uint8_t volume;
static RECNPLAY_RETVAL status_byte;
static uint8_t interr_byte;

static const uint8_t config_play_pwm_spk[ 32 ] = { 0x64, 0x00, 0x44, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x00, 0x57, 0x01, 0x57, 0x00, 0x00, 0xFF, 0x30, 0x02, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00 };
static const uint8_t config_play_aux_out[ 32 ] = { 0x64, 0x00, 0x48, 0x00, 0x40, 0x80, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x00, 0x57, 0x01, 0x57, 0x00, 0x00, 0xFF, 0x30, 0x02, 0xAB, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00 };
static const uint8_t config_rec_mic[ 32 ]      = { 0xA4, 0x80, 0x02, 0xFF, 0x0D, 0x40, 0x50, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x3E, 0x00, 0xD6, 0x00, 0xFF, 0xFF, 0x11, 0x82, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00 };


// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void wait_cmd_fin ( void )
{
	status_byte = recplay_read_status( &recnplay, &interr_byte );
	while ( ( interr_byte != RECPLAY_INT_CMD_FIN_MASK )
		 || ( status_byte != ( RECPLAY_STAT_DBUF_RDY_MASK
		  	                 | RECPLAY_STAT_INT_GEN_MASK ) ) )
	{
		status_byte = recplay_read_status( &recnplay, &interr_byte );
	}
	status_byte = recplay_read_interr( &recnplay, &interr_byte );
}

void wait_ready ( void )
{
	status_byte = recplay_read_status( &recnplay, &interr_byte );
	while ( status_byte != RECPLAY_STAT_DBUF_RDY_MASK )
	{
		status_byte = recplay_read_status( &recnplay, &interr_byte );
	}
	status_byte = recplay_read_interr( &recnplay, &interr_byte );
}

void wait_power_up ( void )
{
	status_byte = recplay_read_status( &recnplay, &interr_byte );
	while ( status_byte == RECPLAY_STAT_PWR_DOWN_MASK )
	{
		status_byte = recplay_read_status( &recnplay, &interr_byte );
	}
	status_byte = recplay_read_interr( &recnplay, &interr_byte );
}

void time_record ( uint32_t seconds_time )
{
	uint8_t cnt;
	for ( cnt = 0; cnt < seconds_time; cnt++ )
	{
		Delay_ms( 1000 );
		log_printf( &logger, ".\r\n" );
	}
}

void set_volume ( uint8_t volume_sel )
{
	uint16_t volume_res;

	if ( volume_sel > 100 )
	{
		volume = 0;
		log_printf( &logger, "Volume is: 100%\r\n" );
		return;
	}

	volume_res = 255 * volume_sel;
	volume_res /= 100;
	volume = 255 - volume_res;

	log_printf( &logger, "Volume is: %d%%\r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    recnplay_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    recnplay_cfg_setup( &cfg );
    RECNPLAY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    recnplay_init( &recnplay, &cfg );

    log_printf( &logger, "Chip reset...\r\n" );
	recplay_reset( &recnplay );
	log_printf( &logger, "Power up...\r\n" );
	recplay_pwr_up( &recnplay );
	wait_power_up( );
	log_printf( &logger, "Chip Erasing...\r\n" );
	recplay_erase_chip( &recnplay );
	wait_cmd_fin( );
	log_printf( &logger, "Clock Configuration...\r\n" );
	status_byte = recplay_set_clk_cnfg( &recnplay, 0x34 );
	volume = 0;
	Delay_ms( 1000 );
}

void application_task ( void )
{
    uint8_t cnt;
    log_printf( &logger, "Preparing to record a message\r\n" );
	for ( cnt = 0; cnt < 32; cnt++ )
	{
		if ( ( cnt != RECPLAY_CFG0A_REG ) && ( cnt != RECPLAY_CFG1C_REG ) &&
			 ( cnt != RECPLAY_CFG1E_REG ) )
		{
			wait_ready( );
			temp_var = config_rec_mic[ cnt ];
			status_byte = recplay_write_cnfg_reg( &recnplay, cnt, &temp_var, 1 );
		}
	}
	wait_ready( );
	Delay_ms( 2000 );

	log_printf( &logger, "Message recording\r\n" );
	status_byte = recplay_record_msg_addr( &recnplay, 0x12000 );
	time_record( 8 );
	status_byte = recplay_stop( &recnplay );
	wait_cmd_fin( );
	log_printf( &logger, "End of recording\r\n" );

	status_byte = recplay_read_msg_addr( &recnplay, &msg_addr, &msg_len );
	log_printf( &logger, "Message Address: 0x%x\r\n", msg_addr );
	log_printf( &logger, "Message Length: %d\r\n", msg_len );
	Delay_ms( 1000 );

	log_printf( &logger, "Preparing to play a message\r\n" );
	set_volume( 100 );
	for ( cnt = 0; cnt < 32; cnt++ )
	{
		if ( ( cnt != RECPLAY_CFG0A_REG ) && ( cnt != RECPLAY_CFG1C_REG )
		  && ( cnt != RECPLAY_CFG1E_REG ) )
		{
			wait_ready( );

			if ( cnt == RECPLAY_CFG03_REG )
			{
				temp_var = volume;
			}
			else
			{
				temp_var = config_play_pwm_spk[ cnt ];
			}
			status_byte = recplay_write_cnfg_reg( &recnplay, cnt, &temp_var, 1 );
		}
	}

	wait_ready( );
	Delay_ms( 2000 );

	log_printf( &logger, "Message is playing...\r\n" );
	status_byte = recplay_play_msg( &recnplay, 0x12000, 0 );
	wait_cmd_fin( );
	log_printf( &logger, "End of playing...\r\n" );


	log_printf( &logger, "Status Byte: 0x%x\r\n", status_byte );
	log_printf( &logger, "Interrupt byte: 0x%x\r\n", interr_byte );
	Delay_ms( 1000 );

	log_printf( &logger, "Message erasing...\r\n" );
	status_byte = recplay_erase_msg( &recnplay, 0x12000 );
	wait_cmd_fin( );
	log_printf( &logger, "End of erasing\r\n" );

	Delay_ms( 10000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
