/*
 * Copyright (C) 2023 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#![allow(missing_docs)]
#![no_main]
extern crate libfuzzer_sys;

use authgraph_hal::service::AuthGraphService;
use authgraph_nonsecure::LocalTa;
use binder_random_parcel_rs::fuzz_service;
use libfuzzer_sys::fuzz_target;

fuzz_target!(|data: &[u8]| {
    let local_ta = LocalTa::new().expect("Failed to create an AuthGraph local TA.");
    let service = AuthGraphService::new_as_binder(local_ta);
    fuzz_service(&mut service.as_binder(), data);
});
