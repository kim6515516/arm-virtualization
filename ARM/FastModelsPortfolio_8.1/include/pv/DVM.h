/*
 * Copyright 2010 ARM Limited. All rights reserved.
 */
/*!
 * \file    DVM.h
 * \brief   AMBA Coherency Extensions define coherency protocols for maintaining virtual memory systems by exchanging Distributed Virtual Memory (DVM) messages.
 */
#ifndef PVBUS_DVM_H
#define PVBUS_DVM_H

#include <vector>
#include <iosfwd>
#include <string>

#include "sg/SGstdint.h"

//
// This is an internal interface for managing distributing DVM messages.
//

///
/// \page DVM DVM Message infrastructure
///
/// DVM messages are 'Distributed Virtual Memory' Messages.  They exist in ACE
/// (AMBA4) to distribute the following messages:
///
///    - various forms of TLB invalidate
///    - various forms of I-cache invalidate
///    - various forms of branch predictor invalidates
///    - a sync message to ask when the previous operations have
///      completed.
///
///
/// The connections of a system form a graph.
///
/// Some links in the graph are ACE and can propagate ACE messages.
///
/// Some nodes in the system may have a local behaviour that needs to be invoked
/// because of a DVM message.  All nodes can potentially generate a DVM message,
/// even if they don't have a local behaviour.
///
/// Non-ACE connections are immediately removed from the graph and do not form
/// part of the graph.
///
/// When a DVM-aware node is reset, then it finds all _immediately_ adjacent
/// nodes that are upstream and downstream.
///
/// When a DVM message is broadcast, then it propagates through the network of
/// nodes that have registered an interest.
///
/// NOTE that in order for this to work then each arc/link in the graph has to be
/// uniquely identified to the node.  We do this by identifying the node on each
/// end and by letting the destination node identify the node with an 'id_t'.  A
/// master will _directly_ call a downstream multiple times only if the id_t are
/// different.  Otherwise, it will assume that the call is idempotent and not
/// bother.
///
/// So each PVBus has
/// discoverDownstreamChildDVMNodes()/discoverUpstreamParentDVMNodes functions
/// that returns (via a visitor) the unique objects for each immediately
/// connected node in the graph that is DVM aware.  The DVMNode is an interface
/// that the supports the graph discovery phase and is used to support the DVM
/// broadcast operation.
///
/// Conceptually this is a getDVMNode() function, however, as a single port can
/// fan-out to many nodes (and be forwarded through bus decoders etc.) then a
/// single port can have many links to down-stream DVMNodes.  This _only_
/// discovers the immediately connected DVM-aware nodes.
///
/// It is also interesting to note that the same DVMNode can be discovered through
/// multiple ports.
///

class DVMNode;

namespace DVM
{
    //
    // Typedefs for ASID/VMIDs
    //
    typedef uint32_t asid_t;
    typedef uint32_t vmid_t;

    ///
    /// A simple id for representing an arc into a node via a port.
    ///
    /// An arc in the graph can be labelled by the destination node using an id_t
    /// that is just a simple integer wrapped to prevent accidental arithmetic.
    ///
    class id_t
    {
        unsigned id;
    public:

        /// explicit prevent accidental implicit conversions from unsigned.
        explicit id_t( unsigned id_ = ~0u ) : id(id_) {}

        // default copy constructor    : OK
        // default destructor          : OK
        // default assignment operator : OK

        unsigned get_id() const { return id; }

        /// \name Comparison operators
        //@{
        bool operator <  (id_t id_) const { return id < id_.id; }
        bool operator == (id_t id_) const { return id == id_.id; }
        bool operator != (id_t id_) const { return id != id_.id; }
        //@}
    };

    std::ostream& operator <<(std::ostream& os_, id_t t_);

    /// \name DVM error response handling
    //@{

    /// DVM Error response code (follows ACE Enconding)
    enum error_response_t
    {
        ok     = 0, // 5'b00000  ACE encoding
        error  = 2  // 5'b00010  ACE encoding
#if 0
        switch (t_)
        {
        case ok:
        case error:
        }
#endif
    };

