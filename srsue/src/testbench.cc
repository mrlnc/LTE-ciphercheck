#include "srsue/hdr/testbench.h"

namespace srsue {
testbench::testbench(srslte::log_filter* _log) : current_testcase_id(0), log(_log) {}
testbench::~testbench()
{
  log->debug("DTOR called\n");
  for (auto t : testcases) {
    delete t.second;
  }
}

uint testbench::start_testcase(uint8_t _eia_mask, uint8_t _eea_mask)
{
  current_testcase_id += 1;
  log->info("New Testcase %i with EIA %s EEA %s\n",
            current_testcase_id,
            std::bitset<8>(_eia_mask).to_string().c_str(),
            std::bitset<8>(_eea_mask).to_string().c_str());
  testcases[current_testcase_id] = new testcase(log, current_testcase_id, _eia_mask, _eea_mask);
  return current_testcase_id;
}

bool testbench::get_result()
{
  return true;
}

bool testbench::is_finished()
{
    auto tc = testcases[current_testcase_id];
    if (tc != nullptr) {
        return tc->is_finished();
    }
    return false;
}

/* NAS interface */
void testbench::report_nas(){

};

void testbench::report_attach_accept()
{
  auto tc = testcases[current_testcase_id];
  if (tc != nullptr) {
    tc->report_attach_accept();
  }
};

void testbench::report_attach_reject(uint8_t _cause)
{
  auto tc = testcases[current_testcase_id];
  if (tc != nullptr) {
    tc->report_attach_reject(_cause);
  }
};

void testbench::report_nas_security_code_command(uint8_t _eia, uint8_t _eea)
{
  auto tc = testcases[current_testcase_id];
  if (tc != nullptr) {
    tc->report_nas_security_code_command(_eia, _eea);
  }
};

/* RRC interface */
void testbench::report_rrc(){

};

testbench::testcase::testcase(srslte::log_filter* _log, uint _id, uint8_t _eia_mask, uint8_t _eea_mask)
{
  log = _log;
  id  = _id;
  for (uint i = 0; i < 8; i++) {
    eia_caps[i] = (_eia_mask & (0b1 << i)) != 0;
    eea_caps[i] = (_eia_mask & (0b1 << i)) != 0;
  }
  /*     eia_caps |= eia_caps[0] ? 0b0001 : 0;
      eia_caps |= eia_caps[1] ? 0b0010 : 0;
      eia_caps |= eia_caps[2] ? 0b0100 : 0;
      eia_caps |= eia_caps[3] ? 0b1000 : 0;

      eea_caps |= eea_caps[0] ? 0b0001 : 0;
      eea_caps |= eea_caps[1] ? 0b0010 : 0;
      eea_caps |= eea_caps[2] ? 0b0100 : 0;
      eea_caps |= eea_caps[3] ? 0b1000 : 0; */
};

bool testbench::testcase::is_finished()
{
    return got_attach_accept || got_attach_reject;
}

void testbench::testcase::report_nas(){};
void testbench::testcase::report_attach_accept(){
    log->info("Testcase %u got Attach Accept\n", id);
    got_attach_accept = true;
};
void testbench::testcase::report_attach_reject(uint8_t _cause){
    log->info("Testcase %u got Attach Reject, cause: %u\n", id, _cause);
    got_attach_reject = true;
};
void testbench::testcase::report_nas_security_code_command(uint8_t _eia, uint8_t _eea){
    log->info("Testcase %u got NAS Security Mode Command\n", id);
    eia = _eia;
    eea = _eea;
    got_nas_security_mode_command = true;
};

} // namespace srsue