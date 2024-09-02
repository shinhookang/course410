# Apache Hadoop

 
## Install 

1. Download the release hadoop-3.4.0.targz from https://hadoop.apache.org 

```bash
curl https://dlcdn.apache.org/hadoop/common/hadoop-3.4.0/hadoop-3.4.0.tar.gz --output hadoop-3.4.0.tar.gz
```

2. Unpack the downloaded Hadoop distribution
```bash
tar -xvf hadoop-3.4.0.tar.gz 
```
 
 
3. Check the hadoop version
```bash
cd hadoop-3.4.0
bin/Hadoop version
```

If the output is simlar to the following, the installation was successful.
```
Hadoop 3.4.0
Source code repository git@github.com:apache/hadoop.git -r bd8b77f398f626bb7791783192ee7a5dfaeec760
Compiled by root on 2024-03-04T06:35Z
Compiled on platform linux-x86_64
Compiled with protoc 3.21.12
From source with checksum f7fe694a3613358b38812ae9c31114e
This command was run using /Users/pepc/Teaching/410-BigdataDistributedProcessingSystem/code/course410-2024/01-ApacheHadoop/hadoop-3.4.0/share/hadoop/common/hadoop-common-3.4.0.jar
```

4. Modify the PATH environment variable.
Open `~/.zshrc` or `~/.bashrc` and add the following.
```bash
export HADOOP_HOME=/Users/pepc/Teaching/410-BigdataDistributedProcessingSystem/code/course410-2024/01-ApacheHadoop/hadoop-3.4.0
export PATH=$PATH:$HADOOP_HOME/bin
```

5. Try the following
```bash
source ~/.zshrc
ls $HADOOP_HOME -d 
```

For Linux users, use `ls $HADOOP_HOME -l | grep '^d'` instead

You will see the following subdirectories of the Hadoop distribution. 

       bin/       include/       libexec/               sbin/
       etc/       lib/           licenses-binary/       share/



## Run Hadoop

Hadoop cluster supports three modes:
* Local (standalone) mode
* Pseudo-Distributed mode 
* Fully-Distributed mode

### Standalone mode 

By default, Hadoop is configured to run in local mode.
Let's try a mapreduce example.

1. Create `data.txt` under `ex1` directory with the following content.

    ```
    Hadoop is great
    Hadoop is open-source
    MapReduce is a programming model
    Hadoop uses MapReduce
    Big data is processed by Hadoop
    ```

2. Run hadoop example.

    ```bash
    hadoop jar $HADOOP_HOME/share/hadoop/mapreduce/hadoop-mapreduce-examples-3.4.0.jar wordcount data.txt output
    ```

3. Check the output in `output` directory.

    ```
    Big     1
    Hadoop  4
    MapReduce       2
    a       1
    by      1
    data    1
    great   1
    is      4
    model   1
    open-source     1
    processed       1
    programming     1
    uses    1
    ``` 


### Pseudo-Distributed mode 

1. Modify the following files: 

    `etc/hadoop/core-site.xml`
    ```xml
    <configuration>
        <property>
            <name>fs.defaultFS</name>
            <value>hdfs://localhost:9000</value>
        </property>
    </configuration>
    ```

    `etc/hadoop/hdfs-site.xml`
    ```xml
    <configuration>
        <property>
            <name>dfs.replication</name>
            <value>1</value>
        </property>
    </configuration>
    ```
    <br>

    For Linux users, set `JAVA_HOME` variable in `$HADOOP_HOME/etc/hadoop/hadoop-env.sh`.
    e.g., 
    ```bash
    export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64
    ```

1. Setup passphraseless ssh
   
    Check if this work, `ssh localhost`
    If not, then execute the following commands.
    ```bash
    ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa
    cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
    chmod 0600 ~/.ssh/authorized_keys
    ```

    For Mac users, turn on `Remote Login` in `System Preferences-> Sharing`.
    <br>
    For Linux users, start `ssh` service.
    ```
    sudo apt remove openssh-server
    sudo apt install openssh-server
    sudo service ssh start
    sudo service ssh status
    ```

2. Format the file system `hdfs namenode`
<br>
1. Start NameNode deamon and DataNode deamon `$HADOOP_HOME/sbin/start-dfs.sh`
<br>
1. Check the Web interfaces http://localhost:9870 for NameNode and http://localhost:9864 for DataNode.
<br>

1. Make the HDFS directories required to execute MapReduce jobs
    ``` bash 
    hdfs dfs -mkdir -p /user/pepc
    ```
    where `pepc` is a username; and `hdfs dfs` is the File System (FS) shell when HDFS is being used. Type `hdfs dfs -help` if you want to see more about the shell command. 
    <br>

2. Create three textfiles under `ex2` directory:
   ```bash
   mkdir ex2
   ```

    `data1.txt`
    ```
    Hadoop is great
    Hadoop is open-source
    ```
    `data2.txt`
    ```
    MapReduce is a programming model
    Hadoop uses MapReduce
    ```
    `data3.txt`
    ```
    Big data is processed by Hadoop
    ```

3. Copy the input files into the distributed filesystem
    ```bash 
    cd ex2
    hdfs dfs -mkdir input
    hdfs dfs -put *.txt input
    ```
    Make sure the copy was successful.
    ```bash
    hdfs dfs -ls input
    ```

4. Run the wordcount example
    ```bash
    hadoop jar $HADOOP_HOME/share/hadoop/mapreduce/hadoop-mapreduce-examples-3.4.0.jar wordcount input output
    ```

5.  View the output file on the distributed system
    ```bash
    hdfs dfs -cat output/part-r-00000
    ```

    ```
    Big	1
    Hadoop	4
    MapReduce	2
    a	1
    by	1
    data	1
    great	1
    is	4
    model	1
    open-source	1
    processed	1
    programming	1
    uses	1
    ```

    You can copy the output files from the distributed filesystem to the local filesystem and examine them.
    ```bash
    hdfs dfs -get output output
    ```

6.  Delete the output files on the distributed system
    ```bash
    hdfs dfs -rm -r output
    ```

7.  Stop the deamon
    ```bash
    $HADOOP_HOME/sbin/stop-dfs.sh
    ```
    
    For Linux users, stop `ssh` service.
    ```bash 
    sudo service ssh stop
    ```

## Reference 

[Setting up a Single Node Cluster](https://hadoop.apache.org/docs/stable/hadoop-project-dist/hadoop-common/SingleCluster.html#Standalone_Operation)
