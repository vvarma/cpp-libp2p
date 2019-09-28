/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LIBP2P_KAD_QUERY_RUNNER_MOCK_HPP
#define LIBP2P_KAD_QUERY_RUNNER_MOCK_HPP

#include "p2p/protocol/kademlia/query_runner.hpp"

#include <gmock/gmock.h>

namespace libp2p::protocol::kademlia {

  struct QueryRunnerMock : public QueryRunner {
    ~QueryRunnerMock() override = default;

    MOCK_METHOD3(run, void(Query query, PeerIdVec peers, PeerInfoResultFunc f));
  };

}  // namespace libp2p::protocol::kademlia

#endif  // LIBP2P_KAD_QUERY_RUNNER_MOCK_HPP