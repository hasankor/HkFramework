QT -= gui

QT += core network serialport

CONFIG += c++17 console

TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += SPDLOG_COMPILED_LIB

HEADERS += \
    Enums.h \
    config/settingsbase.h \
    healtchecker/healthchecker.h \
    languge/customtranslatorbase.h \
    listmodel/adata/alistmodeldata.h \
    listmodel/model/listmodel.h \
    logwriter/consolelogwriter.h \
    logwriter/logwriterbase.h \
    logwriter/rotatinglogwriter.h \
    logwriter/spdlog/async.h \
    logwriter/spdlog/async_logger-inl.h \
    logwriter/spdlog/async_logger.h \
    logwriter/spdlog/cfg/argv.h \
    logwriter/spdlog/cfg/env.h \
    logwriter/spdlog/cfg/helpers-inl.h \
    logwriter/spdlog/cfg/helpers.h \
    logwriter/spdlog/common-inl.h \
    logwriter/spdlog/common.h \
    logwriter/spdlog/details/backtracer-inl.h \
    logwriter/spdlog/details/backtracer.h \
    logwriter/spdlog/details/circular_q.h \
    logwriter/spdlog/details/console_globals.h \
    logwriter/spdlog/details/file_helper-inl.h \
    logwriter/spdlog/details/file_helper.h \
    logwriter/spdlog/details/fmt_helper.h \
    logwriter/spdlog/details/log_msg-inl.h \
    logwriter/spdlog/details/log_msg.h \
    logwriter/spdlog/details/log_msg_buffer-inl.h \
    logwriter/spdlog/details/log_msg_buffer.h \
    logwriter/spdlog/details/mpmc_blocking_q.h \
    logwriter/spdlog/details/null_mutex.h \
    logwriter/spdlog/details/os-inl.h \
    logwriter/spdlog/details/os.h \
    logwriter/spdlog/details/periodic_worker-inl.h \
    logwriter/spdlog/details/periodic_worker.h \
    logwriter/spdlog/details/registry-inl.h \
    logwriter/spdlog/details/registry.h \
    logwriter/spdlog/details/synchronous_factory.h \
    logwriter/spdlog/details/tcp_client-windows.h \
    logwriter/spdlog/details/tcp_client.h \
    logwriter/spdlog/details/thread_pool-inl.h \
    logwriter/spdlog/details/thread_pool.h \
    logwriter/spdlog/details/windows_include.h \
    logwriter/spdlog/fmt/bin_to_hex.h \
    logwriter/spdlog/fmt/bundled/chrono.h \
    logwriter/spdlog/fmt/bundled/color.h \
    logwriter/spdlog/fmt/bundled/compile.h \
    logwriter/spdlog/fmt/bundled/core.h \
    logwriter/spdlog/fmt/bundled/format-inl.h \
    logwriter/spdlog/fmt/bundled/format.h \
    logwriter/spdlog/fmt/bundled/locale.h \
    logwriter/spdlog/fmt/bundled/os.h \
    logwriter/spdlog/fmt/bundled/ostream.h \
    logwriter/spdlog/fmt/bundled/posix.h \
    logwriter/spdlog/fmt/bundled/printf.h \
    logwriter/spdlog/fmt/bundled/ranges.h \
    logwriter/spdlog/fmt/chrono.h \
    logwriter/spdlog/fmt/fmt.h \
    logwriter/spdlog/fmt/ostr.h \
    logwriter/spdlog/formatter.h \
    logwriter/spdlog/fwd.h \
    logwriter/spdlog/logger-inl.h \
    logwriter/spdlog/logger.h \
    logwriter/spdlog/pattern_formatter-inl.h \
    logwriter/spdlog/pattern_formatter.h \
    logwriter/spdlog/sinks/android_sink.h \
    logwriter/spdlog/sinks/ansicolor_sink-inl.h \
    logwriter/spdlog/sinks/ansicolor_sink.h \
    logwriter/spdlog/sinks/base_sink-inl.h \
    logwriter/spdlog/sinks/base_sink.h \
    logwriter/spdlog/sinks/basic_file_sink-inl.h \
    logwriter/spdlog/sinks/basic_file_sink.h \
    logwriter/spdlog/sinks/daily_file_sink.h \
    logwriter/spdlog/sinks/dist_sink.h \
    logwriter/spdlog/sinks/dup_filter_sink.h \
    logwriter/spdlog/sinks/hourly_file_sink.h \
    logwriter/spdlog/sinks/msvc_sink.h \
    logwriter/spdlog/sinks/null_sink.h \
    logwriter/spdlog/sinks/ostream_sink.h \
    logwriter/spdlog/sinks/ringbuffer_sink.h \
    logwriter/spdlog/sinks/rotating_file_sink-inl.h \
    logwriter/spdlog/sinks/rotating_file_sink.h \
    logwriter/spdlog/sinks/sink-inl.h \
    logwriter/spdlog/sinks/sink.h \
    logwriter/spdlog/sinks/stdout_color_sinks-inl.h \
    logwriter/spdlog/sinks/stdout_color_sinks.h \
    logwriter/spdlog/sinks/stdout_sinks-inl.h \
    logwriter/spdlog/sinks/stdout_sinks.h \
    logwriter/spdlog/sinks/syslog_sink.h \
    logwriter/spdlog/sinks/systemd_sink.h \
    logwriter/spdlog/sinks/tcp_sink.h \
    logwriter/spdlog/sinks/win_eventlog_sink.h \
    logwriter/spdlog/sinks/wincolor_sink-inl.h \
    logwriter/spdlog/sinks/wincolor_sink.h \
    logwriter/spdlog/spdlog-inl.h \
    logwriter/spdlog/spdlog.h \
    logwriter/spdlog/stopwatch.h \
    logwriter/spdlog/tweakme.h \
    logwriter/spdlog/version.h \
    logwriter/staticconsolelogwriter.h \
    serial/serialsenderreceiver.h \
    tcpclient/tcpclient.h \
    thread/athread.h \
    toastmanager/toastmanager.h \
    udp/asyncudpdatareceiver.h \
    udp/asyncudpdatasender.h \
    utils.h

SOURCES += \
        config/settingsbase.cpp \
        healtchecker/healthchecker.cpp \
        languge/customtranslatorbase.cpp \
        listmodel/adata/alistmodeldata.cpp \
        listmodel/model/listmodel.cpp \
        logwriter/consolelogwriter.cpp \
        logwriter/logwriterbase.cpp \
        logwriter/rotatinglogwriter.cpp \
        logwriter/spdlog/async.cpp \
        logwriter/spdlog/cfg.cpp \
        logwriter/spdlog/color_sinks.cpp \
        logwriter/spdlog/file_sinks.cpp \
        logwriter/spdlog/fmt.cpp \
        logwriter/spdlog/spdlog.cpp \
        logwriter/spdlog/stdout_sinks.cpp \
        logwriter/staticconsolelogwriter.cpp \
        serial/serialsenderreceiver.cpp \
        tcpclient/tcpclient.cpp \
        thread/athread.cpp \
        toastmanager/toastmanager.cpp \
        udp/asyncudpdatareceiver.cpp \
        udp/asyncudpdatasender.cpp \
        utils.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
