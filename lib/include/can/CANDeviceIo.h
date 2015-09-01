#pragma once

// ensure the MCU series is correct
#ifndef STM32PLUS_F4
#error This class can only be used with the STM32F4 series
#endif


namespace stm32plus {

  /*
   * Methods for sending and receiving 8 and 16-bit data. These are the same on the F4
   */

  struct CANDeviceIo {

    /*
     * Senders
     */

	uint8_t sendData(CAN_TypeDef *peripheralAddress,CanTxMsg &data) const {
      return CAN_Transmit(peripheralAddress, &data);
    }

    /*
     * Receivers
     */

    void receiveData(CAN_TypeDef *peripheralAddress, uint8_t FIFONumber, CanRxMsg* msg) const {
      return CAN_Receive(peripheralAddress, FIFONumber, msg);
    }
  };
}
