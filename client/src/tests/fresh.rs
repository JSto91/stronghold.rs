// Copyright 2021 IOTA Stiftung
// SPDX-License-Identifier: Apache-2.0

use crypto::{keys::slip10::Chain, utils::rand::fill};
pub use stronghold_utils::{random::*, test_utils};

use crate::{Location, RecordHint};

/// Creates a random [`RecordHint`]
pub fn record_hint() -> RecordHint {
    let mut bs = [0; 24];
    fill(&mut bs).expect("Unable to fill record hint");
    bs.into()
}

/// Generates a random [`Location`].
pub fn location() -> Location {
    Location::generic(bytestring(4096), bytestring(4096))
}

/// generates a random string based on a coinflip.
pub fn passphrase() -> Option<String> {
    if coinflip() {
        Some(string(4096))
    } else {
        None
    }
}

/// Creates a random hd_path.
pub fn hd_path() -> (String, Chain) {
    let mut s = "m".to_string();
    let mut is = vec![];
    while coinflip() {
        let i = random::<u32>() & 0x7fffff;
        s.push_str(&format!("/{}'", i));
        is.push(i);
    }
    (s, Chain::from_u32_hardened(is))
}
