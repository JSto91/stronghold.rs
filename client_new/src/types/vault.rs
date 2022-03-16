// Copyright 2020-2021 IOTA Stiftung
// SPDX-License-Identifier: Apache-2.0

use crate::Result;

pub struct Vault {}

impl Vault {
    pub async fn write_secret(&self, location: Vec<u8>, payload: Vec<u8>, hint: Vec<u8>) {
        todo!()
    }

    pub async fn delete_secret(&self, location: Vec<u8>) {
        todo!()
    }

    pub async fn revoke_secret(&self, location: Vec<u8>) {
        todo!()
    }

    pub async fn garbage_collect(&self) {
        todo!()
    }

    pub async fn execute_procedure() -> Result<()> {
        todo!()
    }
}
