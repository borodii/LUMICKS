#pragma once
#include <string>

//Common interface for protocols that simulate different hardware devices' protocols
class IProtocol {
public:
  virtual ~IProtocol() = default;

  //Get input as ASCII-encoded string terminated by a line-end character and returns the emulated output from the device
  virtual std::string GetResponse(std::string i_command) const = 0;
};