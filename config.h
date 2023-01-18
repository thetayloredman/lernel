#pragma once

// https://patorjk.com/software/taag/ font: Big

#define LERNEL_VERSION "0.1"

/*
                    _          __
                   (_)        / /
  _ __   __ _ _ __  _  ___   / /__   ___  _ __  ___
 | '_ \ / _` | '_ \| |/ __| / / _ \ / _ \| '_ \/ __|
 | |_) | (_| | | | | | (__ / / (_) | (_) | |_) \__ \
 | .__/ \__,_|_| |_|_|\___/_/ \___/ \___/| .__/|___/
 | |                                     | |
 |_|                                     |_|
*/

// When we panic(), should we dump all registers to output? This can be needlessly verbose if not debugging
// Enabling this or LERNEL_OOPS_DUMP_REGISTERS compiles in the register dump capability in panic.c
#define LERNEL_PANIC_DUMP_REGISTERS

// When we oops(), should we dump all registers to output? This can be needlessly verbose if not debugging
// Enabling this or LERNEL_PANIC_DUMP_REGISTERS compiles in the register dump capability in panic.c
#define LERNEL_OOPS_DUMP_REGISTERS

// When we panic(), should we dump the stack trace to output? This can be needlessly verbose if not debugging
// Enabling this or LERNEL_OOPS_DUMP_STACK compiles in the stack trace dump capability in panic.c
#define LERNEL_PANIC_DUMP_STACK

// When we oops(), should we dump the stack trace to output? This can be needlessly verbose if not debugging
// Enabling this or LERNEL_PANIC_DUMP_STACK compiles in the stack trace dump capability in panic.c
#define LERNEL_OOPS_DUMP_STACK

// When we dump stack, how many stack frames do we display?
// Must be >1
// Only useful if LERNEL_PANIC_DUMP_STACK or LERNEL_OOPS_DUMP_STACK is enabled
#define LERNEL_STACK_DUMP_LIMIT 5

// When we dump stack, should we attempt to resolve symbols?
// Only useful if LERNEL_PANIC_DUMP_STACK or LERNEL_OOPS_DUMP_STACK is enabled
// Requires the LERNEL_KSYMS_ENABLED facility to be enabled
#define LERNEL_STACK_DUMP_RESOLVE_SYMBOLS

/*
  _                        _    __           _ _ _ _   _
 | |                      | |  / _|         (_) (_) | (_)
 | | _____ _ __ _ __   ___| | | |_ __ _  ___ _| |_| |_ _  ___  ___ 
 | |/ / _ \ '__| '_ \ / _ \ | |  _/ _` |/ __| | | | __| |/ _ \/ __|
 |   <  __/ |  | | | |  __/ | | || (_| | (__| | | | |_| |  __/\__ \
 |_|\_\___|_|  |_| |_|\___|_| |_| \__,_|\___|_|_|_|\__|_|\___||___/
*/

// Do we enable ksyms (symbol table mapping from Multiboot/the ELF table)?
// This is required for LERNEL_STACK_DUMP_RESOLVE_SYMBOLS
#define LERNEL_KSYMS_ENABLED

// must be at end of file
#include <config-validator.h>