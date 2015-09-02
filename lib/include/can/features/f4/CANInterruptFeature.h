#pragma once


/*
 * Forward declare the IRQ handler names
 */
extern "C" void CAN1_RX0_IRQHandler(void);
extern "C" void CAN1_TX_IRQHandler(void);

extern "C" void CAN2_RX0_IRQHandler();
extern "C" void CAN2_TX_IRQHandler();


namespace stm32plus {

  /**
   * Helper class to enable only the desired interrupts in the NVIC. This will
   * be fully specialised for each CAN peripheral
   * @tparam TCANNumber The number of the CAN peripheral (1..2)
   */

  template<uint8_t TCANNumber>
  class CANInterruptFeatureEnabler {

    private:
      typedef void (*FPTR)();         // this trick will force the linker to include the ISR
      static FPTR _forceLinkageRX0;
      static FPTR _forceLinkageTX;

    public:
      static void enableRX(uint8_t priority,uint8_t subPriority);
      static void enableTX(uint8_t priority,uint8_t subPriority);
  };


  /**
   * SPI feature to handle interrupts.
   * @tparam TCANNumber The number of the CAN peripheral (1..5)
   */

  template<uint8_t TCANNumber>
  class CANInterruptFeature : public CANEventSource,
                              public CANFeatureBase {

    protected:
      uint16_t _interruptMask;
      uint8_t _nvicPriority;
      uint8_t _nvicSubPriority;

    public:
      static CANEventSource *_canInstance;

    public:
      CANInterruptFeature(_CAN& can);
      ~CANInterruptFeature();

      void setNvicPriorities(uint8_t priority,uint8_t subPriority=0);

      void enableInterrupts(uint16_t interruptMask);
      void disableInterrupts(uint16_t interruptMask);

      void clearPendingInterruptsFlag(uint16_t interruptMask) const;
  };


  /**
   * Typedefs for easy use
   */

  typedef CANInterruptFeature<1> CAN1InterruptFeature;


  /**
   * Template static data member initialisation
   */

  template<uint8_t TCANNumber>
  CANEventSource *CANInterruptFeature<TCANNumber> ::_canInstance;


  /**
   * Constructor, initialises the interrupt mask for this class to zero.
   */

  template<uint8_t TCANNumber>
  inline CANInterruptFeature<TCANNumber>::CANInterruptFeature(_CAN& can)
    : CANFeatureBase(can) {
    _interruptMask=0;
    _nvicPriority=_nvicSubPriority=0;
    _canInstance=this;
  }


  /**
   * Destructor, if any interrupts are configured for this class then
   * disable them so that ISR calls don't disappear off into nothing
   */

  template<uint8_t TCANNumber>
  inline CANInterruptFeature<TCANNumber>::~CANInterruptFeature() {
    if(_interruptMask!=0)
      disableInterrupts(_interruptMask);
  }


  /**
   * Set the NVIC priority and subpriority numbers.  This function just remembers your
   * numbers. The actual setting of the priority happens in enableInterrupts()
   * @param priority
   * @param subPriority
   */

  template<uint8_t TCANNumber>
  inline void CANInterruptFeature<TCANNumber>::setNvicPriorities(uint8_t priority,uint8_t subPriority) {
    _nvicPriority=priority;
    _nvicSubPriority=subPriority;
  }


  /**
   * Enable the interrupts specified in the mask
   * @param interruptMask The bitmask of interrupts, e.g. CAN_IT_FMP0 / CAN_IT_FMP1 / CAN_IT_TME
   */

  template<uint8_t TCANNumber>
  inline void CANInterruptFeature<TCANNumber>::enableInterrupts(uint16_t interruptMask) {

    _interruptMask|=interruptMask;

    CANInterruptFeatureEnabler<TCANNumber>::enableTX(_nvicPriority,_nvicSubPriority);
    CANInterruptFeatureEnabler<TCANNumber>::enableRX(_nvicPriority,_nvicSubPriority);

    CAN_ITConfig(_can, interruptMask, ENABLE);
  }


  /**
   * Disable the interrupts specified in the mask
   * @param interruptMask The bitmask of interrupts, e.g. CAN_IT_FMP0 / CAN_IT_FMP1 / CAN_IT_TME
   */

  template<uint8_t TCANNumber>
  inline void CANInterruptFeature<TCANNumber>::disableInterrupts(uint16_t interruptMask) {
    _interruptMask&=~interruptMask;
    CAN_ITConfig(_can, interruptMask, DISABLE);
  }


  /**
   * Clear the selected pending interrupt flags
   * @param interruptMask The bitmask of interrupts, e.g. CAN_IT_TME
   */

  template<uint8_t TCANNumber>
  inline void CANInterruptFeature<TCANNumber>::clearPendingInterruptsFlag(uint16_t interruptMask) const {
	  CAN_ClearITPendingBit(_can,interruptMask);
  }


  /**
   * Enabler specialisation, CAN 1
   */

  template<>
  inline void CANInterruptFeatureEnabler<1>::enableRX(uint8_t priority,uint8_t subPriority) {
      _forceLinkageRX0=&CAN1_RX0_IRQHandler;
      Nvic::configureIrq(CAN1_RX0_IRQn,ENABLE,priority,subPriority);
  }

  template<>
  inline void CANInterruptFeatureEnabler<1>::enableTX(uint8_t priority,uint8_t subPriority) {
      _forceLinkageTX=&CAN1_TX_IRQHandler;
      Nvic::configureIrq(CAN1_TX_IRQn,ENABLE,priority,subPriority);
  }

    

  template<>
  inline void CANInterruptFeatureEnabler<2>::enableRX(uint8_t priority,uint8_t subPriority) {
      _forceLinkageRX0=&CAN2_RX0_IRQHandler;
      Nvic::configureIrq(CAN2_RX0_IRQn,ENABLE,priority,subPriority);
  }

  template<>
  inline void CANInterruptFeatureEnabler<2>::enableTX(uint8_t priority,uint8_t subPriority) {
      _forceLinkageTX=&CAN2_TX_IRQHandler;
      Nvic::configureIrq(CAN2_TX_IRQn,ENABLE,priority,subPriority);

  }
}
