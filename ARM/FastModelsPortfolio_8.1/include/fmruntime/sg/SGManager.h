/*!
 * \file    SGManager.h
 * \brief   FastSim Component Manager.
 * \date    Copyright 2005 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 */

#ifndef ARM_SG_MANAGER_H
#define ARM_SG_MANAGER_H

namespace sg {

class ComponentManager;
class SimulationContext;


ComponentManager *ComponentManager_Create(SimulationContext* context);
void ComponentManager_Destroy(ComponentManager *manager);

} // namespace sg

#endif // ARM_SG_MANAGER_H
