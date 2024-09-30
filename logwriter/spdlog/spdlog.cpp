// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef SPDLOG_COMPILED_LIB
#error Please define SPDLOG_COMPILED_LIB to compile this file.
#endif

#include <logwriter/spdlog/spdlog-inl.h>
#include <logwriter/spdlog/common-inl.h>
#include <logwriter/spdlog/details/backtracer-inl.h>
#include <logwriter/spdlog/details/registry-inl.h>
#include <logwriter/spdlog/details/os-inl.h>
#include <logwriter/spdlog/pattern_formatter-inl.h>
#include <logwriter/spdlog/details/log_msg-inl.h>
#include <logwriter/spdlog/details/log_msg_buffer-inl.h>
#include <logwriter/spdlog/logger-inl.h>
#include <logwriter/spdlog/sinks/sink-inl.h>
#include <logwriter/spdlog/sinks/base_sink-inl.h>
#include <logwriter/spdlog/details/null_mutex.h>

#include <mutex>

// template instantiate logger constructor with sinks init list
template SPDLOG_API spdlog::logger::logger(std::string name, sinks_init_list::iterator begin, sinks_init_list::iterator end);
template class SPDLOG_API spdlog::sinks::base_sink<std::mutex>;
template class SPDLOG_API spdlog::sinks::base_sink<spdlog::details::null_mutex>;

