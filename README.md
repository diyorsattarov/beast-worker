# concurrency

```
 ✔ Container beast-worker-test-1  Recreated                                                                            0.2s 
Attaching to test-1
test-1  | [3] Task received: task for Slave
test-1  | [4] Task received: task for Slave
test-1  | [0] Task received: task for Slave
test-1  | Task message sent (14 bytes).
test-1  | [2] Task received: task for Slave
test-1  | Task message sent (14 bytes).
test-1  | Task message sent (14 bytes).
test-1  | Task message sent (14 bytes).
test-1  | Response received: Slave ID: 3
test-1  | Response received: Slave ID: 4
test-1  | Response received: Slave ID: 0
test-1  | Response received: Slave ID: 2
test-1  | Task message sent (14 bytes).
test-1  | Response received: Slave ID: 1
test-1  | [1] Task received: task for Slave
^CGracefully stopping... (press Ctrl+C again to force)
[+] Stopping 1/1
 ✔ Container beast-worker-test-1  Stopped                                                                             10.4s 
test-1 exited with code 0
canceled
```