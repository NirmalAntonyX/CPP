# CPP
ProtocolFSM.cpp
================
Generic FSM state machine for PPP protocol Daemon. This can be modified for any protocol daemon where the requirement is for state machine.
Each state is represented as a state object.
shared pointer is used for cleaner allocation and de-allocation of the state object.

Producer_Consumer.cpp
======================
Generic Producer Consumer code with appropriate lock gaurds.
There can be N producers and N consumers.
signal condition is used between the producers and the consumers for synchronization.
