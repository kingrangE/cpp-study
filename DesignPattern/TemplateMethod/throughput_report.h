#pragma once
#include "report.h"
class ThroughputReport: public Report{
private:
    virtual void measure_record() override;
    virtual void write_record() override;
    virtual void write_result() override;
};