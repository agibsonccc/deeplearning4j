/* ******************************************************************************
 *
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License, Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 *  See the NOTICE file distributed with this work for additional
 *  information regarding copyright ownership.
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/

//
// Created by raver119 on 21.10.17.
//

#include <graph/GraphExecutioner.h>
#include <graph/execution/LogicSwitch.h>

namespace sd {
namespace graph {
Status LogicSwitch::processNode(Graph* graph, Node* node) {
  auto __variableSpace = graph->getVariableSpace();
  auto __flowPath = __variableSpace->flowPath();

  Context ctx(node->getContextPrototype(), __variableSpace);

  // this can be either  our format, or compatible format.
  if (graph->hasScope(node->input()->at(0).first)) {
    sd_debug("Node_%i: Scoped mode.\n", node->id());
    // first input is OpScope, so it's ours
    int scopeConditionIndex = node->input()->at(0).first;
    auto input = ctx.variable(1);

    auto scopeCondition = graph->scopeById(scopeConditionIndex);
    int lastNode = 0;
    for (auto v : *scopeCondition->nodes()) {
      GraphExecutioner::executeFlatNode(graph, v, __variableSpace);
      lastNode = v->id();
    }

    // now we should take result of the OpScope run, and evaluate it
    auto result = __variableSpace->getVariable(lastNode)->getNDArray();

    std::pair<int, int> pair0(node->id(), 0);
    std::pair<int, int> pair1(node->id(), 1);

    if (!__variableSpace->hasVariable(pair0))
      __variableSpace->putVariable(pair0, new Variable(nullptr, nullptr, node->id(), 0));

    if (!__variableSpace->hasVariable(pair1))
      __variableSpace->putVariable(pair1, new Variable(nullptr, nullptr, node->id(), 1));

    if (!result->e<bool>(0)) {
      __flowPath->markBranch(node->id(), 0);
      __variableSpace->getVariable(pair0)->setNDArray(input->getNDArray());
      __variableSpace->getVariable(pair0)->markRemovable(false);
    } else {
      __flowPath->markBranch(node->id(), 1);
      __variableSpace->getVariable(pair1)->setNDArray(input->getNDArray());
      __variableSpace->getVariable(pair1)->markRemovable(false);
    }
  } else {
    // first input is NOT a OpScope, so it's compatible format
    sd_debug("Node_%i: Compatible mode.\n", node->id());

    auto input = ctx.variable(0)->getNDArray();
    auto boolean = ctx.variable(1)->getNDArray();



    std::pair<int, int> pair0(node->id(), 0);
    std::pair<int, int> pair1(node->id(), 1);

    if (!__variableSpace->hasVariable(pair0))
      __variableSpace->putVariable(pair0, new Variable(nullptr, nullptr, node->id(), 0));

    if (!__variableSpace->hasVariable(pair1))
      __variableSpace->putVariable(pair1, new Variable(nullptr, nullptr, node->id(), 1));

    if (!boolean->e<bool>(0)) {
      // false
      sd_debug("Node_%i: FALSE branch active\n", node->id());
      __flowPath->markBranch(node->id(), 0);
      __variableSpace->getVariable(pair0)->setNDArray(input);
      __variableSpace->getVariable(pair0)->markRemovable(false);
    } else {
      // true
      sd_debug("Node_%i: TRUE branch active\n", node->id());
      __flowPath->markBranch(node->id(), 1);
      __variableSpace->getVariable(pair1)->setNDArray(input);
      __variableSpace->getVariable(pair1)->markRemovable(false);
    }
  }

  return Status::OK;
};
}  // namespace graph
}  // namespace sd