    std::ostream& operator <<(std::ostream& os_, error_response_t t_);

    /// DVM Error response codes can be combined using this function.
    error_response_t combine_error_responses(
        error_response_t  a_,
        error_response_t  b_
        );

    //@}

    /// Each DVM message is identified by a particular message number.
    /// \note The encoding follows the ACE encoding on \c ARADDR[14:12]
    enum message_t
    {
        tlbinvalidate                      = 0,
        branchpredictorinvalidate          = 1, // branch predictor invalidate
        physicalinstructioncacheinvalidate = 2,
        virtualinstructioncacheinvalidate  = 3,
        sync                               = 4,
        // hole at 5
        hint                               = 6
        // hole at 7
#if 0
        switch (t_)
        {
        case tlbinvalidate:
        case branchpredictorinvalidate:
        case physicalinstructioncacheinvalidate:
        case virtualinstructioncacheinvalidate:
        case sync:
        case hint:
        }
#endif
    };

    std::ostream& operator <<(std::ostream& os_, message_t t_);

    //
    // Classes that represent specific DVM messages...
    //
    class TLBInvalidate;
    class BranchPredictorInvalidate;
    class PhysicalInstructionCacheInvalidate;
    class VirtualInstructionCacheInvalidate;
    class Sync;
    class Hint;

    // ...all inherit from a base class.
    class Message
    {
    protected:
        message_t message;
    public:
        Message(message_t message_) : message(message_) {}
        virtual ~Message() {}

        message_t getType() const { return message; }

        //
        // Given the message type, then provide the actual message type.
        //
        // These will return 0 if the message is of the wrong type, so it is
        // acceptable to find out the type of something by seeing if it returns
        // 0.
        //
        inline TLBInvalidate*                      getTLBInvalidate();
        inline BranchPredictorInvalidate*          getBranchPredictorInvalidate();
        inline PhysicalInstructionCacheInvalidate* getPhysicalInstructionCacheInvalidate();
        inline VirtualInstructionCacheInvalidate*  getVirtualInstructionCacheInvalidate();
        inline Sync*                               getSync();
        inline Hint*                               getHint();

        virtual void print(std::ostream&) const = 0;
        virtual uint64_t encodeAxADDR(uint64_t&) const =0;
        virtual void decodeAxADDR(uint64_t, uint64_t) = 0;
    };

    Message* newMessageFromAxADDR(uint64_t, uint64_t);

    std::ostream& operator << (std::ostream& os_, Message const& t_);

    enum destination_os_t
    {
        // ACE Encoding on ARADDR[11:10]
        hyp_and_guest_os = 0,
        reserved_os      = 1,
        guest_os_only    = 2,
        hyp_only         = 3,
        monitor_only     = 4, // V8 only, not yet encoded in DVM
#if 0
        switch (os)
        {
        case hyp_and_guest_os:
        case reserved_os:
        case guest_os_only:
        case hyp_only:
        }
#endif
    };

    std::ostream& operator << (std::ostream& os_, destination_os_t t_);

    enum destination_world_t
    {
        // ACE Encoding on ARADDR[9:8]
        secure_and_non_secure = 0,
        reserved_world        = 1,
        secure_only           = 2,
        non_secure_only       = 3
#if 0
        switch (world)
        {
        case secure_and_non_secure:
        case reserved_world:
        case secure_only:
        case non_secure_only:
        }
#endif
    };


    std::ostream& operator << (std::ostream& os_, destination_world_t t_);

    class TLBInvalidate : public Message
    {
    public:
        TLBInvalidate() : Message(tlbinvalidate),
        leaf(false),
        by_ipa(false),
        stage1_only(false)
        {
        }

        // NOTE that only certain combinations of these are allowed!

