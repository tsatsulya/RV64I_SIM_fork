add_module(logger)
target_link_libraries(logger PUBLIC Boost::log)
target_sources(logger PRIVATE src/logger.cpp)
