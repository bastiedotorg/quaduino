
#ifndef COM_HPP
#define COM_HPP


//ReadFromXlane(MESSAGE_ID_TYPE msg_id, LANE_ID_TYPE lane_id, MESSAGE_TYPE* pMessage, ERROR_CODE_TYPE* pError_code)
//*pMessage = "asdasd"
//ReadFromXlane(1, 2, &message, &returncode)

union nachricht{
  
  struct {
    unsigned int einAus;
  };
  char statusB[2];
  
};

nachricht initalizeMsg(unsigned int payload);

int sendMsg(unsigned int payload);

int readMsg(int ModulId);

void rs485Init();

#endif