        //
        // The mapping of TLB maintenance operations onto DVM messages is specified
        // in PRD03-GENC-008353-14-0
        //
        // The following is a modified version of the table at the end of the
        // document.
        //
        // 'Arg' means that the argument to the instruction specifies that field.
        // 'Current' means the current VMID of the executing process.
        //
        //             ACE ARADDR Fields -> [0]
        //                                       [11:10]=os
        //                                          [6]=match_vmid
        //                                                   [5]=match_asid
        //                                                         [0]=match_va
        //                                                                  [9:8]=world
        //     Operation     World  Mode    VA   H  VMID     ASID  Address  NS
        //     --------------------------------------------------------------------
        //     TLBIALLIS      S     Priv    X    0  X        X     0        0
        //     TLBIMVAIS      S     Priv    Arg  0  X        Arg   1        0
        //     TLBIASIDIS     S     Priv    X    0  X        Arg   0        0
        //     TLBIMVAAIS     S     Priv    Arg  0  X        X     1        0
        //     TLBIALLNSNHIS  S     Priv*   X    0  X        X     0        1 // NOTE world is different
        //     TLBIALLHIS     S     Priv*   X    1  X        X     0        1 // NOTE world is different
        //     TLBIMVAHIS     S     Priv*   Arg  1  X        X     1        1 // NOTE world is different
        //     TLBIALLIS     NS     Hyp     X    0  Current  X     0        1
        //     TLBIMVAIS     NS     Hyp     Arg  0  Current  Arg   1        1
        //     TLBIASIDIS    NS     Hyp     X    0  Current  Arg   0        1
        //     TLBIMVAAIS    NS     Hyp     Arg  0  Current  X     1        1
        //     TLBIALLNSNHIS NS     Hyp     X    0  X        X     0        1
        //     TLBIALLHIS    NS     Hyp     X    1  X        X     0        1
        //     TLBIMVAHIS    NS     Hyp     Arg  1  X        X     1        1
        //     TLBIALLIS     NS     Kernel  X    0  Current  X     0        1
        //     TLBIMVAIS     NS     Kernel  Arg  0  Current  Arg   1        1
        //     TLBIASIDIS    NS     Kernel  X    0  Current  Arg   0        1
        //     TLBIMVAAIS    NS     Kernel  Arg  0  Current  X     1        1
        //     TLBIALLNSNHIS NS     Kernel     <Instruction is UNDEFINED>
        //     TLBIALLHIS    NS     Kernel     <Instruction is UNDEFINED>
        //     TLBIMVAHIS    NS     Kernel     <Instruction is UNDEFINED>
        //
        //     (*) these operations are UNPREDICTABLE in any mode other than Monitor modeexec
        //
        // These map to on ACE:
        //
        //
        //             ACE ARADDR Fields -> [0]
        //                                       [11:10]=os
        //                                          [6]=match_vmid
        //                                                   [5]=match_asid
        //                                                         [0]=match_va
        //                                                                  [9:8]=world
        //     Operation                    VA   H  VMID     ASID  Address  NS
        //     --------------------------------------------------------------------
        //     TLBIALLIS                    X    0  X        X     0        0
        //     TLBIMVAIS                    Arg  0  X        Arg   1        0
        //     TLBIASIDIS                   X    0  X        Arg   0        0
        //     TLBIMVAAIS                   Arg  0  X        X     1        0
        //     TLBIALLNSNHIS                X    0  X        X     0        1
        //     TLBIALLHIS                   X    1  X        X     0        1
        //     TLBIMVAHIS                   Arg  1  X        X     1        1
        //     TLBIALLIS                    X    0  Current  X     0        1
        //     TLBIMVAIS                    Arg  0  Current  Arg   1        1
        //     TLBIASIDIS                   X    0  Current  Arg   0        1
        //     TLBIMVAAIS                   Arg  0  Current  X     1        1
        //

