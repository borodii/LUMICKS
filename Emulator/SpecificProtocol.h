#pragma once

#include "IProtocol.h"

class IController;

/**
 * Implements a specific text-based protocol that simulates a specific hardware devices.\n
 * [Details...](InternalDocumentation\...\Protocols\RS232.pdf)
 * \image html Images\RS232.png
 */
class SpecificProtocol : public IProtocol {
public:
  explicit SpecificProtocol(IController& i_controller);
  ~SpecificProtocol() = default;

  SpecificProtocol(const SpecificProtocol& i_other) = delete;
  SpecificProtocol& operator=(const SpecificProtocol& i_other) = delete;

  virtual std::string GetResponse(std::string i_command) const override;

private:
  IController& m_controller;
};