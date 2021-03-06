// Copyright (c) 2018 The Unit-e developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <snapshot/state.h>

#include <snapshot/indexer.h>
#include <snapshot/snapshot_index.h>
#include <test/test_unite.h>
#include <validation.h>
#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(snapshot_state_tests, TestingSetup)

BOOST_AUTO_TEST_CASE(is_initial_snapshot_download) {
  SetDataDir("snapshot_state");
  fs::remove_all(GetDataDir() / snapshot::SNAPSHOT_FOLDER);

  auto *bi = new CBlockIndex;
  bi->nHeight = 1;
  bi->phashBlock = &mapBlockIndex.emplace(uint256S("aa"), bi).first->first;
  snapshot::AddSnapshotHash(uint256S("cc"), bi);

  snapshot::State state;
  BOOST_CHECK(state.IsInitialSnapshotDownload());
  snapshot::FinalizeSnapshots(bi);
  BOOST_CHECK(!state.IsInitialSnapshotDownload());
}

BOOST_AUTO_TEST_SUITE_END()
