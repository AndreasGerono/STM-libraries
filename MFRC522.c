//
// MFRC522.c
// Created by Andreas Gerono on 11/02/2020.

#include "MFRC522.h"


void MFRC522_WriteRegister(PCD_Register reg, uint8_t val);
void MFRC522_WriteRegisters(PCD_Register reg, uint8_t len, uint8_t* val);
uint8_t MFRC522_ReadRegister(PCD_Register reg);
void MFRC522_ReadRegisters(PCD_Register reg, uint8_t len, uint8_t *val);
void MFRC522_SetRegisterBitMask(PCD_Register reg, uint8_t mask);
void MFRC522_ClearRegisterBitMask(PCD_Register reg, uint8_t mask);


void MFRC522_init() {

	MFRC522_Reset();
	
	MFRC522_WriteRegister(TxModeReg, 0x00);	
	MFRC522_WriteRegister(RxModeReg, 0x00);	
	
	MFRC522_WriteRegister(ModWidthReg, 0x26);	
	MFRC522_WriteRegister(TModeReg, 0x80);	
	MFRC522_WriteRegister(TPrescalerReg, 0xA9);	
	MFRC522_WriteRegister(TReloadRegH, 0x03);	
	MFRC522_WriteRegister(TReloadRegL, 0xE8);	
	MFRC522_WriteRegister(TxASKReg, 0x40);	
	MFRC522_WriteRegister(ModeReg, 0x3D);	
	
	MFRC522_AntennaOn();
	
	
	
}


void MFRC522_Reset() {
	MFRC522_WriteRegister(CommandReg, PCD_SoftReset);
	//delay 50ms??
}


void MFRC522_AntennaOn() {
	MFRC522_SetRegisterBitMask(TxControlReg, 0x03);	//warning!
}

void MFRC522_AntennaOff() {
	MFRC522_ClearRegisterBitMask(TxControlReg, 0x03);
}

uint8_t MFRC522_GetAntennaGain() {
	return MFRC522_ReadRegister(RFCfgReg) & (0x07<<4);		
}


void MFRC522_SetAntennaGain(uint8_t gain) {
	MFRC522_ClearRegisterBitMask(RFCfgReg, (0x07<<4));
	MFRC522_SetRegisterBitMask(RFCfgReg, gain & (0x07<<4));
	
	
}


_Bool MFRC522_SelfTest(){
	
	//TODO
}

void MFRC522_SoftPowerDown(){
	MFRC522_SetRegisterBitMask(CommandReg, (1<<4));
}
void MFRC522_SoftPowerUp(){
	
	MFRC522_ClearRegisterBitMask(CommandReg, (1<<4));
	
	//delay?
}





StatusCode MFRC522_CalculateCRC(uint8_t *data, uint8_t len, uint8_t *result) {
	MFRC522_WriteRegister(CommandReg, PCD_Idle);		// Stop any active command.
	MFRC522_WriteRegister(DivIrqReg, 0x04);				// Clear the CRCIRq interrupt request bit
	MFRC522_WriteRegister(FIFOLevelReg, 0x80);			// FlushBuffer = 1, FIFO initialization
	MFRC522_WriteRegisters(FIFODataReg, len, data);	// Write data to the FIFO
	MFRC522_WriteRegister(CommandReg, PCD_CalcCRC);		// Start the calculation
	
	// Wait for the CRC calculation to complete. Each iteration of the while-loop takes 17.73μs.
	// TODO check/modify for other architectures than Arduino Uno 16bit

	// Wait for the CRC calculation to complete. Each iteration of the while-loop takes 17.73us.
	for (uint16_t i = 5000; i > 0; i--) {	//?? po co ten for?
		// DivIrqReg[7..0] bits are: Set2 reserved reserved MfinActIRq reserved CRCIRq reserved reserved
		uint8_t n = MFRC522_ReadRegister(DivIrqReg);
		if (n & 0x04) {									// CRCIRq bit set - calculation done
			MFRC522_WriteRegister(CommandReg, PCD_Idle);	// Stop calculating CRC for new content in the FIFO.
			// Transfer the result from the registers to the result buffer
			result[0] = MFRC522_ReadRegister(CRCResultRegL);
			result[1] = MFRC522_ReadRegister(CRCResultRegH);
			return STATUS_OK;
		}
	}
	// 89ms passed and nothing happend. Communication with the MFRC522 might be down.
	return STATUS_TIMEOUT;
} // End PCD_CalculateCRC()