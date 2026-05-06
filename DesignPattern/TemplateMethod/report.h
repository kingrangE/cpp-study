#pragma once
#include <string>

class Report{
private:
    void write_header(const std::string& header);
    void send(const std::string& name);
    virtual void measure_record() = 0;
    virtual void write_record() = 0;
    virtual void write_result() = 0;
public:
    virtual ~Report() = default;
    void generate_report(const std::string& header, const std::string& name);
};