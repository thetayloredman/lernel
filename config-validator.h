#pragma once

// #include this file at the end of config.h

#if defined(LERNEL_PANIC_DUMP_STACK) && !defined(LERNEL_STACK_DUMP_LIMIT)
#error "LERNEL_DUMP_STACK requires LERNEL_PANIC_STACK_DUMP_LIMIT"
#endif

#if defined(LERNEL_OOPS_DUMP_STACK) && !defined(LERNEL_STACK_DUMP_LIMIT)
#error "LERNEL_OOPS_DUMP_STACK requires LERNEL_STACK_DUMP_LIMIT"
#endif

#if defined(LERNEL_STACK_DUMP_LIMIT) && LERNEL_STACK_DUMP_LIMIT <= 0
#error "LERNEL_STACK_DUMP_LIMIT must be > 0"
#endif

#if defined(LERNEL_STACK_DUMP_RESOLVE_SYMBOLS) && !defined(LERNEL_KSYMS_ENABLED)
#error "LERNEL_STACK_DUMP_RESOLVE_SYMBOLS requires LERNEL_KSYMS_ENABLED"
#endif
