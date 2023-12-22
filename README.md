# concurrency

```
 ✔ Network beast-worker_worker-network  Created                                                                        0.1s 
 ✔ Container beast-worker-slave-1       Created                                                                        0.2s 
 ✔ Container beast-worker-master-1      Created                                                                        0.2s 
Attaching to master-1, slave-1
slave-1   | Task received: Task for slave worker2
master-1  | Task message sent (23 bytes).
slave-1   | 
master-1  | Response received: Task completed.
slave-1 exited with code 0
^CGracefully stopping... (press Ctrl+C again to force)
[+] Stopping 2/2
 ✔ Container beast-worker-slave-1   Stopped                                                                            0.0s 
 ✔ Container beast-worker-master-1  Stopped                                                                           10.5s 
master-1 exited with code 0
canceled
```