        /*
         * V8 extensions
         *
         * These are not part of any specification but allow us to communicate various new
         * invalidation combinations using unmatched VA/ASID fields as a hint.
         *
         *   AArch64
         *              state           message
         *   op         EL  Nsbit       prot    ns  address vmid    asid by_ipa st1_only || stages   
         *                                                                               ||          
         *   VMALL      EL1+    NS      EL1     NS          vmid                   1     || s1       
         *   VA         EL1+    NS      EL1     NS  va      vmid    asid                 || s1       
         *   VAA        EL1+    NS      EL1     NS  va      vmid                         || s1       
         *   ASID       EL1+    NS      EL1     NS          vmid    asid                 || s1       
         *   ALL        EL2+    NS      EL1     NS                                       || s1,s2    
         *   VMALLS12   EL2+    NS      EL1     NS          vmid                         || s1,s2    
         *   IPAS2      EL2+    NS      EL1     NS  ipa     vmid           1             || s2       
         *                                                                               ||          
         *   ALL        EL2+    NS      EL2     NS                                       || s1 (hyp only)   
         *   VA         EL2+    NS      EL2     NS  va                                   || s1 (hyp only)
         *                                                                               ||          
         *   ALL        EL3     *       EL3     S                                        || s1 (el3 only)
         *   VA         EL3     *       EL3     S   va                                   || s1 (el3 only)
         *                                                                               ||          
         *   VMALL      EL1,EL3 S       EL1     S                                        || s1     <-+ (same)
         *   VA         EL1,EL3 S       EL1     S   va              asid                 || s1       |
         *   VAA        EL1,EL3 S       EL1     S   va                                   || s1       |
         *   ASID       EL1,EL3 S       EL1     S                   asid                 || s1       |
         *   ALL        EL3     S       EL1     S                                        || s1     <-+  
         *   VMALLS12   EL3     S       EL1     S                                        || s1     <-+  
         *   IPAS2      EL3     S       EL1     S                          1             || s2     (treat as NOP always)
         *                               |      |   |        |       |
         *         is the 'os' field____/       |   |        |       |
         *         is the 'world' field________/    |        |       |
         *         is the match_va and va fields___/         |       |
         *         is the match_vmid and vmid fields________/        |
         *         is the match_asid and asid fields________________/
         *
         *  NOTE that there are the fields 'leaf', 'by_ipa' (treat as S2 only) and
         *       'stage1_only' to distinguish the ambiguous cases.
         *
         *   AArch32
         *              state           message
         *   op         EL      NSBit   prot    NS  address vmid    asid    stages
         *   ALL        EL1     NS      EL1     NS          vmid            s1
         *   MVA        EL1,EL2 NS      EL1     NS  va      vmid    asid    s1
         *   ASID       EL1,EL2 NS      EL1     NS          vmid    asid    s1
         *   MVAA       EL1,EL2 NS      EL1     NS  va      vmid            s1
         *   ALL        EL2     NS      EL1     NS          vmid            s1,s2
         *   ALLNSNH    EL2,EL3 NS      EL1     NS                          s1,s2
         *   IPAS2      EL2     NS      EL1     NS  ipa     vmid            s2
         *
         *   ALLH       EL2,EL3 NS      EL2     NS                          s1 (hyp only)
         *   VAH        EL2,EL3 NS      EL2     NS  va                      s1 (hyp only)
         *
         *   ALL        EL3     *       EL1     S                           s1 (secure priv + mon)
         *   MVA        EL3     *       EL1     S   va              asid    s1 (secure priv + mon)
         *   ASID       EL3     *       EL1     S                   asid    s1 (secure priv + mon)
         *   MVAA       EL3     *       EL1     S   va                      s1 (secure priv + mon)
         *
         *  
         *
         */


        destination_os_t     os;    // Only valid version is guest_os_only or hyp_only or monitor_only
        destination_world_t  world; // If hyp_only then only allowed non_secure_only, not allowed secure_only
                                    // only secure_only or non_secure_only (ever)

        // ARADDR[6] -- VMID Specified
        bool                 match_vmid;

        // ARADDR[5] -- ASID Specified
        bool                 match_asid;

        // ARADDR[0] -- Address Specified
        bool                 match_va;

        // V8 hints - not yet encoded
        bool                 leaf;        // hint - only need to invalidate leaf operations
        bool                 by_ipa;      // hint - unmatched va field contains a pa
        bool                 stage1_only; // hint - no need to invalidate stage2 entries

