#ifndef _TSSP_PAT_SECTION_FILTER_IMPL_HPP_
#define _TSSP_PAT_SECTION_FILTER_IMPL_HPP_

#include "printer.hpp"

namespace tssp
{

void pat_section_filter::do_handle_section(
      context& c,
      const char* section_buffer,
      size_t section_length) {
  program_association_table pat;
  pat.unpack(section_buffer, section_length);

  printer<program_association_table> pri(std::cout);
  pri.print_json(pat, false);

  //DEBUG
  //cerr << "----- pat -----" << endl;
  //dump_section_header(pat.header);
  {
    auto i = pat.program_num_to_pid.begin();
    auto i_end = pat.program_num_to_pid.end();
    for(; i != i_end; ++i) {
      if(i->first != 0) {
        if(!c.is_opened(i->second)) {
          c.open_section_filter(
              i->second, std::unique_ptr<section_filter>(
                new pmt_section_filter()));
        }
      }
    }
  }
}

}


#endif
