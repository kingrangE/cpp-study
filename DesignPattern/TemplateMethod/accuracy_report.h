#pragma once
#include "report.h"
class AccuracyReport: public Report{
private:
    virtual void measure_record() override;
    virtual void write_record() override;
    virtual void write_result() override;
};