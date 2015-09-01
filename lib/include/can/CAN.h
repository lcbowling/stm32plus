#pragma once


namespace stm32plus {


  /**
   * Base class for all SPI peripherals. Supports synchronous sending and receiving of
   * data encoded into 8 or 16-bit values. The SPI peripheral on the F0 can be initialised
   * to send/receive bit streams that are no a multiple of 8.
   *
   * This class inherits from the very small device specifc IO class that handles the differences
   * in the ST peripheral library between devices.
   */

  class CAN {

    protected:
      CAN_TypeDef *_peripheralAddress;

    public:
      enum {
        E_CAN_ERROR = 1
      };

    protected:
      CAN(CAN_TypeDef *address);

    public:
      bool readyToReceive() const;

      bool receive(CanRxMsg* msg) const;

      bool readyToSend(uint8_t TransmitMailbox) const;
      bool send(CanTxMsg &msg, uint8_t &TransmitMailbox) const;

      void waitForIdle(uint8_t TransmitMailbox) const;

      operator CAN_TypeDef *() const;
      bool hasError() const;

      void deInit() const;
  };


  /**
   * Constructor
   * @param[in] address The peripheral address, e.g. SPI1
   * @param[in] nssPort The chip select port
   * @param[in] nssPin The chip select pin - we control it manually
   */

  inline CAN::CAN(CAN_TypeDef *address){
    _peripheralAddress=address;
  }


  /**
   * Cast this class to the SPI peripheral address.
   * @return The SPI peripheral address.
   */

  inline CAN::operator CAN_TypeDef *() const {
    return _peripheralAddress;
  }


  /**
   * Check if the device has an error status
   */

  inline bool CAN::hasError() const {

	  uint8_t status;

    if((status=CAN_GetLastErrorCode(_peripheralAddress)) != 0x00 )
      return !errorProvider.set(ErrorProvider::ERROR_PROVIDER_CAN,E_CAN_ERROR,status);

    return false;
  }


  /**
   * Check if the peripheral is ready to receive
   * @return true if it's ready
   */

  inline bool CAN::readyToReceive() const {
    return !!CAN_MessagePending(_peripheralAddress, CAN_FIFO0);
  }


  /**
   * Read a byte from the peripheral
   * @param byte[out] The byte read out
   */

  inline bool CAN::receive(CanRxMsg* msg) const {

    while(!readyToReceive())
      if(hasError())
        return false;

    CAN_Receive(_peripheralAddress, CAN_FIFO0, msg);
    return true;
  }


  /**
   * Check for TXE
   * @return true if ready to send
   */

  inline bool CAN::readyToSend(uint8_t TransmitMailbox) const {
    return (CAN_TransmitStatus(_peripheralAddress, TransmitMailbox) == CANTXOK);
  }


  /**
   * Send a single byte.
   * @param dataToSend The byte to send
   * @return true if it worked, false on error
   */

  inline bool CAN::send(CanTxMsg &msg, uint8_t &TransmitMailbox) const {

    // wait for ready to send

    if(hasError())
      return false;

    // send the byte

    TransmitMailbox = CAN_Transmit(_peripheralAddress, &msg);
    return true;
  }


  /**
   * Wait for the peripheral to become idle. If transmitting then the peripheral becomes
   * idle when the last word written to the TX register has been shifted out to the bus.
   */

  inline void CAN::waitForIdle(uint8_t TransmitMailbox) const {
	  while(CAN_TransmitStatus(_peripheralAddress, TransmitMailbox)  !=  CANTXOK);
  }

  inline void CAN::deInit() const {
	  CAN_DeInit(_peripheralAddress);
  }
}
