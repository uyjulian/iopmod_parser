#include <idc.idc>
static main(void) {
set_inf_attr(INF_COMPILER, COMP_GNU);
ParseTypes("./typedefs.h", PT_FILE);
qexit(0);
}
