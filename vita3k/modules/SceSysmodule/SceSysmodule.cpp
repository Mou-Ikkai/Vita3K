// Vita3K emulator project
// Copyright (C) 2021 Vita3K team
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "SceSysmodule.h"

#include <modules/module_parent.h>

#include <module/load_module.h>

static bool is_modules_enable(HostState &host, SceSysmoduleModuleId module_id) {
    if (host.cfg.current_config.modules_mode == ModulesMode::MANUAL)
        return !host.cfg.current_config.lle_modules.empty() && is_lle_module(module_id, host);
    else
        return is_lle_module(module_id, host);
}

EXPORT(int, sceSysmoduleIsLoaded, SceSysmoduleModuleId module_id) {
    if (module_id < 0 || module_id > SYSMODULE_COUNT)
        return SCE_SYSMODULE_ERROR_INVALID_VALUE;

    if (is_modules_enable(host, module_id)) {
        if (is_module_loaded(host.kernel, module_id))
            return SCE_SYSMODULE_LOADED;
        else
            return SCE_SYSMODULE_ERROR_UNLOADED;
    } else
        return SCE_SYSMODULE_LOADED;
}

EXPORT(int, sceSysmoduleIsLoadedInternal) {
    return UNIMPLEMENTED();
}

EXPORT(int, sceSysmoduleLoadModule, SceSysmoduleModuleId module_id) {
    if (module_id < 0 || module_id > SYSMODULE_COUNT)
        return SCE_SYSMODULE_ERROR_INVALID_VALUE;

    if (is_modules_enable(host, module_id)) {
        if (load_module(host, thread_id, module_id))
            return SCE_SYSMODULE_LOADED;
        else
            return SCE_SYSMODULE_ERROR_UNLOADED;
    } else
        return SCE_SYSMODULE_LOADED;
}

EXPORT(int, sceSysmoduleLoadModuleInternal) {
    return UNIMPLEMENTED();
}

EXPORT(int, sceSysmoduleLoadModuleInternalWithArg) {
    return UNIMPLEMENTED();
}

EXPORT(int, sceSysmoduleUnloadModule) {
    return UNIMPLEMENTED();
}

EXPORT(int, sceSysmoduleUnloadModuleInternal) {
    return UNIMPLEMENTED();
}

EXPORT(int, sceSysmoduleUnloadModuleInternalWithArg) {
    return UNIMPLEMENTED();
}

BRIDGE_IMPL(sceSysmoduleIsLoaded)
BRIDGE_IMPL(sceSysmoduleIsLoadedInternal)
BRIDGE_IMPL(sceSysmoduleLoadModule)
BRIDGE_IMPL(sceSysmoduleLoadModuleInternal)
BRIDGE_IMPL(sceSysmoduleLoadModuleInternalWithArg)
BRIDGE_IMPL(sceSysmoduleUnloadModule)
BRIDGE_IMPL(sceSysmoduleUnloadModuleInternal)
BRIDGE_IMPL(sceSysmoduleUnloadModuleInternalWithArg)
