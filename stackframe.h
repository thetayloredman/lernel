#pragma once

struct stackframe {
    struct stackframe *ebp;
    uint32_t eip;
};
