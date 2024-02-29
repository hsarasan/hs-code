I am trying to implement a mechanism for identifying an instance of a process going down using a very simple sequencing using UDP

Assume there are N instances of the same service running. 

All instances are configured as in a ring 

Instance 1 -> Instance 2 -> Instance 3 -> .....Instance N -> Instance 1

The designated master instance sends a message with a sequence number to the next instance, which propogates to the next one and so on.
Eventually Instance1 will get it back. If it doesnt, it raises an alarm.
Once it receives it back, it knows all instances are up and sends the next sequence.

After 3 seconds of non receipt of a message, the instance throws a warning.
