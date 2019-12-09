#ifndef SRSUE_TESTBENCH_H
#define SRSUE_TESTBENCH_H

#include <map>
#include "srslte/interfaces/ue_interfaces.h"

namespace srsue {

/* testbench: collect the results of all testcases
 */
class testbench : public testbench_interface_stack, public testbench_interface_nas, public testbench_interface_rrc {
private:

    /* testcase: results of an individual testcase
     */
    class testcase {
        /* starts with ExA0. indices 4 to 7 are spare bits */
        bool eia_caps[8] = {};
        bool eea_caps[8] = {};

        testcase() {};
    };

    std::map<uint16_t, testcase* > testcases;

public:
    testbench() {};

    /* stack / main() interface */
    bool get_result();

    /* NAS interface */
    void report_nas();
/*     void report_attach_complete() = 0;
    void report_attach_reject() = 0;
    void report_security_code_command() = { return; }; */

    /* RRC interface */
    void report_rrc();
};

}

#endif // SRSUE_TESTBENCH_H