# concurrency

```
➜  service-worker git:(concurrency-dev) ✗ ls
docker-compose.yaml  service  worker  worker-2
➜  service-worker git:(concurrency-dev) ✗ docker-compose up --build 
[+] Building 4.3s (18/18) FINISHED                                                                                                                                      docker:default
 => [worker internal] load build definition from Dockerfile                                                                                                                       0.1s
 => => transferring dockerfile: 298B                                                                                                                                              0.0s
 => [worker internal] load .dockerignore                                                                                                                                          0.1s
 => => transferring context: 2B                                                                                                                                                   0.0s
 => [worker-2 internal] load .dockerignore                                                                                                                                        0.1s
 => => transferring context: 2B                                                                                                                                                   0.0s
 => [worker-2 internal] load build definition from Dockerfile                                                                                                                     0.1s
 => => transferring dockerfile: 304B                                                                                                                                              0.0s
 => [worker-2 internal] load metadata for docker.io/library/ubuntu:18.04                                                                                                          0.5s
 => CACHED [worker-2 build 1/5] FROM docker.io/library/ubuntu:18.04@sha256:152dc042452c496007f07ca9127571cb9c29697f42acbfad72324b2bb2e43c98                                       0.0s
 => [worker-2 internal] load build context                                                                                                                                        0.1s
 => => transferring context: 561B                                                                                                                                                 0.0s
 => [worker internal] load build context                                                                                                                                          0.1s
 => => transferring context: 446B                                                                                                                                                 0.0s
 => CACHED [worker-2 build 2/5] RUN apt-get update && apt-get install -y     g++     cmake     && rm -rf /var /lib/apt/lists/*                                                    0.0s
 => CACHED [worker-2 build 3/5] WORKDIR /app                                                                                                                                      0.0s
 => [worker-2 build 4/5] COPY . /app                                                                                                                                              0.2s
 => [worker build 4/5] COPY . /app                                                                                                                                                0.2s
 => [worker-2 build 5/5] RUN cmake . && make                                                                                                                                      2.6s
 => [worker build 5/5] RUN cmake . && make                                                                                                                                        2.6s
 => [worker-2 stage-1 2/2] COPY --from=build /app/worker-2 /app/worker-2                                                                                                          0.1s
 => [worker stage-1 2/2] COPY --from=build /app/worker /app/worker                                                                                                                0.1s
 => [worker-2] exporting to image                                                                                                                                                 0.2s
 => => exporting layers                                                                                                                                                           0.1s
 => => writing image sha256:e370e2dbc37925b90176ff8e3dccab98c7fc706fadf640747296a655a7c046d0                                                                                      0.0s
 => => naming to docker.io/library/service-worker-worker-2                                                                                                                        0.0s
 => [worker] exporting to image                                                                                                                                                   0.2s
 => => exporting layers                                                                                                                                                           0.2s
 => => writing image sha256:1eb5ebc2216088196d2fafdc96fa01c5cab482826729059e140c8c95cb4455ce                                                                                      0.0s
 => => naming to docker.io/library/service-worker-worker                                                                                                                          0.0s
[+] Running 3/3
 ✔ Volume "service-worker_shared_data"  Created                                                                                                                                   0.0s 
 ✔ Container worker                     Recreated                                                                                                                                 0.4s 
 ✔ Container worker-2                   Recreated                                                                                                                                 0.4s 
Attaching to worker, worker-2
worker-2  | Received: Data from worker 1
worker-2 exited with code 0
worker exited with code 0
```