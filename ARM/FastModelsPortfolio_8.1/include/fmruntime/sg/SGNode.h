 /*!
 * \file    SGNode.h
 * \brief   Abstract base-class for entities in a component hierarchy.
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 */

#ifndef ARM_SG_NODE_H
#define ARM_SG_NODE_H

#include <string>

namespace sg {

/*! A Node is a thing that has a name and a parent. */
class Node
{
public:
    /*! Ensure that any subclasses of Node will always be destroyed correctly.
     */
    virtual ~Node() { }

    /*! Get the name of this node. */
    virtual std::string getName() const = 0;

    /*! Find out what kind of thing this node is. */
    virtual std::string getClassName() const = 0;

    /*! Find who owns this node.  Returns NULL for the top-level component
     *  in a system.
     */
    virtual const Node * getParent() const = 0;

    /*! Tell this node who its owner is. */
    virtual void setParent(Node *) = 0;

    /*! Get a full hierarchical name for this component. */
    std::string getHierarchicalName() const;
};

} // namespace sg

#endif // ARM_SG_NODE_H
