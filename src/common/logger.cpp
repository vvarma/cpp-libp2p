/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <libp2p/common/logger.hpp>

#include <boost/scoped_ptr.hpp>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace {
    void setGlobalPattern(spdlog::logger &logger) {
        logger.set_pattern("[%Y-%m-%d %H:%M:%S.%F] %n %v");
    }

    void setDebugPattern(spdlog::logger &logger) {
        logger.set_pattern("[%Y-%m-%d %H:%M:%S.%F][th:%t][%l] %n %v");
    }

    std::shared_ptr<spdlog::logger> createLogger(const std::string &tag,
                                                 bool debug_mode = true) {
        auto logger = spdlog::default_logger()->clone(tag);
        if (debug_mode) {
            setDebugPattern(*logger);
        } else {
            setGlobalPattern(*logger);
        }
        return logger;
    }
}  // namespace

namespace libp2p::common {
    Logger createLogger(const std::string &tag) {
        static std::mutex mutex;
        std::lock_guard<std::mutex> lock(mutex);
        auto logger = spdlog::get(tag);
        if (logger == nullptr) {  // NOLINT
            logger = ::createLogger(tag);
        }
        return logger;
    }

    void registerDefaultLogger(std::vector<spdlog::sink_ptr> sinks) {
        if (sinks.empty()) {
            auto logger = spdlog::stderr_color_mt("libp2p");
            spdlog::set_default_logger(logger);
        } else {
            auto logger = std::make_shared<spdlog::logger>("libp2p", sinks.begin(), sinks.end());
            spdlog::set_default_logger(logger);
        }
    }
}  // namespace libp2p::common
