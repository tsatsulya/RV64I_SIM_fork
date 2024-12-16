#include <chrono>
#include <string>
#include <sstream>

#include "CLI/CLI.hpp"
#include "executor.hpp"
#include "hart.hpp"
#include "logger.hpp"

int main(int argc, char **argv) {
    CLI::App app{"RISV RV64_I simulator"};
    std::string elf_file;
    app.add_option("-f,--file", elf_file, "Required RISC-V elf file")
        ->required()
        ->check(CLI::ExistingFile);

    Logger::severity_level log_level;
    app.add_option("-l,--log_severity", log_level,
                   "Sets log level:\n"
                   "\t0: standard\n"
                   "\t1: verbose\n"
                   "default = standard")
        ->default_val(Logger::severity_level::standard)
        ->check(CLI::Range(Logger::severity_level::standard, Logger::severity_level::verbose));

    CLI11_PARSE(app, argc, argv);

    Logger &myLogger = Logger::getInstance();
    myLogger.init(log_level);
    myLogger.message(Logger::standard, "main", "RISV RV64_I simulator");

    sim::Hart hart{elf_file};

    size_t instr_counter = 0;

    const auto begin = std::chrono::steady_clock::now();
    sim::Executor::run(hart, instr_counter);
    const auto end = std::chrono::steady_clock::now();

    auto time = static_cast<std::chrono::duration<double>>(end - begin).count();

    myLogger.message(Logger::standard, "main", std::to_string(time) + " seconds");
    myLogger.message(Logger::standard, "main", std::to_string(instr_counter) + " instructions");

    auto ips = instr_counter / time;
    myLogger.message(Logger::standard, "main", std::to_string(ips) + " instr per second");

}
