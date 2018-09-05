Tests for XParser
Author: Sander van der Hoog
Date: 5 Sept 2018

This test is meant for checking agent order of function execution.

Observations:

1. The original order of agents in the 0.xml file is inverted due to the xml read-in function.
2. If the agents only print out their IDs (no messages send and read), then the order is maintained.
3. If messages are send and read, then the order gets inverted upon activating the read function, and then remains that order also for the next add-message functions, until the next message loop.
4. If, in addition, a function is inserted between the write and read functions, then the order is again reversed.
5. Each new iteration starts with the same agent order as at the end of the previous iteration.

Hypothesis:

The reversal is caused by an agent-iterator related to functions that have message input/output.

The problem is *not* related to the message iterator itself (in the message loop), since the order in which messages appear in the message loop (for a single agent) is the same order as the messages were added by the agents.

Test model:
- basic_agent_order

Output:

```
------------------------
IT 1 ID 6
IT 1 ID 5
IT 1 ID 4
IT 1 ID 3
IT 1 ID 2
IT 1 ID 1
------------------------
IT 2 ID 6
IT 2 ID 5
IT 2 ID 4
IT 2 ID 3
IT 2 ID 2
IT 2 ID 1
------------------------
IT 3 ID 6
IT 3 ID 5
IT 3 ID 4
IT 3 ID 3
IT 3 ID 2
IT 3 ID 1
------------------------
IT 4 ID 6
IT 4 ID 5
IT 4 ID 4
IT 4 ID 3
IT 4 ID 2
IT 4 ID 1
------------------------
```

3. However, if messages are send and read, the order is again inverted upon activating the read function (function with message input).
Also note that the agent order at the start of a new iteration is the same as at the end of the previous iteration, so it does not revert to the original order it has after reading from the 0.xml.

Test model:
- message_reading: 

Output:

```
------------------------
IT 1 ID 6 adds ID message
IT 1 ID 5 adds ID message
IT 1 ID 4 adds ID message
IT 1 ID 3 adds ID message
IT 1 ID 2 adds ID message
IT 1 ID 1 adds ID message
IT 1 ID 1 reads ID messages:	6 5 4 3 2 1 
IT 1 ID 2 reads ID messages:	6 5 4 3 2 1 
IT 1 ID 3 reads ID messages:	6 5 4 3 2 1 
IT 1 ID 4 reads ID messages:	6 5 4 3 2 1 
IT 1 ID 5 reads ID messages:	6 5 4 3 2 1 
IT 1 ID 6 reads ID messages:	6 5 4 3 2 1 
------------------------
IT 2 ID 1 adds ID message
IT 2 ID 2 adds ID message
IT 2 ID 3 adds ID message
IT 2 ID 4 adds ID message
IT 2 ID 5 adds ID message
IT 2 ID 6 adds ID message
IT 2 ID 6 reads ID messages:	1 2 3 4 5 6 
IT 2 ID 5 reads ID messages:	1 2 3 4 5 6 
IT 2 ID 4 reads ID messages:	1 2 3 4 5 6 
IT 2 ID 3 reads ID messages:	1 2 3 4 5 6 
IT 2 ID 2 reads ID messages:	1 2 3 4 5 6 
IT 2 ID 1 reads ID messages:	1 2 3 4 5 6 
------------------------
IT 3 ID 6 adds ID message
IT 3 ID 5 adds ID message
IT 3 ID 4 adds ID message
IT 3 ID 3 adds ID message
IT 3 ID 2 adds ID message
IT 3 ID 1 adds ID message
IT 3 ID 1 reads ID messages:	6 5 4 3 2 1 
IT 3 ID 2 reads ID messages:	6 5 4 3 2 1 
IT 3 ID 3 reads ID messages:	6 5 4 3 2 1 
IT 3 ID 4 reads ID messages:	6 5 4 3 2 1 
IT 3 ID 5 reads ID messages:	6 5 4 3 2 1 
IT 3 ID 6 reads ID messages:	6 5 4 3 2 1 
------------------------
IT 4 ID 1 adds ID message
IT 4 ID 2 adds ID message
IT 4 ID 3 adds ID message
IT 4 ID 4 adds ID message
IT 4 ID 5 adds ID message
IT 4 ID 6 adds ID message
IT 4 ID 6 reads ID messages:	1 2 3 4 5 6 
IT 4 ID 5 reads ID messages:	1 2 3 4 5 6 
IT 4 ID 4 reads ID messages:	1 2 3 4 5 6 
IT 4 ID 3 reads ID messages:	1 2 3 4 5 6 
IT 4 ID 2 reads ID messages:	1 2 3 4 5 6 
IT 4 ID 1 reads ID messages:	1 2 3 4 5 6 
------------------------
```

