// Copyright 2010 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
// back-end
#include <boost/msm/back11/state_machine.hpp>
//front-end
#include <boost/msm/front/state_machine_def.hpp>
// functors
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;

namespace
{
    // events
    struct event1 {};


    // front-end: define the FSM structure
    struct my_machine_ : public msm::front::state_machine_def<my_machine_>
    {
        // The list of FSM states
        struct State1 : public msm::front::state<>
        {
            // every (optional) entry/exit methods get the event passed.
            template <class Event,class FSM>
            void on_entry(Event const&,FSM& ) {std::cout << "entering: State1" << std::endl;}
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) {std::cout << "leaving: State1" << std::endl;}
        };
        struct State2 : public msm::front::state<>
        {
            template <class Event,class FSM>
            void on_entry(Event const& ,FSM&) {std::cout << "entering: State2" << std::endl;}
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) {std::cout << "leaving: State2" << std::endl;}
        };

        struct State3 : public msm::front::state<>
        {
            // when stopped, the CD is loaded
            template <class Event,class FSM>
            void on_entry(Event const& ,FSM&) {std::cout << "entering: State3" << std::endl;}
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) {std::cout << "leaving: State3" << std::endl;}
        };

        struct State4 : public msm::front::state<>
        {
            template <class Event,class FSM>
            void on_entry(Event const&,FSM& ) {std::cout << "entering: State4" << std::endl;}
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) {std::cout << "leaving: State4" << std::endl;}
        };

        // the initial state of the player SM. Must be defined
        typedef State1 initial_state;

        // transition actions
        struct State2ToState3
        {
            template <class EVT,class FSM,class SourceState,class TargetState>
            void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
            {
                std::cout << "my_machine::State2ToState3" << std::endl;
            }
        };
        struct State3ToState4
        {
            template <class EVT,class FSM,class SourceState,class TargetState>
            void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
            {
                std::cout << "my_machine::State3ToState4" << std::endl;
            }
        };
        // guard conditions
        struct always_true
        {
            template <class EVT,class FSM,class SourceState,class TargetState>
            bool operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt)
            {
                std::cout << "always_true" << std::endl;
                return true;
            }
        };
        struct always_false
        {
            template <class EVT,class FSM,class SourceState,class TargetState>
            bool operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt)
            {
                std::cout << "always_false" << std::endl;
                return false;
            }
        };

        typedef my_machine_ p; // makes transition table cleaner

        // Transition table for player
        struct transition_table : mpl::vector<
            //    Start     Event         Next      Action               Guard
            //  +---------+-------------+---------+---------------------+----------------------+
            Row < State1  , none        , State2                                               >,
            Row < State2  , none        , State3  , State2ToState3                             >,
            Row < State3  , none        , State4  , none                , always_false         >,
            //  +---------+-------------+---------+---------------------+----------------------+
            Row < State3  , none        , State4  , State3ToState4      , always_true          >,
            Row < State4  , event1      , State1                                               >
            //  +---------+-------------+---------+---------------------+----------------------+
        > {};
        // Replaces the default no-transition response.
        template <class FSM,class Event>
        void no_transition(Event const& e, FSM&,int state)
        {
            std::cout << "no transition from state " << state
                << " on event " << typeid(e).name() << std::endl;
        }
    };
    // Pick a back-end
    typedef msm::back11::state_machine<my_machine_> my_machine;

    //
    // Testing utilities.
    //
    static char const* const state_names[] = { "State1", "State2", "State3", "State4" };
    void pstate(my_machine const& p)
    {
        std::cout << " -> " << state_names[p.current_state()[0]] << std::endl;
    }

    void test()
    {
        my_machine p;

        // needed to start the highest-level SM. This will call on_entry and mark the start of the SM
        // in this case it will also immediately trigger all anonymous transitions
        p.start();
        // this event will bring us back to the initial state and thus, a new "loop" will be started
        p.process_event(event1());

    }
}

int main()
{
    test();
    return 0;
}
