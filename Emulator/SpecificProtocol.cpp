#include "SpecificProtocol.h"
#include "IController.h"

SpecificProtocol::SpecificProtocol(IController& i_controller)
  : m_controller(i_controller)
{
}

std::string SpecificProtocol::GetResponse(std::string i_command) const
{
  int value = -1;
  if (m_controller.IsSillyMode())
    std::reverse(i_command.begin(), i_command.end());

  auto pos = i_command.find("|");
  if (pos != std::string::npos)
  {
    value = std::stoi(i_command.substr(pos + 1));
    i_command = i_command.substr(0, pos);
  }

  if (i_command == "STR")
  {
    if (m_controller.StartEmission())
      return "STR#\n";
  }
  else if (i_command == "STP")
  {
    if (m_controller.StopEmission())
      return "STP#\n";
  }
  else if (i_command == "ST?")
  {
    auto status = m_controller.GetEmissionStatus();
    return "ST?#" + std::to_string(status) + "|\n";
  }
  else if (i_command == "KAL")
  {
    if (m_controller.KeepSignalAlive())
      return "KAL#\n";
  }
  else if (i_command == "PW?")
  {
    auto laser_power = m_controller.GetLaserPower();
    if (laser_power !=-1)
      return "PW?|" + std::to_string(laser_power) + "#\n";
  }
  else if (i_command == "PW=")
  {
    if(value != -1)
      if (m_controller.SetLaserPower(value))
        return "PW=#\n";
  }
  else if (i_command == "ESM")
  {
    if (m_controller.EnableSillyMode())
      return "ESM#\n";
  }
  else if (i_command == "DSM")
  {
    if (m_controller.DisableSillyMode())
      return "DSM#\n";
  }
  else
  {
    return "UK!\n";
  }

  return i_command + "!\n";
}
