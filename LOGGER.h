#pragma once
#ifndef LOGGER_
#define LOGGER_

#include "spdlog/spdlog.h"

#define SPDLOG_TRACE(logger,...) (logger->should_log(level::trace))?logger->trace("{}::{}()#{}: ",__FILE__,__FUNCTION__,__LINE__,fmt::format(__VA_ARGS)):(void)0)
#define SPDLOG_CRITICAL(logger,...) (logger->should_log(level::critical))?logger->critical("{}::{}()#{}: ",__FILE__,__FUNCTION__,__LINE__,fmt::format(__VA_ARGS)):(void)0)
#define SPDLOG_INFO(logger,...) (logger->should_log(level::info))?logger->info("{}::{}()#{}: ",__FILE__,__FUNCTION__,__LINE__,fmt::format(__VA_ARGS)):(void)0)


#endif