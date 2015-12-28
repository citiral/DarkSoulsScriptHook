/*extern crate winapi;
extern crate libc;
extern crate kernel32;*/
extern crate native;

use std::io::prelude::*;
use std::fs::File;
/*use std::ffi::CString;
use std::str;
use libc::c_void;
use winapi::xinput;

pub type Voidptr = *mut c_void;

static mut MODULE: Option<winapi::HMODULE> = None;*/

#[allow(non_snake_case)]
pub extern "stdcall" fn DllMain(module: u32, reason_for_call: u32) {

    //match reason_for_call {
        //1 => {
native::start(0, 0 as *mut u8, proc() {
            let mut f = File::create("debug.txt");
            f.unwrap().write_all(b"Getting state!");
        });
            // dll_process_attach
            //initialize();
        //}
        //_ => {}
    //}
}
/*
extern "stdcall" {
    fn GetModuleHandleA(module_name: *const libc::c_char) -> winapi::HMODULE;
    fn LoadLibrary(file_name: *const libc::c_char) -> winapi::HMODULE;
    fn GetProcAddress(module: winapi::HMODULE, proc_name: *const libc::c_char) -> extern "C" fn();
}

fn initialize() {
    unsafe {
        MODULE = Some(GetModuleHandleA(CString::new("C:\\Windows\\System32\\xinput1_3.dll")
                                           .unwrap()
                                           .as_ptr()));
    }
}

// start proxy functions
#[no_mangle]
#[allow(non_snake_case)]
pub extern "stdcall" fn XInputEnable(enabled: bool) {
    unsafe {
        match MODULE {
            Some(module) => {
                let func: extern "C" fn(bool) =
                    std::mem::transmute(GetProcAddress(module,
                                                       CString::new("XInputEnable")
                                                           .unwrap()
                                                           .as_ptr()));
                func(enabled);
            }
            _ => (),
        }
    }
}

#[no_mangle]
#[allow(non_snake_case)]
pub extern "stdcall" fn XInputGetBatteryInformation(user_index: u32,
                                                    dev_type: u8,
                                                    battery_information: Voidptr)
                                                    -> u32 {
    unsafe {
        match MODULE {
            Some(module) => {
                let func: extern "C" fn(u32, u8, Voidptr) -> u32 =
                    std::mem::transmute(GetProcAddress(module,
                                                       CString::new("XInputGetBatteryInformatio\
                                                                     n")
                                                           .unwrap()
                                                           .as_ptr()));
                func(user_index, dev_type, battery_information)
            }
            _ => 0,
        }
    }
}

#[no_mangle]
#[allow(non_snake_case)]
pub extern "stdcall" fn XInputGetCapabilities(user_index: u32,
                                              flags: u32,
                                              capabilities: Voidptr)
                                              -> u32 {
    unsafe {
        match MODULE {
            Some(module) => {
                let func: extern "C" fn(u32, u32, Voidptr) -> u32 =
                    std::mem::transmute(GetProcAddress(module,
                                                       CString::new("XInputGetCapabilities")
                                                           .unwrap()
                                                           .as_ptr()));
                func(user_index, flags, capabilities)
            }
            _ => 0,
        }
    }
}

#[no_mangle]
#[allow(non_snake_case)]
pub extern "stdcall" fn XInputGetDSoundAudioDeviceGuids(user_index: u32,
                                                        pDSoundRenderGuid: Voidptr,
                                                        pDSoundCaptureGuid: Voidptr)
                                                        -> u32 {
    unsafe {
        match MODULE {
            Some(module) => {
                let func: extern "C" fn(u32, Voidptr, Voidptr) -> u32 =
                    std::mem::transmute(GetProcAddress(module,
                                                       CString::new("XInputGetDSoundAudioDevice\
                                                                     Guids")
                                                           .unwrap()
                                                           .as_ptr()));
                func(user_index, pDSoundRenderGuid, pDSoundCaptureGuid)
            }
            _ => 0,
        }
    }
}

#[no_mangle]
#[allow(non_snake_case)]
pub extern "stdcall" fn XInputGetKeystroke(user_index: u32,
                                           reserved: u32,
                                           keystroke: xinput::XINPUT_STATE)
                                           -> u32 {
    unsafe {
        match MODULE {
            Some(module) => {
                let func: extern "C" fn(u32, u32, xinput::XINPUT_STATE) -> u32 =
                    std::mem::transmute(GetProcAddress(module,
                                                       CString::new("XInputGetDSoundAudioDevice\
                                                                     Guids")
                                                           .unwrap()
                                                           .as_ptr()));
                func(user_index, reserved, keystroke)
            }
            _ => 0,
        }
    }
}

#[no_mangle]
#[allow(non_snake_case)]
pub extern "stdcall" fn XInputGetState(user_index: u32, state: Voidptr) -> u32 {
    unsafe {
        match MODULE {
            Some(module) => {
                let func: extern "C" fn(u32, Voidptr) -> u32 =
                    std::mem::transmute(GetProcAddress(module,
                                                       CString::new("XInputGetState")
                                                           .unwrap()
                                                           .as_ptr()));
                func(user_index, state)
            }
            _ => 0,
        }
    }
}

#[no_mangle]
#[allow(non_snake_case)]
pub extern "stdcall" fn XInputSetState(user_index: u32, vibration: Voidptr) -> u32 {
    unsafe {
        match MODULE {
            Some(module) => {
                let func: extern "C" fn(u32, Voidptr) -> u32 =
                    std::mem::transmute(GetProcAddress(module,
                                                       CString::new("XInputSetState")
                                                           .unwrap()
                                                           .as_ptr()));
                func(user_index, vibration)
            }
            _ => 0,
        }
    }
}
*/
