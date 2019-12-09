#ifndef SRSUE_TESTBENCH_H
#define SRSUE_TESTBENCH_H

#include "srslte/common/log_filter.h"
#include "srslte/interfaces/ue_interfaces.h"
#include <bitset>
#include <map>

namespace srsue {

/* testbench: collect the results of all testcases
 */
class testbench : public testbench_interface_stack, public testbench_interface_nas, public testbench_interface_rrc
{
protected:
  /* testcase: results of an individual testcase
   */
  class testcase
  {
    uint id;
    /* starts with ExA0. indices 4 to 7 are spare bits */
    bool eia_caps[8] = {};
    bool eea_caps[8] = {};

    uint8_t eia = 0;
    uint8_t eea = 0;

    srslte::log_filter* log;

    /* NAS */
    bool got_nas_security_mode_command = false;
    bool got_attach_accept             = false;
    bool got_attach_reject             = false;

    /* RRC */
    bool got_rrc_security_mode_command = false;

  public:
    testcase(srslte::log_filter* _log, uint _id, uint8_t _eia_mask, uint8_t _eea_mask);

    /* stack */
    bool is_finished();

    /* NAS */
    void report_nas();
    void report_attach_accept();
    void report_attach_reject(uint8_t _cause);
    void report_nas_security_code_command(uint8_t eia, uint8_t eea);
  };

  uint                                        current_testcase_id; // TODO locking
  std::map<uint /* testcase id */, testcase*> testcases;           // TODO locking

  srslte::log_filter* log;

public:
  testbench(srslte::log_filter* _log);
  ~testbench();

  /* registers new testcase; returns testcase ID */
  uint start_testcase(uint8_t _eia_mask, uint8_t _eea_mask);

  /* stack / main() interface */
  bool get_result();
  bool is_finished();

  /* NAS interface */
  void report_nas();
  void report_attach_accept();
  void report_attach_reject(uint8_t _cause);
  void report_nas_security_code_command(uint8_t eia, uint8_t eea);

  /* RRC interface */
  void report_rrc();
};

} // namespace srsue

#endif // SRSUE_TESTBENCH_H