        asid_t               asid;
        vmid_t               vmid;
        uint64_t             va;

        // Returns false if the fields filled in are valid.
        bool check() const;

        virtual void print(std::ostream& os_) const;
        virtual uint64_t encodeAxADDR(uint64_t& additional_addr) const;
        virtual void decodeAxADDR(uint64_t addr, uint64_t additional_addr);
    };

    class BranchPredictorInvalidate : public Message
    {
    public:
        BranchPredictorInvalidate() : Message( branchpredictorinvalidate ) {}

        bool                 match_va;
        uint64_t             va;

        // Returns false if the fields filled in are valid.
        bool check() const;

        virtual void print(std::ostream& os_) const;
        virtual uint64_t encodeAxADDR(uint64_t& additional_addr) const;
        virtual void decodeAxADDR(uint64_t addr, uint64_t additional_addr);
    };

    class PhysicalInstructionCacheInvalidate : public Message
    {
    public:
        PhysicalInstructionCacheInvalidate()
            : Message( physicalinstructioncacheinvalidate ),
              with_va_index( false )
        {}

        //
        // We can invalidate all ICIALLUIS with ! match_pa, or we can invalidate
        // by a PA (match_pa).  In this case, we may or may not include a
        // virtual index to help VIPT caches invalidate a minimal amount.  The
        // VA passed is actually all the virtual address bits (down to at least
        // address bit 4), though ACE only requires bits [27:4].
        //

        destination_world_t  world;
        bool                 match_pa;
        bool                 with_va_index;
        uint64_t             pa;
        uint64_t             va_index;

        // Returns false if the fields filled in are valid.
        bool check() const;

        virtual void print(std::ostream& os_) const;
        virtual uint64_t encodeAxADDR(uint64_t& additional_addr) const;
        virtual void decodeAxADDR(uint64_t addr, uint64_t additional_addr);
    };

    class VirtualInstructionCacheInvalidate : public Message
    {
    public:
        VirtualInstructionCacheInvalidate() : Message( virtualinstructioncacheinvalidate ) {}

        destination_os_t     os;
        destination_world_t  world;
        bool                 match_vmid;
        bool                 match_asid;
        bool                 match_va;

        vmid_t               vmid;
        asid_t               asid;

        uint64_t             va;

        // Returns false if the fields filled in are valid.
        bool check() const;

        virtual void print(std::ostream& os_) const;
        virtual uint64_t encodeAxADDR(uint64_t& additional_addr) const;
        virtual void decodeAxADDR(uint64_t addr, uint64_t additional_addr);
    };


    class Sync : public Message
    {
    public:
        Sync() : Message( sync ) {}

        // No fields

        // Returns false if the fields filled in are valid.
        bool check() const;

        virtual void print(std::ostream& os_) const;
        virtual uint64_t encodeAxADDR(uint64_t& additional_addr) const;
        virtual void decodeAxADDR(uint64_t addr, uint64_t additional_addr);
    };

    class Hint : public Message
    {
    public:
        Hint() : Message( hint ) {}

        // No fields

        // Returns false if the fields filled in are valid.
        bool check() const;

        virtual void print(std::ostream& os_) const;
        virtual uint64_t encodeAxADDR(uint64_t& additional_addr) const;
        virtual void decodeAxADDR(uint64_t addr, uint64_t additional_addr);
    };

    class UpstreamVisitor
    {
        UpstreamVisitor(UpstreamVisitor const&); // disallow
        void operator = (UpstreamVisitor const&); // disallow
    protected:
        virtual ~UpstreamVisitor() {}

        UpstreamVisitor() {}
    public:

        //
        // Register a DVMNode that is an upstream-node to the node owning the
        // visitor.
        //
        // When the downstream node (the node owning the visitor), talks to the
        // upstream node it will always use the specified id.
        //
        virtual void registerDVMNode( DVMNode*, DVM::id_t ) = 0;
    };

