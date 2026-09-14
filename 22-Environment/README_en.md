# 02. Development Environment and the Basics of Distributed Processing


## What it covers

- **Reproducibility**: pinning the seed and pinning versions (`requirements.txt`). 
Reproducibility = the tripod of code + data + environment.
- **The shell and Unix pipes** (`cut | sort | uniq -c`) and **GIT** (commits, branches,
  hashes) understood as the archetypes of data processing and experiment reproduction.
- **Why distributed**: a volume estimate showing that the multivariate city twin crosses
  both the RAM wall and the time wall.
- **HDFS**: block splitting + replication. Verified by simulation that R
  replicas mean **zero loss** up to R−1 simultaneous node failures.
- **MapReduce**: mean temperature per station aggregated in a distributed way with
  map→shuffle→reduce, confirmed identical to the serial answer (<1e-12) regardless of the
  partition count. Reduce carries the (sum, count) partial aggregate.

## Key message

Distributed processing is not magic. It is the structure of **splitting the storage
(HDFS blocks and replication) and splitting the computation (MapReduce)**. 
Spark automates on a real cluster, through `DataFrame` and `SQL`.