4. Now we add an additional function inbetween the write-read functions that only prints out the agent IDs.

Test model:
- message_reading_print: 

Output:

```
------------------------
IT 1 ID 6 adds ID message
IT 1 ID 5 adds ID message
IT 1 ID 4 adds ID message
IT 1 ID 3 adds ID message
IT 1 ID 2 adds ID message
IT 1 ID 1 adds ID message
------------------------
IT 1 ID 1 prints own ID
IT 1 ID 2 prints own ID
IT 1 ID 3 prints own ID
IT 1 ID 4 prints own ID
IT 1 ID 5 prints own ID
IT 1 ID 6 prints own ID
------------------------
IT 1 ID 6 reads ID messages:	6 5 4 3 2 1 
IT 1 ID 5 reads ID messages:	6 5 4 3 2 1 
IT 1 ID 4 reads ID messages:	6 5 4 3 2 1 
IT 1 ID 3 reads ID messages:	6 5 4 3 2 1 
IT 1 ID 2 reads ID messages:	6 5 4 3 2 1 
IT 1 ID 1 reads ID messages:	6 5 4 3 2 1 
------------------------
IT 2 ID 6 adds ID message
IT 2 ID 5 adds ID message
IT 2 ID 4 adds ID message
IT 2 ID 3 adds ID message
IT 2 ID 2 adds ID message
IT 2 ID 1 adds ID message
------------------------
IT 2 ID 1 prints own ID
IT 2 ID 2 prints own ID
IT 2 ID 3 prints own ID
IT 2 ID 4 prints own ID
IT 2 ID 5 prints own ID
IT 2 ID 6 prints own ID
------------------------
IT 2 ID 6 reads ID messages:	6 5 4 3 2 1 
IT 2 ID 5 reads ID messages:	6 5 4 3 2 1 
IT 2 ID 4 reads ID messages:	6 5 4 3 2 1 
IT 2 ID 3 reads ID messages:	6 5 4 3 2 1 
IT 2 ID 2 reads ID messages:	6 5 4 3 2 1 
IT 2 ID 1 reads ID messages:	6 5 4 3 2 1 
------------------------
IT 3 ID 6 adds ID message
IT 3 ID 5 adds ID message
IT 3 ID 4 adds ID message
IT 3 ID 3 adds ID message
IT 3 ID 2 adds ID message
IT 3 ID 1 adds ID message
------------------------
IT 3 ID 1 prints own ID
IT 3 ID 2 prints own ID
IT 3 ID 3 prints own ID
IT 3 ID 4 prints own ID
IT 3 ID 5 prints own ID
IT 3 ID 6 prints own ID
------------------------
IT 3 ID 6 reads ID messages:	6 5 4 3 2 1 
IT 3 ID 5 reads ID messages:	6 5 4 3 2 1 
IT 3 ID 4 reads ID messages:	6 5 4 3 2 1 
IT 3 ID 3 reads ID messages:	6 5 4 3 2 1 
IT 3 ID 2 reads ID messages:	6 5 4 3 2 1 
IT 3 ID 1 reads ID messages:	6 5 4 3 2 1 
------------------------
IT 4 ID 6 adds ID message
IT 4 ID 5 adds ID message
IT 4 ID 4 adds ID message
IT 4 ID 3 adds ID message
IT 4 ID 2 adds ID message
IT 4 ID 1 adds ID message
------------------------
IT 4 ID 1 prints own ID
IT 4 ID 2 prints own ID
IT 4 ID 3 prints own ID
IT 4 ID 4 prints own ID
IT 4 ID 5 prints own ID
IT 4 ID 6 prints own ID
------------------------
IT 4 ID 6 reads ID messages:	6 5 4 3 2 1 
IT 4 ID 5 reads ID messages:	6 5 4 3 2 1 
IT 4 ID 4 reads ID messages:	6 5 4 3 2 1 
IT 4 ID 3 reads ID messages:	6 5 4 3 2 1 
IT 4 ID 2 reads ID messages:	6 5 4 3 2 1 
IT 4 ID 1 reads ID messages:	6 5 4 3 2 1 
------------------------
```
 
5. Note that here, again, each new iteration starts with the same agent order as at the end of the previous iteration.
