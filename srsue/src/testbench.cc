#include "srsue/hdr/testbench.h"

namespace srsue {
    void testbench::report_nas() { return; }
    void testbench::report_rrc() { return; }
    bool testbench::get_result() { return true; }


/* void nas::report_attach_result(bool is_attached, uint8_t originating_msg) {
  if (stack == nullptr) {
    nas_log->error("UE stack ptr not initialized.\n");
  }

  uint8_t _eia_caps{};
  uint8_t _eea_caps{};
  _eia_caps |= eia_caps[0] ? 0b0001 : 0;
  _eia_caps |= eia_caps[1] ? 0b0010 : 0;
  _eia_caps |= eia_caps[2] ? 0b0100 : 0;
  _eia_caps |= eia_caps[3] ? 0b1000 : 0;

  _eea_caps |= eea_caps[0] ? 0b0001 : 0;
  _eea_caps |= eea_caps[1] ? 0b0010 : 0;
  _eea_caps |= eea_caps[2] ? 0b0100 : 0;
  _eea_caps |= eea_caps[3] ? 0b1000 : 0;

  stack->report_attach_result(is_attached, originating_msg, _eia_caps, ctxt.integ_algo, _eea_caps, ctxt.cipher_algo);
} */

}