    class DownstreamVisitor
    {
        DownstreamVisitor(DownstreamVisitor const&); // disallow
        void operator = (DownstreamVisitor const&); // disallow
    protected:
        virtual ~DownstreamVisitor() {}

        DownstreamVisitor() {}
    public:

        //
        // Register a DVMNode that is an downstream-node to the node owning the
        // visitor.
        //
        // When the upstream node (the node owning the visitor), talks to the
        // downstream node it will always use the specified id.
        //
        virtual void registerDVMNode( DVMNode*, DVM::id_t ) = 0;
    };

    namespace details
    {
        //
        // A helper for DVMNode
        //
        class Thunk;
    }


    //
    // Supply the iniine definitions for the Message class
    //
#define S(lower,upper)                                                  \
    inline upper* Message::get##upper()                                 \
    {                                                                   \
        return message == lower ? static_cast<upper*>(this) : 0;        \
    }
        S(tlbinvalidate, TLBInvalidate)
        S(branchpredictorinvalidate, BranchPredictorInvalidate)
        S(physicalinstructioncacheinvalidate, PhysicalInstructionCacheInvalidate)
        S(virtualinstructioncacheinvalidate, VirtualInstructionCacheInvalidate)
        S(sync, Sync)
        S(hint, Hint)
#undef S
}


///
/// A representation of a DVM node in the graph of DVM-aware components.
///
/// NOTE that this node does \e not have a \c sendDVMMessage() function.
///
/// This is because it may be that the implementation of where to send the DVM
/// message may be conditional on the state of the component and so we allow the
/// implementation of this interface to provide an implementation-specific way of
/// launching a DVM request.
///
class DVMNode
{
public: ///
        /// \name Discovery protocol and PVBus interfacing
        ///
        /// The PVBus protocol for discoverDownstreamChildDVMNodes and
        /// discoverUpstreamParentDVMNodes does \e not have a DVM::id_t field.
        ///
        /// However, the virtual functions in this class \e do.
        ///
        /// The id_t field is intended to be filled in by the _receiving_ component
        /// to identify its receiving port and so it can do any port-specific
        /// behaviour.
        ///
        /// In order to bind a behaviour to the PVBus port then you need a shim.
        ///
        /// We provide the following:
        ///    - a static version
        ///    - a thunk-style object
        //@{

    ///
    /// Static version:
    ///
    /// Use:
    /// \code
    ///     bind_method( my_port,
    ///                  discoverUpstreamParentDVMNodes,
    ///                  &DVMNode::discoverDownstreamChildDVMNodesWithID< 0 >,
    ///                  dvm_node );
    /// \endcode
    /// etc.
    ///
    template< unsigned id_ >
    void discoverDownstreamChildDVMNodesWithID( DVM::DownstreamVisitor* parent_ )
    {
        discoverDownstreamChildDVMNodes( parent_, DVM::id_t(id_) );
    }

    template< unsigned id_ >
    void discoverUpstreamParentDVMNodesWithID( DVM::UpstreamVisitor* child_ )
    {
        discoverUpstreamParentDVMNodes( child_, DVM::id_t(id_) );
    }

    ///
    /// \name Thunk style
    ///
    /// Use:
    /// \code
    ///     // Memory of thunk explicitly managed:
    ///     DVMNode::Thunk  down_thunk_0;
    ///     ...
    ///     down_thunk.setParentAndId( dvm_node, 0 );
    ///     bind_method( my_port,
    ///                  discoverUpstreamParentDVMNodes,
    ///                  &DVMNode::Thunk::discoverDownstreamChildDVMNodes,
    ///                  &down_thunk_0 );
    /// \endcode
    /// or:
    /// \code
    ///     // PREFERRED
    ///     // Memory managed by DVMNode
    ///     bind_method( my_port,
    ///                  discoverUpstreamParentDVMNodes,
    ///                  &DVMNode::Thunk::discoverDownstreamChildDVMNodes,
    ///                  dvm_node.makeThunk( 0 ) );
    /// \endcode
    ///
    //@{
    typedef DVM::details::Thunk Thunk;

