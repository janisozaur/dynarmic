/* This file is part of the dynarmic project.
 * Copyright (c) 2018 MerryMage
 * This software may be used and distributed according to the terms of the GNU
 * General Public License version 2 or any later version.
 */

#include "frontend/A64/translate/impl/impl.h"

namespace Dynarmic::A64 {

bool TranslatorVisitor::EXT(bool Q, Vec Vm, Imm<4> imm4, Vec Vn, Vec Vd) {
    if (!Q && imm4.Bit<3>()) {
        return UnallocatedEncoding();
    }

    const size_t datasize = Q ? 128 : 64;
    const size_t position = imm4.ZeroExtend<size_t>() << 3;

    const IR::U128 lo = V(datasize, Vn);
    const IR::U128 hi = V(datasize, Vm);
    const IR::U128 result = datasize == 64 ? ir.VectorExtractLower(lo, hi, position) : ir.VectorExtract(lo, hi, position);

    V(datasize, Vd, result);

    return true;
}

} // namespace Dynarmic::A64
