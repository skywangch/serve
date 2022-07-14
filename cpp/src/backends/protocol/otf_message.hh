#ifndef TS_CPP_BACKENDS_PROTOCOL_OTF_MESSAGE_HH_
#define TS_CPP_BACKENDS_PROTOCOL_OTF_MESSAGE_HH_

#include <chrono>
#include <ctime>
#include <string>
#include <variant>
#include <vector>

#include "src/utils/message.hh"

namespace torchserve {
  using Socket = int;
  using StatusCode = int;
  typedef std::vector<std::byte> byte_buffer;

  //https://docs.python.org/3/library/struct.html#format-characters
  #define BOOL_STD_SIZE 1
  #define INT_STD_SIZE 4
  #define LOAD_MSG 'L'
  #define PREDICT_MSG 'I'

  #define LOG_CURRENT_TIMESTAMP() { \
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); \
    std::string timestr = std::ctime(&time); \
    return timestr; \
  }

  class OTFMessage {
    public:
    static byte_buffer CreateLoadModelResponse(StatusCode code, const std::string& message);
    static char RetrieveCmd(Socket conn); 
    static std::shared_ptr<LoadModelRequest> RetrieveLoadMsg(Socket conn);
    // TODO: impl.
    static std::vector<std::shared_ptr<InferenceRequest>> RetrieveInferenceMsg(Socket conn);
    
    private:
    static void RetrieveBuffer(Socket conn, size_t length, char *data);     
    static int RetrieveInt(Socket conn);
    static bool RetrieveBool(Socket conn);
  };
} // namespace torchserve
#endif // TS_CPP_BACKENDS_PROTOCOL_OTF_MESSAGE_HH_