    virtual Thunk* makeThunk( DVM::id_t id_ ) = 0;
    Thunk*         makeThunk( unsigned id_ );
    //@}

    //@}

public: ///
        /// \name Implementation should override these...
        //@{

    ///
    /// \name Responding to discovery
    ///
    /// The behaviour of these methods is very important to implement correctly.
    ///
    /// A DVMNode either exists for the whole simulation or not.  It is
    /// _independent_ of if it is currently enabled to send DVM messages or not.
    ///
    /// Thus a DVMNode must \e always reply identically to every request -- i.e. a
    /// call is idempotent.
    ///
    /// The reason for this restriction, is that the discovery process can occur
    /// at any time, but typically during reset() and as the ordering or resets
    /// between components is unknown then it is hard to know when to throw away
    /// previously built lists.  A node is allowed to throw away its list _at
    /// any time_.  This means that when we eventually support save-and-restore
    /// then the DVMNode topology need not be saved as it can be dynamically
    /// rediscovered.
    ///
    /// A subtlety that should also be considered is that the same DVMNode can be
    /// discovered by multiple arcs between two DVMNodes.  For example, a
    /// component could have two down-stream ports that sometimes point to the
    /// same DVMNode.  If your component cares about the identity of the link
    /// then it should arrange to distinguish the incoming ports using id_ at the
    /// point at which it binds the PVBus port behaviour to the node.
    ///
    /// TODO: consider if this is actually part of the interface of a DVMNode or
    ///       an implementation detail?
    ///
    //@{
    virtual void discoverDownstreamChildDVMNodes( DVM::DownstreamVisitor* parent_, DVM::id_t id_ = DVM::id_t() ) = 0;
    virtual void discoverUpstreamParentDVMNodes( DVM::UpstreamVisitor* child_, DVM::id_t id_ = DVM::id_t() ) = 0;
    //@}

    virtual std::string const& getInstanceName() const = 0;

    /// Inform the node that a reset() has occurred.  This is not a useful as
    /// one might expect; we do not know whether our node has been called before
    /// or after our the resets of our upstream or downstream nodes (and so
    /// would have tried to discover us) and we don't know if our parent
    /// component has triggered our discovery of our up- and down-stream nodes.
    /// Thus reset() is best used only to reset internal state -- for example,
    /// whether DVM messages are broadcast or terminated, etc.
    virtual void reset() = 0;

    ///
    /// Display configuration information (so far) to the specified stream, using
    /// the indent for each line specified.
    ///
    virtual void print(std::ostream& os_, std::string const& indent_ = "") const = 0;

    //@}

public: //
        // TODO change these to declare_behaviour() slots so that inheritance is
        // not necessary.  However, it then becomes complicated to abstract sending
        // to different ports.
        //

    // This is called when a DVM message is received _from_ downstream and so it is
    // an Upstream message.
    virtual DVM::error_response_t handleUpstreamDVMMessage(DVMNode* from_, DVM::id_t, DVM::Message*) = 0;

    // This is called when a DVM message is received _from_ upstream and so it is
    // a Downstream message.
    virtual DVM::error_response_t handleDownstreamDVMMessage(DVMNode* from_, DVM::id_t, DVM::Message*) = 0;

protected:
    virtual ~DVMNode() {}
};

namespace DVM
{
    namespace details
    {
        ///
        /// A helper for DVMNode
        ///
        class Thunk
        {
            DVMNode*  parent;
            DVM::id_t id;
        public:
            Thunk( DVMNode* parent_, DVM::id_t id_ );
            void setParentAndId( DVMNode* parent_, DVM::id_t id_ );
            DVM::id_t getId() const;
            void discoverDownstreamChildDVMNodes( DVM::DownstreamVisitor* parent_ );
            void discoverUpstreamParentDVMNodes( DVM::UpstreamVisitor* child_ );
        };
    }
}


/// \typedef DVM::asid_t
/// Representation of an Address Space ID.

/// \typedef DVM::vmid_t
/// Representation of an Virtual Machine ID.


#endif
