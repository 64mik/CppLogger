#ifndef MLOG_H
#define MLOG_H
#include "logger.h"
#define MLOG MLOG_INFO //추후 콜백으로 변경 예정
#define MLOG_INFO mik64::Logger::Wrapper(mik64::Logger::LogLevel::L_INFO, __FUNCTION__, __LINE__)
#define MLOG_WARNING mik64::Logger::Wrapper(mik64::Logger::LogLevel::L_WARNING, __FUNCTION__, __LINE__)
#define MLOG_ERROR mik64::Logger::Wrapper(mik64::Logger::LogLevel::L_ERROR, __FUNCTION__, __LINE__)
#endif // MLOG_H