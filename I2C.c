
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_port.h"
#include "MK64F12.h"
#include "fsl_i2c.h"
#include "I2C.h"
#include "LEDs.h"
#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
//#include "fsl_pit.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */


//REVISAR EL DOCUMENTO 700CQ o algo asi. EN el IMU pagina 16

    i2c_master_transfer_t masterXfer;


    i2c_master_handle_t g_m_handle;
    uint8_t buffer[6];
    uint16_t accelerometer[3];

    volatile bool g_MasterCompletionFlag = false;

    static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle,
            status_t status, void * userData)
    {

    	if (status == kStatus_Success)
    	{
    		g_MasterCompletionFlag = true;
    	}
    }

void initI2C()
{

	/* Init board hardware. */
		BOARD_InitBootPins();
		BOARD_InitBootClocks();
		BOARD_InitBootPeripherals();
		/* Init FSL debug console. */
		BOARD_InitDebugConsole();

		CLOCK_EnableClock(kCLOCK_PortE);
		CLOCK_EnableClock(kCLOCK_I2c0);

		port_pin_config_t config_i2c =
		{ kPORT_PullDisable, kPORT_SlowSlewRate, kPORT_PassiveFilterDisable,
		        kPORT_OpenDrainDisable, kPORT_LowDriveStrength, kPORT_MuxAlt5,
		        kPORT_UnlockRegister, };

		PORT_SetPinConfig(PORTE, 24, &config_i2c);
		PORT_SetPinConfig(PORTE, 25, &config_i2c);

		i2c_master_config_t masterConfig;
		I2C_MasterGetDefaultConfig(&masterConfig);
		masterConfig.baudRate_Bps = 100000;
		I2C_MasterInit(I2C0, &masterConfig, CLOCK_GetFreq(kCLOCK_BusClk));

		i2c_master_handle_t g_m_handle;
		I2C_MasterTransferCreateHandle(I2C0, &g_m_handle,
		        i2c_master_callback, NULL);

		i2c_master_transfer_t masterXfer;


		uint8_t data_buffer = 0x01;

	#if 0
		masterXfer.slaveAddress = 0x1D;
		masterXfer.direction = kI2C_Write;
		masterXfer.subaddress = 0;
		masterXfer.subaddressSize = 0;
		masterXfer.data = &data_buffer;
		masterXfer.dataSize = 1;
		masterXfer.flags = kI2C_TransferNoStopFlag;

		I2C_MasterTransferNonBlocking(I2C0,  &g_m_handle,
		        &masterXfer);
		while (!g_MasterCompletionFlag){}
		g_MasterCompletionFlag = false;

		uint8_t read_data;

		masterXfer.slaveAddress = 0x1D;
		masterXfer.direction = kI2C_Read;
		masterXfer.subaddress = 0;
		masterXfer.subaddressSize = 0;
		masterXfer.data = &read_data;
		masterXfer.dataSize = 1;
		masterXfer.flags = kI2C_TransferRepeatedStartFlag;

		I2C_MasterTransferNonBlocking(I2C0, &g_m_handle,
		        &masterXfer);
		while (!g_MasterCompletionFlag){}
		g_MasterCompletionFlag = false;
	#else

		masterXfer.slaveAddress = 0x1D;
		masterXfer.direction = kI2C_Write;
		masterXfer.subaddress = 0x2A;
		masterXfer.subaddressSize = 1;
		masterXfer.data = &data_buffer;
		masterXfer.dataSize = 1;
		masterXfer.flags = kI2C_TransferDefaultFlag;

		I2C_MasterTransferNonBlocking(I2C0,  &g_m_handle,
		        &masterXfer);
		while (!g_MasterCompletionFlag){}
		g_MasterCompletionFlag = false;

	#endif
}

uint16_t getI2C()
{
	masterXfer.slaveAddress = 0x1D;
			masterXfer.direction = kI2C_Read;
			masterXfer.subaddress = 0x01;
			masterXfer.subaddressSize = 1;
			masterXfer.data = buffer;
			masterXfer.dataSize = 6;
			masterXfer.flags = kI2C_TransferDefaultFlag;

			I2C_MasterTransferNonBlocking(I2C0,  &g_m_handle,
					&masterXfer);
			while (!g_MasterCompletionFlag){}
			g_MasterCompletionFlag = false;

			accelerometer[0] = buffer[0]<<8 | buffer[1]; //x
			accelerometer[1] = buffer[2]<<8 | buffer[3]; //y
			accelerometer[2] = buffer[4]<<8 | buffer[5]; //z

			return accelerometer[2];
   }
